//
// Created by zsotroav on 2024-03-23.
//

#include <stdexcept>
#include <cmath>
#include "common.h"
#include "plush.h"

using plushies::ActionContext;
using namespace plushies;



/// Ctor

Plush::Plush(Brand& brand, const int UV[6],
                       Action *actions[4]): brand(brand) {
    for (int i = 0; i < 6; ++i) {
        if (UV[i] > 63 || UV[i] < 0)
            throw std::invalid_argument("Invalid UV value");
        this->UV[i] = UV[i];
    }

    health = floor(0.75 * (2*(this->brand.getBaseStat(HP)) + UV[HP]) + 50);

    this->Actions[0] = actions[0];
    this->Actions[1] = actions[1];
    this->Actions[2] = actions[2];
    this->Actions[3] = actions[3];
}


/// Functions

int Plush::validMoves() const {
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (Actions[i] == nullptr ||
            Actions[i]->getType() == NONE)
            continue;
        cnt++;
    }
    return cnt;
}

int Plush::calcDamage(Action* act) {
    // TODO: Accuracy and random variation

    int lvl = 50;
    auto cat = act->getCategory() == Physical ? Atk : SpA;
    auto type = act->getType();
    return floor(
            (
                    (((2.0*lvl)/8 + 5) * // Base power multiplier
                     act->getDamage() *   // Base power
                     brand.getBaseStat(cat) * // Stat multiplier
                     ((double) UV[cat] / 120 + 1)) // UV multiplier
            ) / 20 // Move base power

            * // Same Type Attack Bonus
            (type == brand.getBaseType() ||
             type == brand.getSecondaryType() ? 1.5 : 1)
    );
}

int Plush::calcDamage(int actionId) {
    if (actionId > 3) throw std::invalid_argument("Invalid move");
    return calcDamage(Actions[actionId]);
}

int Plush::calcSpeed(Action* act) {
    return floor(brand.getBaseStat(StatOrder::Spe) *
           (UV[StatOrder::Spe] / 120.0 + 1) *
           act->getPriority());
}

int Plush::calcSpeed(int actionId) {
    if (actionId > 3) throw std::invalid_argument("Invalid move");
    return calcSpeed(Actions[actionId]);
}

/// Operators

ActionContext Plush::operator>>(Action* act) {
    if (act == nullptr) throw std::invalid_argument("Invalid move");
    int dmg = calcDamage(act);
    int spd = calcSpeed(act);

    return {dmg, spd, act->getType(), act->getCategory()};
}

ActionContext Plush::operator>>(int actionId) {
    if (actionId > 3) throw std::invalid_argument("Invalid move");
    return *this >> this->Actions[actionId];
}

void Plush::operator<<(int hp) { health -= hp; }

void Plush::operator<<(ActionContext damage) {
    *this << (damage >> *this);
}

int operator>>(const ActionContext& damage, const Plush& target) {
    auto cat = damage.category == Physical ? Def : SpD;
    auto brand = target.getBrand();
    return floor(damage.damage *
                 (damage.type >> brand.getBaseType()) *
                 (damage.type >> brand.getSecondaryType())

                 /

                 (brand.getBaseStat(cat) *
                 (target.getUV(cat) / 120.0 + 1))
    );

}
