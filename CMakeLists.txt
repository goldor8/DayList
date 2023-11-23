cmake_minimum_required(VERSION 3.24)
project(DayList C)

set(CMAKE_C_STANDARD 11)

add_executable(DayList main.c levelsList.c levelsList.h timer.c contact.c contact.h)
target_link_libraries(DayList m)