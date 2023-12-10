//
// Created by dimgo on 10/12/2023.
//

#ifndef DAYLIST_APP_H
#define DAYLIST_APP_H

#include "dateTime.h"

//Initialize the application
void startApp();
//Stop the application
void stopApp();

void appSaveCalendar();
void appLoadCalendar();

void appAddContact(char* firstname, char* lastname);
void appSearchContact(char* partialLastname);
void appShowContacts();

void appAddAppointment(char* description, t_date* date,t_time* startTime, t_time* duration, char* firstname, char* lastname);
void appRemoveAppointment(int id);
void appShowAppointments(char* lastname);

void appLoadNameDataset();

#endif //DAYLIST_APP_H
