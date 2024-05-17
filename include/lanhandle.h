//
// Created by zsotroav on 2024-04-25.
//

#ifndef LANHANDLE_H
#define LANHANDLE_H

#include <cstring>

#include "common.h"
#include "nyetwork.h"
#include "plush.h"
#include "server.h"

#define LANPROTOCOL 1

namespace plushies::lanplay {
    class Connection {
    protected:
        nyetwork::Communicator* communicator;

        /**
         * Receive into buffer
         * @param buf Buffer to receive into
         * @param len Maximum length to receive
         * @param flags recv() flags
         */
        void rec(char* buf, const int len, const int flags = 0) const
        { communicator->rec(buf, len, flags); }

        /**
         * Send char* buffer
         * @param buf Buffer to send
         * @param len Size of buffer to send
         * @param flags sen() flags
         */
        void sen(const char* buf, const int len, const int flags = 0) const
        { communicator->sen(buf, len, flags); }

        /**
         * Send string
         * @param string string to send
         */
        void sen(const std::string& string) const
        { communicator->sen(string.c_str(), string.length(), 0); }

        /**
         * Send string stream's data
         * @param ss StringStream to send
         */
        void sen(const stringstream& ss) const
        { communicator->sen(ss.str().c_str(), strlen(ss.str().c_str()), 0); }


    public:
        /**
         * @brief Handle Communication handshake and initial setup
         * @param server Game Server to set up with connection
         * @return Result of the connection attempt
         * @note This function creates player0 (the opponent dummy player) for
         * the server
         */
        virtual bool connect(Server& server) = 0;

        /**
         * @brief Let the lan player know we are ready to receive their choice
         */
        virtual void ActionReady() = 0;

        /**
         * @brief Sync the choice of the local and lan player
         * @param myChoice The choice of the local player to send
         * @return Choice of the lan player
         */
        virtual int SyncActions(int myChoice) = 0;

        /**
         * Send PSYN (Plush Sync) command for a plush
         * @param s Server for brand/plush/action database
         * @param plush Plush to send
         */
        void sendPSYN(const Server& s, const Plush& plush) const;

        /**
         * Receive PSYN (Plsuh Sync) command and get the plsuh from it
         * @param s Server for brand/plush/action database
         * @return Received plush
         * @throws std::invalid_argument did not receive PSYN
         */
        Plush recPSYN(Server& s) const;

        /**
         * Set up a generic connection
         * @param com Communicator used for TCP communicating
         */
        Connection(nyetwork::Communicator* com) : communicator(com) {}

        virtual ~Connection() { delete communicator; }
    };

    class ServerConnection final : public Connection {
    public:
        bool connect(Server& server) override;
        void ActionReady() override;
        int SyncActions(int myChoice) override;
        ServerConnection(nyetwork::Communicator* com) : Connection(com) {}
        ~ServerConnection() override {}
    };

    class ClientConnection final : public Connection {
    public:
        bool connect(Server& server) override;
        void ActionReady() override;
        int SyncActions(int myChoice) override;
        ClientConnection(nyetwork::Communicator* com) : Connection(com) {}
        ~ClientConnection() override {}
    };


}

#endif //LANHANDLE_H
