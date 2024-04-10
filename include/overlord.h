//
// Created by zsotroav on 2024-04-10.
//

#ifndef PLUSHIES_OVERLORD_H
#define PLUSHIES_OVERLORD_H

#include <vector>
#include "common.h"
#include "plush.h"
#include "player.h"


namespace plushies::overlord {
    /**
     * @brief Random moves, random plushes
     */
    class Dennis : public plushies::Player {
    public:
        inline int ready(const Plush& opponent) override
        { return random(1, active().validMoves()); }
    };

    /**
     * @brief Waits 5-10 secs random move, random plushes
     */
    class Clyde : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;
    };

    /**
     * @brief Most damage, high stat, high UVs
     */
    class Ninty : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;
    };

    /**
     * @brief Use least damage, high stat, mid UVs
     */
    class Waffles : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;
    };

    /**
     * @brief Least damage, random plushes
     */
    class Muffins : public plushies::Player {
    public:
        int ready(const Plush& opponent) override;
    };
} // plushies::overlord

#endif //PLUSHIES_OVERLORD_H
