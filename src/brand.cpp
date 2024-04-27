//
// Created by zsotroav on 2024-03-24.
//

#include "brand.h"
#include "common.h"

using namespace plushies;

Brand::Brand(string name, const Type base, const Type secondary,
             const int *baseStats) : name(std::move(name)),
             baseType(base), secondaryType(secondary) {
    for (int i = 0; i < 6; ++i)  this->baseStats[i] = baseStats[i];
}