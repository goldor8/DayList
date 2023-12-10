#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "math.h"
#include "contact.h"
#include "contactCalendar.h"
#include "dateTime.h"
#include "contact.h"
#include "highRand.h"

#define RESEARCH_VALUE 100

int main() {
    t_contact_calendar_list *list = createContactCalendarList(4);

    t_contact *contact2 = createContact("Dimitri", "aaaa");
    createContactCalendar(contact2, list);

    t_contact *contact = createContact("Dimitri", "baaa");
    createContactCalendar(contact, list);

    t_contact *contact3 = createContact("Dimitri", "baab");
    createContactCalendar(contact3, list);



    displayPrettyContactCalendarList(*list);

    freeContactCalendarList(list);

    return 0;
}