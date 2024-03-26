//
// Created by zsotroav on 2024-03-24.
//

#ifndef _NHF_PLAYER_H
#define _NHF_PLAYER_H

#include <vector>
#include "common.h"
#include "plush.h"


namespace plushies {

    class Player {
        std::vector<Plush> plushes;

    public:
        void addPlush(Plush p);
        int numPlushes(bool alive = false);
        virtual int ready();
    };

} // plushies

#endif //_NHF_PLAYER_H
