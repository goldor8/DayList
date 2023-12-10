//
// Created by Maxime on 30/11/2023.
//

#include "appointment.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int currentId = 0;

int GetNextId() {
    return currentId++;
}


t_appointment_cell * createAppointment(char *description, t_date *date, t_time *startTime, t_time *duration){
    t_appointment_cell *appointmentCell = (t_appointment_cell *) malloc(sizeof(t_appointment_cell));
    appointmentCell->id = GetNextId();
    appointmentCell->description = description;
    appointmentCell->date = date;
    appointmentCell->startTime = startTime;
    appointmentCell->duration = duration;
    appointmentCell->next = NULL;
    return appointmentCell;
}

void insertAppointment(t_appointment_cell *appointment, t_appointment_list *list){
    if(list->head == NULL){
        list->head = appointment;
        return;
    }
    t_appointment_cell *current = list->head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = appointment;
}

void freeAppointmentList(t_appointment_list *list) {
    t_appointment_cell *current = list->head;
    t_appointment_cell *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

t_appointment_list *createAppointmentList() {
    t_appointment_list* list = (t_appointment_list *) malloc(sizeof(t_appointment_list));
    list->head = NULL;
    return list;
}
