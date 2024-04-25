//
// Created by zsotroav on 2024-04-25.
//

#ifndef LANHANDLE_H
#define LANHANDLE_H

#include <future>

#include "common.h"
#include "nyetwork.h"
#include "plush.h"
#include "server.h"

#define LANPROTOCOL 1

namespace plushies::lanplay {
    class Connection {
    protected:
        nyetwork::Communicator* communicator;

        inline void rec(char* buf, const int len, const int flags = 0) const
        { communicator->rec(buf, len, flags); }
        inline void sen(const char* buf, const int len, const int flags = 0) const
        { communicator->sen(buf, len, flags); }

        inline void sen(const stringstream& ss) const
        { communicator->sen(ss.str().c_str(), strlen(ss.str().c_str()), 0); }


    public:
        /**
         * @brief Handle Communication handshake and initial setup
         * @param server Game Server to set up with connection
         * @return Result of the connection attempt
         * @note This function creates player0 (the opponent dummy player) for
         * the server
         */
        virtual ConnStatus connect(Server& server) = 0;

        /**
         * @brief Get action choice of user
         * @param myChoice The choice this user made that is to be sent
         * @return Choice of opponent
         */
        //virtual int ActionReady(future<int> myChoice) = 0;

        // TODO: PSYN ?
        void sendPSYN(const Server& s, Plush& plush) const;
        Plush recPSYN(Server& s) const;

        /**
         * Set up a generic connection
         * @param com Communicator used for TCP communicating
         */
        Connection(nyetwork::Communicator* com) : communicator(com) {}

        virtual ~Connection() { delete communicator; }
    };

    class ServerConnection : public Connection {
    public:
        ConnStatus connect(Server& server) override;
        //int ActionReady(future<int> myChoice) override;
        ServerConnection(nyetwork::Communicator* com) : Connection(com) {}
        ~ServerConnection() override { delete communicator; }
    };

    class ClientConnection : public Connection {
    public:
        ConnStatus connect(Server& server) override;
        //int ActionReady(future<int> myChoice) override;
        ClientConnection(nyetwork::Communicator* com) : Connection(com) {}
        ~ClientConnection() override { delete communicator; }
    };


}


#endif //LANHANDLE_H
