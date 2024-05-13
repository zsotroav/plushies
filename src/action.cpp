//
// Created by zsotroav on 2024-03-24.
//

#include <utility>
#include "action.h"

#include <stdexcept>

using namespace plushies;


/// Constructors

Action::Action(string name, const int dam, const int acc, const int en,
               const double pri, const Type typ, const ActionCategory cat):
               name(std::move(name)), damage(dam),
               energy(en), maxEnergy(en), priority(pri), type(typ),
               category(cat) {
    if (acc > 100 || acc < 0) throw std::invalid_argument("Invalid accuracy");
    this->accuracy = acc;
}

bool Action::operator==(const Action& rhs) const {
     return name == rhs.name && damage == rhs.damage && accuracy == rhs.accuracy;
}
