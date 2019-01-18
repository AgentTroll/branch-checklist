cmake_minimum_required(VERSION 3.12)
project(pjcart C)

set(CMAKE_C_STANDARD 99)

add_executable(pjcart main.c util.h util.c)