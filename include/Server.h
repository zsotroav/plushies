//
// Created by zsotroav on 2024-03-22.
//


#ifndef PLUSHIES_SERVER_H
#define PLUSHIES_SERVER_H

#include <vector>
#include <string>
#include "action.h"
#include "common.h"
#include "player.h"
#include "plush.h"

using std::string;

namespace plushies {

    class Server {
        ActionContext executedActions[2];

        Player* players[2];
    public:

        /**
         * @brief Available Brands in the current game
         */
        std::vector<Brand> brands;

        /**
         * @brief Available actions in the current game
         */
        std::vector<Action> actions;

        /**
         * @brief Get all info about a specific player to sync local state
         * @param id ID of player (0-1)
         * @return Copy of player
         */
        Player syncPlayer(int id);

        /**
         * @brief Generate a random plush with optional strength restrictions 
         * @param bst Minimum Base Stat Total (negative for maximum)
         * @param movepwr Miminum move power (negative for max)
         * @param uvmin minimum values for UVs
         * @param uvmax maximum values for UVs
         */
        Plush createRandomPlush(int bst = 0, int movepwr = 0, 
                                int uvmin = 0, int uvmax = 63);

        void serverLoop();

        inline void RegisterPlayer(Player* p, int num = 0) {
            players[num] = p;
        }

        Server(const string& brandFile = "data/brands.csv",
               const string& actionFile = "data/actions.csv",
               const string& actionLearnFile = "data/action_learn.csv");

        ~Server() {
            delete players[0];
            delete players[1];
        }
    };
}

#endif //PLUSHIES_SERVER_H
