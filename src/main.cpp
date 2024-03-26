#include <iostream>
#include "plush.h"
#include "memtrace.h"
#include "server.h"

using namespace plushies;


int main() {
    std::cout << "Hello, World!" << std::endl;




    std::cout << (type::GRASS >> type::WATER) << std::endl;

    Action *ac1 = new Action("a", 50, 100, 1, type::WATER, ActionCategory::Physical);
    Action *ac2 = new Action("b", 10, 100, 2, type::NORMAL, ActionCategory::Physical);

    int st[] = {100, 90, 45, 45, 90, 60 };
    Brand br = Brand(1, "Blahaj", type::WATER, type::NONE, st);

    int uv[] = {63, 40, 45, 20, 32, 10};
    Action* actions[] = { ac1, ac2, nullptr, nullptr};
    Plush pl = Plush(br, uv, actions);

    Player p0, p1;
    p0.addPlush(pl);
    p1.addPlush(pl);

    Server s = Server(p0, p1);

    s.serverLoop();

    std::cout << "HP before: " << pl.getHP() << std::endl;

    auto dmg = pl >> 1;

    pl << dmg;

    std::cout << "HP after: " << pl.getHP() << std::endl;

    delete ac1;
    delete ac2;

    return 0;
}
