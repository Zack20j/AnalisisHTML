#include "graphics/terminalUI.hpp"
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/component/component.hpp"       // for Menu, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"  // for ComponentBase

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
    option.on_enter = [this, screen_exit]() {
        switch (optionSelected) {
            case 0:
                // Mostrar el documento
                this->showMenu = false;
                this->showAnalisis = !this->showMenu;
                break;
            case 1:
                // Analizar el documento
                this->showMenu = true;
                this->showAnalisis = !this->showMenu;
                break;
            default:
                screen_exit();
                break;
        }
    };
    Component menu = Container::Horizontal({
        Maybe(Menu(&entries, &optionSelected, option) | border,
              &showMenu),  // Menu principal
        Maybe(Input(), &showAnalisis),
    });
    Component render = Renderer(menu, [&] {
        Element result = hbox({
            emptyElement() | flex,
            vbox({
                emptyElement() | flex,
                menu->Render(),
                emptyElement() | flex,
            }),
            emptyElement() | flex,
        });
        if (false) {  // Mostrar Documento
            result = paragraphAlignLeft("Hola") | border | flex;
        }
        return result;
    });

    screen.Loop(render);
}
