//
// Created by zsotroav on 2024-04-10.
//

#include <thread>
#include "common.h"
#include "overlord.h"
#include "server.h"

using namespace plushies::overlord;


int maxminAction(plushies::Player& att,
                 const plushies::Plush& opponent,
                 bool maxmode = true) {

    int max = 0;
    try { max = (att.active().getSafeAC(0)) >> opponent; }
    catch (...) { max = 0; }
    int mid = 0;

    for (int i = 1; i < 4; ++i) {
        if (att.activeAction(i).getType() == plushies::Type::NONE ||
                att.activeAction(i).getType() == plushies::Type::NONE)
            continue;

        int c = 0;
        try { c = (att.active().getSafeAC(i)) >> opponent; }
        catch (...) { c = 0; }
        if ((c < max && maxmode) || (c > max && !maxmode)) continue;
        if ((c == max &&
                att.activeAction(i).getAccuracy() >
                        att.activeAction(mid).getAccuracy())
            || (c > max && maxmode) || (c < max && !maxmode)) {
            max = c; mid = i;
        }
    }
    return mid + 1;
}


int Dennis::ready(const Plush&) {
    return random(1, active().validMoves()); 
}

int Clyde::ready(const Plush&) {
    std::this_thread::sleep_for(std::chrono::seconds(random(5, 10)));

    return random(1, active().validMoves());
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


Dennis::Dennis(Server& s, int count) {
    for (int i = 0; i < count; i++) addPlush(s.createRandomPlush());
}

Clyde::Clyde(Server& s, int count) {
    for (int i = 0; i < count; i++) addPlush(s.createRandomPlush());
}

Ninty::Ninty(Server& s, int count) {
    for (int i = 0; i < count; i++) addPlush(s.createRandomPlush(300, 50));
}

Waffles::Waffles(Server& s, int count) {
    for (int i = 0; i < count; i++) addPlush(s.createRandomPlush(300, 30, 50));
}

Muffins::Muffins(Server& s, int count) {
    for (int i = 0; i < count; i++) addPlush(s.createRandomPlush());
}