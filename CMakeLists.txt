cmake_minimum_required(VERSION 3.1)

project(tds)
set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio network window system REQUIRED)
find_package(Lua51  REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} ${LUA_INCLUDE_DIR})

include_directories(src include)

set(GAME_SRC 
    src/main.cpp
    src/entity_manager.cpp
    src/position_component.cpp
    src/game.cpp
    src/texture_manager.cpp
    src/battle_state.cpp
    src/graphics_component.cpp
    )

add_executable(game ${GAME_SRC})
target_link_libraries(game sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${LUA_LIBRARIES} ${LUA_DEPENDENCIES})