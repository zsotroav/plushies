# Plush Monsters' Fight Club <br /> DEVELOPER'S DOCUMENTATION

## Table of contents
<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=3 orderedList=false} -->

<!-- code_chunk_output -->

- [Table of contents](#table-of-contents)
- [Legal & License](#legal--license)
- [About](#about)
- [Compiling](#compiling)
- [High-level overview](#high-level-overview)
  - [Files and folder structure](#files-and-folder-structure)
  - [Used external resources](#used-external-resources)
- [Files](#files)
  - [Action](#action)
  - [Brand](#brand)
  - [Common](#common)
  - [Game screen](#game-screen)
  - [Game](#game)
  - [Lanhandle](#lanhandle)
  - [Menu Lanconf](#menu-lanconf)
  - [Menu Plush Create](#menu-plush-create)
  - [Menu](#menu)
  - [Overlord](#overlord)
  - [Player](#player)
  - [Plush](#plush)
  - [Server](#server)

<!-- /code_chunk_output -->

## Legal & License
Copyright (C) 2024  Zsombor Török

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

## About
Plush Monsters' Fight Club is a basic command-line turn-based battle system
emulator made as the big homework for the "Basics of Programming 2" course.

For more information, see the [spec.md](specification) or [plan.md](plan).

## Compiling
The project is intended for compiling with CMake. If compiled for debugging, memtrace will automatically be enabled and set to output in the `mem.trace` file.

To add additional compile definitions, define `BUILD` with the definitions to add.
- Define `CPORTA` to compile into test mode, where only the gtest_lite tests are run.
- Define `DEBUG_EXTRA` to show additional information while playing

## High-level overview

### Files and folder structure 
The project follows a simple folder structure with C source code in the 
`src` directory and related header files in the `include` directory.
```
plushies
├── src
|   ├── action.cpp            // Action (move) handling
|   ├── brand.cpp             // Plush brands
|   ├── common.cpp            // Common code used in multiple places
|   ├── game_screan.cpp       // Main gameplay screen
│   ├── game.cpp              // Gameplay (frontend) handle logic
|   ├── lanhandle.cpp         // Handle lan communication
|   ├── main.cpp              // Main code entry point
|   ├── menu_lanconf.cpp      // LAN play configuration menu
|   ├── menu_plush_create.cpp // Plush creation menu
|   ├── menu.cpp              // Main menu handling
|   ├── overlord.cpp          // Overlord (AI) players
|   ├── player.cpp            // Human players
|   ├── plush.cpp             // Plush class(es)
|   ├── server.cpp            // Server (backend) game handling
|   └── test.cpp              // gtest-lite test code
├── lib
|   ├── ECONIO_LICENSE        // MIT License file for the econio library
|   ├── econio.c              // Econio library for fancy console output
|   ├── econio.h
|   ├── gtest_lite.h          // gtest_lite for unit testing
|   ├── memtrace.cpp          // memory managment checker
|   ├── memtrace.h
|   ├── nyetwork_excep.h      // nyetwork networking library
|   ├── nyetwork.cpp
|   └── nyetwork.h
├── include
|   └── ...          // Headers for all files
├── .gitignore
├── CMakeLists.txt
├── DEV_DOC.md       // Developer documentation (this file)
├── LICENSE          // AGPL-3.0 (License file)
├── plan.md          // Plan as required by the subject
├── spec.md          // Specifications for the game
└── USR_DOC.md       // User documentation (quickstart guide)
```

### Used external resources
- Libraries:
  1. [c-econio](https://infoc.eet.bme.hu/megjelenites/c-econio.zip) 
    by Zoltan Czirkos. [MIT License](include/lib/ECONIO_LICENSE)
  2. [memtrace](https://infocpp.iit.bme.hu)
  3. [gtest_lite](https://infocpp.iit.bme.hu)
- Code snippets: Noted in source if applicable
- Miscellaneous: 
  1. ASCII font for logo generated with [patorjk.com](https://patorjk.com/software/taag)
  2. ASCII plush generated with [asciiart.eu](https://www.asciiart.eu/image-to-ascii)

<div class="page"></div>

## Files 

### Action
<!-- BEGIN DOC-COMMENT H4 include/action.h -->

#### `Action(string name, int dam, int acc, int en, double pri, Type typ, ActionCategory cat)`

**Parameters:**

* `name` — Name of the Action
* `dam` — Base damage
* `acc` — Accuracy (0-100)
* `en` — Maximum energy
* `pri` — Priority modifier
* `typ` — Base type for the Action
* `cat` — Category of the Action

<!-- END DOC-COMMENT -->

### Brand
<!-- BEGIN DOC-COMMENT H4 include/brand.h -->

#### `int baseStatTotal() const`

Calculate the base stat total of the brand
**Returns:** `The` — base stat total (sum of all six stats) of the brand

#### `void addLearnableAction(Action* ac)`

Add an Action to the brand's available actions
**Parameters:**

* `ac` — Pointer to Action in the server

#### `Brand(string name, Type base, Type secondary, const int baseStats[6])`

Constructor
**Parameters:**

* `name` — Name of brand
* `base` — Base type
* `secondary` — Secondary type
* `baseStats` — Array of the Base Stats in standard StatOrder

<!-- END DOC-COMMENT -->

### Common
<!-- BEGIN DOC-COMMENT H4 include/common.h -->

#### `enum StatOrder`

displayed in the stat hexagon (starting at the top edge, going clock-wise)
**Brief:** The order in which Stats and Unique Values are stored and should be

#### `int random(int a, int b)`

**Brief:** Get a random number between a and b

**Parameters:**

* `a` — Random from (inclusive)
* `b` — Random to (inclusive)

**Returns:** `pseudo` — random int

#### `double operator>>(plushies::Type attacker, plushies::Type target)`

Get the type effectiveness between two types
**Parameters:**

* `attacker` — Type of attacker
* `target` — Type of target

**Returns:** `Type` — effectiveness modifier

#### `std::wstring convertUFT8(const std::string& s)`

Convert string to wstring for wcout
**Parameters:**

* `s` — regular string to convert

**Returns:** `UTF-8` — (wide) string

#### `std::string convertFromUFT8(const std::wstring& ws)`

Convert wstring to string from wcin
**Parameters:**

* `ws` — UTF-8 (wide) string to convert

**Returns:** `regular` — string

#### `inline std::wostream& operator<<(std::wostream& wos, const std::string& s)`

Write a regular string out to a wide ostream
**Parameters:**

* `wos` — Wide output stream (such as wcout)
* `s` — Regular string to be converted to wstring and written out

**Returns:** `Chainable` — wostream

#### `std::wostream& operator<<(std::wostream& wos, plushies::Type type)`

Write Type out to wide output stream
**Parameters:**

* `wos` — Wide output stream (such as wcout)
* `type` — Plush Type to write out

**Returns:** `Chainable` — wostream

#### `std::wostream& operator<<(std::wostream& wos, plushies::ActionCategory ac)`

Write Action Category out to wide output stream
**Parameters:**

* `wos` — Wide output stream (such as wcout)
* `ac` — Action Category to write out

**Returns:** `Chainable` — wostream

#### `std::wostream& operator<<(std::wostream& wos, plushies::EnemyMode em)`

Write Enemy Mode out to wide output stream
**Parameters:**

* `wos` — Wide output stream (such as wcout)
* `em` — Enemy Mode to write out

**Returns:** `Chainable` — wostream

#### `std::vector<std::string> split(const std::string& s, char delim)`

Split a string at delimiters
**Parameters:**

* `s` — String to be split
* `delim` — Delimiter to split at

**Returns:** `std::vector` — of split strings

#### `std::string encodeChoice(int c)`

Encode int choice to string for lan communication
**Parameters:**

* `c` — Choice to be encoded

**Returns:** `Encoded` — choice ready for send

#### `int decodeChoice(const char* c)`

Decode choice from lan communication for internal server use
**Parameters:**

* `c` — String to decode

**Returns:** `Decoded` — choice

<!-- END DOC-COMMENT -->

### Game screen
<!-- BEGIN DOC-COMMENT H4 include/game_screen.h -->

#### `void printScreen()`

Print the main game screen

#### `void updatePlush(const plushies::Plush& p, bool foe = false)`

Update displayed plush information
**Parameters:**

* `p` — Plush to grab details from
* `foe` — Indicate if it is the foe or the player

#### `void updateActionInfo(const plushies::Action &a)`

Update the Action info on the UI
**Parameters:**

* `a` — Action to display

#### `void updateSelection(const std::string& item, int id, bool highlight = false)`

Update selected item display on the UI
**Parameters:**

* `item` — Display name of selected item
* `id` — ID (spot) of selected item
* `highlight` — Highligt or reset item

#### `void printList(const std::vector<std::string>& list)`

Write a list of available options to the select menu on the UI
**Parameters:**

* `list` — List of items (max 4)

#### `int chooseAction(const plushies::Plush& p)`

Write out the actions of the plush and prompt the player to choose one
**Parameters:**

* `p` — Plush to grab actions from

**Returns:** `Choice` — id (0-4)

#### `int choosePlush(const plushies::Player& p)`

Write out the available plushies and prompt the player to choose one
**Parameters:**

* `p` — Player to grab plushies from

**Returns:** `Choice` — id (0-3)

#### `int chooseMove(const plushies::Player& player)`

Ask player to choose their turn's action (move)
**Parameters:**

* `player` — Player to grab all data from

**Returns:** `Final` — choice

<!-- END DOC-COMMENT -->

### Game
<!-- BEGIN DOC-COMMENT H4 include/game.h -->

#### `bool setUnicodeMode()`

Try to set the output mode to wide characters for compatibility with all systems (for UI wide chars)
**Returns:** Success/Failiure

#### `void warningScreen()`

Test for terminal size and/or show warning screen if terminal size can't be determined or is too small for the game

#### `void gameInit()`

Initialize the game and all settings

<!-- END DOC-COMMENT -->

### Lanhandle
<!-- BEGIN DOC-COMMENT H4 include/lanhandle.h -->

#### `void rec(char* buf, const int len = sizeof(buf), const int flags = 0) const`

Receive into buffer
**Parameters:**

* `buf` — Buffer to receive into
* `len` — Maximum length to receive
* `flags` — recv() flags

#### `void sen(const char* buf, const int len, const int flags = 0) const`

Send char* buffer
**Parameters:**

* `buf` — Buffer to send
* `len` — Size of buffer to send
* `flags` — sen() flags

#### `void sen(const std::string& string) const`

Send string
**Parameters:**

* `string` — string to send

#### `void sen(const stringstream& ss) const`

Send string stream's data
**Parameters:**

* `ss` — StringStream to send

#### `virtual bool connect(Server& server) = 0`

the server
**Brief:** Handle Communication handshake and initial setup

**Note:** This function creates player0 (the opponent dummy player) for

**Parameters:**

* `server` — Game Server to set up with connection

**Returns:** `Result` — of the connection attempt

#### `virtual void ActionReady() = 0`

**Brief:** Let the lan player know we are ready to receive their choice

#### `virtual int SyncActions(int myChoice) = 0`

**Brief:** Sync the choice of the local and lan player

**Parameters:**

* `myChoice` — The choice of the local player to send

**Returns:** `Choice` — of the lan player

#### `void sendPSYN(const Server& s, const Plush& plush) const`

Send PSYN (Plush Sync) command for a plush
**Parameters:**

* `s` — Server for brand/plush/action database
* `plush` — Plush to send

#### `Plush recPSYN(Server& s) const`

Receive PSYN (Plsuh Sync) command and get the plsuh from it
**Parameters:**

* `s` — Server for brand/plush/action database

**Returns:** `Received` — plush

#### `Connection(nyetwork::Communicator* com) : communicator(com)`

Set up a generic connection
**Parameters:**

* `com` — Communicator used for TCP communicating

<!-- END DOC-COMMENT -->

### Menu Lanconf
<!-- BEGIN DOC-COMMENT H4 include/menu_lanconf.h -->

#### `void printIP()`

Get and print IP Addresses of the computer

#### `string menuLanconf(bool server)`

Open lan configuration menu
**Parameters:**

* `server` — Server to configure based on

**Returns:** `IP` — to connect to

#### `bool lanConfirm(int numPlushes, int gameMode)`

Ask player to confirm if the connection is acceptable
**Parameters:**

* `numPlushes` — Number of plushies used by opponent
* `gameMode` — Game Mode of opponent

**Returns:** `Accept/Deny` — of player

<!-- END DOC-COMMENT -->

### Menu Plush Create
<!-- BEGIN DOC-COMMENT H4 include/meu_plush_create.h -->
<!-- END DOC-COMMENT -->

### Menu
<!-- BEGIN DOC-COMMENT H4 include/menu.h -->

#### `void menu(plushies::GameMode& gm, int& cnt, plushies::EnemyMode& opp)`

**Brief:** Handle all of the main menu and initialization

**Parameters:**

* `gm` — Output GameMode value
* `cnt` — Output Plush count value
* `opp` — Output Opponent selection

#### `void writeMainHeader()`

**Brief:** Write the main menu header (logo and welcome message)

#### `plushies::GameMode modeSelect()`

**Brief:** Ask the player to select the game mode

**Returns:** `Selected` — game mode

#### `int plushCountSelect()`

**Brief:** Ask the player to select the number of plushes to use

**Returns:** `The` — number of plushes selected (1-3) <br> -1 for invalid selection

#### `plushies::EnemyMode opponentSelect(bool detail)`

**Brief:** Ask the player to choose their opponent (AI or LAN play mode)

**Parameters:**

* `detail` — Detailed mode - if true, player can choose specific AI

**Returns:** `enemy` — choice

<!-- END DOC-COMMENT -->

### Overlord
<!-- BEGIN DOC-COMMENT H4 include/overlord.h -->

#### `class Dennis final : public Player`

**Brief:** Random moves, random plushes

#### `Dennis(Server& s, int count)`

**Brief:** Generate AI with random plushes

**Parameters:**

* `s` — Server for the available brands and actions
* `count` — Number of plushes to generate

#### `class Clyde final : public Player`

**Brief:** Waits 5-10 secs random move, random plushes

#### `Clyde(Server& s, int count)`

**Brief:** Generate AI with random plushes

**Parameters:**

* `s` — Server for the available brands and actions
* `count` — Number of plushes to generate

#### `class Ninty final : public Player`

**Brief:** Most damage, high stat, high UVs

#### `Ninty(Server& s, int count)`

**Brief:** Generate AI with random, but strong plushes

**Parameters:**

* `s` — Server for the available brands and actions
* `count` — Number of plushes to generate

#### `class Waffles final : public plushies::Player`

**Brief:** Use least damage, high stat, mid UVs

#### `Waffles(Server& s, int count)`

**Brief:** Generate AI with random, but strong plushes

**Parameters:**

* `s` — Server for the available brands and actions
* `count` — Number of plushes to generate

#### `class Muffins final : public plushies::Player`

**Brief:** Least damage, random plushes

#### `Muffins(Server& s, int count)`

**Brief:** Generate AI with random plushes

**Parameters:**

* `s` — Server for the available brands and actions
* `count` — Number of plushes to generate

<!-- END DOC-COMMENT -->

### Player
<!-- BEGIN DOC-COMMENT H4 include/player.h -->

#### `void addPlush(const Plush &p)`

Add a plush to the player
**Parameters:**

* `p` — plush to ad

#### `void setActive(int i)`

Set a different plush active (when swapping)
**Parameters:**

* `i` — ID of plush to set active

#### `void nextAlive()`

Set the next alive plush active

#### `int numPlushes(bool alive = false)`

Get the number of plushes of the player
**Parameters:**

* `alive` — Count dead ones or only alive ones

**Returns:** `Number` — of plushes

#### `virtual int ready(const Plush& opponent)`

0 : Forefit <br> 1-4 index of selected move <br> negative 1-4 selected plush
**Brief:** Request Action from the player

**Returns:** `Negative` — : Swap plushes (to index of abs value) <br>

#### `std::vector<Plush> getPlushes() const`

Get the plushes of the player
**Returns:** `Array` — of plushes of the player

#### `Plush& active()`

Get a reference to the currenlty active plush
**Returns:** `Reference` — to currently active plush

#### `Plush getActivePlush() const`

Get the currently active plush
**Returns:** `Currently` — active plush

#### `Action activeAction(const int id) const`

Get an action of the current plush
**Parameters:**

* `id` — ID of action to get

**Returns:** `The` — action

<!-- END DOC-COMMENT -->

### Plush
<!-- BEGIN DOC-COMMENT H4 include/plush.h -->

#### `int getUV(const StatOrder uvo) const`

Get a specific UV (Unique Value)
**Parameters:**

* `uvo` — StatOrder for the UV to get

**Returns:** `Selected` — UV

#### `int calcDamage(const Action& act) const`

Get the damage dealt by a move
**Parameters:**

* `act` — Action to use for calculations

**Returns:** `The` — damage the move will deal before defense calculations

#### `int calcDamage(int actionId) const`

Get the damage dealt by a move from the move ID
**Parameters:**

* `actionId` — Action to use for calculations

**Returns:** `The` — damage the move will deal before defense calculations

#### `static void validateACThrow(const Action& act)`

Check if action can be used
**Parameters:**

* `act` — Action to check

#### `void validateACThrow(const int actId) const`

Check if action can be used
**Parameters:**

* `actId` — Action to check

#### `static bool validateAC(const Action& act)`

Check if action can be used
**Parameters:**

* `act` — Action to check

**Returns:** `Boolean` — can/can't be used

#### `bool validateAC(const int actId) const`

Check if action can be used
**Parameters:**

* `actId` — Action to check

**Returns:** `Boolean` — can/can't be used

#### `ActionContext getAC(const Action& act) const`

Get an Action Context for a move
**Parameters:**

* `act` — Action to use

**Returns:** `Calculated` — Action context from plush pov

#### `ActionContext getAC(const int actId) const`

Get an Action Context for a move
**Parameters:**

* `actId` — Action to use

**Returns:** `Calculated` — Action context from plush pov

#### `ActionContext getSafeAC(const Action& act) const`

Get an Action Context for a move with move validation
**Parameters:**

* `act` — Action to use

**Returns:** `Calculated` — Action context from plush pov

#### `ActionContext getSafeAC(const int actId) const`

Get an Action Context for a move with move validation
**Parameters:**

* `actId` — Action to use

**Returns:** `Calculated` — Action context from plush pov

#### `int calcSpeed(const Action& act) const`

Calculate the speed of the action
**Parameters:**

* `act` — Action to use

**Returns:** `Calculated` — speed based on action priority

#### `int calcSpeed(int actionId) const`

Calculate the speed of the action
**Parameters:**

* `actionId` — Action to use

**Returns:** `Calculated` — speed based on action priority

#### `ActionContext operator>>(Action& act) const`

**Brief:** Get damage of executed action

**Parameters:**

* `act` — Pointer to action

**Returns:** `Damage` — before type effectiveness calculations

#### `ActionContext operator>>(int actionId)`

**Brief:** Get damage of executed action

**Parameters:**

* `actionId` — Executed Action's slot number

**Returns:** `Damage` — before type effectiveness calculations

#### `void operator<<(int hp)`

**Brief:** Apply exact amount of damage to Plush

**Parameters:**

* `hp` — Exact number of health points to remove

#### `void operator<<(ActionContext damage)`

**Brief:** Apply damage based on context

**Parameters:**

* `damage` — damage context to use

#### `Plush(Brand& brand, const int UV[6], Action actions[4])`

Ctor for Plushies
**Parameters:**

* `brand` — Brand of the plush
* `UV` — Unique values of the plush
* `actions` — Actions for the plush

#### `int operator>>(const plushies::ActionContext& damage, const plushies::Plush& target)`

**Brief:** Get exact amount of damage dealt by an Action context on a plush

**Parameters:**

* `damage` — Action Context attacking the plush
* `target` — Plush being attacked

**Returns:** `Damage` — after all defense and type calculations.

<!-- END DOC-COMMENT -->

### Server
<!-- BEGIN DOC-COMMENT H4 include/server.h -->

#### `std::vector<string> readCSV(std::ifstream& ifstream)`

Read in a line from a CSV file
**Parameters:**

* `ifstream` — Stream to read from

**Returns:** `vector` — of strings

#### `Player* getPlayer(const int i) const`

Get a player from the server
**Parameters:**

* `i` — ID of player

**Returns:** `Pointer` — to the player

#### `void registerComm(nyetwork::Communicator* c)`

Register a communicator for LAN Play
**Parameters:**

* `c` — Communicator to register

#### `Plush createRandomPlush(int bst = 0, int uvmin = 0, int uvmax = 63)`

Generate a random plush with optional strength restrictions
**Parameters:**

* `bst` — Minimum Base Stat Total (negative for maximum)
* `uvmin` — minimum values for UVs
* `uvmax` — maximum values for UVs

#### `int serverLoop()`

Start the main server loop  - 1 : Won
 - 0 : Lost
 - -1: Catastrophic internal error (couldn't recover)

**Returns:** `The` — game end result

#### `void RegisterPlayer(Player* p, const int num = 0)`

Register a player to the server
**Parameters:**

* `p` — Player pointer to register (deletes: server)
* `num` — ID of player

#### `Server(EnemyMode em, GameMode gm, int cnt, const string& brandFile = "data/brands.csv", const string& actionFile = "data/actions.csv", const string& actionLearnFile = "data/action_learn.csv")`

Initialize the server and all data
**Parameters:**

* `em` — Enemy Mode to start with
* `gm` — Game Mode
* `cnt` — Number of plushes
* `brandFile` — Brand csv location
* `actionFile` — Actions csv location
* `actionLearnFile` — Action Learn csv location

<!-- END DOC-COMMENT -->
