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
#include "lanplayer_excep.h"
#include <sstream>

#define LANPROTOCOL "1"

namespace plushies::lanplay {
    enum ConnStatus {
        DISCONNECTED = -1,
        CONFIRM = 0,
        CONNECTED = 1
    };

    class LanPlayer : public Player {
    protected:
        ConnStatus conn_status;
        int serverSocket;
        sockaddr_in address{};
    public:
        /**
         * @brief Initialize connection to the server/client
         * @param gm Game mode the player is in
         * @param plushcnt Number of plushes used
         * @return Connection Status (ACC/DEN/Approve reques)
         */
        virtual ConnStatus Connect(GameMode gm, int plushcnt) = 0;

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

        LanPlayer(const char* ip);
        virtual ~LanPlayer();
    };

    class Client : public LanPlayer {
    public:
        int ready(const Plush& opponent) override;

        ConnStatus Connect(GameMode gm, int plushcnt) override;

        void rec(char *buf, const int len, const int flags) override {
            if (conn_status != CONNECTED) throw InvalidConnection();
            recv(serverSocket, buf, len, flags);
        }

        void sen(const char *buf, const int len, const int flags) override {
            if (conn_status != CONNECTED) throw InvalidConnection();
            send(serverSocket, buf, len, flags);
        }

        Client(const char* ip, GameMode gm, int plushcnt);
        ~Client() override;
    };

    class Server : public LanPlayer {

        int clientSocket;

    public:
        int ready(const Plush& opponent) override;

        ConnStatus Connect(GameMode gm, int plushcnt) override;

        /**
         * @brief Approve or Deny conneciton manually
         * @param approve Set true to accept connection, false to deny
         */
        void ConnectionRespond(bool approve);

        void rec(char *buf, const int len, const int flags) override {
            if (conn_status != CONNECTED) throw InvalidConnection();
            send(clientSocket, buf, len, flags);
        }

        void sen(const char *buf, const int len, const int flags) override {
            if (conn_status != CONNECTED) throw InvalidConnection();
            send(clientSocket, buf, len, flags);
        }

        Server(const char* ip);
        ~Server() override;
    };

}
#endif //PLUSHIES_LANPLAYER_H
