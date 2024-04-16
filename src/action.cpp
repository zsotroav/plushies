//
// Created by zsotroav on 2024-03-24.
//

#include <utility>
#include "action.h"

using namespace plushies;


/// Constructors

Action::Action(string name, int dam, int acc, int en, double pri,
               plushies::type typ,plushies::ActionCategory cat):
               name(std::move(name)), damage(dam), accuracy(acc),
               energy(en), maxEnergy(en), priority(pri), type(typ),
               category(cat) {}

bool Action::operator==(const Action& rhs) {
     return name == rhs.name && damage == rhs.damage && accuracy == rhs.accuracy;
}