//
// Created by zsotroav on 2024-04-16.
//

#ifdef __WIN32__
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

#include <cstring>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "common.h"

#include "lanplayer.h"
#include "lanplayer_excep.h"


using namespace plushies;
using namespace std;


// TODO: PSYN


/// LanPlayer

lanplay::LanPlayer::LanPlayer(const char* const ip) : conn_status(DISCONNECTED) {
    #ifdef __WIN32__
        WORD versionWanted = MAKEWORD(1, 1);
        WSADATA wsaData;
        WSAStartup(versionWanted, &wsaData);
    #endif

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(65000);
    address.sin_addr.s_addr = inet_addr(ip);
}

/// Ctor

lanplay::Server::Server(const char* const ip) : LanPlayer(ip) {
    const int status = bind(serverSocket,
                                reinterpret_cast<struct sockaddr *>(&address),
                                sizeof(address));
    if (status != 0) throw ConnectionFailed(status);

    // Wait for connection
    listen(serverSocket, 1);
    clientSocket = accept(serverSocket, nullptr, nullptr);
}

lanplay::Client::Client(const char* const ip, GameMode gm,
                        int plushcnt) : LanPlayer(ip) {
    const int status = connect(serverSocket,
                               reinterpret_cast<struct sockaddr *>(&address),
                               sizeof(address));
    if (status != 0) throw ConnectionFailed(status);
}

/// Connect

lanplay::ConnStatus lanplay::Client::Connect(GameMode gm, int plushcnt) {
    // Send connection request
    // CONN <VERSION> <GAME MODE> <PLUSH COUNT>
    stringstream ss;
    ss << "CONN " << LANPROTOCOL << " " << gm << " " << plushcnt;
    sen(ss.str().c_str(), strlen(ss.str().c_str()), 0);

    char buff[8] = { 0 };
    rec(buff, 8, 0); // CACK
    rec(buff, 8, 0); // CACC/CDEN

    if (strcmp(buff, "CACC") == 0) return (conn_status = CONNECTED);
    return DISCONNECTED;
}

lanplay::ConnStatus lanplay::Server::Connect(GameMode gm, int plushcnt) {
    // Get connection request
    // CONN <VERSION> <GAME MODE> <PLUSH COUNT>
    char buffer[16] = { 0 };

    stringstream ss;
    ss << "CONN " << LANPROTOCOL << " " << gm << " " << plushcnt;
    rec(buffer, sizeof(buffer), 0);
    sen("CACK", 4, 0);

    if (strcmp(ss.str().c_str(), buffer) == 0) {
        sen("CACC", 4, 0);
        return (conn_status = CONNECTED);
    }

    // TODO: Prompt manual check


    return DISCONNECTED;
}

/// Dtor

lanplay::LanPlayer::~LanPlayer() {
    close(serverSocket);
#ifdef __WIN32__
    WSACleanup();
#endif
}

lanplay::Server::~Server() {
    close(clientSocket);
    close(serverSocket);
#ifdef __WIN32__
    WSACleanup();
#endif
}

lanplay::Client::~Client() {
    close(serverSocket);
#ifdef __WIN32__
    WSACleanup();
#endif
}

/// Ready

int lanplay::Client::ready(const Plush& opponent) {
    return 0;
}

int lanplay::Server::ready(const Plush& opponent) {
    return 0;
}
