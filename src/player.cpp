//
// Created by zsotroav on 2024-03-24.
//
#include <iostream>
#include "player.h"
#include "game_screen.h"

namespace plushies {


    void Player::addPlush(Plush p) { plushes.push_back(p); }

    void Player::setActive(int i) {
        if (activePlush == i) throw std::invalid_argument("Already active");
        if (numPlushes() < i) throw std::invalid_argument("Unknown plush");
        if (plushes[i].getHP() <= 0) throw std::invalid_argument("Dead plush");

        activePlush = i;
    }

    void Player::nextAlive() {
        for (int i = 0; i < numPlushes(); i++) {
            try { setActive(i); break; }
            catch (...) {}
        }
    }

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