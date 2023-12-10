//
// Created by Dimitri on 23/11/2023.
//

#ifndef DAYLIST_CONTACT_H
#define DAYLIST_CONTACT_H

#include "appointment.h"

typedef struct s_contact
{
    char *firstname;
    char *lastname;
} t_contact;

t_contact* createContact(char *firstname, char *lastname);
void freeContact(t_contact *cell);


#endif //DAYLIST_CONTACT_H
