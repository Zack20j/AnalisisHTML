#include "graphics/terminalUI.hpp"
#include <algorithm>
#include <cstdlib>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <sstream>
#include "ftxui/component/component.hpp"       // for Menu, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/dom/elements.hpp"
#include "storage/archive.hpp"

TermMenu::TermMenu() {
}

TermMenu::~TermMenu() {
}

void TermMenu::start() {
    using namespace ftxui;
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    Closure screen_exit = screen.ExitLoopClosure();

    // Menu para introducir el nombre del archivo
    std::string nombreArchivoHTML = "../index.html";
    InputOption opts;
    opts.on_enter = [&]() {
        if (filePath.empty()) {  // || !FileManager::exists(filePath)
            filePath = nombreArchivoHTML;
        }
        screen_exit();
    };
    Component input = Input(&filePath, nombreArchivoHTML, opts);

    Component renderer = Renderer(input, [&] {
        return hbox({
            separatorEmpty() | flex,
            vbox({
                separatorEmpty() | flex,
                window(text("Introduzca la direccion al archivo:"),
                       input->Render()) | color(Color::CyanLight),
                separatorEmpty() | flex,
            }) | flex,
            separatorEmpty() | flex,
        });
    });

    renderer |= CatchEvent([&](Event event) {
        if (event == Event::Character('q')) {
            screen_exit();
            exit(0);
            return true;
        }
        return false;
    });

    screen.Loop(renderer);

    // Menu principal
    const std::vector<std::string> entries = {
        "Visualizar documento ",
        "Analizar documento ",
        "Salir ",
    };
    MenuOption option;
    option.on_enter = [&]() {
        switch (optionSelected) {
            case 0:
                // Mostrar el documento
                showDocument();
                break;
            case 1:
                // Analizar el documento
                break;
            default:
                screen_exit();
                break;
        }
    };
    Component menu = Menu(&entries, &optionSelected, option);
    renderer = Renderer(menu, [&] {
        return hbox({
            separatorEmpty() | flex,
            vbox({
                separatorEmpty() | flex,
                menu->Render() | borderRounded | color(Color::CyanLight),
                separatorEmpty() | flex,
            }) | flex,
            separatorEmpty() | flex,
        });
    });

    renderer |= CatchEvent([&](Event event) {
        if (event == Event::Character('q')) {
            screen_exit();
            return true;
        }
        return false;
    });

    screen.Loop(renderer);
}

void TermMenu::showDocument() {
    using namespace ftxui;
    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    // Parte de datos o logica
    // Obtener el html crudo
    std::string nombreArchivoHTML = "../index.html";
    FileManager archivo = FileManager(nombreArchivoHTML);
    std::string textoHTML = archivo.readFile(), str;
    // Convertir el html crudo a elementos ftxui
    std::stringstream streamHTML(textoHTML);
    Elements elements = {};
    while (std::getline(streamHTML, str, '\n')) {
        elements.push_back(paragraph(str));
    }
    str.clear();

    Closure screenExit = screen.ExitLoopClosure();
    Component backButton = Button("Volver", [&] { screenExit(); });
    Component renderer = Renderer(backButton, [&] {
        return vbox({
                   vflow(elements) | focusPosition(0, docScrollPos) |
                       vscroll_indicator | yframe | borderRounded | yflex,
                   hbox({
                       text("q") | bold | color(Color::CyanLight),
                       text(" para volver, ") | color(Color::CyanLight),
                       text("k/Flecha arriba o j/Flecha abajo") | bold | color(Color::CyanLight),
                       text(" para desplazarse") | color(Color::CyanLight),
                   }) | hcenter |
                       borderEmpty | size(HEIGHT, EQUAL, 3),
               }) |
               borderEmpty;
    });

    renderer |= CatchEvent([&](Event event) {
        if (event == Event::Character('q')) {
            screenExit();
            return true;
        }

        int docScrollPosOld = docScrollPos;
        if (event == Event::ArrowUp || event == Event::Character('k') ||
            (event.is_mouse() && event.mouse().button == Mouse::WheelUp)) {
            docScrollPos -= 5;
        }
        if ((event == Event::ArrowDown || event == Event::Character('j') ||
             (event.is_mouse() && event.mouse().button == Mouse::WheelDown))) {
            docScrollPos += 5;
        }
        if (event == Event::Home)
            docScrollPos = 0;
        if (event == Event::End)
            docScrollPos = elements.size() - 1;

        docScrollPos = std::clamp(docScrollPos, 0, (int)elements.size() - 1);
        return docScrollPosOld != docScrollPos;
    });

    screen.Loop(renderer);
}
