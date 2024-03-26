//
// Created by zsotroav on 2024-03-24.
//

#include "brand.h"
#include "common.h"

using namespace plushies;

int Brand::getID() { return id; }
string Brand::getName() { return name; }
type Brand::getBaseType() { return baseType; }
type Brand::getSecondaryType() { return secondaryType; }
int Brand::getBaseStat(StatOrder stat) { return baseStats[stat]; }


plushies::Brand::Brand(int id, string name, plushies::type base,
                       plushies::type secondary, const int *baseStats) :
        id(id), name(std::move(name)), baseType(base), secondaryType(secondary) {
    for (int i = 0; i < 6; ++i) {
        this->baseStats[i] = baseStats[i];
    }
}