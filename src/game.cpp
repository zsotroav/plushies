//
// Created by zsotroav on 2024-04-09.
//
#include <fcntl.h>      // for _setmode
#include <iostream>
#include "econio.h"
#include "menu.h"
#include "menu_plush_create.h"
#include "common.h"
#include "server.h"
#include "overlord.h"

#include "game.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif // Windows

using namespace plushies;
using std::wcout, std::endl, std::flush;

bool setUnicodeMode() {
    // GH/GiovanniDicanio/PrintUnicodeTextToConsoleWin/PrintUnicodeToConsoleWin/PrintUnicodeToConsoleWin.cpp#L23
    int result = _setmode(_fileno(stdout), _O_U16TEXT);
    if (result == -1) {
        wcout << L"*** ERROR: _setmode failed - "
                 "Can't set stdout to Unicode UTF-16.\n\n";
        return false;
    }
    return true;
}

void warningScreen() {
#if defined(_WIN32) || defined(_WIN64)
    // Check Terminal size on windows
    // https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    std::cout << columns << rows;
    if (columns >= 120 && rows >= 30) return;
#endif // Windows

        // On non-windows platforms we always write it because checking size
        // is much more difficult and would require a lot more

        // This top row is exactly 120 chars
        econio_textcolor(COL_RED);
        wcout << L"╔════ Please make sure your terminal size is at least 120x30 and "
                 "can see the whole box. Press any key to continue. ════╗" << endl;

        econio_textcolor(COL_LIGHTGRAY);
        for (int i = 0; i < 28; ++i) {
            wcout << L"║";
            for (int j = 0; j < 118; ++j) wcout << " ";
            wcout << L"║" << endl;
        }

        wcout << L"╚";
        for (int j = 0; j < 118; ++j) wcout << L"═";
        wcout << L"╝" << flush;

        // Welcome splash screen (end exactly at col 80)
        econio_textcolor(COL_WHITE);
        econio_gotoxy(46, 14);
        wcout << "Plush Monsters' Fight Club" << endl;

        // Wait for a keyboard input to dismiss the warning screen
        while (!econio_kbhit()) econio_sleep(0.2);

        // Clear screen so we are starting from the top left with the menu as well
        econio_clrscr();
}

void gameInit() {
    if(!setUnicodeMode()) return; // Set the output mode to support Unicode
    econio_rawmode(); // Direct keyboard input
    econio_clrscr();  // Start with empty screen
    warningScreen();  // Screen size check and warning

    GameMode gm;
    int cnt, opp;
    menu(gm, cnt, opp); // Get game config

    Server s;

    if (opp == 0) {
        // TODO: LAN PLAY
    } else {
        // Register overlords
        switch ( opp > 0 ? opp : random(1, 5)) {
            case 1:  s.RegisterPlayer(new overlord::Dennis (s, cnt)); break;
            case 2:  s.RegisterPlayer(new overlord::Clyde  (s, cnt)); break;
            case 3:  s.RegisterPlayer(new overlord::Ninty  (s, cnt)); break;
            case 4:  s.RegisterPlayer(new overlord::Waffles(s, cnt)); break;
            default: s.RegisterPlayer(new overlord::Muffins(s, cnt)); break;
        }
    }

    Player* human = new Player();
    for (int i = 0; i < cnt; ++i) {
        if (gm == RANDOM) // Register random plushies for player
            human->addPlush(s.createRandomPlush(0, 0, 30));
        else
            human->addPlush(menuPlushCreate(s, gm == DETAIL));
    }
    s.RegisterPlayer(human, 1);

    econio_clrscr();








    wcout << "Game init" << endl;
}