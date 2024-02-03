cmake_minimum_required(VERSION 3.26)
project(prog2 C)

set(CMAKE_C_STANDARD 17)

add_executable(prog2 main.c
        compute.c
        io.c
        header.h)
