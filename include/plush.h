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
        std::vector<Action> Actions; //!< Actions of this specific plush

        /// Getters
        std::string getName() const { return brand.getName(); } //!< Get the name of the plush
        Brand& getBrand() const { return brand; } //!< Get the brand of the plush
        int getHP() const { return health; } //!< Get the current HP
        int getMaxHP() const { return maxhp; } //!< Get the max possible HP
        /**
         * Get a specific UV (Unique Value)
         * @param uvo StatOrder for the UV to get
         * @return Selected UV
         */
        int getUV(const StatOrder uvo) const { return UV[uvo]; }

        /// Functions
        int validMoves() const; //!< Get the number of valid moves

        /**
         * Get the damage dealt by a move
         * @param act Action to use for calculations
         * @return The damage the move will deal before defense calculations
         */
        int calcDamage(const Action& act) const;

        /**
         * Get the damage dealt by a move from the move ID
         * @param actionId Action to use for calculations
         * @return The damage the move will deal before defense calculations
         */
        int calcDamage(int actionId) const;

        /**
         * Check if action can be used
         * @param act Action to check
         * @throws std::invalid_argument if the move is invalid
         * @throws FailedAction if the the move is out of energy or accuracy failed
         */
        static void validateACThrow(const Action& act);

        /**
         * Check if action can be used
         * @param actId Action to check
         * @throws std::invalid_argument if the move is invalid
         * @throws FailedAction if the the move is out of energy or accuracy failed
         */
        void validateACThrow(const int actId) const { validateACThrow(Actions[actId]); }


        /**
         * Check if action can be used
         * @param act Action to check
         * @return Boolean can/can't be used
         */
        static bool validateAC(const Action& act);

        /**
         * Check if action can be used
         * @param actId Action to check
         * @return Boolean can/can't be used
         */
        bool validateAC(const int actId) const { return validateAC(Actions[actId]); }

        /**
         * Get an Action Context for a move
         * @param act Action to use
         * @return Calculated Action context from plush pov
         * @throws std::invalid_argument invalid move
         */
        ActionContext getAC(const Action& act) const
        { return {calcDamage(act), calcSpeed(act), act.getType(), act.getCategory()}; }

        /**
         * Get an Action Context for a move
         * @param actId Action to use
         * @return Calculated Action context from plush pov
         * @throws std::invalid_argument invalid move
         */
        ActionContext getAC(const int actId) const
        { return getAC(Actions[actId]); }

        /**
         * Get an Action Context for a move with move validation
         * @param act Action to use
         * @return Calculated Action context from plush pov
         * @throws std::invalid_argument if the move is invalid
         * @throws FailedAction if the the move is out of energy or accuracy failed
         */
        ActionContext getSafeAC(const Action& act) const;

        /**
         * Get an Action Context for a move with move validation
         * @param actId Action to use
         * @return Calculated Action context from plush pov
         * @throws std::invalid_argument if the move is invalid
         * @throws FailedAction if the the move is out of energy or accuracy failed
         */
        ActionContext getSafeAC(const int actId) const
        { return getSafeAC(Actions[actId]); }

        /**
         * Calculate the speed of the action
         * @param act Action to use
         * @return Calculated speed based on action priority
         * @throws std::invalid_argument invalid move
         */
        int calcSpeed(const Action& act) const;

        /**
         * Calculate the speed of the action
         * @param actionId Action to use
         * @return Calculated speed based on action priority
         * @throws std::invalid_argument invalid move
         */
        int calcSpeed(int actionId) const;

        /// Operators

        /**
         * @brief Get damage of executed action
         * @param act Pointer to action
         * @return Damage before type effectiveness calculations
         * @throws std::invalid_argument invalid move
         */
        ActionContext operator>>(Action& act) const;

        /**
         * @brief Get damage of executed action
         * @param actionId Executed Action's slot number
         * @return Damage before type effectiveness calculations
         * @throws std::invalid_argument invalid move
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


        /**
         * Ctor for Plushies
         * @param brand Brand of the plush
         * @param UV Unique values of the plush
         * @param actions Actions for the plush
         * @throws std::invalid_argument Invalid UV value
         */
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
