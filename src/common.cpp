//
// Created by zsotroav on 2024-03-24.
//

#include <codecvt>
#include <iostream>
#include <locale>
#include <random>
#include <string>

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

std::wstring convertUFT8(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(s);
}

std::string convertFromUFT8(const std::wstring& ws) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(ws);
}

std::wostream& operator<<(std::wostream& os, plushies::type type) {
    switch (type) {
        case plushies::NONE:     return os << "NONE    ";
        case plushies::NORMAL:   return os << "NORMAL  ";
        case plushies::FIRE:     return os << "FIRE    ";
        case plushies::WATER:    return os << "WATER   ";
        case plushies::GRASS:    return os << "GRASS   ";
        case plushies::ELECTRIC: return os << "ELECTRIC";
        case plushies::FIGHTING: return os << "FIGHTING";
        case plushies::FLYING:   return os << "FLYING  ";
        case plushies::ROCK:     return os << "ROCK    ";
        case plushies::GHOST:    return os << "GHOST   ";
    }
    return os;
}

std::wostream& operator<<(std::wostream& os, plushies::ActionCategory ac) {
    switch (ac) {
        case plushies::Physical: return os << "PHYSICAL";
        case plushies::Special:  return os << "SPECIAL ";
    }
    return os;
}

