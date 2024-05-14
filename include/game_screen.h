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
 * Print the main game screen
 */
void printScreen();

/**
 * Update displayed plush information
 * @param p Plush to grab details from
 * @param foe Indicate if it is the foe or the player
 */
void updatePlush(const plushies::Plush& p, bool foe = false);

/**
 * Update the Action info on the UI
 * @param a Action to display
 */
void updateActionInfo(const plushies::Action &a);

/**
 * Update selected item display on the UI
 * @param item Display name of selected item
 * @param id ID (spot) of selected item
 * @param highlight Highligt or reset item
 */
void updateSelection(const std::string& item, int id, bool highlight = false);

/**
 * Write a list of available options to the select menu on the UI
 * @param list List of items (max 4)
 * @throws std::out_of_range too many items are to be displayed (max 4)
 */
void printList(const std::vector<std::string>& list);

/**
 * Write out the actions of the plush and prompt the player to choose one
 * @param p Plush to grab actions from
 * @return Choice id (0-4)
 */
int chooseAction(const plushies::Plush& p);

/**
 * Write out the available plushies and prompt the player to choose one
 * @param p Player to grab plushies from
 * @return Choice id (0-3)
 */
int choosePlush(const plushies::Player& p);

/**
 * Ask player to choose their turn's action (move)
 * @param player Player to grab all data from
 * @return Final choice
 */
int chooseMove(const plushies::Player& player);

#endif //PLUSHIES_GAME_SCREEN_H
