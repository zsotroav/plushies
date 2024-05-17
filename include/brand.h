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
        Type baseType;
        Type secondaryType;
        int baseStats[6]; //!< Base stat for the brand in standard StatOrder

        std::vector<Action*> learnActions; //!< Learnable Actions 

    public:
        /// Getters

        string getName() const {return name; }
        Type getBaseType() const { return baseType; }
        Type getSecondaryType() const { return secondaryType; }
        int getBaseStat(const StatOrder stat) const { return baseStats[stat]; }
        std::vector<Action*> getLearnableActions() const { return learnActions; }

        /**
         * Calculate the base stat total of the brand
         * @return The base stat total (sum of all six stats) of the brand
         */
        int baseStatTotal() const {
            return baseStats[0] + baseStats[1] + baseStats[2] +
                   baseStats[3] + baseStats[4] + baseStats[5];
        }

        /**
         * Add an Action to the brand's available actions
         * @param ac Pointer to Action in the server
         */
        void addLearnableAction(Action* ac);


        /**
         * Constructor
         * @param name Name of brand
         * @param base Base type
         * @param secondary Secondary type
         * @param baseStats Array of the Base Stats in standard StatOrder
         */
        Brand(string name, Type base, Type secondary, const int baseStats[6]);

        bool operator==(const Brand& rhs) const {
            // If this much matches the game is either configured terribly
            // or they are actually the same brand
            return name == rhs.name && baseType == rhs.baseType &&
                secondaryType == rhs.secondaryType &&
                baseStatTotal() == rhs.baseStatTotal();
        }
    };
}

#endif //PLUSHIES_BRAND_H
