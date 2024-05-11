//
// Created by zsotroav on 2024-03-24.
//

#include <codecvt>
#include <locale>
#include <random>
#include <sstream>
#include <string>

#include "common.h"

using namespace plushies;

int random(const int a, const int b) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(a, b);
    return uniform_dist(e1);
}

double operator>>(const Type attacker, const Type target) {
    if (attacker == NONE || target == NONE) return 1;
    return relationChart[attacker-1][target-1];
}

std::wstring convertUFT8(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(s);
}

std::string convertFromUFT8(const std::wstring& ws) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(ws);
}

std::wostream& operator<<(std::wostream& os, const Type type) {
    switch (type) {
        case NONE:     return os << "NONE    ";
        case NORMAL:   return os << "NORMAL  ";
        case FIRE:     return os << "FIRE    ";
        case WATER:    return os << "WATER   ";
        case GRASS:    return os << "GRASS   ";
        case ELECTRIC: return os << "ELECTRIC";
        case FIGHTING: return os << "FIGHTING";
        case FLYING:   return os << "FLYING  ";
        case ROCK:     return os << "ROCK    ";
        case GHOST:    return os << "GHOST   ";
    }
    return os;
}

std::wostream& operator<<(std::wostream& os, const GameMode gm) {
    switch(gm) {
        case RANDOM: return os << "Random";
        case CUSTOM: return os << "Custom";
        case DETAIL: return os << "Detailed custom";
        defualt:     return os << "??";
    }
}

std::wostream& operator<<(std::wostream& os, const ActionCategory ac) {
    switch (ac) {
        case Physical: return os << "PHYSICAL";
        case Special:  return os << "SPECIAL ";
    }
    return os;
}

std::vector<std::string> split(const std::string& s, const char delim) {
    std::string word;
    std::vector<std::string> row;
    std::stringstream ss(s);
    while (std::getline(ss, word, delim)) row.push_back(word);
    return row;
}
