# Plush Monsters' Fight Club <br /> DEVELOPER'S DOCUMENTATION

## Table of contents
<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=3 orderedList=false} -->

<!-- code_chunk_output -->

<div class="page"></div>

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
|   ├── econio.c
|   ├── econio.h
|   ├── gtest_lite.h
|   ├── memtrace.cpp
|   ├── memtrace.h
|   ├── nyetwork_excep.h
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
└── USR_DOC.md        // User documentation (quickstart guide)
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






