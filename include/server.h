//
// Created by zsotroav on 2024-03-22.
//


#ifndef PLUSHIES_SERVER_H
#define PLUSHIES_SERVER_H

#include <string>
#include <vector>
#include "action.h"
#include "common.h"
#include "player.h"
#include "plush.h"
#include "nyetwork.h"

using std::string;

namespace plushies {

    class Server {
        EnemyMode enemyMode;
        nyetwork::Communicator* com;

        Player* players[2];
    public:

        [[nodiscard]] Player* getPlayer(const int i) const
        { return players[i]; }

        [[nodiscard]] EnemyMode getLanMode() const { return enemyMode; }
        [[nodiscard]] bool againstLAN() const
        { return enemyMode == LAN_CLIENT || enemyMode == LAN_SERVER; }

        void registerComm(nyetwork::Communicator* c);

        /**
         * @brief Available Brands in the current game
         */
        std::vector<Brand> brands;

        /**
         * @brief Available actions in the current game
         */
        std::vector<Action> actions;

        /**
         * @brief Generate a random plush with optional strength restrictions 
         * @param bst Minimum Base Stat Total (negative for maximum)
         * @param uvmin minimum values for UVs
         * @param uvmax maximum values for UVs
         */
        Plush createRandomPlush(int bst = 0, int uvmin = 0, int uvmax = 63);

        int serverLoop();

        inline void RegisterPlayer(Player* p, int num = 0) {
            players[num] = p;
        }

        Server(EnemyMode em, const string& brandFile = "data/brands.csv",
               const string& actionFile = "data/actions.csv",
               const string& actionLearnFile = "data/action_learn.csv");

        ~Server() {
            delete players[0];
            delete players[1];
            if (com != nullptr) delete com; // NOLINT(*-delete-null-pointer)
        }
    };
}

#endif //PLUSHIES_SERVER_H
