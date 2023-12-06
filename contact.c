//
// Created by Dimitri on 23/11/2023.
//
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "stringCopy.h"

void createContact(char *firstname, char *lastname, t_contact_list *list) {
    t_contact_cell *cell = (t_contact_cell *) malloc(sizeof(t_contact_cell));
    cell->firstname = stringcpy(firstname);
    cell->lastname = stringcpy(lastname);
    cell->next = list->head;
    list->head = cell;
}

void addContact(t_contact_list *list, char *firstname, char *lastname) {
    t_contact_cell *newContact = (t_contact_cell *)malloc(sizeof(t_contact_cell));
    newContact->firstname = firstname;
    newContact->lastname = lastname;
    newContact->next = list->head;
    list->head = newContact;
}

t_contact_cell *searchContact(char* partialName, t_contact_list *list) {
    if (list == NULL || partialName == NULL || strlen(partialName) < 3 || list->head == NULL) {
        return NULL;
    }

    for (t_contact_cell *currentContact = list->head; currentContact != NULL; currentContact = currentContact->next) {
        if (strncasecmp(currentContact->firstname, partialName, strlen(partialName)) == 0) {
            return currentContact;
        }
    }

    return NULL;
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

