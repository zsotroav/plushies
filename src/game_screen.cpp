//
// Created by zsotroav on 2024-04-14.
//

#include <iostream>
#include <iomanip>

#include "brand.h"
#include "econio.h"
#include "plush.h"
#include "server.h"

#include "game_screen.h"

using namespace plushies;
using std::wcout, std::flush, std::endl;

void printScreen() {
    wcout << L"                                                                                                X::$         x+     \n"
             "     ___  _    _   _  ___  _  _  ___  ___  ___               ╔══════════════════════╕          x;;:::::::;x;::;x    \n"
             "    | _ \\| |  | | | |/ __|| || ||_ _|| __|/ __|              ║                      ││        X;::;::::::::;;++$    \n"
             "    |  _/| |__| |_| |\\__ \\| __ | | | | _| \\__ \\              ║                      ││      X::;:::::::+$;;$;;+X    \n"
             "    |_|  |____|\\___/ |___/|_||_||___||___||___/              ║[████████████████████]││     X::;;:.:::::::::::;++X   \n"
             "                                                             ╙──────────────────────┘│     &++++++$;::::::.   ++x   \n"
             "                                                                ─────────────────────┘      x++++++++X$$X++. :+++&  \n"
             "                                                                                         X::;xx++++++++++++++++++$  \n"
             "                                                                                         ;::;++x+x+++++x::::;;+++X  \n"
             "                                                                                         x++++x;      :x;::;+++++X  \n"
             "                                                                                            &X          ;xxx++x++X  \n"
             "                                                                                           XX            :+++++++X  \n"
             "                                                                                       X;;::;            .+:::;x+$  \n"
             "          xx      xx                                                                  X++++++           :;+;++::+&  \n"
             "        x;::;xXXX;::x                                                                 X++++++;          +++++++++$  \n"
             "        +...:;........;xX                                                              $xx++++x:.       +x+++++xX   \n"
             "       X;..:;...........+xX                                                                        &&&   $x++xx$    \n"
             "       +...+..........xx:.;x                                                                                        \n"
             "      X..:;+.........x...:+x                                                                                        \n"
             "      +.;:.+:............:+x                                                             ╔═══════════════════════╗  \n"
             "     X:.:::+.............:+                                                              ║   What will you do?   ║  \n"
             "     x:..;;.............;;;+X                                                            ╟───────────────────────╢  \n"
             "     +:::.;............;:...:X                                                           ║                       ║  \n"
             "    x;.+..;.............+:.:+                                                            ║                       ║  \n"
             "    x:.:;;:.............:;x          ┌────────────────────                               ║                       ║  \n"
             "    x.:+;:;;...........+....;+x      │┌──────────────────────╖                           ║                       ║  \n"
             "   Xx;......::........;:.......;     ││                      ║                           ╟───────────────────────╢  \n"
             "x:...........;........;:.......:     ││           000/000 HP ║                           ║ TYP/FIGHTING   00/00  ║  \n"
             "X;...........;.......:;........x     ││[████████████████████]║                           ║ 000 PWR   ◎   ACC 100 ║  \n"
             " XXx;:::::;;;.....::::+x+;;++xX       ╘══════════════════════╝                           ╚═══════════════════════╝  ";
}

void updatePlush(const plushies::Plush& p, bool foe) {
    econio_gotoxy(foe ? 63 : 40, foe ? 2 : 26);
    wcout << p.getBrand().getName();

    for (int i = 0; i < 20 - p.getBrand().getName().length(); ++i)  wcout << " ";

    econio_gotoxy(foe ? 63 : 40, foe ? 4 : 28);
    int n = ((double)p.getHP() / p.getMaxHP()) * 20;

    for (int i = 0; i < n; ++i) wcout << L"█";
    for (int i = 0; i < 20 - n; ++i) wcout << " ";

    if (foe) return;

    econio_gotoxy(50, 27);

    std::stringstream ss;
    ss << std::setfill(' ') << std::setw(3) << p.getHP();

    wcout << ss.str() << "/" << p.getMaxHP() << " HP" << flush;
}


void updateActionInfo(const Action* a) {
    econio_gotoxy(95, 27);
    wcout << a->getType() << "     ";

    // TODO: Energy

    econio_gotoxy(91, 28);
    wcout << a->getDamage() << " ";

    econio_gotoxy(101, 28);
    wcout << (a->getCategory() == ActionCategory::Physical ? L"★" : L"◎")
    << "   ACC " << a->getAccuracy() << (a->getAccuracy() < 100 ? "%" : "")

    << flush;
}

void updateSelection(const std::string& item, const int id, const bool highlight) {
    econio_gotoxy(91, 22 + id);
    if (highlight) {
        econio_textbackground(COL_WHITE);
        econio_textcolor(COL_BLACK);
    }

    wcout << item;

    for (int i = 0; i < 21 - item.length(); ++i) wcout << " ";

    if (highlight) {
        econio_textbackground(COL_BLACK);
        econio_textcolor(COL_WHITE);
    }

    wcout << flush;
}

void printList(std::vector<std::string>& list) {
    updateSelection(list[0], 0, true);
    for (int i = 1; i < list.size(); ++i) updateSelection(list[i], i);
}

// TODO: Template?

int chooseAction(const Plush& p) {
    updateSelection(p.Actions[0]->getName(), 0, true);
    updateActionInfo(p.Actions[0]);
    int i = 1;
    for (; i < 4; ++i) {
        if (p.Actions[i] == nullptr || p.Actions[i]->getType() == NONE) break;
        updateSelection(p.Actions[i]->getName(), i);
    }

    int curr = 0, prev = 0;

    while (true) {
        while (!econio_kbhit()) econio_sleep(0.2);

        switch (econio_getch()) {
            case 'w': case KEY_UP:
                if (curr == 0) continue;
                prev = curr; --curr; break;
            case 's': case KEY_DOWN:
                if (curr == i - 1) continue;
                prev = curr; ++curr; break;
            case ' ': case KEY_ENTER:
                std::vector<std::string> v = {"", "", "", ""};
                printList(v);
                return curr;
        }

        updateSelection(p.Actions[curr]->getName(), curr, true);
        updateSelection(p.Actions[prev]->getName(), prev, false);

        updateActionInfo(p.Actions[curr]);
    }

}

int choosePlush(const Player& p) {
    auto pl = p.getPlushes();
    updateSelection(pl[0].getName(), 0, true);
    int i = 1;
    for (; i < pl.size(); ++i) {
        updateSelection(pl[i].getName(), i);
    }

    int curr = 0, prev = 0;

    while (true) {
        while (!econio_kbhit()) econio_sleep(0.2);

        switch (econio_getch()) {
            case 'w': case KEY_UP:
                if (curr == 0) continue;
                prev = curr; --curr; break;
            case 's': case KEY_DOWN:
                if (curr == i - 1) continue;
                prev = curr; ++curr; break;
            case ' ': case KEY_ENTER:
                std::vector<std::string> v = {"", "", "", ""};
                printList(v);
                return curr;
        }

        updateSelection(pl[curr].getName(), curr, true);
        updateSelection(pl[prev].getName(), prev, false);
    }
}

int chooseMove(const plushies::Player& player) {
    std::vector<string> options = { "Attack", "Swap plushies", "Forfeit", ""};
    printList(options);
    int curr = 0, prev = 0;
    bool selecting = true;

    while (selecting) {
        while (!econio_kbhit()) econio_sleep(0.2);

        switch (econio_getch()) {
            case 'w': case KEY_UP:
                if (curr == 0) continue;
                prev = curr; --curr; break;
            case 's': case KEY_DOWN:
                if (curr == 2) continue;
                prev = curr; ++curr; break;
            case ' ': case KEY_ENTER: selecting = false;
        }

        updateSelection(options[curr], curr, true);
        updateSelection(options[prev], prev, false);
    }
    switch (curr) {
        case 0: return chooseAction(player.getActivePlush()) + 1;
        case 1: return -1 * (choosePlush(player) + 1);
        default: return 0;
    }
}