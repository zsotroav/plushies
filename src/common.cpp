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

std::wostream& operator<<(std::wostream& wos, const Type type) {
    switch (type) {
        case NONE:     return wos << "NONE    ";
        case NORMAL:   return wos << "NORMAL  ";
        case FIRE:     return wos << "FIRE    ";
        case WATER:    return wos << "WATER   ";
        case GRASS:    return wos << "GRASS   ";
        case ELECTRIC: return wos << "ELECTRIC";
        case FIGHTING: return wos << "FIGHTING";
        case FLYING:   return wos << "FLYING  ";
        case ROCK:     return wos << "ROCK    ";
        case GHOST:    return wos << "GHOST   ";
    }
    return wos;
}

std::wostream& operator<<(std::wostream& wos, const GameMode gm) {
    switch(gm) {
        case RANDOM: return wos << "Random";
        case CUSTOM: return wos << "Custom";
        case DETAIL: return wos << "Detailed custom";
        default:     return wos << "??";
    }
}

std::wostream& operator<<(std::wostream& wos, const ActionCategory ac) {
    switch (ac) {
        case Physical: return wos << "PHYSICAL";
        case Special:  return wos << "SPECIAL ";
    }
    return wos;
}

std::vector<std::string> split(const std::string& s, const char delim) {
    std::string word;
    std::vector<std::string> row;
    std::stringstream ss(s);
    while (std::getline(ss, word, delim)) row.push_back(word);
    return row;
}
