//
// Created by zsotroav on 2024-03-24.
//
#include "common.h"

double operator>>(plushies::type attacker, plushies::type target) {
    if (attacker == plushies::NONE || target == plushies::NONE) return 1;
    return plushies::relationChart[attacker-1][target-1];
}