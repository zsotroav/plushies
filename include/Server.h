//
// Created by zsotroav on 2024-03-22.
//


#ifndef _NHF_SERVER_H
#define _NHF_SERVER_H

#include <vector>
#include "action.h"
#include "common.h"
#include "player.h"
#include "plush.h"


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

        Server(Player player0, Player player1);
    };
}

#endif //_NHF_SERVER_H
