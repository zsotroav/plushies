//
// Created by zsotroav on 2024-04-25.
//

#include "lanhandle.h"

#include "common.h"
#include "nyetwork.h"

using namespace plushies::lanplay;
using namespace plushies;

ConnStatus ServerConnection::connect(const GameMode gm, const int plushcnt) {
    // Get connection request
    // CONN <VERSION> <GAME MODE> <PLUSH COUNT>
    char buffer[16] = { 0 };

    stringstream ss;
    ss << "CONN " << LANPROTOCOL << " " << gm << " " << plushcnt;
    rec(buffer, sizeof(buffer), 0);
    sen("CACK", 4, 0);

    if (strcmp(ss.str().c_str(), buffer) == 0) {
        sen("CACC", 4, 0);
        return CONNECTED;
    }

    // TODO: Prompt manual check


    return DISCONNECTED;
}

ConnStatus ClientConnection::connect(const GameMode gm, const int plushcnt) {
    // Send connection request
    // CONN <VERSION> <GAME MODE> <PLUSH COUNT>
    stringstream ss;
    ss << "CONN " << LANPROTOCOL << " " << gm << " " << plushcnt;
    sen(ss.str().c_str(), strlen(ss.str().c_str()), 0);

    char buff[8] = { 0 };
    rec(buff, 8, 0); // CACK
    rec(buff, 8, 0); // CACC/CDEN

    if (strcmp(buff, "CACC") == 0) return CONNECTED;
    return DISCONNECTED;
}

