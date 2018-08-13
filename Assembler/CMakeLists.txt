cmake_minimum_required(VERSION 3.5)
project(Assembler C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -ansi")

add_executable(Assembler main.c settings.h tables.h tables.c definitions.h text_handling.c text_handling.h binary_word.c binary_word.h settings.c)
