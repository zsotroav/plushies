//
// Created by zsotroav on 2024-03-24.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <future>
#include <utility>
#include <string>
#include <vector>
#include "common.h"
#include "server.h"
#include "player.h"

using std::string, std::stoi;

namespace plushies {

    Player Server::syncPlayer(int id) { return *players[id]; }

    int Server::serverLoop() {
        bool active = true;
        while(active) {
            auto f0 = std::async(&Player::ready, players[0], players[1]->active());
            auto f1 = std::async(&Player::ready, players[1], players[0]->active());

            int p0 = f0.get();
            int p1 = f1.get();

            bool sw0 = p0 < 0, sw1 = p1 < 0;

            // Forfeit
            if (p0 == 0) return 1;
            if (p1 == 0) return 0;

            // Swap
            if (sw0) {
                players[0]->setActive(-1*p0);
                players[0]->active() << (players[1]->active() >> (p1-1));
                continue;
            }
            if (sw1) {
                players[1]->setActive(-1*p1);
                players[1]->active() << (players[0]->active() >> (p1-1));
                continue;
            }

            // Actions
            auto ac0 = players[0]->active() >> (p0-1);
            auto ac1 = players[1]->active() >> (p1-1);

            if (ac0.speed > ac1.speed) {
                players[0]->active() << ac1;
                if (players[0]->active().getHP() > 0)
                    players[1]->active() << ac0;
            } else {
                players[1]->active() << ac0;
                if (players[1]->active().getHP() > 0)
                    players[0]->active() << ac1;
            }

            // Alive checks
            if (players[0]->numPlushes(true) <= 0) return 1;
            if (players[1]->numPlushes(true) <= 0) return 0;

            if (players[0]->active().getHP() <= 0) players[0]->nextAlive();
            if (players[1]->active().getHP() <= 0) players[1]->nextAlive();

        }

    }

    std::vector<string> readCSV(std::ifstream& ifstream) {
        string line, word;

        std::getline(ifstream, line);
        std::vector<string> row;
        std::stringstream ss(line);
        while (std::getline(ss, word, ';'))
            row.push_back(word);

        return row;
    }

    Server::Server(const string& brandFile,
                   const string& actionFile,
                   const string& actionLearnFile) {
        std::ifstream ifbrand(brandFile, std::ios::in);
        while (ifbrand.good()) {
            auto l = readCSV(ifbrand);


            int arr[] = { stoi(l[3]), stoi(l[4]), stoi(l[5]), stoi(l[6]), stoi(l[7]), stoi(l[8]) };
            this->brands.emplace_back(
                    l[0],
                    static_cast<type>(stoi(l[1])),
                    static_cast<type>(stoi(l[2])),
                    arr);
        }
        ifbrand.close();

        std::ifstream ifaction(actionFile, std::ios::in);
        while (ifaction.good()) {
            auto l = readCSV(ifaction);

            this->actions.emplace_back(
                    l[0],       // Name
                    stoi(l[1]), // Base Power/Damage
                    stoi(l[2]), // Accuracy
                    std::stod(l[3]), // Priority mod
                    static_cast<type>(stoi(l[4])),
                    static_cast<ActionCategory>(stoi(l[5])));
        }
        ifaction.close();

        std::ifstream iflearn(actionLearnFile, std::ios::in);
        while (iflearn.good()) {
            auto l = readCSV(iflearn);
            for (size_t i = 1; i < l.size(); i++) {
                brands[stoi(l[0])].addLearnableAction(&actions[stoi(l[i])]);    
            }
            
        }
        iflearn.close();

    }

    Plush Server::createRandomPlush(int bst, int,
                                    int uvmin, int uvmax) {
        int brandid = random(0, brands.size() - 1);
        bool bsts = bst >= 0;
        
        while ((brands[brandid].baseStatTotal() < bst && bsts) ||
               (brands[brandid].baseStatTotal() > -1* bst && !bsts)) 
            brandid = random(0, brands.size() - 1);

        int uv[] = {random(uvmin, uvmax),
                    random(uvmin, uvmax),
                    random(uvmin, uvmax),
                    random(uvmin, uvmax),
                    random(uvmin, uvmax),
                    random(uvmin, uvmax)};

        auto learn = brands[brandid].getLearnableActions();
        
        Action* ac[] = { nullptr, nullptr, nullptr, nullptr};

        // TODO: implement movepwr
        if (learn.size() <= 4)
            for (size_t i = 0; i < learn.size(); i++) ac[i] = learn[i];
        else 
            for (auto & i : ac) i = learn[random(0, learn.size()-1)];

        return Plush(brands[brandid], uv, ac);
    }
}