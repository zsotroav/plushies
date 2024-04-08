//
// Created by zsotroav on 2024-04-08.
//

// This
#include "menu.h"
// Global
#include <iostream>
#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for string, basic_string
#include <vector>  // for vector
// Library
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Toggle, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, vbox, Element
#include "memtrace/memtrace.h"
// Header
#include "plush.h"
#include "server.h"

//using namespace plushies;
using namespace ftxui;

using std::vector, std::string;

void menu() {
    vector<string> tge_mode = { "Random", "Custom", "Detailed" };
    vector<string> tge_pcnt = { "1", "2", "3" };
    vector<string> tge_com2 = { "Overlord", "LAN Play" };

    int tgs_mode = 0, tgs_pcnt = 0, tgs_com2 = 0;

    Component tgc_mode = Toggle(&tge_mode, &tgs_mode);
    Component tgc_pcnt = Toggle(&tge_pcnt, &tgs_pcnt);
    Component tgc_com2 = Toggle(&tge_com2, &tgs_com2);

    auto screen = ScreenInteractive::TerminalOutput();


    // Function to start the game with the button
    auto start = [&] {
        switch (tgs_mode) {
            case 0: break;
            case 1: menuPlushConfig(); break;
            case 2: menuPlushConfig(true);
            default: break;
        }

        screen.Clear();

        screen.Exit();
        std::cout << "HI" << std::endl;

    };

    Component button = Button("Start game", start, ButtonOption::Simple());

    auto container = Container::Vertical({ tgc_mode,
                                           tgc_pcnt,
                                           tgc_com2,
                                           button
                                         });

    auto renderer = Renderer(container, [&] {
        return vbox({
                      text("Welcome to Plush Monsters' Fight Club!"),
                      text("How do you want to fight today?"),
                      text(""),
                      hbox(text("Game mode   : "), tgc_mode->Render()),
                      hbox(text("Plush count : "), tgc_pcnt->Render()),
                      hbox(text("Opponent    : "), tgc_com2->Render()),
                      text(""),
                      hbox(button->Render(), filler()),
                    });
    });

    screen.Loop(renderer);
}

void menuPlushConfig(bool detailed) {

}