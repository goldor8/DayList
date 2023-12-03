//
// Created by Maxime on 30/11/2023.
//

#include "appointment.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


t_appointment_cell * createAppointment(char *description, t_date *date, t_time *startTime, t_time *duration){
    t_appointment_cell *appointmentCell = (t_appointment_cell *) malloc(sizeof(t_appointment_cell));
    appointmentCell->description = description;
    appointmentCell->date = date;
    appointmentCell->startTime = startTime;
    appointmentCell->duration = duration;
    return appointmentCell;
}

void saveAppointment(t_contact_list *list, char *nameFile) {
    if (list == NULL || list->head == NULL || nameFile == NULL) {
        return;
    }

    FILE *fichier = fopen(nameFile, "w");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    t_contact_cell *currentContact = list->head;

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
        // Supprimer le saut de ligne à la fin de la description
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