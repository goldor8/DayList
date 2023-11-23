//
// Created by Dimitri on 23/11/2023.
//

#include <stdlib.h>
#include <string.h>
#include "contact.h"

void createContact(char *firstname, char *lastname, t_contact_list *list) {
    t_contact_cell *cell = (t_contact_cell *) malloc(sizeof(t_contact_cell));
    strcpy(cell->firstname, firstname);
    strcpy(cell->lastname, lastname);
    cell->next = list->head;
    list->head = cell;
}

void freeContactCell(t_contact_cell *cell) {
    free(cell->firstname);
    free(cell->lastname);
    free(cell);
}

t_contact_list *createContactList() {
    t_contact_list *list = (t_contact_list *) malloc(sizeof(t_contact_list));
    list->head = NULL;
    return list;
}

void freeContactList(t_contact_list *list) {
    t_contact_cell *current = list->head;
    t_contact_cell *next = NULL;
    while (current != NULL) {
        next = current->next;
        freeContactCell(current);
        current = next;
    }
    free(list);
}
