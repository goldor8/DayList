//
// Created by Dimitri on 23/11/2023.
//

#include "calendarEvent.h"
#include "contact.h"
#include <stdlib.h>
#include <stdio.h>

t_calendar_event* createCalendarEvent(t_contact_cell *contact, t_appointment_cell *appointment) {
    t_calendar_event *event = (t_calendar_event *) malloc(sizeof(t_calendar_event));

    if (event != NULL) {
        event->contact = contact;
        event->appointment = appointment;
        if (event->appointment != NULL) {
            event->appointment->next = NULL;
        }

        return event;
    } else {
        return NULL;
    }
}


void freeCalendarEvent(t_calendar_event *event){
    freeContactCell(event->contact);
    free(event->appointment->description);
    freeDate(event->appointment->date);
    freeTime(event->appointment->startTime);
    freeTime(event->appointment->duration);
    free(event);
}

t_calendar_event_cell* createCalendarEventCell(t_calendar_event *event, int levels){
    t_calendar_event_cell *cell = (t_calendar_event_cell *) malloc(sizeof(t_calendar_event_cell));
    cell->event = event;
    cell->levels = levels;
    cell->nexts = (t_calendar_event_cell **) malloc(sizeof(t_calendar_event_cell *) * levels);
}

void freeCalendarEventCell(t_calendar_event_cell* cell){
    freeCalendarEvent(cell->event);
    free(cell->nexts);
    free(cell);
}

t_calendar_event_list* createCalendarEventList(int levels){
    t_calendar_event_list *list = (t_calendar_event_list *) malloc(sizeof(t_calendar_event_list));
    list->heads = (t_calendar_event_cell **) malloc(sizeof(t_calendar_event_cell *) * levels);
    for (int i = 0; i < levels; ++i) {
        list->heads[i] = NULL;
    }
    return list;
}

void freeCalendarEventList(t_calendar_event_list* list){
    t_calendar_event_cell * current = list->heads[0];
    t_calendar_event_cell* next = NULL;
    while (current != NULL){
        next = current->nexts[0];
        freeCalendarEventCell(current);
        current = next;
    }
    free(list->heads);
    free(list);
}

void displayCalendarEventListLevel(int level, t_calendar_event_list list){
    t_calendar_event_cell * current = list.heads[level];
    printf("Level %d : ", level);
    printf("HEAD->");
    while (current != NULL){
        printf("%s->", current->event->contact->firstname);
        current = current->nexts[level];
    }
    printf("NULL\n");
}
void displayPrettyCalendarEventListLevel(int level, t_calendar_event_list list){
    int maxCharactersCount = 4;
    char format[12]; // set it to "%" + maxCharactersCount + "d"
    sprintf(format, "[%%0.%ds | @]", maxCharactersCount);
    //maxCharactersCount = 4;
    t_calendar_event_cell * cell = list.heads[level];
    t_calendar_event_cell * lowPrevious = list.heads[0];
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
void displayCalendarEventList(t_calendar_event_list list) {
    for (int i = 0; i < 5; ++i) {
        displayCalendarEventListLevel(i, list);
    }
}
void displayPrettyCalendarEventList(t_calendar_event_list list){
    for (int i = 0; i < 5; ++i) {
        displayPrettyCalendarEventListLevel(i, list);
    }
}
void insertCalendarEventCellAtHead(t_calendar_event_cell *cell, t_calendar_event_list * list){
    for (int i = 0; i < cell->levels; ++i) {
        cell->nexts[i] = list->heads[i];
        list->heads[i] = cell;
    }
}
void insertCalendarEventCell(t_calendar_event_cell *cell,t_calendar_event_list * list){
    //todo: implement
}

t_calendar_event_cell* findCalendarEventInSortedListNotFast(int value, t_calendar_event_list list){
    //todo: implement
}
t_calendar_event_cell* findCalenderEventInSortedList(int value, t_calendar_event_list list){
    //todo: implement
}

