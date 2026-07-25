cmake_minimum_required(VERSION 3.10)
project(dungeon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dungeon
    src/main.cpp
    src/map.cpp
    src/player.cpp
    src/enemy.cpp
    src/bullet.cpp
    src/render.cpp
    src/input.cpp
)

target_include_directories(dungeon PRIVATE include)

# select() needs a bit of leeway on some platforms; harmless elsewhere
target_compile_options(dungeon PRIVATE -Wall -Wextra)
