//
// Created by zsotroav on 2024-04-11.
//

#include <iostream>
#include <string>

#include <iomanip>
#include "action.h"
#include "brand.h"
#include "common.h"
#include "plush.h"
#include "server.h"

#include "econio.h"

#include "menu_plush_create.h"

using namespace plushies;
using std::wcout, std::flush;


void printMPC() {
    wcout << L"                                    Plush Monsters' Fight Club - Plush Configuration                                    \n"
             "                                                                                       ╔══════╤════════════════════════╗\n"
             "Plush Brand:                                                        ╔═══════════════╗  ║      │                        ║\n"
             "                                                                    ║      HP       ║  ║      │                        ║\n"
             "Action 1:                                                           ║               ║  ║      │                        ║\n"
             "                                                                    ║  SA      AT   ║  ║      │                        ║\n"
             "Action 2:                                                           ║               ║  ║      │                        ║\n"
             "                                                                    ║  SD      DE   ║  ║      │                        ║\n"
             "Action 3:                                                           ║               ║  ║      │                        ║\n"
             "                                                                    ║      SP       ║  ║      │                        ║\n"
             "Action 4:                                                           ╚═══════════════╝  ║      │                        ║\n"
             "                                                                                       ║      │                        ║\n"
             "Uniquie Values:                                                                        ║      │                        ║\n"
             "  - HP:        How tanky are you?                                                      ║      │                        ║\n"
             "  - ATK:       That's gonna hurt                                                       ║      │                        ║\n"
             "  - DEF:       Nothing without a good defense                                          ║      │                        ║\n"
             "  - SPD:       We're *special*                                                         ║      │                        ║\n"
             "  - SPA:       We attack *special*                                                     ║      │                        ║\n"
             "  - SPE:       Gotta go fast                                                           ║      │                        ║\n"
             "                                                                                       ║      │                        ║\n"
             "                                                                                       ║      │                        ║\n"
             "                                                                                       ║      │                        ║\n"
             "                                                                                       ║      │                        ║\n"
             "                                                            ╔═══════════════════════╗  ║      │                        ║\n"
             "                                                            ║      POWER            ║  ║      │                        ║\n"
             "                                                            ║   ACCURACY            ║  ║      │                        ║\n"
             "                                                            ║     ENERGY            ║  ║      │                        ║\n"
             "                                                            ║       TYPE            ║  ║      │                        ║\n"
             "                                                            ║   CATEGORY            ║  ║      │                        ║\n"
             "                                                            ╚═══════════════════════╝  ╚══════╧════════════════════════╝";
}

void printDetail(int i, std::string s, bool highlight = false) {
    econio_gotoxy(90, 2+i);
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << i;

    if (highlight) {
        econio_textcolor(COL_BLACK);
        econio_textbackground(COL_WHITE);
    }
    wcout << ss.str();
    econio_textcolor(COL_WHITE);
    econio_textbackground(COL_BLACK);

    wcout << L"  │ " << s;

    for (size_t j = 0; j < 23 - s.length(); ++j) wcout << " ";
}

// TODO: Print brand types

void printBrandDetail(const Brand& b, int i, bool highlight = false) {
    printDetail(i, b.getName(), highlight);

    econio_gotoxy(75, 3);
    wcout << b.getBaseStat(HP);
    econio_gotoxy(71, 5);
    wcout << b.getBaseStat(SpA) << "      " << b.getBaseStat(Atk);
    econio_gotoxy(71, 7);
    wcout << b.getBaseStat(SpD) << "      " << b.getBaseStat(Def);
    econio_gotoxy(75, 9);
    wcout << b.getBaseStat(Spe);
}

void printActionDetail(const Action* a, int i, bool highlight = false) {
    printDetail(i, a->getName(), highlight);

    econio_gotoxy(74, 24);
    wcout << a->getDamage() << "   ";
    econio_gotoxy(74, 25);
    wcout << a->getAccuracy() << "%   ";
    econio_gotoxy(74, 26);
    wcout << "--";
    econio_gotoxy(74, 27);
    wcout << a->getType();
    econio_gotoxy(74, 28);
    wcout << a->getCategory();
}

void printBrands(Server& s) {
    auto b = s.brands;
    int l = b.size();

    for (int i = 1; i < l; ++i) printBrandDetail(b[i], i);
    for (int i = 0; i < 27-l; ++i) {
        econio_gotoxy(90, l+2+i);
        wcout << L"    │                        ║" ;
    }

    printBrandDetail(b[0], 0, true);
    wcout << flush;
}

void printActions(Brand& b) {
    auto a = b.getLearnableActions();
    int l = a.size();

    for (int i = 1; i < l; ++i) printActionDetail(a[i], i);
    for (int i = 0; i < 27-l; ++i) {
        econio_gotoxy(90, l+2+i);
        wcout << L"    │                        ║" ;
    }

    printActionDetail(a[0], 0, true);
    wcout << flush;
}

int selectItem(Server& s, int brandid = -1) {
    int curr = 0;
    int prev = 0;
    int l = brandid < 0 ? ( brandid == -2 ? 5 : s.brands.size()) :
                          s.brands[brandid].getLearnableActions().size();

    while (true) {
        while (!econio_kbhit()) econio_sleep(0.2);

        switch (econio_getch()) {
            case 'w': case KEY_UP:
                if (curr == 0) continue;
                prev = curr; --curr; break;
            case 's': case KEY_DOWN:
                if (curr == l - 1) continue;
                prev = curr; ++curr; break;
            case ' ': case KEY_ENTER: return curr;
        }

        if (brandid == -1) {
            printBrandDetail(s.brands[prev], prev);
            printBrandDetail(s.brands[curr], curr, true);
        } else {
            printActionDetail(s.brands[brandid].getLearnableActions()[prev], prev);
            printActionDetail(s.brands[brandid].getLearnableActions()[curr], curr, true);
        }
    }
}


Plush plushies::menuPlushCreate(Server& s, bool detailed) {
    econio_clrscr();
    printMPC();
    if (detailed) {
        econio_gotoxy(51, 1);
        wcout << "[DETAILED CONFIG]";
    }

    printBrands(s);

    int brandid = selectItem(s);
    econio_gotoxy(13, 2);
    wcout << brandid << " - " << s.brands[brandid].getName() << flush;

    Action* ac[] = { nullptr, nullptr, nullptr, nullptr };

    for (int i = 0; i < 4; ++i) {
        printActions(s.brands[brandid]);

        int acid = selectItem(s, brandid);
        ac[i] = s.brands[brandid].getLearnableActions()[acid];

        econio_gotoxy(10, 4 + 2*i);
        wcout << acid << " - " << ac[i]->getName() << flush;
    }

    int uv[] = { random(30, 63), random(30, 63), random(30, 63),
                 random(30, 63), random(30, 63), random(30, 63)};
    if (detailed) {
        econio_normalmode();
        for (int i = 0; i < 6; ++i) {
            econio_gotoxy(9, 13 + i);
            std::wcin >> uv[i];
            if (uv[i] < 0 || uv[i] > 63) {
                econio_gotoxy(9, 13 + i);
                wcout << "?     ";
                econio_gotoxy(9, 13 + i);
                i--;
            }
        }
        econio_rawmode();
    }

    return {s.brands[brandid], uv, ac};
}
