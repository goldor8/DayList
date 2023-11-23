//
// Created by Dimitri on 23/11/2023.
//

#ifndef DAYLIST_CONTACT_H
#define DAYLIST_CONTACT_H

typedef struct s_contact_cell
{
    char *firstname;
    char *lastname;
    struct s_contact_cell *next;
} t_contact_cell;

typedef struct s_contact_list
{
    t_contact_cell *head;
} t_contact_list;

void createContact(char *firstname, char *lastname, t_contact_list *list);
void freeContactCell(t_contact_cell *cell);
t_contact_list* createContactList();
void freeContactList(t_contact_list *list);


#endif //DAYLIST_CONTACT_H
