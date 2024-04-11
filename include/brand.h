//
// Created by zsotroav on 2024-03-24.
//

#ifndef PLUSHIES_BRAND_H
#define PLUSHIES_BRAND_H

#include <string>
#include <vector>
#include "action.h"
#include "common.h"

using std::string;

namespace plushies {
    class Brand {
        string name;
        type baseType;
        type secondaryType;
        int baseStats[6];

        std::vector<Action*> learnActions; //!< Learnable Actions 

    public:
        // Getters
        inline string getName() const {return name; }
        inline type getBaseType() const { return baseType; }
        inline type getSecondaryType() const { return secondaryType; }
        inline int getBaseStat(const StatOrder stat) const { return baseStats[stat]; }

        inline int baseStatTotal() const { 
            return baseStats[0] + baseStats[1] + baseStats[2] + 
                   baseStats[3] + baseStats[4] + baseStats[5];
        }

        inline std::vector<Action*> getLearnableActions() const { return learnActions; }

        /// Setters
        inline void addLearnableAction(Action* ac) { learnActions.push_back(ac); }


        // ctor
        Brand(string name, type base, type secondary, const int baseStats[6]);
    };
}

#endif //PLUSHIES_BRAND_H
