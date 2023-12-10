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
    return appointmentCell;
}

void saveAppointment(t_contact *contact, char *nameFile) {
    if (contact == NULL || ->head == NULL || nameFile == NULL) {
        return;
    }

    FILE *fichier = fopen(nameFile, "w");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    t_contact *currentContact = list->head;

    while (currentContact != NULL) {
        fprintf(fichier, "%s %s\n", currentContact->firstname, currentContact->lastname);
        currentContact = currentContact->next;
    }

    fclose(fichier);
}

void loadAppointmentsFromFile(char *filename, t_appointment_list *appointmentList) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char description[100];  // Ajustez la taille selon vos besoins
    while (fgets(description, sizeof(description), file) != NULL) {
        strlen(description);
        if (strlen(description) > 0 && description[strlen(description) - 1] == '\n') {
            description[strlen(description) - 1] = '\0';
        }
        t_appointment_cell *appointmentCell = (t_appointment_cell *)malloc(sizeof(t_appointment_cell));
        appointmentCell->description = description;
        appointmentCell->next = appointmentList->head;
        appointmentList->head = appointmentCell;
    }

    fclose(file);
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