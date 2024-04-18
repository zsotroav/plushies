cmake_minimum_required(VERSION 3.27)
project(Plushies)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall)

include_directories(include)
include_directories(src)
include_directories(lib)

add_executable(Plushies src/main.cpp

        lib/memtrace.h
        lib/memtrace.cpp

        lib/econio.c
        lib/econio.h

        include/Server.h

        include/plush.h
        src/plush.cpp
        src/brand.cpp
        include/brand.h
        include/common.h
        include/action.h
        src/action.cpp
        src/common.cpp
        src/common.cpp
        src/player.cpp
        include/player.h
        src/server.cpp
        src/menu.cpp
        include/menu.h
        src/game.cpp
        include/game.h
        include/overlord.h
        src/overlord.cpp
        src/menu_plush_create.cpp
        include/menu_plush_create.h
        src/game_screen.cpp
        include/game_screen.h
        include/lanplayer.h
        src/lanplayer.cpp
        lib/nyetwork.h
        lib/nyetwork.cpp

)

add_compile_definitions(MEMTRACE)

configure_file(data/brands.csv data/brands.csv COPYONLY)
configure_file(data/actions.csv data/actions.csv COPYONLY)
configure_file(data/action_learn.csv data/action_learn.csv COPYONLY)

if(WIN32)
    target_link_libraries(Plushies wsock32 ws2_32)
endif()
