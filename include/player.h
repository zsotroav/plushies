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
        /**
         * Add a plush to the player
         * @param p plush to ad
         */
        void addPlush(const Plush &p);

        /**
         * Set a different plush active (when swapping)
         * @param i ID of plush to set active
         */
        void setActive(int i);

        /**
         * Set the next alive plush active
         */
        void nextAlive();

        /**
         * Get the number of plushes of the player
         * @param alive Count dead ones or only alive ones
         * @return Number of plushes
         */
        int numPlushes(bool alive = false);

        /**
         * @brief Request Action from the player
         * @returns Negative : Swap plushes (to index of abs value) <br>
         * 0 : Forefit <br> 1-4 index of selected move <br> negative 1-4 selected plush
         */
        virtual int ready(const Plush& opponent);

        /**
         * Get the plushes of the player
         * @return Array of plushes of the player
         */
        std::vector<Plush> getPlushes() const { return plushes; }

        /**
         * Get the currently active plush
         * @return Currently active plush
         */
        Plush getActivePlush() const { return plushes[activePlush]; }

        /**
         * Get an action of the current plush
         * @param id ID of action to get
         * @return The action
         */
        Action activeAction(const int id) const { return getActivePlush().Actions[id]; }

        Player() : activePlush(0) {}

        virtual ~Player() = default;
    };

} // plushies

#endif //PLUSHIES_PLAYER_H
