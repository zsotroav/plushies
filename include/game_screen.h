//
// Created by zsotroav on 2024-04-14.
//

#ifndef PLUSHIES_GAME_SCREEN_H
#define PLUSHIES_GAME_SCREEN_H

#include <string>
#include <vector>
#include "action.h"
#include "plush.h"
#include "player.h"

/**
 * @brief Print the main game screen
 */
void printScreen();

/**
 * @brief Update displayed plush information
 * @param p Plush to grab details from
 * @param foe Indicate if it is the foe or the player
 */
void updatePlush(const plushies::Plush& p, bool foe = false);

void updateActionInfo(const plushies::Action &a);

void updateSelection(const std::string& item, int id, bool highlight = false);

void printList(const std::vector<std::string>& list);

int chooseAction(const plushies::Plush& p);

int choosePlush(const plushies::Player& p);

int chooseMove(const plushies::Player& player);

#endif //PLUSHIES_GAME_SCREEN_H
