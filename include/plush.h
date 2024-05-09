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
        std::vector<Action> Actions;

        /// Getters
        [[nodiscard]] inline std::string getName() const { return brand.getName(); }
        [[nodiscard]] inline Brand& getBrand() const { return brand; }
        [[nodiscard]] inline int getHP() const { return health; }
        [[nodiscard]] inline int getMaxHP() const { return maxhp; }
        [[nodiscard]] inline int getUV(const StatOrder uvo) const { return UV[uvo]; }

        /// Functions
        int validMoves() const;

        int calcDamage(const Action& act) const;
        int calcDamage(int actionId) const;

        static void validateACThrow(const Action& act);
        void validateACThrow(const int actId) const { validateACThrow(Actions[actId]); }

        static bool validateAC(const Action& act);
        bool validateAC(const int actId) const { return validateAC(Actions[actId]); }

        ActionContext getAC(const Action& act) const
        { return {calcDamage(act), calcSpeed(act), act.getType(), act.getCategory()}; }
        ActionContext getAC(const int actId) const
        { return getAC(Actions[actId]); }

        ActionContext getSafeAC(const Action& act) const;
        ActionContext getSafeAC(const int actId) const
        { return getSafeAC(Actions[actId]); }

        int calcSpeed(const Action& act) const;
        int calcSpeed(int actionId) const;

        /// Operators

        /**
         * @brief Get damage of executed action
         * @param act Pointer to action
         * @return Damage before type effectiveness calculations
         */
        ActionContext operator>>(Action& act) const;

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
        Plush(Brand& brand, const int UV[6], Action actions[4]);
    };
}

/**
 * @brief Get exact amount of damage dealt by an Action context on a plush
 * @param damage Action Context attacking the plush
 * @param target Plush being attacked
 * @return Damage after all defense and type calculations.
 */
int operator>>(const plushies::ActionContext& damage,
               const plushies::Plush& target);


#endif //PLUSHIES_PLUSH_H
