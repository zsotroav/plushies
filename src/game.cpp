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

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif // Windows

using namespace plushies;
using std::wcout, std::endl, std::flush;


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

    econio_clrscr();

#if defined(_WIN32) || defined(_WIN64)
    // Check Terminal size on windows
    // https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    std::cout << columns << rows;
    if (columns < 120 || rows < 30) { // Too small => write the message
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
#if defined(_WIN32) || defined(_WIN64)
    } // Check terminal size on windows
#endif

    GameMode gm;
    int cnt, opp;
    menu(gm, cnt, opp);

    plushies::Server s;

}