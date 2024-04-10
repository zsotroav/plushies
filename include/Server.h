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

        Player players[2];

        /**
         * @brief Available Brands in the current game
         */
        std::vector<Brand> brands;

        /**
         * @brief Available actions in the current game
         */
        std::vector<Action> actions;
    public:

        /**
         * @brief Get all info about a specific player to sync local state
         * @param id ID of player (0-1)
         * @return Copy of player
         */
        Player syncPlayer(int id);

        void serverLoop();

        inline void RegisterPlayer(Player p, int num = 0) {
            players[num] = std::move(p);
        }

        Server(const string& brandFile = "data/brands.csv",
               const string& actionFile = "data/actions.csv",
               const string& actionLearnFile = "data/action_learn.csv");
    };
}

#endif //PLUSHIES_SERVER_H
