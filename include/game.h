//
// Created by zsotroav on 2024-04-09.
//

#ifndef PLUSHIES_GAME_H
#define PLUSHIES_GAME_H


/**
 * Try to set the output mode to wide characters for compatibility with all
 * systems (for UI wide chars)
 * @return Success/Failiure
 */
bool setUnicodeMode();

/**
 * Test for terminal size and/or show warning screen if terminal size can't be
 * determined or is too small for the game
 */
void warningScreen();

/**
 * Initialize the game and all settings
 */
void gameInit();

#endif //PLUSHIES_GAME_H
