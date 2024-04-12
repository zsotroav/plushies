//
// Created by zsotroav on 2024-03-24.
//

#include <utility>
#include "action.h"

using namespace plushies;


/// Constructors

Action::Action(string name, int dam, int acc, double pri, plushies::type typ,
               plushies::ActionCategory cat): name(std::move(name)), damage(dam),
               accuracy(acc), priority(pri), type(typ), category(cat) {}
