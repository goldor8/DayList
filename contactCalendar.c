//
// Created by Dimitri on 23/11/2023.
//

#include "contactCalendar.h"
#include "contact.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringUtil.h"

void createContactCalendar(t_contact *contact, t_contact_calendar_list *list){
    if (contact == NULL || list == NULL){
        return;
    }
    t_contact_calendar *contactCalendar = (t_contact_calendar *) malloc(sizeof(t_contact_calendar));
    contactCalendar->contact = contact;
    contactCalendar->appointments = createAppointmentList();
    insertContactCalendar(contactCalendar, list);
}

void addAppointment(t_contact *contact, t_appointment_cell *appointment, t_contact_calendar_list *list){
    if (contact == NULL || appointment == NULL || list == NULL){
        return;
    }
    t_contact_calendar_cell *current = list->heads[0];
    if (searchContactCalendar(contact->firstname, list) != NULL){
        while (current != NULL){
            if (strcmp(current->event->contact->firstname, contact->firstname) == 0){
                t_appointment_cell *currentAppointment = current->event->appointments->head;
                while (currentAppointment != NULL){
                    if (currentAppointment->id == appointment->id){
                        printf("Appointment with id %d already exists for %s %s\n", appointment->id, contact->firstname, contact->lastname);
                        return;
                    }
                    currentAppointment = currentAppointment->next;
                }
                return;
            }
            current = current->nexts[0];
        }
    }
    createContactCalendar(contact, list);
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

void displayAppointmentFromContactCalendar(t_contact_calendar_list *list, char *name){
    if (list == NULL || list->heads == NULL || name == NULL){
        return;
    }
    t_contact_calendar_cell *current = list->heads[0];
    //make the best display ever !
    while (current != NULL){
        if (strcmp(current->event->contact->lastname, name) == 0){
            printf("Appointments for %s %s :\n", current->event->contact->firstname, current->event->contact->lastname);
            t_appointment_cell *currentAppointment = current->event->appointments->head;
            while (currentAppointment != NULL){
                printf("    Appointment %d : %s on %d/%d/%d at %d:%d for %d:%d\n", currentAppointment->id, currentAppointment->description, currentAppointment->date->day,currentAppointment->date->month,currentAppointment->date->year, currentAppointment->startTime->hour,currentAppointment->startTime->minute, currentAppointment->duration->hour, currentAppointment->duration->minute);
                currentAppointment = currentAppointment->next;
            }
            return;
        }
        current = current->nexts[0];
    }
    printf("No contact found with the name %s\n", name);
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

void saveAppointment(t_contact_calendar_list *list){
    FILE *file = fopen("appointments.txt", "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (t_contact_calendar_cell *currentContact = list->heads[0]; currentContact != NULL; currentContact = currentContact->nexts[0]) {
        for (t_appointment_cell *currentAppointment = currentContact->event->appointments->head; currentAppointment != NULL; currentAppointment = currentAppointment->next) {
            fprintf(file, "%s %s %d %s %d %d %d %d %d\n", currentContact->event->contact->firstname, currentContact->event->contact->lastname, currentAppointment->id, currentAppointment->description, currentAppointment->date->day, currentAppointment->date->month, currentAppointment->date->year, currentAppointment->startTime->hour, currentAppointment->startTime->minute, currentAppointment->duration->hour, currentAppointment->duration->minute);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void loadAppointment(t_contact_calendar_list *list){
    FILE *file = fopen("appointments.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char firstname[50];
    char lastname[50];
    int id;
    char description[50];
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int durationHour;
    int durationMinute;

    while (fscanf(file, "%s %s %d %s %d %d %d %d %d %d %d", firstname, lastname, &id, description, &day, &month, &year, &hour, &minute, &durationHour, &durationMinute) != EOF) {
        t_contact *contact = createContact(firstname, lastname);
        t_date *date = createDate(day, month, year);
        t_time *startTime = createTime(hour, minute);
        t_time *duration = createTime(durationHour, durationMinute);
        t_appointment_cell *appointment = createAppointment(description, date, startTime, duration);
        addAppointment(contact, appointment, list);
    }

    fclose(file);
}