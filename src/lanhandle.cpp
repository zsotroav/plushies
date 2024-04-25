//
// Created by zsotroav on 2024-04-25.
//

#include "lanhandle.h"

#include "common.h"
#include "nyetwork.h"
#include "server.h"
#include "memtrace.h"

using namespace plushies::lanplay;
using namespace plushies;


void Connection::sendPSYN(const Server& s, Plush &plush) const {
    stringstream ss;
    ss << "PSYN " << plush.getBrand().getName() << " ";

    for (int i = 0; i < 6; ++i)
        ss << plush.getUV(static_cast<StatOrder>(i)) << " ";

    ss << plush.getHP() << " ";

    for (int i = 0; i < 4; ++i) {
        if (plush.Actions[i] == NullAction) { ss << "-1"; continue; }

        for (int j = 0; j < s.actions.size(); ++j) {
            if (s.actions[j].getName() != plush.Actions[i].getName()) continue;
            ss << j << " ";
            break;
        }
    }

    sen(ss);
}

Plush Connection::recPSYN(Server &s) const {
    // PSYN <BRAND NAME> <PLUSH UVs> <HP> <MOVE IDs>
    // PSYN Blahaj 63 63 63 63 63 63 200 -1 -1 -1 -1
    char buff[64] = { 0 };
    rec(buff, sizeof(buff), 0);

    // Split received data
    auto row = split(buff, ' ');

    // We want PSYN and can't deal with anything else
    if (row.size() != 13 || row[0] != "PSYN")
        throw std::invalid_argument("nop");

    // Init temporary brand
    int brand = 0;

    // Find actual brand
    for (int i = 0; i < s.brands.size(); ++i) {
        if (s.brands[i].getName() != row[1]) continue;
        brand = i;
        break;
    }

    // Create array for Unique Values
    int uv[] = { stoi(row[2]), stoi(row[3]), stoi(row[4]),
                 stoi(row[5]), stoi(row[6]), stoi(row[7]) };

    // Create array for Actions with invalid actions
    Action ac[4] = {NullAction, NullAction, NullAction, NullAction};

    // Get the Action from index, only replace NullActions if needed
    for (int i = 0; i < 4; ++i) {
        if (row[9+i] == "-1") continue;
        ac[i] = s.actions[stoi(row[9+i])];
    }

    // Create plush and set HP to what was received
    auto p = Plush(s.brands[brand], uv, ac);
    p << p.getHP() - stoi(row[8]);

    return p;
}

ConnStatus ServerConnection::connect(Server& server) {
    auto player = server.getPlayer(1);
    // Get connection request
    // CONN <VERSION> <GAME MODE> <PLUSH COUNT>
    char buffer[16] = { 0 };

    stringstream ss;
    ss << "CONN " << LANPROTOCOL << " " << server.getGameMode()
       << " " << player->numPlushes();
    rec(buffer, sizeof(buffer), 0);
    sen("CACK", 4, 0);

    if (strcmp(ss.str().c_str(), buffer) != 0) {
        // TODO: Prompt manual check
        sen("CDEN", 4, 0);
        return DISCONNECTED;
    }

    sen("CACC", 4, 0);

    // PSYN - Plush Sync

    for (int i = 0; i < player->numPlushes(); ++i)
        sendPSYN(server, player->getPlushes()[i]);

    Player* dummy = new Player();

    // TODO: Actual number sync
    for (int i = 0; i < player->numPlushes(); ++i) {
        auto p = recPSYN(server);
        dummy->addPlush(p);
    }

    server.RegisterPlayer(dummy);

    return CONNECTED;
}

ConnStatus ClientConnection::connect(Server& server) {
    auto player = server.getPlayer(1);
    // Send connection request
    // CONN <VERSION> <GAME MODE> <PLUSH COUNT>
    stringstream ss;
    ss << "CONN " << LANPROTOCOL << " " << server.getGameMode()
       << " " << player->numPlushes();
    sen(ss);

    char buff[8] = { 0 };
    rec(buff, 8, 0); // CACK
    rec(buff, 8, 0); // CACC/CDEN

    if (strcmp(buff, "CACC") != 0) return DISCONNECTED;

    // PSYN - Plush Sync

    Player* dummy = new Player();

    // TODO: Actual number sync
    for (int i = 0; i < player->numPlushes(); ++i)
        dummy->addPlush(recPSYN(server));

    for (int i = 0; i < player->numPlushes(); ++i)
        sendPSYN(server, player->getPlushes()[i]);

    server.RegisterPlayer(dummy);

    return CONNECTED;
}

