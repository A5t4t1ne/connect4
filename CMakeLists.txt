cmake_minimum_required(VERSION 3.10) # Specify the minimum version of CMake

project(Connect4 VERSION 0.1) # Define the project name and version

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target with source files
file(GLOB SOURCES "*.c" "*.h")
add_executable(connect_four ${SOURCES})


find_library(NCURSES_LIBRARY ncurses)
if(NOT NCURSES_LIBRARY)
    message(FATAL_ERROR "ncurses not found")
endif()

target_link_libraries(connect_four ${NCURSES_LIBRARY})