//
// Created by zsotroav on 2024-04-16.
//

#ifndef PLUSHIES_LANPLAYER_H
#define PLUSHIES_LANPLAYER_H

#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include <unistd.h>

#include <utility>
#include "player.h"
#include <sstream>

namespace plushies::lanplay {
    class LanPlayer : public Player {
    protected:
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
        virtual void sen(char* buf, int len, int flags) = 0;

        LanPlayer(const char* ip);
        virtual ~LanPlayer();
    };

    class Client : public LanPlayer {
    public:
        int ready(const Plush& opponent) override;

        void rec(char *buf, const int len, const int flags) override {
            recv(serverSocket, buf, len, flags);
        }

        void sen(char *buf, const int len, const int flags) override {
            send(serverSocket, buf, len, flags);
        }

        Client(const char* ip);
        ~Client() override;
    };

    class Server : public LanPlayer {

        int clientSocket;

    public:
        int ready(const Plush& opponent) override;

        void rec(char *buf, const int len, const int flags) override {
            send(clientSocket, buf, len, flags);
        }

        void sen(char *buf, const int len, const int flags) override {
            send(clientSocket, buf, len, flags);
        }

        Server(const char* ip);
        ~Server() override;
    };

    class ConnectionFailed final : public std::exception {
        std::string message;

    public:
        explicit ConnectionFailed(const char * msg) : message(msg) {}
        explicit ConnectionFailed(string msg) : message(std::move(msg)) {}
        explicit ConnectionFailed(int code) {
            std::stringstream ss;
            ss << "Connection error: " << code;
            message = ss.str();
        }
        ConnectionFailed() : message("Connection failed!") {}

        [[nodiscard]] const char* what() const noexcept override
        { return message.c_str(); }
    };
}
#endif //PLUSHIES_LANPLAYER_H
