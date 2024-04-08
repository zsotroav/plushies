cmake_minimum_required(VERSION 3.27)
project(Plushies)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)
include_directories(lib)

add_executable(_NHF src/main.cpp

        lib/memtrace.h
        lib/memtrace.cpp

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

)

add_compile_definitions(MEMTRACE)

configure_file(data/brands.txt data/brands.txt COPYONLY)
configure_file(data/actions.txt data/actions.txt COPYONLY)
