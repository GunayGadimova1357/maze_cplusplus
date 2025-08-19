cmake_minimum_required(VERSION 3.14)
project(HelloSFML)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Cell.cpp
        Cell.h
        Lives.cpp
        Lives.h
        Maze.cpp
        Maze.h
        Enemy.cpp
        Enemy.h
        Buff.cpp
        Buff.h
        Score.cpp
        Score.h
        FileOperations.cpp
        FileOperations.h)
add_executable(HelloSFML ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
