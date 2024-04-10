//
// Created by zsotroav on 2024-04-09.
//
#include <fcntl.h>      // for _setmode
#include <iostream>
#include "econio.h"
#include "menu.h"
#include "common.h"
#include "server.h"

#include "game.h"

using namespace plushies;
using std::wcout, std::endl;


void gameInit() {
    // Set the output mode to support Unicode
    // GH/GiovanniDicanio/PrintUnicodeTextToConsoleWin/PrintUnicodeToConsoleWin/PrintUnicodeToConsoleWin.cpp#L23
    int result = _setmode(_fileno(stdout), _O_U16TEXT);
    if (result == -1) {
        wcout << L"*** ERROR: _setmode failed - Can't set stdout to Unicode UTF-16.\n\n";
        return;
    }

    // Econio raw mode to have keyboard input directly
    econio_rawmode();

    econio_textcolor(COL_RED);
    wcout << "* ATTENTION: Please make sure your terminal screen buffer size is"
             " at least 120 characters x 30 lines then press any key." << endl;

    econio_gotoxy(55, 29);
    wcout << "You are good if you can read both of these lines at the same time";

    econio_textcolor(COL_WHITE);
    econio_gotoxy(46, 14);
    wcout << "Plush Monsters' Fight Club" << endl;

    while (!econio_kbhit()) econio_sleep(0.2);

    econio_clrscr();


    GameMode gm;
    int cnt, opp;
    menu(gm, cnt, opp);

    plushies::Server s;

}