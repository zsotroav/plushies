//
// Created by zsotroav on 2024-03-24.
//

/// @file Common data structures and enums

#ifndef PLUSHIES_COMMON_H
#define PLUSHIES_COMMON_H

#include <ostream>
#include <string>

namespace plushies {
    const double relationChart[9][9] = {
            // Attacked -->                                   | By
            // NOR  FIR  WAT  GRA  ELE  FIG  FLY  ROC  GHO    ˇ
            {1,   1,   1,   1,   1,   1,   1,   1,   0   }, // Normal
            {1,   0.5, 0.5, 2,   1,   1,   1,   0.5, 1   }, // Fire
            {1,   2,   0.5, 0.5, 2,   0.5, 2,   2,   1   }, // Water
            {1,   0.5, 2,   0.5, 1,   0.5, 1,   2,   1   }, // Grass
            {1,   1,   2,   0.5, 0.5, 2,   2,   0.5, 1   }, // Electric
            {2,   0.5, 0.5, 1,   1,   1,   2,   2,   0   }, // Fighting
            {1,   1,   1,   2,   0.5, 2,   1,   0.5, 1   }, // Flying
            {1,   2,   0.5, 2,   2,   2,   2,   1,   0.5 }, // Rock
            {0,   1,   1,   1,   1,   2,   1,   1,   2   }, // Ghost
    };

    enum type {
        NONE     = 0,
        NORMAL   = 1,
        FIRE     = 2,
        WATER    = 3,
        GRASS    = 4,
        ELECTRIC = 5,
        FIGHTING = 6,
        FLYING   = 7,
        ROCK     = 8,
        GHOST    = 9
    };

    /**
     * @brief The order in which Stats and Unique Values are stored and should be
     * displayed in the stat hexagon (starting at the top edge, going clock-wise)
     */
    enum StatOrder {
        HP = 0,  //!< Health Points
        Atk = 1, //!< Attack
        Def = 2, //!< Defense
        Spe = 3, //!< Speed
        SpD = 4, //!< Special Defense
        SpA = 5  //!< Special Attack
    };

    enum ActionCategory {
        Physical = 0,
        Special = 1
    };

    struct ActionContext {
        int damage;
        int speed;
        type type;
        ActionCategory category;
    };

    enum GameMode {
        RANDOM = 0,
        CUSTOM = 1,
        DETAIL = 2,
        INVALID = -1
    };
}

/**
 * @brief Get a random number between a and b
 * @param a Random from (inclusive)
 * @param b Random to (inclusive)
 * @returns pseudo random int
 */
int random(int a, int b);

double operator>>(plushies::type attacker, plushies::type target);

std::wostream& operator<<(std::wostream& os, plushies::type type);

std::wostream& operator<<(std::wostream& os, plushies::ActionCategory ac);

std::wstring convertUFT8(const std::string& s);

#endif //PLUSHIES_COMMON_H
