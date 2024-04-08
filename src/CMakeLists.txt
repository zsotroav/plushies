include_directories(../include)
include_directories(../lib)

file(GLOB SRC_FILES *.cpp)
file(GLOB H_FILES ../include/*.h)
add_executable(Plushies
        ${SRC_FILES}
        ${H_FILES}
        ../lib/memtrace/memtrace.cpp
        ../lib/memtrace/memtrace.h)

target_link_libraries(Plushies
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)

add_compile_definitions(MEMTRACE)
