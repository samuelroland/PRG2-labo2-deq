cmake_minimum_required(VERSION 3.23)
project(listes_dynamiques C)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic")

add_executable(listes_dynamiques tests.c src/listes_dynamiques.c)