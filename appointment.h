//
// Created by Maxime on 30/11/2023.
//

#ifndef DAYLIST_APPOINTMENT_H
#define DAYLIST_APPOINTMENT_H
#include "dateTime.h"
#include "contact.h"

int GetNextId();

typedef struct s_appointment_cell
{
    int id;
    char *description;
    t_date *date;
    t_time *startTime;
    t_time *duration;
    struct s_appointment_cell *next;
} t_appointment_cell;

typedef struct s_appointment_list
{
    t_appointment_cell *head;
} t_appointment_list;

t_appointment_cell * createAppointment(char *description, t_date *date, t_time *startTime, t_time *duration);
void saveAppointment(t_contact_list *list,char *nameFile);
void loadAppointmentsFromFile(char *filename, t_appointment_list *appointmentList);

#endif //DAYLIST_APPOINTMENT_H
