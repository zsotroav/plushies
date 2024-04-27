//
// Created by zsotroav on 2024-04-09.
//

// ReSharper disable CppPossiblyErroneousEmptyStatements

#include <iostream>
#include "common.h"
#include "econio.h"

#include "menu.h"

using namespace plushies;
using std::wcout, std::endl, std::flush;

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

    wcout << "Game mode: Random/Custom/Detailed " << flush;

    while (!econio_kbhit()) econio_sleep(0.2);
    econio_gotoxy(11, 21);

    switch (econio_getch()) {
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
    wcout << "Number of plushes: 1-3 " << flush;

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

EnemyMode opponentSelect(const bool detail) {
    econio_gotoxy(0, 25);
    wcout << "Play against local AI or LAN play? " << flush;


    while (!econio_kbhit()) econio_sleep(0.2);
    int c = econio_getch();

    if (c == 'l' || c == 'L') {
        wcout << endl << "Are you Hosting the game, or joining as Client?" << flush;
        while (true) {
            while (!econio_kbhit()) econio_sleep(0.2);
            c = econio_getch();
            if (c == 'h' || c == 'H' || c == 's' || c == 'S') return LAN_SERVER;
            if (c == 'c' || c == 'C') return  LAN_CLIENT;
        }
    }// LAN

    if (c != 'a' && c != 'A') return INVALIDENEMY; // INV

    if (!detail) return OVERLORD_GENERIC; // Random AI
    
    econio_gotoxy(35, 25);
    wcout << "Overlord" << endl << endl <<
             "Which Overlord do you want to play against? "
             "(Dennis/Clyde/Ninty/Waffles/Muffins)" << flush;

    while(true) {
        while (!econio_kbhit()) econio_sleep(0.2);
        c = econio_getch();
        switch (c) {
            case 'd': case 'D': return OVERLORD_DENNIS;
            case 'c': case 'C': return OVERLORD_CLYDE;
            case 'n': case 'N': return OVERLORD_NINTY;
            case 'w': case 'W': return OVERLORD_WAFFLES;
            case 'm': case 'M': return OVERLORD_MUFFINS;
            default: break; // Invalid choice, try again
        }
    }
}

void menu(GameMode& gm, int& cnt, EnemyMode& opp) {
    writeMainHeader();
    
    // Get game mode - wait until selection is valid
    while((gm = modeSelect()) == -1) ;

    while((cnt = plushCountSelect()) == -1) ;

    while((opp = opponentSelect(gm == DETAIL)) == -1) ;

    econio_clrscr();
}