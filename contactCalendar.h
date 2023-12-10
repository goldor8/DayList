//
// Created by Dimitri on 23/11/2023.
//

#ifndef DAYLIST_CONTACTCALENDAR_H
#define DAYLIST_CONTACTCALENDAR_H

#include "contact.h"
#include "dateTime.h"
#include "appointment.h"

typedef struct s_contact_calendar{
    t_contact *contact;
    t_appointment_list *appointments;
} t_contact_calendar;

typedef struct s_contact_calendar_cell
{
    t_contact_calendar *event;
    int levels;
    struct s_contact_calendar_cell **nexts;
} t_contact_calendar_cell;

typedef struct s_contact_calendar_list
{
    t_contact_calendar_cell **heads;
    int levels;
} t_contact_calendar_list;


void createContactCalendar(t_contact *contact, t_contact_calendar_list *list);
void addAppointment(t_contact *contact, t_appointment_cell *appointment, t_contact_calendar_list *list);

void freeContactCalendar(t_contact_calendar *event);

t_contact_calendar_cell* createContactCalendarCell(t_contact_calendar *event, int levels);
void freeCalendarCalendarCell(t_contact_calendar_cell* cell);

t_contact_calendar_list* createContactCalendarList(int levels);
void freeContactCalendarList(t_contact_calendar_list* list);

void displayContactCalendarListLevel(int level, t_contact_calendar_list list);
void displayPrettyContactCalendarListLevel(int level, t_contact_calendar_list list);
void displayContactCalendarList(t_contact_calendar_list list);
void displayPrettyContactCalendarList(t_contact_calendar_list list);



void insertContactCalendarCellAtHead(t_contact_calendar_cell *cell, t_contact_calendar_list * list);
void insertContactCalendarCell(t_contact_calendar_cell *cell, t_contact_calendar_list * list);

void removeAppointmentFromContactCalendar(t_contact_calendar_list *list, int id);

t_contact_calendar_cell* searchContactCalendar(char *partialName, t_contact_calendar_list *list);
#endif //DAYLIST_CONTACTCALENDAR_H
