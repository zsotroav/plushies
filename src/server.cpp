//
// Created by zsotroav on 2024-03-24.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include "common.h"
#include "server.h"
#include "player.h"
#include "lanhandle.h"
#include "memtrace.h"
#include "menu_lanconf.h"
#include "overlord.h"

using std::string, std::stoi;

namespace plushies {
    int Server::serverLoop() {
        if (againstLAN()) {
            switch (con->connect(*this)) {
                case DISCONNECTED: return -1;
                case CONFIRM:   break; // TODO: Confirm
                case CONNECTED: break;
            }
        }

        // Enter server gameplay loop
        while(true) {
            // Send LAN player notice that we are ready for the next choice
            if (againstLAN()) con->ActionReady();

            // Ask local player to choose
            future<int> f1 = std::async(&Player::ready, players[1],
                                        players[0]->active());
            future<int> f0; // For LAN player/local AI

            int p0, p1; // Result storage

            // If we aren't against a lan player we can just get their choice
            if (!againstLAN())
                f0 = std::async(&Player::ready, players[0],
                                players[1]->active());

            // We need the local player's choice before we can get the lan's
            p1 = f1.get();

            // If we are against a lan player, get their choices
            if (enemyMode == LAN_CLIENT)
                f0 = std::async(&lanplay::ClientConnection::SyncActions,
                                (dynamic_cast<lanplay::ClientConnection *>(con)),
                                p1);
            else if (enemyMode == LAN_SERVER)
                f0 = std::async(&lanplay::ServerConnection::SyncActions,
                                (dynamic_cast<lanplay::ServerConnection *>(con)),
                                p1);

            // Get enemy's (overlord/lan player) choice as well
            p0 = f0.get();

            const bool sw0 = p0 < 0, sw1 = p1 < 0;

            // Forfeit
            if (p0 == 0) return 1;
            if (p1 == 0) return 0;

            // Swap
            if (sw0) {
                players[0]->setActive(-1*p0 - 1);
                try { players[0]->active() << (players[1]->active() >> (p1-1)); }
                catch (...) { } // If the move failed, oh well, suck for you ig
                continue;
            }
            if (sw1) {
                players[1]->setActive(-1*p1 - 1);
                try {
                    if (!againstLAN()) { // Lan has accuracy precalculated
                        players[1]->active() << (players[0]->active() >> (p0 - 1));
                        continue;
                    }

                    if (p0 > 10) {
                        // Opponent's action failed, we just decrement the energy
                        players[0]->active().Actions[p0-11].decEnergy();
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
                    std::cout << "asd";
                } else {
                    if (p0 > 10) {
                        // Opponent's action failed, we just decrement the energy
                        players[0]->active().Actions[p0-11].decEnergy();
                    } else {
                        // use getAC to avoid double calculating accuracy
                        ac0 = players[0]->active().getAC(p0 - 1);
                    }
                }
            } catch (...) {}
            try { ac1 = players[1]->active() >> (p1-1);} catch (...) {}

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


    std::vector<string> readCSV(std::ifstream& ifstream) {
        string line, word;

        std::getline(ifstream, line);
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

    void Server::registerOpponents(int cnt) {

        if (enemyMode == LAN_CLIENT || enemyMode == LAN_SERVER) {
            try {
                if (enemyMode == LAN_CLIENT) registerComm(new nyetwork::Client(menuLanconf(false)));
                else registerComm(new nyetwork::Server(menuLanconf(true)));
            } catch (...) { // Can only throw conn failed
                wcout << "Connection failed!" << endl;
                return;
            }
        } else {
            // Register overlords
            switch ( enemyMode > 0 ? enemyMode : random(1, 5)) {
                case 1: RegisterPlayer(new overlord::Dennis (*this, cnt)); break;
                case 2: RegisterPlayer(new overlord::Clyde  (*this, cnt)); break;
                case 3: RegisterPlayer(new overlord::Ninty  (*this, cnt)); break;
                case 4: RegisterPlayer(new overlord::Waffles(*this, cnt)); break;
                case 5: RegisterPlayer(new overlord::Muffins(*this, cnt)); break;
            }
        }
    }

    Server::Server(EnemyMode em, GameMode gm, int cnt,
                   const string& brandFile,
                   const string& actionFile,
                   const string& actionLearnFile) :
        enemyMode(em), game_mode_(gm), con(nullptr) {

        loadFiles(brandFile, actionFile, actionLearnFile);
        registerOpponents(cnt);
    }

    Plush Server::createRandomPlush(int bst, int uvmin, int uvmax) {
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
        if (con != nullptr) delete con;
    }

}