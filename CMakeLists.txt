cmake_minimum_required(VERSION 3.7)
project(branch-checklist C)

set(CMAKE_C_STANDARD 99)

add_executable(branch-checklist main.c util.h util.c)