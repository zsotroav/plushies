//
// Created by zsotroav on 2024-04-23.
//

#ifndef MENU_LANCONF_H
#define MENU_LANCONF_H

#include <string>

/**
 * Get and print IP Addresses of the computer
 */
void printIP();

/**
 * Open lan configuration menu
 * @param server Server to configure based on
 * @return IP to connect to
 */
string menuLanconf(bool server);

/**
 * Ask player to confirm if the connection is acceptable
 * @param numPlushes Number of plushies used by opponent
 * @param gameMode Game Mode of opponent
 * @return Accept/Deny of player
 */
bool lanConfirm(int numPlushes, int gameMode);

#endif //MENU_LANCONF_H
