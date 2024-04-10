//
// Created by zsotroav on 2024-03-24.
//

#include <random>
#include <thread>
#include <chrono>
#include "common.h"

int random(int a, int b) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(a, b);
    int mean = uniform_dist(e1);
    return mean;
}

double operator>>(plushies::type attacker, plushies::type target) {
    if (attacker == plushies::NONE || target == plushies::NONE) return 1;
    return plushies::relationChart[attacker-1][target-1];
}