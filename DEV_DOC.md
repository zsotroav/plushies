# Plush Monsters' Fight Club <br /> DEVELOPER'S DOCUMENTATION

## Table of contents
<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=3 orderedList=false} -->

<!-- code_chunk_output -->

<div class="page"></div>

## 1 Legal & License
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

## 2 About
Plush Monsters' Fight Club is a basic command-line turn-based battle system
emulator made as the big homework for the "Basics of Programming 2" course.

For more information, see the [spec.md](specification) or [plan.md](plan).

## 3 High-level overview
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
└── USR_DOC.md       // User documentation (quickstart guide)
```