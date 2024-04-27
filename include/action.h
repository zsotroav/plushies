//
// Created by zsotroav on 2024-03-24.
//

#ifndef PLUSHIES_ACTION_H
#define PLUSHIES_ACTION_H

#include <string>
#include "common.h"

using std::string;

namespace plushies {
    class Action {
        string name;
        int damage;
        int accuracy;
        int energy;
        int maxEnergy;
        double priority;
        Type type;
        ActionCategory category;
    public:
        /// Getters

        inline string getName() const { return name; }
        inline int getDamage() const { return damage; }
        inline int getAccuracy() const { return accuracy; }
        inline int getEnergy() const { return energy; }
        inline int getMaxEnergy() const { return maxEnergy; }
        inline void decEnergy() { energy -= 1; }
        inline double getPriority() const { return priority; }
        inline ActionCategory getCategory() const { return category; }
        inline plushies::Type getType() const { return type; }

        Action(string name, int dam, int acc, int en, double pri, Type typ,
               ActionCategory cat);

        bool operator==(const Action& rhs) const;
    };


    const Action NullAction = Action("Invalid", 0, 0, 0, 0, NONE, Physical);
}

class FailedAction : public std::exception {
    std::string message;

public:
    explicit FailedAction(const char * msg) : message(msg) {}
    FailedAction() : message("Action failed!") {}

    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};


#endif //PLUSHIES_ACTION_H
