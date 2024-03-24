cmake_minimum_required(VERSION 3.26)
project(Backgammon)
set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(Backgammon ${CURSES_LIBRARIES})
set(CMAKE_CXX_FLAGS "-lncurses")
add_executable(Backgammon main.cpp)
