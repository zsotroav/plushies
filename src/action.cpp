//
// Created by zsotroav on 2024-03-24.
//
#include "action.h"

using namespace plushies;

/// Getters

int Action::getDamage() { return damage; }
int Action::getAccuracy() { return accuracy; }
double Action::getPriority() { return priority; }
ActionCategory Action::getCategory() { return category; }
plushies::type Action::getType() { return type; }


/// Constructors

Action::Action(string name, int dam, int acc, double pri, plushies::type typ,
               plushies::ActionCategory cat): name(name), damage(dam),
               accuracy(acc), priority(pri), type(typ), category(cat) {}
