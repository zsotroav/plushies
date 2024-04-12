//
// Created by zsotroav on 2024-04-09.
//

#include <iostream>
#include "econio.h"
#include "common.h"

#include "menu.h"

using namespace plushies;
using std::wcout, std::endl;

#define cout wcout

void writeMainHeader() {
    static auto logo =  L"                        ▄███████▄  ▄█       ███    █▄     ▄████████    ▄█    █▄   \n"
                        "                       ███    ███ ███       ███    ███   ███    ███   ███    ███  \n"
                        "                       ███    ███ ███       ███    ███   ███    █▀    ███    ███  \n"
                        "                       ███    ███ ███       ███    ███   ███         ▄███▄▄▄▄███▄▄\n"
                        "                     ▀█████████▀  ███       ███    ███ ▀███████████ ▀▀███▀▀▀▀███▀ \n"
                        "                       ███        ███       ███    ███          ███   ███    ███  \n"
                        "                       ███        ███▌    ▄ ███    ███    ▄█    ███   ███    ███  \n"
                        "                      ▄████▀      █████▄▄██ ████████▀   ▄████████▀    ███    █▀   \n"
                        "                                  ▀                                               \n"
                        "   ▄▄▄▄███▄▄▄▄    ▄██████▄  ███▄▄▄▄      ▄████████     ███        ▄████████    ▄████████    ▄████████ \n"
                        " ▄██▀▀▀███▀▀▀██▄ ███    ███ ███▀▀▀██▄   ███    ███ ▀█████████▄   ███    ███   ███    ███   ███    ███ \n"
                        " ███   ███   ███ ███    ███ ███   ███   ███    █▀     ▀███▀▀██   ███    █▀    ███    ███   ███    █▀  \n"
                        " ███   ███   ███ ███    ███ ███   ███   ███            ███   ▀  ▄███▄▄▄      ▄███▄▄▄▄██▀   ███        \n"
                        " ███   ███   ███ ███    ███ ███   ███ ▀███████████     ███     ▀▀███▀▀▀     ▀▀███▀▀▀▀▀   ▀███████████ \n"
                        " ███   ███   ███ ███    ███ ███   ███          ███     ███       ███    █▄  ▀███████████          ███ \n"
                        " ███   ███   ███ ███    ███ ███   ███    ▄█    ███     ███       ███    ███   ███    ███    ▄█    ███ \n"
                        "  ▀█   ███   █▀   ▀██████▀   ▀█   █▀   ▄████████▀     ▄████▀     ██████████   ███    ███  ▄████████▀  ";

    wcout << logo << endl<< endl<< endl;
    wcout << "Welcome to Plush Monsters' Fight Club! How will you fight today?"
          << endl << endl;
}

GameMode modeSelect() {
    econio_gotoxy(0, 21);

    wcout << "Game mode: Random/Custom/Detailed " << std::flush;


    while (!econio_kbhit()) econio_sleep(0.2);
    int c = econio_getch();
    econio_gotoxy(11, 21);

    switch (c) {
        case 'r': case 'R':
            wcout << "Random                    " << endl;
            return RANDOM;

        case 'c': case 'C':
            wcout << "Custom                    " << endl;
            return CUSTOM;

        case 'd': case 'D':
            wcout << "Detailed custom           "<< endl;
            return DETAIL;
            
        default:
            econio_gotoxy(35, 21);
            wcout << "??" << endl;
            return INVALID;
    }
}

int plushCountSelect() {
    econio_gotoxy(0, 23);
    wcout << "Number of plushes: 1-3 " << std::flush;

    while (!econio_kbhit()) econio_sleep(0.2);
    int c = econio_getch();

    econio_gotoxy(19, 23);


    if (c >= 49 && c <= 51) {
        c -= 48;
        wcout << c << "      " << endl;
        return c;
    }
    econio_gotoxy(24, 23);
    wcout << "??" << endl;
    return -1;
}

int opponentSelect(bool detail) {
    econio_gotoxy(0, 25);
    wcout << "Play against local AI or LAN play? " << std::flush;


    while (!econio_kbhit()) econio_sleep(0.2);
    int c = econio_getch();

    if (c == 'l' || c == 'L') return 0;  // LAN

    if (c != 'a' && c != 'A') return -1; // INV

    if (!detail) return -2; // Random AI
    
    econio_gotoxy(35, 25);
    wcout << "Overlord" << endl << endl <<
             "Which Overlord do you want to play against? "
             "(Dennis/Clyde/Ninty/Waffles/Muffins)" << std::flush;

    while(true) {
        while (!econio_kbhit()) econio_sleep(0.2);
        c = econio_getch();
        switch (c) {
            case 'd': case 'D': return 1; // Dennis
            case 'c': case 'C': return 2; // Clyde
            case 'n': case 'N': return 3; // Ninty
            case 'w': case 'W': return 4; // Waffles
            case 'm': case 'M': return 5; // Muffins
            default: break; // Invalid choice, try again
        }
    }
}

void menu(GameMode& gm, int& cnt, int& opp) {
    writeMainHeader();
    
    // Get game mode - wait until selection is valid
    while((gm = modeSelect()) == -1) ;

    while((cnt = plushCountSelect()) == -1) ;

    while((opp = opponentSelect(gm == DETAIL)) == -1) ;

    econio_clrscr();
}