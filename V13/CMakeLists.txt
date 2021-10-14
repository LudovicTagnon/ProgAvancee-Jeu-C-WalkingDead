cmake_minimum_required(VERSION 3.20)
project(V1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(V1
        constants.h
        data.c
        data.h
        fonctions_SDL.c
        fonctions_SDL.h
        main.c)
