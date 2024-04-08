cmake_minimum_required(VERSION 3.27)
project(Plushies)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(lib/FTXUI)
add_subdirectory(lib/memtrace)

configure_file(data/brands.txt data/brands.txt COPYONLY)
configure_file(data/actions.txt data/actions.txt COPYONLY)
