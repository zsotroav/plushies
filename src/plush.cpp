//
// Created by zsotroav on 2024-03-23.
//

#include <cmath>
#include <stdexcept>
#include "common.h"
#include "plush.h"

using plushies::ActionContext;
using namespace plushies;



/// Ctor

Plush::Plush(Brand& brand, const int UV[6],
                       Action actions[4]): brand(brand) {
    for (int i = 0; i < 6; ++i) {
        if (UV[i] > 63 || UV[i] < 0)
            throw std::invalid_argument("Invalid UV value");
        this->UV[i] = UV[i];
    }

    maxhp = health = floor(0.75 * (2*(this->brand.getBaseStat(HP)) + UV[HP]) + 50);

    this->Actions = {Action(actions[0]), Action(actions[1]),
                     Action(actions[2]), Action(actions[3])};
}


/// Functions

int Plush::validMoves() const {
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (Actions[i].getType() == NONE)
            continue;
        cnt++;
    }
    return cnt;
}

int Plush::calcDamage(const Action& act) {
    int lvl = 50;
    auto cat = act.getCategory() == Physical ? Atk : SpA;
    auto type = act.getType();
    return floor(
            (
                    (((2.0*lvl)/8 + 5) * // Base power multiplier
                     act.getDamage() *   // Base power
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

int Plush::calcSpeed(const Action& act) {
    return floor(brand.getBaseStat(StatOrder::Spe) *
           (UV[StatOrder::Spe] / 120.0 + 1) *
           act.getPriority());
}

int Plush::calcSpeed(int actionId) {
    if (actionId > 3) throw std::invalid_argument("Invalid move");
    return calcSpeed(Actions[actionId]);
}

ActionContext Plush::getAC(const Action& act) {
    int dmg = calcDamage(act);
    int spd = calcSpeed(act);

    return {dmg, spd, act.getType(), act.getCategory()};
}

ActionContext Plush::getAC(const int actId) {
    return getAC(Actions[actId]);
}

ActionContext Plush::getSafeAC(const Action& act){
    if (act.getType() == NONE) throw std::invalid_argument("Invalid move");
    if (act.getEnergy() <= 0) throw std::invalid_argument("No more energy");
    return getAC(act);
}

ActionContext Plush::getSafeAC(const int actId) {
    return getSafeAC(Actions[actId]);
}

/// Operators

ActionContext Plush::operator>>(Action& act) {
    auto ac = getSafeAC(act);

    act.decEnergy();

    int ran = random(0,100);
    if (ran < act.getAccuracy()) throw FailedAction();

    return ac;
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
