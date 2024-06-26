cmake_minimum_required(VERSION 3.25)
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

        include/server.h

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
        src/menu_lanconf.cpp
        include/menu_lanconf.h
        src/game_screen.cpp
        include/game_screen.h
        #include/lanplayer.h
        #src/lanplayer.cpp
        lib/nyetwork.h
        lib/nyetwork.cpp
        lib/nyetwork_excep.h
        include/lanhandle.h
        src/lanhandle.cpp
        include/test.h
        src/test.cpp
        lib/gtest_lite.h

)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(MEMTRACE MEMTRACE_ERRFILE=mem.trace)
endif()

add_compile_definitions(${BUILD})

configure_file(data/brands.csv data/brands.csv COPYONLY)
configure_file(data/actions.csv data/actions.csv COPYONLY)
configure_file(data/action_learn.csv data/action_learn.csv COPYONLY)

if(WIN32)
    target_link_libraries(Plushies wsock32 ws2_32)
endif()
