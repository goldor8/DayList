//
// Created by Dimitri on 23/11/2023.
//

#include "contactCalendar.h"
#include "contact.h"
#include "stringUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void createContactCalendar(t_contact *contact, t_contact_calendar_list *list){
    if (contact == NULL || list == NULL){
        return;
    }
    t_contact_calendar *contactCalendar = (t_contact_calendar *) malloc(sizeof(t_contact_calendar));
    contactCalendar->contact = contact;
    contactCalendar->appointments = createAppointmentList();
    insertContactCalendar(contactCalendar, list);
}

void freeContactCalendar(t_contact_calendar *event){
    freeContact(event->contact);
    freeAppointmentList(event->appointments);
    free(event);
}

t_contact_calendar_cell* createContactCalendarCell(t_contact_calendar *event, int levels){
    t_contact_calendar_cell *cell = (t_contact_calendar_cell *) malloc(sizeof(t_contact_calendar_cell));
    cell->event = event;
    cell->levels = levels;
    cell->nexts = (t_contact_calendar_cell **) malloc(sizeof(t_contact_calendar_cell *) * levels);
    for (int i = 0; i < levels; ++i) {
        cell->nexts[i] = NULL;
    }
    return cell;
}

void freeCalendarCalendarCell(t_contact_calendar_cell* cell){
    freeContactCalendar(cell->event);
    free(cell->nexts);
    free(cell);
}

t_contact_calendar_list* createContactCalendarList(int levels){
    t_contact_calendar_list *list = (t_contact_calendar_list *) malloc(sizeof(t_contact_calendar_list));
    list->levels = levels;
    list->heads = (t_contact_calendar_cell **) malloc(sizeof(t_contact_calendar_cell *) * levels);
    for (int i = 0; i < levels; ++i) {
        list->heads[i] = NULL;
    }
    return list;
}

void freeContactCalendarList(t_contact_calendar_list* list){
    t_contact_calendar_cell * current = list->heads[0];
    t_contact_calendar_cell* next = NULL;
    while (current != NULL){
        next = current->nexts[0];
        freeCalendarCalendarCell(current);
        current = next;
    }
    free(list->heads);
    free(list);
}

void displayAppointmentFromContactCalendar(t_contact_calendar_list *list){
    if (list == NULL || list->heads == NULL){
        return;
    }
    t_contact_calendar_cell * current = list->heads[0];
    while (current != NULL){
        printf("Contact : %s %s\n", current->event->contact->firstname, current->event->contact->lastname);
        t_appointment_cell * currentAppointment = current->event->appointments->head;
        while (currentAppointment != NULL){
            printf("Appointment : %s %s %s %s\n", currentAppointment->description, currentAppointment->date, currentAppointment->startTime, currentAppointment->duration);
            currentAppointment = currentAppointment->next;
        }
        current = current->nexts[0];
    }
}

void displayContactCalendarListLevel(int level, t_contact_calendar_list list){
    if (level >= list.levels){
        printf("cannot display level %d, max level is %d\n", level, list.levels - 1);
        return;
    }
    t_contact_calendar_cell * current = list.heads[level];
    printf("Level %d : ", level);
    printf("HEAD->");
    while (current != NULL){
        printf("%s->", current->event->contact->firstname);
        current = current->nexts[level];
    }
    printf("NULL\n");
}
void displayPrettyContactCalendarListLevel(int level, t_contact_calendar_list list){
    if (level >= list.levels){
        printf("cannot display level %d, max level is %d\n", level, list.levels - 1);
        return;
    }
    char* format = "[%s | @]";
    t_contact_calendar_cell * cell = list.heads[level];
    t_contact_calendar_cell * lowPrevious = list.heads[0];
    printf("Level %d : [HEAD | @]", level);
    while (cell != NULL){
        while (lowPrevious != cell){
            for (int i = 0; i < 9 + strlen(lowPrevious->event->contact->lastname); ++i) {
                printf("-");
            }
            lowPrevious = lowPrevious->nexts[0];
        }
        printf("-->");
        printf(format, cell->event->contact->lastname);
        cell = cell->nexts[level];
        lowPrevious = lowPrevious->nexts[0];
    }
    while (lowPrevious != cell){
        for (int i = 0; i < 9 + strlen(lowPrevious->event->contact->lastname); ++i) {
            printf("-");
        }
        lowPrevious = lowPrevious->nexts[0];
    }
    printf("-->NULL\n");
}
void displayContactCalendarList(t_contact_calendar_list list) {
    for (int i = 0; i < 5; ++i) {
        displayContactCalendarListLevel(i, list);
    }
}
void displayPrettyContactCalendarList(t_contact_calendar_list list){
    for (int i = 0; i < list.levels; ++i) {
        displayPrettyContactCalendarListLevel(i, list);
    }
}

void insertContactCalendar(t_contact_calendar *contactCalendar, t_contact_calendar_list * list){
    if(contactCalendar == NULL || list == NULL) {
        printf("Error: contactCalendar or list is NULL\n");
        return;
    }

    int searchLevel = list->levels - 1;
    t_contact_calendar_cell *current = list->heads[searchLevel];
    if(current == NULL){
        t_contact_calendar_cell *newCell = createContactCalendarCell(contactCalendar, list->levels);

        for (int i = 0; i < searchLevel + 1; ++i) {
            list->heads[i] = newCell;
        }
        return;
    }

    if(isBefore(contactCalendar->contact->lastname, current->event->contact->lastname)){
        t_contact_calendar_cell *newCell = createContactCalendarCell(contactCalendar, list->levels);

        for (int i = 0; i < searchLevel + 1; ++i) {
            newCell->nexts[i] = current;
            list->heads[i] = newCell;
        }

        for(int i = searchLevel; i > 0; i--){
            if(isEqual(getFirstChars(contactCalendar->contact->lastname, list->levels - i),
                       getFirstChars(current->event->contact->lastname, list->levels - i))){
                newCell->nexts[i] = current->nexts[i];
            }
            else{
                break;
            }
        }

        return;
    }

    while (searchLevel > 0){
        //move pointer to the cell juste before the one we want to insert depending on the level
        while (current->nexts[searchLevel] != NULL && isBefore(getFirstChars(current->nexts[searchLevel]->event->contact->lastname, list->levels - searchLevel),
                                                               getFirstChars(contactCalendar->contact->lastname, list->levels - searchLevel))){
            current = current->nexts[searchLevel];
        }

        // check if the cell selected has the same first chars as the one we want to insert depending on the level
        if(current->nexts[searchLevel] != NULL && isEqual(getFirstChars(current->nexts[searchLevel]->event->contact->lastname, list->levels - searchLevel),
                   getFirstChars(contactCalendar->contact->lastname, list->levels - searchLevel))){
            // if it's the case, we check if the cell we want to insert should be before or after the one we selected
            if(isBefore(contactCalendar->contact->lastname, current->nexts[searchLevel]->event->contact->lastname)){
                t_contact_calendar_cell *newCell = createContactCalendarCell(contactCalendar, searchLevel + 1);
                for (int i = 0; i <= searchLevel; ++i) {
                    newCell->nexts[i] = current->nexts[i];
                    current->nexts[i] = newCell;
                }
                int i;
                for(i = searchLevel; i > 0; i--){
                    if(isEqual(getFirstChars(contactCalendar->contact->lastname, list->levels - i),
                               getFirstChars(newCell->nexts[i]->event->contact->lastname, list->levels - i))){
                        newCell->nexts[i] = newCell->nexts[i]->nexts[i];
                    }
                    else{
                        break;
                    }
                }
                newCell->nexts[i]->levels = i; //lower the level of the current cell, because we inserted a new cell before it and first chars are the same

                return;
            }
                //if it should be after we move to the level below
            else{
                searchLevel--;
            }
        }
        //if the first chars are not the same, we insert the cell at the level we are
        else{
            t_contact_calendar_cell *newCell = createContactCalendarCell(contactCalendar, searchLevel + 1);

            for (int i = 0; i < searchLevel + 1; ++i) {
                newCell->nexts[i] = current->nexts[i];
                current->nexts[i] = newCell;
            }
            return;
        }
    }

    while (current->nexts[searchLevel] != NULL && isBefore(current->nexts[searchLevel]->event->contact->lastname, contactCalendar->contact->lastname)){
        current = current->nexts[searchLevel];
    }

    t_contact_calendar_cell *newCell = createContactCalendarCell(contactCalendar, searchLevel + 1);
    if(current->nexts[searchLevel] == NULL){
        current->nexts[searchLevel] = newCell;
        return;
    }
    current->nexts[searchLevel]->nexts[searchLevel] = newCell;
}

void removeAppointmentFromCalendarEvent(t_contact_calendar_list *list, int id)
{
    if (list == NULL || list->heads == NULL)
    {
        return;
    }

    int maxLevel = list->heads[0]->levels;

    for (int level = maxLevel - 1; level >= 0; level--)
    {
        t_contact_calendar_cell *current = list->heads[level];
        t_contact_calendar_cell *prev = NULL;

        while (current != NULL)
        {
            if (current->event->appointments->head->id == id)
            {
                if (prev == NULL)
                {
                    list->heads[level] = current->nexts[0];
                }
                else
                {
                    prev->nexts[level] = current->nexts[level];
                }
                free(current->event->appointments->head->description);
                free(current->event->appointments->head->date);
                free(current->event->appointments->head->startTime);
                free(current->event->appointments->head->duration);
                free(current->event->appointments->head);
                free(current->event->appointments);
                free(current->event->contact->firstname);
                free(current->event->contact->lastname);
                free(current->event->contact);
                free(current->event);
                free(current);
                break;
            }
            prev = current;
            current = current->nexts[level];
        }
    }
}

t_contact_calendar_cell* searchContactCalendar(char *partialName, t_contact_calendar_list *list){
    if (list == NULL || partialName == NULL || strlen(partialName) < 3) {
        return NULL;
    }

    for (t_contact_calendar_cell *currentContact = list->heads[0]; currentContact != NULL; currentContact = currentContact->nexts[0]) {
        if (strncasecmp(currentContact->event->contact->lastname, partialName, strlen(partialName)) == 0) {
            return currentContact;
        }
    }

    return NULL;
}

//void saveAppointment(t_contact *contact, char *nameFile) {
//    if (contact == NULL || ->head == NULL || nameFile == NULL) {
//        return;
//    }
//
//    FILE *fichier = fopen(nameFile, "w");
//
//    if (fichier == NULL) {
//        perror("Erreur lors de l'ouverture du fichier");
//        return;
//    }
//
//    t_contact *currentContact = list->head;
//
//    while (currentContact != NULL) {
//        fprintf(fichier, "%s %s\n", currentContact->firstname, currentContact->lastname);
//        currentContact = currentContact->next;
//    }
//
//    fclose(fichier);
//}
//
//void loadAppointmentsFromFile(char *filename, t_appointment_list *appointmentList) {
//    FILE *file = fopen(filename, "r");
//    if (file == NULL) {
//        perror("Erreur lors de l'ouverture du fichier");
//        exit(EXIT_FAILURE);
//    }
//
//    char description[100];  // Ajustez la taille selon vos besoins
//    while (fgets(description, sizeof(description), file) != NULL) {
//        strlen(description);
//        if (strlen(description) > 0 && description[strlen(description) - 1] == '\n') {
//            description[strlen(description) - 1] = '\0';
//        }
//        t_appointment_cell *appointmentCell = (t_appointment_cell *)malloc(sizeof(t_appointment_cell));
//        appointmentCell->description = description;
//        appointmentCell->next = appointmentList->head;
//        appointmentList->head = appointmentCell;
//    }
//
//    fclose(file);
//}