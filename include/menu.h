//
// Created by zsotroav on 2024-04-09.
//

#ifndef PLUSHIES_MENU_H
#define PLUSHIES_MENU_H

#include "common.h"

/**
 * @brief Handle all of the main menu and initialization
 * @param gm Output GameMode value
 * @param cnt Output Plush count value
 * @param opp Output Opponent selection
 */
void menu(plushies::GameMode& gm, int& cnt, plushies::EnemyMode& opp);

/**
 * @brief Write the main menu header (logo and welcome message)
 */
void writeMainHeader();

/**
 * @brief Ask the player to select the game mode
 * @return Selected game mode
 */
plushies::GameMode modeSelect();

/**
 * @brief Ask the player to select the number of plushes to use
 * @return The number of plushes selected (1-3) <br> -1 for invalid selection
 */
int plushCountSelect();

/**
 * @brief Ask the player to choose their opponent (AI or LAN play mode)
 * @return 1 - AI <br> 2 - LAN <br> -1 - Invalid selection
 */
int opponentSelect();

#endif //PLUSHIES_MENU_H
