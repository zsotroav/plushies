//
// Created by zsotroav on 2024-04-10.
//

#include <thread>
#include "overlord.h"
#include "common.h"

using namespace plushies::overlord;

int Clyde::ready(const Plush& opponent) {
    std::this_thread::sleep_for(std::chrono::seconds(random(5, 10)));

    return random(1, active().validMoves());
}

int maxminAction(plushies::Player& att,
                 const plushies::Plush& opponent,
                 bool maxmode = true) {

    int max = (att.active() >> 0) >> opponent;
    int mid = 1;

    for (int i = 1; i < 4; ++i) {
        if (att.activeAction(i) == nullptr ||
                att.activeAction(i)->getType() == plushies::type::NONE)
            continue;

        auto c = (att.active() >> i) >> opponent;
        if ((c < max && maxmode) || c > max && !maxmode) continue;
        if ((c == max &&
                att.activeAction(i)->getAccuracy() >
                        att.activeAction(mid)->getAccuracy())
            || (c > max && maxmode) || (c < max && !maxmode)) {
            max = c; mid = i;
        }
    }
    return mid;
}

int Ninty::ready(const Plush& opponent) {
    return maxminAction(*this, opponent);
}

int Waffles::ready(const plushies::Plush &opponent) {
    return maxminAction(*this, opponent, false);
}

int Muffins::ready(const plushies::Plush &opponent) {
    return maxminAction(*this, opponent, false);
}