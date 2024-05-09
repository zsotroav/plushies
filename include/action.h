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

        string getName() const { return name; }
        int getDamage() const { return damage; }
        int getAccuracy() const { return accuracy; }
        int getEnergy() const { return energy; }
        int getMaxEnergy() const { return maxEnergy; }
        void decEnergy() { energy -= 1; }
        double getPriority() const { return priority; }
        ActionCategory getCategory() const { return category; }
        Type getType() const { return type; }

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
