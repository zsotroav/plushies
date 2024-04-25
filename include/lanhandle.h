//
// Created by zsotroav on 2024-04-25.
//

#ifndef LANHANDLE_H
#define LANHANDLE_H

#include <future>

#include "common.h"
#include "nyetwork.h"

#define LANPROTOCOL 1

namespace plushies::lanplay {
    enum ConnStatus {
        DISCONNECTED = -1,
        CONFIRM = 0,
        CONNECTED = 1
    };

    class Connection {
    protected:
        nyetwork::Communicator* communicator;

        inline void rec(char* buf, const int len, const int flags = 0)
        { communicator->rec(buf, len, flags); }
        inline void sen(const char* buf, const int len, const int flags = 0)
        { communicator->sen(buf, len, flags); }

    public:
        /**
         * @brief Handle Communication handshake
         * @param gm GameMode of connection
         * @param plushcnt Number of plushes in use in the game
         * @return Result of the connection attempt
         */
        virtual ConnStatus connect(GameMode gm, int plushcnt) = 0;

        /**
         * @brief Get action choice of user
         * @param myChoice The choice this user made that is to be sent
         * @return Choice of opponent
         */
        //virtual int ActionReady(future<int> myChoice) = 0;

        Connection(nyetwork::Communicator* com) : communicator(com) {}

        virtual ~Connection() { delete communicator; }
    };

    class ServerConnection : public Connection {
    public:
        ConnStatus connect(GameMode gm, int plushcnt) override;
        //int ActionReady(future<int> myChoice) override;
        ServerConnection(nyetwork::Communicator* com) : Connection(com) {}
        ~ServerConnection() override { delete communicator; }
    };

    class ClientConnection : public Connection {
    public:
        ConnStatus connect(GameMode gm, int plushcnt) override;
        //int ActionReady(future<int> myChoice) override;
        ClientConnection(nyetwork::Communicator* com) : Connection(com) {}
        ~ClientConnection() override { delete communicator; }
    };


}


#endif //LANHANDLE_H
