cmake_minimum_required(VERSION 3.24)
project(DayList C)

set(CMAKE_C_STANDARD 11)

add_executable(DayList main.c part1-2/levelsList.c part1-2/levelsList.h part1-2/timer.c contact.c contact.h contactCalendar.c contactCalendar.h dateTime.c dateTime.h appointment.c appointment.h appointment.c highRand.c highRand.h commands.c commands.h stringUtil.c)
target_link_libraries(DayList m)