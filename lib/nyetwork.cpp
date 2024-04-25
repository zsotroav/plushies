#include "nyetwork.h"

#include <array>
#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#ifdef __WIN32__
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

using namespace std;

namespace nyetwork {
    string exec(const char* cmd) {
        array<char, 128> buffer { 0 };
        string result;
        const unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) throw runtime_error("popen() failed!");

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }

     vector<string> getIPv4() {
        string sys, line;
        vector<string> re;
        #ifdef __WIN32__
            sys = exec(R"(for /f "tokens=2 delims=[]" %a in ('ping -n 1 -4 "%computername%"') do @echo %a)");
        #else
            sys = exec(R"(ip -4 addr | grep -oP '(?<=inet\s)\\d+(\.\d+){3}')");
        #endif

        stringstream ss(sys);
        while (getline(ss, line, '\n')) re.emplace_back(line);

        return re;
    }

    Communicator::Communicator(const char *ip) : conn_status(DISCONNECTED) {
        #ifdef __WIN32__
            WORD versionWanted = MAKEWORD(1, 1);
            WSADATA wsaData;
            WSAStartup(versionWanted, &wsaData);
        #endif

        serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        address.sin_family = AF_INET;
        address.sin_port = htons(6000);
        address.sin_addr.s_addr = inet_addr(ip);
    }

    Server::Server(const char *ip) : Communicator(ip) {
        const int status = bind(serverSocket,
                                (struct sockaddr*)&address,
                                sizeof(address));
        if (status != 0) throw ConnectionFailed(status);

        // Wait for connection
        listen(serverSocket, 1);
        clientSocket = accept(serverSocket, nullptr, nullptr);
        conn_status = CONNECTED;
    }

    Client::Client(const char *ip) : Communicator(ip) {
        const int status = connect(serverSocket,
                                   (struct sockaddr*)(&address),
                                   sizeof(address));
        if (status != 0) throw ConnectionFailed(status);
        conn_status = CONNECTED;
    }

    Communicator::~Communicator() {
        close(serverSocket);
        #ifdef __WIN32__
            WSACleanup();
        #endif
    }

    Client::~Client() {
        close(serverSocket);
        #ifdef __WIN32__
            WSACleanup();
        #endif
    }

    Server::~Server() {
        close(serverSocket);
        close(clientSocket);
        #ifdef __WIN32__
            WSACleanup();
        #endif
    }

}
