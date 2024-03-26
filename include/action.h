//
// Created by zsotroav on 2024-03-24.
//

#ifndef NHF_ACTION_H
#define NHF_ACTION_H

#include "common.h"
#include <string>

using std::string;

namespace plushies {
    class Action {
        string name;
        int damage;
        int accuracy;
        double priority;
        type type;
        ActionCategory category;
    public:
        /// Getters

        int getDamage();
        int getAccuracy();
        double getPriority();
        ActionCategory getCategory();
        plushies::type getType();

        Action(string name, int dam, int acc, double pri, plushies::type typ,
               ActionCategory cat);
    };
}

#endif //NHF_ACTION_H
