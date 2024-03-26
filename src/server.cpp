//
// Created by zsotroav on 2024-03-24.
//

#include <iostream>
#include <thread>
#include <future>
#include <utility>
#include "server.h"
#include "player.h"

namespace plushies {

    Player Server::syncPlayer(int id) { return players[id]; }

    void Server::serverLoop() {
        auto future0 = std::async(&Player::ready, &players[0]);
        auto future1 = std::async(&Player::ready, &players[1]);

        std::cout << future0.get() << " - " << future1.get() << std::endl;
    }

    Server::Server(plushies::Player player0, plushies::Player player1) {
        players[0] = std::move(player0);
        players[1] = std::move(player1);
    }
}