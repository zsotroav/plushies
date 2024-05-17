//
// Created by zsotroav on 2024-03-24.
//

#include <fstream>
#include <future>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include "common.h"
#include "lanhandle.h"
#include "menu_lanconf.h"
#include "overlord.h"
#include "player.h"

#include "memtrace.h"

#include "server.h"

using std::string, std::stoi;

namespace plushies {
    int Server::serverLoop() {
        if (againstLAN()) { if (!con->connect(*this)) return -1; }

        // Enter server gameplay loop
        while(true) {
            // Send LAN player notice that we are ready for the next choice
            if (againstLAN()) con->ActionReady();

            // Ask local player to choose
            future<int> f1 = std::async(&Player::ready, players[1],
                                        players[0]->active());
            future<int> f0; // For LAN player/local AI

            int p1; // Result storage

            // If we aren't against a lan player we can just get their choice
            if (!againstLAN())
                f0 = std::async(&Player::ready, players[0],
                                players[1]->active());

            // We need the local player's choice before we can get the lan's
            p1 = f1.get();

            // Pre-calculate accuracy of our attack
            const bool p1fail = p1 > 0 ? !players[1]->active().validateAC(p1) : false;

            // If we are against a lan player, get their choices
            if (enemyMode == LAN_CLIENT)
                f0 = std::async(&lanplay::ClientConnection::SyncActions,
                                (dynamic_cast<lanplay::ClientConnection *>(con)),
                                p1 + (p1fail ? 10 : 0));
            else if (enemyMode == LAN_SERVER)
                f0 = std::async(&lanplay::ServerConnection::SyncActions,
                                (dynamic_cast<lanplay::ServerConnection *>(con)),
                                p1 + (p1fail ? 10 : 0));

            // Get enemy's (overlord/lan player) choice as well
            const int p0 = f0.get();

            const bool sw0 = p0 < 0, sw1 = p1 < 0;

            // Forfeit
            if (p0 == 0) return 1;
            if (p1 == 0) return 0;

            // Swap
            if (sw0) {
                try { players[0]->setActive(-1*p0 - 1); }
                catch (...) { } // Trying to swap into the active plush...
                try { players[0]->active() << (players[1]->active() >> (p1-1)); }
                catch (...) { } // If the move failed, oh well, suck for you ig
                continue;
            }
            if (sw1) {
                try { players[1]->setActive(-1*p1 - 1); }
                catch (...) { } // Trying to swap into the active plush...
                try {
                    if (!againstLAN()) { // Lan has accuracy precalculated
                        players[1]->active() << (players[0]->active() >> (p0 - 1));
                        continue;
                    }
                    // use getAC to avoid double calculating accuracy
                    players[1]->active() << (players[0]->active().getAC(p0-1));
                }
                catch (...) { }
                continue;
            }

            // Actions
            ActionContext ac0 = {0, 0, NONE, Physical};
            ActionContext ac1 = {0, 0, NONE, Physical};
            try {
                if (!againstLAN()) { // Lan has accuracy precalculated
                    ac0 = players[0]->active() >> (p0 - 1);
                } else if (p0 < 10) {
                    // use getAC to avoid double calculating accuracy
                    ac0 = players[0]->active().getAC(p0 - 1);
                }
            } catch (...) {}
            try { ac1 = p1fail ? ac1 : players[1]->active() >> (p1-1); } catch (...) {}

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

    void Server::registerComm(nyetwork::Communicator *c) {
        switch (enemyMode) {
            case LAN_CLIENT: con = new lanplay::ClientConnection(c); break;
            case LAN_SERVER: con = new lanplay::ServerConnection(c); break;
            default: throw std::invalid_argument("Register lan on non-lan mode?");
        }
    }


    std::vector<string> readCSV(std::istream& istream) {
        string line, word;

        std::getline(istream, line);
        std::vector<string> row;
        std::stringstream ss(line);
        while (std::getline(ss, word, ';'))
            row.push_back(word);

        return row;
    }

    void Server::loadFiles(const string &brandFile, const string &actionFile,
                           const string &actionLearnFile) {
        std::ifstream ifbrand(brandFile, std::ios::in);
        while (ifbrand.good()) {
            auto l = readCSV(ifbrand);


            int arr[] = { stoi(l[3]), stoi(l[4]), stoi(l[5]), stoi(l[6]), stoi(l[7]), stoi(l[8]) };
            this->brands.emplace_back(
                    l[0],
                    static_cast<Type>(stoi(l[1])),
                    static_cast<Type>(stoi(l[2])),
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
                    stoi(l[3]), // Energy
                    std::stod(l[4]), // Priority mod
                    static_cast<Type>(stoi(l[5])),
                    static_cast<ActionCategory>(stoi(l[6])));
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

    void Server::registerOpponents(const int cnt) {

        if (enemyMode == LAN_CLIENT || enemyMode == LAN_SERVER) {
            try {
                if (enemyMode == LAN_CLIENT) registerComm(new nyetwork::Client(menuLanconf(false)));
                else registerComm(new nyetwork::Server(menuLanconf(true)));
            } catch (...) { // Can only throw conn failed
                wcout << "Connection failed!" << endl;
            }
        } else {
            // Register overlords
            switch ( enemyMode > 0 ? enemyMode : random(1, 5)) {
                case 1: RegisterPlayer(new overlord::Dennis (*this, cnt)); break;
                case 2: RegisterPlayer(new overlord::Clyde  (*this, cnt)); break;
                case 3: RegisterPlayer(new overlord::Ninty  (*this, cnt)); break;
                case 4: RegisterPlayer(new overlord::Waffles(*this, cnt)); break;
                case 5: RegisterPlayer(new overlord::Muffins(*this, cnt)); break;
                default: break; // Impossible to reach here but needed due to warnings
            }
        }
    }

    Server::Server(const EnemyMode em, const GameMode gm, const int cnt,
                   const string& brandFile,
                   const string& actionFile,
                   const string& actionLearnFile) :
        enemyMode(em), game_mode_(gm), con(nullptr) {

        loadFiles(brandFile, actionFile, actionLearnFile);
        registerOpponents(cnt);
    }

    Plush Server::createRandomPlush(const int bst, const int uvmin, const int uvmax) {
        int brandid = random(0, brands.size() - 1);
        const bool bsts = bst >= 0;
        
        while ((brands[brandid].baseStatTotal() < bst && bsts) ||
               (brands[brandid].baseStatTotal() > -1* bst && !bsts)) 
            brandid = random(0, brands.size() - 1);

        int uv[] = {random(uvmin, uvmax),
                    random(uvmin, uvmax),
                    random(uvmin, uvmax),
                    random(uvmin, uvmax),
                    random(uvmin, uvmax),
                    random(uvmin, uvmax)};

        const auto learn = brands[brandid].getLearnableActions();
        
        Action ac[] = { NullAction, NullAction, NullAction, NullAction};

        if (learn.size() <= 4) {
            for (size_t i = 0; i < learn.size(); i++) ac[i] = *learn[i];
            return {brands[brandid], uv, ac};
        }
        for (int i = 0; i < 4; ++i) {
            ac[i] = *learn[random(0, learn.size()-1)];
            for (int j = 0; j < i; ++j) {
                if (ac[i] == ac[j]) { i--; break; }
            }
        }

        return Plush(brands[brandid], uv, ac);
    }

    Server::~Server() {
        delete players[0];
        delete players[1];
        delete con;
    }

}