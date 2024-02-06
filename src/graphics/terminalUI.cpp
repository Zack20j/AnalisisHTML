#include "graphics/terminalUI.hpp"
#include <algorithm>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <sstream>
#include <string>
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

    const std::vector<std::string> entries = {
        "Ver documento ",
        "Analizar documento ",
        "Salir ",
    };
    MenuOption option;
    Closure screen_exit = screen.ExitLoopClosure();
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
    Component renderer = Renderer(menu, [&] {
        return hbox({
            separatorEmpty() | flex,
            vbox({
                separatorEmpty() | flex,
                menu->Render() | borderRounded,
                separatorEmpty() | flex,
            }) | flex,
            separatorEmpty() | flex,
        });
    });

    renderer |= CatchEvent([&](Event event) {
        if (event == Event::Character('q')) {
            screen.ExitLoopClosure()();
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
    // elements.insert(elements.begin(),
    //                 paragraph("") | focusCursorUnderlineBlinking);

    Closure screenExit = screen.ExitLoopClosure();
    Component backButton = Button("Volver", [&] { screenExit(); });
    Component renderer = Renderer(backButton, [&] {
        return vbox({
                   vflow(elements) | focusPosition(0, docScrollPos) |
                       vscroll_indicator | yframe | borderRounded | yflex,
                   hbox({
                       text("q") | bold,
                       text(" para volver, "),
                       text("k/Flecha arriba o j/Flecha abajo") | bold,
                       text(" para desplazarse"),
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
