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
    ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

    // auto menu = Container::Vertical({
    //     MenuEntry("Ver documento"),
    //     MenuEntry("Analizar documento"),
    //     MenuEntry("Salir"),
    // });

    const std::vector<std::string> entries = {
        "Ver documento",
        "Analizar documento",
        "Salir",
    };
    MenuOption option;
    Closure screen_exit = screen.ExitLoopClosure();
    option.on_enter = [this, screen_exit]() {
        switch (optionSelected) {
            case 0:
                break;
            case 1:
                break;
            default:
                screen_exit();
                break;
        }
    };
    Component menu = Menu(&entries, &optionSelected, option);
    Component actualMenu = Container::Horizontal({menu | border});
    // auto render = Renderer(actualMenu, [&] {
    //     return vbox({
    //
    //     });
    // });

    screen.Loop(actualMenu);
}
