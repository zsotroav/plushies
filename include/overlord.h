//
// Created by zsotroav on 2024-04-10.
//

#ifndef PLUSHIES_OVERLORD_H
#define PLUSHIES_OVERLORD_H

#include <vector>
#include "common.h"
#include "plush.h"
#include "player.h"
#include "server.h"


namespace plushies::overlord {
    /**
     * @brief Random moves, random plushes
     */
    class Dennis : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;

        /**
         * @brief Generate AI with random plushes
         * @param s Server for the available brands and actions
         * @param count Number of plushes to generate
         */
        Dennis(Server& s, int count);
    };

    /**
     * @brief Waits 5-10 secs random move, random plushes
     */
    class Clyde : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;
        
        /**
         * @brief Generate AI with random plushes
         * @param s Server for the available brands and actions
         * @param count Number of plushes to generate
         */
        Clyde(Server& s, int count);
    };

    /**
     * @brief Most damage, high stat, high UVs
     */
    class Ninty : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;

        /**
         * @brief Generate AI with random, but strong plushes
         * @param s Server for the available brands and actions
         * @param count Number of plushes to generate
         */
        Ninty(Server& s, int count);
    };

    /**
     * @brief Use least damage, high stat, mid UVs
     */
    class Waffles : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;

        /**
         * @brief Generate AI with random, but strong plushes
         * @param s Server for the available brands and actions
         * @param count Number of plushes to generate
         */
        Waffles(Server& s, int count);
    };

    /**
     * @brief Least damage, random plushes
     */
    class Muffins : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;
        
        /**
         * @brief Generate AI with random plushes
         * @param s Server for the available brands and actions
         * @param count Number of plushes to generate
         */
        Muffins(Server& s, int count);
    };
} // plushies::overlord

#endif //PLUSHIES_OVERLORD_H
