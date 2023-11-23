//
// Created by Dimitri on 23/11/2023.
//

#include "dateTime.h"
#include <stdlib.h>

t_date *createDate(int day, int month, int year) {
    t_date *date = (t_date *) malloc(sizeof(t_date));
    date->day = day;
    date->month = month;
    date->year = year;
    return date;
}

t_time *createTime(int hour, int minute) {
    t_time *time = (t_time *) malloc(sizeof(t_time));
    time->hour = hour;
    time->minute = minute;
    return time;
}

void freeDate(t_date *date) {
    free(date);
}

void freeTime(t_time *time) {
    free(time);
}