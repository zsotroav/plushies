//
// Created by zsotroav on 2024-03-24.
//
#include <iostream>
#include "player.h"
#include "game_screen.h"

namespace plushies {


    void Player::addPlush(Plush p) { plushes.push_back(p); }

    int Player::numPlushes(bool alive) {
        if (!alive) return plushes.size();

        int counter = 0;
        for (Plush p : plushes) if (p.getHP() > 0) counter++;
        return counter;
    }

    int Player::ready(const Plush& foe) {
        updatePlush(plushes[activePlush]);
        updatePlush(foe, true);
        return chooseMove(*this);
    }

}