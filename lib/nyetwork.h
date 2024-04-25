//
// Created by zsotroav on 2024-04-18.
//

#ifndef NYETWORK_H
#define NYETWORK_H

#ifdef __WIN32__
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif
#include <unistd.h>
#include <string>
#include <vector>
#include "nyetwork_excep.h"

namespace nyetwork {
    std::vector<std::string> getIPv4();

    enum ConnStatus {
        DISCONNECTED = -1,
        CONFIRM = 0,
        CONNECTED = 1
    };

    class Communicator {
    protected:
        ConnStatus conn_status;
        int serverSocket;
        sockaddr_in address{};
    public:
        /**
         * @brief Receive message from the socket
         * @param buf Buffer to store data in
         * @param len Max size of the buffer
         * @param flags Socket connection flags
        */
        virtual void rec(char* buf, int len, int flags) = 0;

        /**
         * @brief Send message to the socket
         * @param buf Buffer to send data from
         * @param len Ammount of data to send from buffer (will ignore \0 as end)
         * @param flags Socket connection flags
        */
        virtual void sen(const char* buf, int len, int flags) = 0;

        explicit Communicator(const char* ip);
        virtual ~Communicator();
    };

    class Client : public Communicator {
    public:
        void rec(char *buf, const int len, const int flags) override {
            if (conn_status != CONNECTED) throw InvalidConnection();
            recv(serverSocket, buf, len, flags);
        }

        void sen(const char *buf, const int len, const int flags) override {
            if (conn_status != CONNECTED) throw InvalidConnection();
            send(serverSocket, buf, len, flags);
        }

        explicit Client(const char* ip);
        explicit Client(const string& ip) : Client(ip.c_str()) {};
        ~Client() override;
    };

    class Server : public Communicator {
        int clientSocket;

    public:
        void rec(char *buf, const int len, const int flags) override {
            if (conn_status != CONNECTED) throw InvalidConnection();
            recv(clientSocket, buf, len, flags);
        }

        void sen(const char *buf, const int len, const int flags) override {
            if (conn_status != CONNECTED) throw InvalidConnection();
            send(clientSocket, buf, len, flags);
        }

        explicit Server(const char* ip);
        explicit Server(const string& ip) : Server(ip.c_str()) {};
        ~Server() override;
    };

}

#endif //NYETWORK_H
