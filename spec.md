# Plush Monsters' fight club <br /> PROGRAM SPECIFICATION

## Table of contents {ignore=true}
<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=3 orderedList=false} -->

<!-- code_chunk_output -->

- [About](#about)
- [Definitions](#definitions)
- [Running the simulation](#running-the-simulation)
  - [Main menu](#main-menu)
  - [Plush configuration screen](#plush-configuration-screen)
  - [LAN play (network connection setup)](#lan-play-network-connection-setup)

<!-- /code_chunk_output -->


## About
Plush Monsters' fight club is a basic command-line turn-based battle system
emulator made as the big homework for the "Basics of porgramming 2" course.

## Definitions
- **Statistics (stats):** Numbers and other information used to calculate
attack damage. The six stats are the following:
  - Health (HP)
  - Attack (Atk)
  - Defense (Def)
  - Speed (Spd)
  - Special Attack (SpA)
  - Special Defense (SpD)
- **Brand:** A general group of creatures that have shared base stats
- **Plush:** A specific, attack-ready creature that has base stats based on
its brand, and **unique values (UVs)** which are additional numbers (0-63) 
to the base stats representing diversity.
- **Moves (attacks):** Plushes attack each other using moves (or also known as
attacks). Every plush can know up to 4 moves and each plush may only know moves
its brand can learn.
  - **Move categories:** Moves can be in the *Physical* or *Special* category.
  These categories affect which statistic are used for damage calculations.
  - **Move power:** Each move has a base power for damage calculations.
  - **Move accuracy:** Attacks can miss and for example, a low accuracy can 
  balance high base power for moves.
  - **Move energy:** Every move can only be used a limited number of times. 
  This varies move by move and even failed moves decrease the move's energy.
  - **Move priority:** Moves may have a priority value that can override the
  order of attacking. 
- **Type:** Plushes can have one or two types while moves always have one.
These types affect *type effectiveness* of attacks and can greatly increase or
completely nullify the damage dealt. 
- **Battle:** A battle is between two plushes that are using moves to attack
each other. A battle ends when one of the plushes get ripped (looses all HP).

## Running the simulation

### Main menu
When starting up the application you are asked to choose the mode(s) you want
to play in:
- **Game mode:** The way you want to play against your enemy
  - **Random:** You will be given a randomly selected plush with random UVs.
  - **Custom:** You can choose what brand and moves you want your plush with.
  - **Detailed:** Same as custom, but you can also set UVs
- **Plush count:** The number of plushes to use (1-3)
- **Play against:** What you want to play against
  - **Overlord:** You will play against a basic AI
  - **Player 2:** A second player on the same computer
  - **LAN play:** A second player from their own computer

### Plush configuration screen
If custom or detailed mode was selected, you will be asked to select the 
following details for each of your plushes:
1. Plush's brand
1. Up to four moves for the plush
1. Exact UVs (if in detailed mode)

If local player 2 was selected, the same screens will appear again to configure
the second player's plushes.

There is an option to save or load the current plush into/from a file.

### LAN play (network connection setup)
If LAN play was selected, you are first asked if you want to host the game or
connect to another player's game.

If you are hosting, all required information for the connection will be
displayed on screen. Once a connection request comes in, you can choose to 
accept or decline it.

If you are connecting to another player's game, you need to enter the required
connection details and get accepted by the host.

Before the game begins, players don't see the other's selected plush, only the
number of plushes.