//
// Created by dimgo on 10/12/2023.
//

#include <stdio.h>
#include "App.h"
#include "commands.h"
#include "contactCalendar.h"

int running = 0;
t_contact_calendar_list *list = NULL;

void startApp() {
    running = 1;
    printf("Welcome to DayList !\n");

    InitCommands();
    list = createContactCalendarList(4);

    printf("Type 'help' for a list of commands.\n");
    while (running) {
        ReadCommand();
    }

    FreeCommands();
    printf("Goodbye!\n");
}

void stopApp() {
    running = 0;
}

void appSaveCalendar(){
    saveAppointment(list);
}

void appLoadCalendar(){
    loadAppointment(list);
}

void appAddContact(char *firstname, char *lastname) {
    t_contact *contact = createContact(firstname, lastname);
    createContactCalendar(contact, list);
}

void appSearchContact(char *partialLastname) {
    t_contact_calendar_cell* contactCalendarCell = searchContactCalendar(partialLastname, list);
    if(contactCalendarCell != NULL){
        printf("Contact found: %s %s\n", contactCalendarCell->event->contact->firstname, contactCalendarCell->event->contact->lastname);
    } else {
        printf("Contact not found\n");
    }
}

void appAddAppointment(char *description, t_date *date, t_time *startTime, t_time *duration, char *firstname, char *lastname) {
    t_contact_calendar_cell* contactCalendarCell = searchContactCalendar(lastname, list);
    t_appointment_cell *appointmentCell = createAppointment(description, date, startTime, duration);
    if(contactCalendarCell != NULL){
        addAppointment(contactCalendarCell->event->contact, appointmentCell, list);
    } else {
        printf("Contact not found, creating new one\n");
        t_contact *contact = createContact(firstname, lastname);
        createContactCalendar(contact, list);
        addAppointment(contact, appointmentCell, list);
    }
}

void appRemoveAppointment(int id) {
    removeAppointmentFromCalendarEvent(list, id);
}

void appShowAppointments(char *lastname) {
    t_contact_calendar_cell* contactCalendarCell = searchContactCalendar(lastname, list);
    if(contactCalendarCell != NULL){
        displayAppointmentFromContactCalendar(list, contactCalendarCell->event->contact->lastname);
    } else {
        printf("Contact not found\n");
    }
}

void appShowContacts() {
    displayPrettyContactCalendarList(*list);
}





