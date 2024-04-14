//
// Created by zsotroav on 2024-04-11.
//

#ifndef PLUSHIES_MENU_PLUSH_CREATE_H
#define PLUSHIES_MENU_PLUSH_CREATE_H

#include "action.h"
#include "brand.h"
#include "common.h"
#include "player.h"
#include "plush.h"
#include "server.h"


namespace plushies {
    Plush menuPlushCreate(Server& s, bool detailed);
}


#endif //PLUSHIES_MENU_PLUSH_CREATE_H