//
// Created by zsotroav on 2024-03-24.
//

#ifndef PLUSHIES_PLAYER_H
#define PLUSHIES_PLAYER_H

#include <vector>
#include "common.h"
#include "plush.h"


namespace plushies {

    class Player {

    protected:
        std::vector<Plush> plushes;
        int activePlush;

    public:
        void addPlush(Plush p);
        int numPlushes(bool alive = false);
        /**
         * @brief Request Action from the player
         * @returns Negative : Swap plushes (to index of abs value) <br>
         * 0 : Forefit <br> 1-4 index of selected move  
         */
        virtual int ready(const Plush& opponent);

        inline Plush& active() { return plushes[activePlush]; }
        inline Action* activeAction(int id) { return active().Actions[id]; }

        Player() : activePlush(0) {}
    };

} // plushies

#endif //PLUSHIES_PLAYER_H
