//
// Created by Dimitri on 23/11/2023.
//

#ifndef DAYLIST_CALENDAREVENT_H
#define DAYLIST_CALENDAREVENT_H

#include "contact.h"
#include "dateTime.h"
#include "appointment.h"

typedef struct s_calendar_event{
    t_contact_cell *contact;
    t_appointment_cell *appointment;
} t_calendar_event;

typedef struct s_calendar_event_cell
{
    t_calendar_event *event;
    int levels;
    struct s_calendar_event_cell **nexts;
} t_calendar_event_cell;

typedef struct s_calendar_event_list
{
    t_calendar_event_cell **heads;
} t_calendar_event_list;


t_calendar_event* createCalendarEvent(t_contact_cell *contact, t_appointment_cell *appointment);
void freeCalendarEvent(t_calendar_event *event);
t_calendar_event_cell* createCalendarEventCell(t_calendar_event *event, int levels);
void freeCalendarEventCell(t_calendar_event_cell* cell);
t_calendar_event_list* createCalendarEventList(int levels);
void freeCalendarEventList(t_calendar_event_list* list);
void displayCalendarEventListLevel(int level, t_calendar_event_list list);
void displayPrettyCalendarEventListLevel(int level, t_calendar_event_list list);
void displayCalendarEventList(t_calendar_event_list list); // Dimitri
void displayPrettyCalendarEventList(t_calendar_event_list list); // Dimitri
void insertCalendarEventCellAtHead(t_calendar_event_cell *cell, t_calendar_event_list * list);
void insertCalendarEventCell(t_calendar_event_cell *cell,t_calendar_event_list * list);
t_calendar_event_cell* findCalendarEventInSortedListNotFast(int value, t_calendar_event_list list);
t_calendar_event_cell* findCalenderEventInSortedList(int value, t_calendar_event_list list);


#endif //DAYLIST_CALENDAREVENT_H
