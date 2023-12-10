//
// Created by Dimitri on 23/11/2023.
//
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "stringUtil.h"

t_contact *createContact(char *firstname, char *lastname) {
    t_contact *contact = (t_contact *) malloc(sizeof(t_contact));
    contact->firstname = stringcpy(firstname);
    contact->lastname = stringcpy(lastname);
    return contact;
}

void freeContact(t_contact *cell) {
    free(cell->firstname);
    free(cell->lastname);
    free(cell);
}

