//
// Created by zsotroav on 2024-03-22.
//
#ifndef NHF_PLUSH_H
#define NHF_PLUSH_H

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

    public:
        // Public members
        Action* Actions[4];


        /// Getters
        int getBrandId();
        Brand& getBrand();
        int getHP();
        int getUV(StatOrder uvo);


        /// Functions
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


#endif //NHF_PLUSH_H
