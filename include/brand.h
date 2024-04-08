//
// Created by zsotroav on 2024-03-24.
//

#ifndef PLUSHIES_BRAND_H
#define PLUSHIES_BRAND_H

#include <string>
#include "common.h"

using std::string;

namespace plushies {
    class Brand {
        string name;
        type baseType;
        type secondaryType;
        int baseStats[6];

    public:
        // Getters
        string getName();
        type getBaseType();
        type getSecondaryType();
        int getBaseStat(StatOrder stat);

        // ctor
        Brand(string name, type base, type secondary, const int baseStats[6]);
    };
}

#endif //PLUSHIES_BRAND_H
