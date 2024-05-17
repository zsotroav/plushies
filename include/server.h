//
// Created by zsotroav on 2024-03-22.
//


#ifndef PLUSHIES_SERVER_H
#define PLUSHIES_SERVER_H

#include <string>
#include <vector>
#include "action.h"
#include "common.h"
#include "player.h"
#include "plush.h"
#include "nyetwork.h"

using std::string;

namespace plushies {
    namespace lanplay {
        class Connection;
    }

    /**
     * Read in a line from a CSV file
     * @param istream Stream to read from
     * @return vector of strings
     */
    std::vector<string> readCSV(std::istream& istream);

    class Server {
        EnemyMode enemyMode;
        GameMode game_mode_;
        lanplay::Connection* con;

        Player* players[2];

        void loadFiles(const string& brandFile,
                       const string& actionFile,
                       const string& actionLearnFile);
        void registerOpponents(int cnt);
    public:

        std::vector<Brand> brands; //!< Available Brands in the current game
        std::vector<Action> actions; //!< Available actions in the current game

        /**
         * Get a player from the server
         * @param i ID of player
         * @return Pointer to the player
         */
        Player* getPlayer(const int i) const { return players[i]; }

        EnemyMode getLanMode() const { return enemyMode; } //!< Get enemy mode
        bool againstLAN() const //!< Check if playing against LAN player
        { return enemyMode == LAN_CLIENT || enemyMode == LAN_SERVER; }

        GameMode getGameMode() const { return game_mode_; } //!< Get the game mode

        /**
         * Register a communicator for LAN Play
         * @param c Communicator to register
         * @throws std::invalid_argument If called in non LAN context
         */
        void registerComm(nyetwork::Communicator* c);

        /**
         * Generate a random plush with optional strength restrictions
         * @param bst Minimum Base Stat Total (negative for maximum)
         * @param uvmin minimum values for UVs
         * @param uvmax maximum values for UVs
         */
        Plush createRandomPlush(int bst = 0, int uvmin = 0, int uvmax = 63);

        /**
         * Start the main server loop
         * @return The game end result
         *  - 1 : Won
         *  - 0 : Lost
         *  - -1: Catastrophic internal error (couldn't recover)
         */
        int serverLoop();

        /**
         * Register a player to the server
         * @param p Player pointer to register (deletes: server)
         * @param num ID of player
         */
        void RegisterPlayer(Player* p, const int num = 0) { players[num] = p; }

        /**
         * Initialize the server and all data
         * @param em Enemy Mode to start with
         * @param gm Game Mode
         * @param cnt Number of plushes
         * @param brandFile Brand csv location
         * @param actionFile Actions csv location
         * @param actionLearnFile Action Learn csv location
         */
        Server(EnemyMode em, GameMode gm, int cnt,
               const string& brandFile = "data/brands.csv",
               const string& actionFile = "data/actions.csv",
               const string& actionLearnFile = "data/action_learn.csv");

        ~Server();
    };
}

#endif //PLUSHIES_SERVER_H
