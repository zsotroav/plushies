//
// Created by zsotroav on 2024-04-11.
//

#ifndef PLUSHIES_MENU_PLUSH_CREATE_H
#define PLUSHIES_MENU_PLUSH_CREATE_H

#include "plush.h"
#include "server.h"


/**
 * Print plush create menu skeleton
 */
void printMPC();

/**
 * Print an item to the side selector
 * @param i ID of item
 * @param s String to show
 * @param highlight Highlight the choice
 */
void printDetail(int i, const std::string& s, bool highlight = false);

/**
 * Print details of a brand to the menu, this will highlight it in the side
 * selector as well
 * @param b Brand to grab details from
 * @param i ID for the side selector
 * @param highlight Highlight state for the side selector
 */
void printBrandDetail(const plushies::Brand& b, int i, bool highlight = false);

/**
 * Print details of the action to the menu, this will highlight it in the side
 * selector as well
 * @param a Action to grab details from
 * @param i ID for the side selector
 * @param highlight Highlight state for the side selector
 */
void printActionDetail(const plushies::Action* a, int i, bool highlight = false);

/**
 * Print all brands from the server to the menu
 * @param s Server to get the data from
 */
void printBrands(const plushies::Server& s);

/**
 * Print all actions a brand can learn
 * @param b Brand to get the data from
 */
void printActions(const plushies::Brand& b);

/**
 * Multi purpose selector function for asking the player to select a
 * brand/action for a brand
 * @param s Server to grab data from
 * @param brandid the brand ID to get Actions from, <0 for selecting brands
 * @return Selected brand or action from brand
*/
int selectItem(const plushies::Server& s, int brandid = -1);

namespace plushies {
    /**
     * Prompt player to create plush
     * @param s Server for brand/plush/action database
     * @param detailed Detailed mode
     * @return created plush
     */
    Plush menuPlushCreate(Server& s, bool detailed);
}


#endif //PLUSHIES_MENU_PLUSH_CREATE_H
