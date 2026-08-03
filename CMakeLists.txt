cmake_minimum_required(VERSION 3.10)
project(dungeon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(dungeon ${SRC_FILES})

target_include_directories(dungeon PRIVATE include)

# select() needs a bit of leeway on some platforms; harmless elsewhere
target_compile_options(dungeon PRIVATE -Wall -Wextra)
