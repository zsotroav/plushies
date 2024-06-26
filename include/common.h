//
// Created by zsotroav on 2024-03-24.
//

/// @file common.h Common data structures and enums

#ifndef PLUSHIES_COMMON_H
#define PLUSHIES_COMMON_H

#include <string>
#include <vector>
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

    enum Type {
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
        Type type;
        ActionCategory category;
    };

    enum GameMode {
        RANDOM = 0,
        CUSTOM = 1,
        DETAIL = 2,
        INVALID = -1
    };

    enum EnemyMode {
        INVALIDENEMY = -1,
        OVERLORD_GENERIC = 0,
        OVERLORD_DENNIS  = 1,
        OVERLORD_CLYDE   = 2,
        OVERLORD_NINTY   = 3,
        OVERLORD_WAFFLES = 4,
        OVERLORD_MUFFINS = 5,
        LAN_SERVER       = 10,
        LAN_CLIENT       = 15
    };
}

/**
 * @brief Get a random number between a and b
 * @param a Random from (inclusive)
 * @param b Random to (inclusive)
 * @returns pseudo random int
 */
int random(int a, int b);

/**
 * Get the type effectiveness between two types
 * @param attacker Type of attacker
 * @param target Type of target
 * @return Type effectiveness modifier
 */
double operator>>(plushies::Type attacker, plushies::Type target);

/**
 * Convert string to wstring for wcout
 * @param s regular string to convert
 * @return UTF-8 (wide) string
 */
std::wstring convertUFT8(const std::string& s);

/**
 * Convert wstring to string from wcin
 * @param ws UTF-8 (wide) string to convert
 * @return regular string
 */
std::string convertFromUFT8(const std::wstring& ws);

/**
 * Write a regular string out to a wide ostream
 * @param wos Wide output stream (such as wcout)
 * @param s Regular string to be converted to wstring and written out
 * @return Chainable wostream
 */
inline std::wostream& operator<<(std::wostream& wos, const std::string& s)
{ return wos << convertUFT8(s); }

/**
 * Write Type out to wide output stream
 * @param wos Wide output stream (such as wcout)
 * @param type Plush Type to write out
 * @return Chainable wostream
 */
std::wostream& operator<<(std::wostream& wos, plushies::Type type);

/**
 * Write Action Category out to wide output stream
 * @param wos Wide output stream (such as wcout)
 * @param ac Action Category to write out
 * @return Chainable wostream
 */
std::wostream& operator<<(std::wostream& wos, plushies::ActionCategory ac);

/**
 * Write Game Mode out to wide output stream
 * @param wos Wide output stream (such as wcout)
 * @param gm Game Mode to write out
 * @return Chainable wostream
 */
std::wostream& operator<<(std::wostream& wos, plushies::GameMode gm);

/**
 * Split a string at delimiters
 * @param s String to be split
 * @param delim Delimiter to split at
 * @return std::vector of split strings
 */
std::vector<std::string> split(const std::string& s, char delim);


/**
 * Encode int choice to string for lan communication
 * @param c Choice to be encoded
 * @return Encoded choice ready for send
 */
std::string encodeChoice(int c);

/**
 * Decode choice from lan communication for internal server use
 * @param c String to decode
 * @return Decoded choice
 */
int decodeChoice(const char* c);

#endif //PLUSHIES_COMMON_H
