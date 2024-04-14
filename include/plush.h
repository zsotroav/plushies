//
// Created by zsotroav on 2024-03-22.
//
#ifndef PLUSHIES_PLUSH_H
#define PLUSHIES_PLUSH_H

#include <string>
#include "action.h"
#include "brand.h"
#include "common.h"

using std::string;

namespace plushies {

    class Plush {
        Brand& brand; //!< ID of plush's brand
        int UV[6];    //!< Unique Values for plush
        int health;   //!< Current health value
        int maxhp;    //!< Max possible hp

    public:
        // Public members
        Action* Actions[4];


        /// Getters
        [[nodiscard]] inline std::string getName() const { return brand.getName(); }
        [[nodiscard]] inline Brand& getBrand() const { return brand; }
        [[nodiscard]] inline int getHP() const { return health; }
        [[nodiscard]] inline int getMaxHP() const { return maxhp; }
        [[nodiscard]] inline int getUV(StatOrder uvo) const { return UV[uvo]; }

        /// Functions
        int validMoves() const;

        int calcDamage(Action* act);
        int calcDamage(int actionId);

        int calcSpeed(Action* act);
        int calcSpeed(int actionId);

        /// Operators

        /**
         * @brief Get damage of executed action
         * @param act Pointer to action
         * @return Damage before type effectiveness calculations
         */
        ActionContext operator>>(Action* act);

        /**
         * @brief Get damage of executed action
         * @param actionId Executed Action's slot number
         * @return Damage before type effectiveness calculations
         */
        ActionContext operator>>(int actionId);

        /**
         * @brief Apply exact amount of damage to Plush
         * @param hp Exact number of health points to remove
         */
        void operator<<(int hp);

        /**
         * @brief Apply damage based on context
         * @param damage damage context to use
         */
        void operator<<(ActionContext damage);



        /// Ctor
        Plush(Brand& brand, const int UV[6], Action* actions[4]);
    };
}

/**
 * @brief Get exact amount of damage dealt by an Action context on a plush
 * @param lhs Action Context attacking the plush
 * @param rhs Plush being attacked
 * @return Damage after all defense and type calculations.
 */
int operator>>(const plushies::ActionContext& lhs,
               const plushies::Plush& rhs);


#endif //PLUSHIES_PLUSH_H
