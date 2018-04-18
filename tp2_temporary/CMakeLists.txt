cmake_minimum_required(VERSION 3.10)
project(tp2_temporary C)

set(CMAKE_C_STANDARD 99)

add_executable(tp2_temporary main.c process.c process.h processQueue.c processQueue.h main.c scheduler.c scheduler.h testLib.c testLib.h schedulerTest.c schedulerTest.h)