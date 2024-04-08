cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)


include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(.
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG e03a0797be167e12a3809cd45c95ad86a134e832
)

FetchContent_GetProperties(.)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(.)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()