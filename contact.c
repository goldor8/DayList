//
// Created by Dimitri on 23/11/2023.
//
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "stringCopy.h"

t_contact *searchContact(char* partialName, t_contact_list *list) {
    if (list == NULL || partialName == NULL || strlen(partialName) < 3 || list->head == NULL) {
        return NULL;
    }

    for (t_contact *currentContact = list->head; currentContact != NULL; currentContact = currentContact->next) {
        if (strncasecmp(currentContact->firstname, partialName, strlen(partialName)) == 0) {
            return currentContact;
        }
    }

    return NULL;
}


t_contact *createContact(char *firstname, char *lastname) {
    t_contact *contact = (t_contact *) malloc(sizeof(t_contact));
    contact->firstname = firstname;
    contact->lastname = lastname;
    return contact;
}

void freeContact(t_contact *cell) {
    free(cell->firstname);
    free(cell->lastname);
    free(cell);
}

