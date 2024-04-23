//
// Created by zsotroav on 2024-04-23.
//


#include <iostream>
#include <string>
#include "nyetwork.h"
#include "common.h"

#include "menu_lanconf.h"

using std::wcout, std::wcin, std::endl, std::string;

void printIP() {
    auto ip = nyetwork::getIPv4();
    for (auto & i : ip) {
        wcout << "- " << i << endl;
    }
}

void menuLanconf(string& ip_me, string& ip_re, bool server) {
    wcout << "Configuring LAN Play  --  "
          << (server ? "Server mode" : "Client mode") << endl << endl
          << "Your potential IP addresses are: " << endl;
    printIP();
    wcout << endl << endl << "Enter the IP you want to use: " << flush;

    std::wstring ws;
    wcin >> ws;
    ip_me = convertFromUFT8(ws);

    wcout << "Enter the IP of the server you want to connect to: " << flush;

    wcin >> ws;
    ip_re = convertFromUFT8(ws);
}
