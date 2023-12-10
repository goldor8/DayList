//
// Created by Dimitri on 23/11/2023.
//

#include "contactCalendar.h"
#include "contact.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_contact_calendar* createContactCalendar(t_contact *contact, t_appointment_cell *appointment) {
    t_contact_calendar *event = (t_contact_calendar *) malloc(sizeof(t_contact_calendar));

    if (event != NULL) {
        event->contact = contact;
        event->appointments = appointment;
        if (event->appointments != NULL) {
            event->appointments->next = NULL;
        }

        return event;
    } else {
        return NULL;
    }
}

void freeContactCalendar(t_contact_calendar *event){
    freeContact(event->contact);
    free(event->appointments->description);
    freeDate(event->appointments->date);
    freeTime(event->appointments->startTime);
    freeTime(event->appointments->duration);
    free(event);
}

t_contact_calendar_cell* createContactCalendarCell(t_contact_calendar *event, int levels){
    t_contact_calendar_cell *cell = (t_contact_calendar_cell *) malloc(sizeof(t_contact_calendar_cell));
    cell->event = event;
    cell->levels = levels;
    cell->nexts = (t_contact_calendar_cell **) malloc(sizeof(t_contact_calendar_cell *) * levels);
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
    int maxCharactersCount = 4;
    char format[12]; // set it to "%" + maxCharactersCount + "d"
    sprintf(format, "[%%0.%ds | @]", maxCharactersCount);
    //maxCharactersCount = 4;
    t_contact_calendar_cell * cell = list.heads[level];
    t_contact_calendar_cell * lowPrevious = list.heads[0];
    printf("Level %d : [HEAD | @]", level);
    while (cell != NULL){
        while (lowPrevious != cell){
            for (int i = 0; i < 9 + maxCharactersCount; ++i) {
                printf("-");
            }
            lowPrevious = lowPrevious->nexts[0];
        }
        printf("-->");
        printf(format, cell->event->contact->firstname);
        cell = cell->nexts[level];
        lowPrevious = lowPrevious->nexts[0];
    }
    while (lowPrevious != cell){
        for (int i = 0; i < 9 + maxCharactersCount; ++i) {
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
void displayPrettyCalendarEventList(t_contact_calendar_list list){
    for (int i = 0; i < 5; ++i) {
        displayPrettyContactCalendarListLevel(i, list);
    }
}
void insertContactCalendarCellAtHead(t_contact_calendar_cell *cell, t_contact_calendar_list * list){
    for (int i = 0; i < cell->levels; ++i) {
        cell->nexts[i] = list->heads[i];
        list->heads[i] = cell;
    }
}
void insertContactCalendarCell(t_contact_calendar_cell *cell, t_contact_calendar_list * list){
    //todo: implement
}

void removeAppointmentFromCalendarEvent(t_contact_calendar_list *list, char *description)
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
            if (strcmp(current->event->appointments->description, description) == 0)
            {
                if (prev == NULL)
                {
                    list->heads[level] = current->nexts[0];
                }
                else
                {
                    prev->nexts[level] = current->nexts[level];
                }
                free(current->event->appointments->description);
                free(current->event->appointments->date);
                free(current->event->appointments->startTime);
                free(current->event->appointments->duration);
                free(current->event->appointments);
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

t_contact_calendar_cell* findCalendarEventInSortedListNotFast(int value, t_contact_calendar_list list){
    //todo: implement
}
t_contact_calendar_cell* findCalenderEventInSortedList(int value, t_contact_calendar_list list){
    //todo: implement
}