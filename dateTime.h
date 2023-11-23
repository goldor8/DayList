//
// Created by Dimitri on 23/11/2023.
//

#ifndef DAYLIST_DATETIME_H
#define DAYLIST_DATETIME_H

typedef struct s_date
{
    int day;
    int month;
    int year;
} t_date;

typedef struct s_time
{
    int hour;
    int minute;
} t_time;

t_date *createDate(int day, int month, int year);
t_time *createTime(int hour, int minute);
void freeDate(t_date *date);
void freeTime(t_time *time);

#endif //DAYLIST_DATETIME_H
