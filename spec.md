# Plush Monsters' Fight Club <br /> PROGRAM SPECIFICATION

## Table of contents {ignore=true}
<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=3 orderedList=false} -->

<!-- code_chunk_output -->

- [About](#about)
- [Definitions](#definitions)
- [Running the simulation](#running-the-simulation)
  - [Menu screens](#menu-screens)
  - [Game screen](#game-screen)
- [File formats](#file-formats)
  - [data/brands.csv](#databrandscsv)
  - [data/actions.csv](#dataactionscsv)
  - [data/action_learn.csv](#dataaction_learncsv)
- [AI Players](#ai-players)
- [Network Communication protocol](#network-communication-protocol)
  - [Message Structure](#message-structure)

<!-- /code_chunk_output -->


## About
Plush Monsters' Fight Club is a basic command-line turn-based battle system
emulator made as the big homework for the "Basics of Programming 2" course.

## Definitions
- **Statistics (stats):** Numbers and other information used to calculate
attack damage. The six stats are the following:
  - Health (HP)
  - Attack (Atk)
  - Defense (Def)
  - Speed (Spe)
  - Special Attack (SpA)
  - Special Defense (SpD)
- **Brand:** A general group of creatures that have shared base stats
- **Plush:** A specific, attack-ready creature that has base stats based on
its brand and **unique values (UVs)**, which are additional numbers (0-63) 
to the base stats representing diversity.
- **Actions:** Plushes attack each other using actions (moves/attacks). Every
plush can know up to 4 moves, and each plush may only know moves its brand can
learn.
  - **Categories:** Moves can be in the *Physical* or *Special* category.
  These categories affect which statistics are used for damage calculations.
  - **Power:** Each move has a base power for damage calculations.
  - **Accuracy:** Attacks can miss, and for example, a low accuracy can 
  balance high base power for moves.
  - **Energy:** Every move can only be used a limited number of times. 
  This varies move by move; failed moves also decrease the move's energy.
  - **Priority:** Moves may have a priority value that can override the
  order of attacking. 
- **Type:** Plushes can have one or two types while moves always have one.
These types affect *type effectiveness* of attacks and can greatly increase or
completely nullify the damage dealt. 
- **Battle:** A battle is between two plushes that are using moves to attack
each other. A battle ends when one of the plushes gets ripped (loses all HP).

## Running the simulation

### Menu screens

#### Main menu
When starting up the application you are asked to choose the mode(s) you want
to play in:
- **Game mode:** The way you want to play against your enemy
  - **Random:** You will be given a randomly selected plush with random UVs.
  - **Custom:** You can choose what brand and moves you want your plush with.
  - **Detailed:** Same as custom, but you can also set UVs
- **Plush count:** The number of plushes to use (generally 1-3)
- **Play against:** What you want to play against
  - **Overlord:** You will play against a basic AI
  - **LAN play:** A second player from their own computer

#### Plush configuration screen
If custom or detailed mode was selected, you will be asked to select the 
following details for each of your plushes:
1. Plush's brand
2. Up to four moves for the plush
3. Exact UVs (if in detailed mode)

There is an option to save or load the current plush into/from a file.

#### LAN play (network connection setup)
If LAN play was selected you are first asked if you want to host the game or
connect to another player's game.

If you are hosting, all required information for the connection will be
displayed on screen. Once a connection request comes in, you can choose to 
accept or decline it.

If you are connecting to another player's game, you need to enter the required
connection details and get accepted by the host.

Before the game begins, players don't see the other's selected plush, only the
number of plushes.

### Game screen
During gameplay, the main game screen is shown where most information about the
current state of the game can be found: The current Plushes in play, their
health points at the moment (opponent's is only visible as a percentage), and
the action selection buttons.

During the player's turn, they may choose one of these actions:
* Attack with their current plush 
  * If the player chooses to use an Action to attack, they are asked which
    Action should their plush use. During selection, basic info about the
    moves (such as power, accuracy, and remaining energy) is displayed. 
* Swap their current plush for another available one
  * If the player wants to change out their plush for a different one, they can
    choose to swap their plush for another one instead of using an Action. 
    Swapping always happens first before any other actions get executed.
* Forefit the fight

## File formats
Files are stored in a CSV format (using semicolons) with the following layouts:

### data/brands.csv
Used for storing the brands in the game.
```
NAME; BASE_TYPE_ID; SECONDARY_TYPE_ID; HP; ATK; DEF; SPD; SPA; SPE
```

### data/actions.csv
Used for storing the actions available to use in the game
```
NAME; BASE_POWER; ACCURACY; SPEED_MULTIPLYER; TYPE_ID; CATEGORY_ID
```

### data/action_learn.csv
Used to store which moves a brand can learn. There is no limit to the number of
Move IDs that can be listed. The IDs refer to the line of the brand/action in
`brands.csv`/`actions.csv`.
```
BRAND_ID; MOVE_ID_1; MOVE_ID_2; ...
```

## AI Players 
If the "Overlord" opponent option is selected at the beginning of the game, the 
player will play against a randomly picked AI opponent:
* Dennis: Picks moves randomly
* Clyde: Waits 5-10 seconds before selecting a move randomly
* Ninty: Will always use the move that deals the most damage, always has high
  stat plush with high UVs (50-63)
* Waffles: Will always use the move that deals the least damage, but always has
  high stat plush with medium-high UVs (40-50)
* Muffins: Will always use the move that deals the least damage

## Network Communication protocol
LAN play may use any TCP port for communicating using plaintext messages.

### Message Structure
Each message is made up of the various parts separated by whitespaces:

#### Connection
* Client connection request: 
`CONN <VERSION> <GAME MODE> <PLUSH COUNT>`
* Server response: `CACK` - Acknowledge the request
  * If the settings do not match the server's, ask the user to accept the
  connection manually otherwise send accept automatically.
  * Mismatched version requests should be denied automatically.
* Server response accept/deny:
  * Accept: `CACC` - Continue sync
  * Deny: `CDEN` - The server waits for another request, and the client is sent
  back to the config menu
* Base sync: First client to server, then server to client
  * Send plush data (one for each plush): 
    `PSYN <BRAND NAME> <PLUSH UVs> <HP> <MOVE ID>` (sending four move IDs; -1
    for none in that spot)

#### Ready for attack
The server asks the client to choose an action to perform with `ARDY`.
* Attack: `AATK <ACTION ID>`
* Swap: `ASWP <PLUSH NUMBER>`
* Forefit: `ADEF`

Since the damage is deterministic, there is no need to sync the whole game
state every turn, only the changes. The server will let the client know of
all changes using the same messages the client sends.

Optionally, the same `PSYN` (Plush Sync) command can be sent by the server or
be requested by the client using the `RSYN` (Request Sync) command. The
client is forced to accept all synced-down information from the server to fix
any potential errors.

#### End of game 
The server will send a `CEND` (Connection End) command to signal the end of
the game and terminate the connection.
