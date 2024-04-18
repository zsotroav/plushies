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

#include "lanplayer.h"


using namespace plushies;
using namespace std;


/// LanPlayer

lanplay::LanPlayer::LanPlayer(const char* const ip) {    
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

lanplay::Client::Client(const char* const ip) : LanPlayer(ip) {
    const int status = connect(serverSocket,
                               reinterpret_cast<struct sockaddr *>(&address),
                               sizeof(address));
    if (status != 0) throw ConnectionFailed(status);
}


/// Ready

int lanplay::Client::ready(const Plush& opponent) {
    return 0;
}

int lanplay::Server::ready(const Plush& opponent) {
    return 0;
}
