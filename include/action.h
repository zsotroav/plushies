//
// Created by zsotroav on 2024-03-24.
//

#ifndef PLUSHIES_ACTION_H
#define PLUSHIES_ACTION_H

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

        inline string getName() const { return name; }
        inline int getDamage() const { return damage; }
        inline int getAccuracy() const { return accuracy; }
        inline double getPriority() const { return priority; }
        inline ActionCategory getCategory() const { return category; }
        inline plushies::type getType() const { return type; }

        Action(string name, int dam, int acc, double pri, plushies::type typ,
               ActionCategory cat);
    };
}

#endif //PLUSHIES_ACTION_H
