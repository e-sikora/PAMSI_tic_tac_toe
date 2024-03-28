cmake_minimum_required(VERSION 3.16)

project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 17)

# Dodanie pliku nagłówkowego
include_directories(inc)

# Dodanie plików źródłowych
add_executable(${PROJECT_NAME} src/main.cpp src/board.cpp src/ai.cpp)