cmake_minimum_required(VERSION 3.31)
project(KnightOfZodiacRPG C)

set(CMAKE_C_STANDARD 11)

add_executable(KnightOfZodiacRPG main.c
        Knight/knights.h
        Knight/knights.c
        Story/story.h
        Story/story.c
        Houses/house.h
        Houses/house.c)
