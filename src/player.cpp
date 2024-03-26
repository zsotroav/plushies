//
// Created by zsotroav on 2024-03-24.
//
#include <random>
#include <thread>
#include <chrono>
#include <iostream>
#include "player.h"

namespace plushies {


    void Player::addPlush(Plush p) { plushes.push_back(p); }

    int Player::numPlushes(bool alive) {
        if (!alive) return plushes.size();

        int counter = 0;
        for (Plush p : plushes) if (p.getHP() > 0) counter++;
        return counter;
    }

    int Player::ready() {

        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 6);
        int mean = uniform_dist(e1);
        std::this_thread::sleep_for(std::chrono::seconds(mean));
        return mean;
    }

}