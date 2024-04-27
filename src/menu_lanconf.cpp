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

string menuLanconf(const bool server) {
    wcout << "Configuring LAN Play  --  "
          << (server ? "Server mode" : "Client mode") << endl << endl
          << "Your potential IP addresses are: " << endl;
    printIP();

    wcout << (server ? "Enter the IP address you want to use: " :
                       "Enter the IP of the server you want to connect to: ")
          << flush;

    std::wstring ws;
    wcin >> ws;
    return convertFromUFT8(ws);
}
