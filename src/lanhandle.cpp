//
// Created by zsotroav on 2024-04-25.
//

#include "lanhandle.h"

#include "common.h"
#include "nyetwork.h"
#include "server.h"

#include "memtrace.h"
#include "menu_lanconf.h"

using namespace plushies::lanplay;
using namespace plushies;


void Connection::sendPSYN(const Server& s, const Plush &plush) const {
    stringstream ss;
    ss << "PSYN " << plush.getBrand().getName() << " ";

    for (int i = 0; i < 6; ++i)
        ss << plush.getUV(static_cast<StatOrder>(i)) << " ";

    ss << plush.getHP() << " ";

    for (int i = 0; i < 4; ++i) {
        if (plush.Actions[i] == NullAction) { ss << "-1"; continue; }

        for (size_t j = 0; j < s.actions.size(); ++j) {
            if (s.actions[j].getName() != plush.Actions[i].getName()) continue;
            ss << j << " ";
            break;
        }
    }

    sen(ss);
}

Plush Connection::recPSYN(Server &s) const {
    // PSYN <BRAND NAME> <PLUSH UVs> <HP> <MOVE IDs>
    // PSYN Blahaj 63 63 63 63 63 63 200 -1 -1 -1 -1   <-- Example
    char buff[64] = { 0 };
    rec(buff, sizeof(buff), 0);

    // Split received data
    const auto row = split(buff, ' ');

    // We want PSYN and can't deal with anything else
    if (row.size() != 13 || row[0] != "PSYN")
        throw std::invalid_argument("Didn't receive PSYN");

    // Init temporary brand
    int brand = 0;

    // Find actual brand
    for (size_t i = 0; i < s.brands.size(); ++i) {
        if (s.brands[i].getName() != row[1]) continue;
        brand = i;
        break;
    }

    // Create array for Unique Values
    const int uv[] = { stoi(row[2]), stoi(row[3]), stoi(row[4]),
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

bool ServerConnection::connect(Server& server) {
    const auto player = server.getPlayer(1);
    // Get connection request
    // CONN <VERSION> <GAME MODE> <PLUSH COUNT>
    char buffer[16] = { 0 };

    stringstream ss;
    ss << "CONN " << LANPROTOCOL << " " << server.getGameMode()
       << " " << player->numPlushes();
    rec(buffer, sizeof(buffer), 0);
    sen("CACK");

    const auto spl = split(ss.str(), ' ');

    stringstream ver;
    ver << LANPROTOCOL;
    int pc = player->numPlushes();

    if (strcmp(ss.str().c_str(), buffer) != 0) {
        // If it is not a connection request or the version is incorrect
        if (spl.size() != 4 || spl[0] != "CONN" || spl[1] != ver.str()) return false;

        pc = stoi(spl[3]);
        if (!lanConfirm(pc, stoi(spl[2]))) { sen("CDEN"); return false; }
    }

    // Anything that isn't an accept is good as a deny
    ss.clear();
    ss << "CACC " << player->numPlushes();

    sen(ss);

    // PSYN - Plush Sync
    for (int i = 0; i < player->numPlushes(); ++i)
        sendPSYN(server, player->getPlushes()[i]);

    Player* dummy = new Player();

    for (int i = 0; i < pc; ++i)
        dummy->addPlush(recPSYN(server));

    // Register synced dummy player to the server
    server.RegisterPlayer(dummy);

    // Connection established and game is ready
    return true;
}

bool ClientConnection::connect(Server& server) {
    const auto player = server.getPlayer(1);
    // Send connection request
    // CONN <VERSION> <GAME MODE> <PLUSH COUNT>
    stringstream ss;
    ss << "CONN " << LANPROTOCOL << " " << server.getGameMode()
       << " " << player->numPlushes();
    sen(ss);

    char buff[8] = { 0 };
    rec(buff, 8, 0); // CACK
    rec(buff, 8, 0); // CACC/CDEN

    auto spl = split(buff, ' ');

    // Anything that isn't an accept is good as a deny
    if (spl[0]!= "CACC") return false;

    Player* dummy = new Player();

    // PSYN - Plush Sync

    for (int i = 0; i < stoi(spl[1]); ++i)
        dummy->addPlush(recPSYN(server));

    for (int i = 0; i < player->numPlushes(); ++i)
        sendPSYN(server, player->getPlushes()[i]);

    // Register synced dummy player to the server
    server.RegisterPlayer(dummy);

    // Connection established and game is ready
    return true;
}

void ClientConnection::ActionReady() {
    char buff[8] = { 0 };
    while (strcmp(buff, "ARDY") != 0) rec(buff, sizeof(buff), 0);
}

int ClientConnection::SyncActions(const int myChoice) {
    char buff[8] = { 0 };

    sen(encodeChoice(myChoice));
    rec(buff, sizeof(buff), 0);
    return decodeChoice(buff);
}

void ServerConnection::ActionReady() { sen("ARDY"); }

int ServerConnection::SyncActions(const int myChoice) {
    char buff[8] = { 0 };

    rec(buff, sizeof(buff), 0);
    sen(encodeChoice(myChoice));
    return decodeChoice(buff);
}
