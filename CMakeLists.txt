cmake_minimum_required(VERSION 3.16)
project(tetris)

set(CMAKE_CXX_STANDARD 17)

add_executable(tetris src/main.cpp src/tetris/falling.h src/tetris/gameboard.h src/tetris/shapes.h src/tetris/types.h src/main_auxiliary.h src/main_auxiliary.hpp src/tetris/gameboard.hpp src/tetris/falling.cpp src/tetris/types.cpp src/tetris/shapes.cpp)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(NCURSES REQUIRED ncurses)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${NCURSES_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${NCURSES_LIBRARIES})