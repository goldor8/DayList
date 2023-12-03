#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "levelsList.h"
#include "timer.h"
#include "contact.h"
#include "calendarEvent.h"
#include "dateTime.h"
#include "contact.h"


int main() {
    printf("Hello, World!\n");

    t_levels_list * list = create2NLevelsSortedList(16);

    t_levels_cell* celltest = createCell(1, 3);
    insertCell(celltest, list);

    printf("Last value: %d\n", findLastValue(*list));

    startTimer();
    t_levels_cell* cell = findCellInSortedListNotFast(1000000000, *list);
    stopTimer();
    displayTime();
    if(cell != NULL){
        printf("Cell found: %d\n", cell->value);
    }
    else{
        printf("Cell not found\n");
    }

    startTimer();
    t_levels_cell* cell2 = findCellInSortedList(1000000000, *list);
    stopTimer();
    displayTime();if(cell2 != NULL){
        printf("Cell found: %d\n", cell2->value);
    }
    else{
        printf("Cell not found\n");
    }

    freeList(list);



/*
    t_contact_list contactList;

    addContact(&contactList, "John", "Doe");
    addContact(&contactList, "Jane", "Smith");
    addContact(&contactList, "Bob", "Johnson");

    printf("Entrez le nom de recherche (à partir de la 3ème lettre) : ");
    char partialName[4];
    partialName[3] = '\0';
    scanf("%s", partialName); // Utilisation de %s pour lire une chaîne de caractères

    // Vérification de la longueur de la chaîne pour s'assurer qu'elle a au moins 3 caractères
    while(strlen(partialName) < 3) {
        printf("Veuillez entrer au moins 3 caractères : ");
        scanf("%s", partialName);
    }
    printf("Recherche en cours pour : %s\n", partialName);

    t_contact_cell *foundContact = searchContact(partialName,&contactList);

    if (foundContact != NULL) {
        printf("Contact trouvé : %s %s\n", foundContact->firstname, foundContact->lastname);
    } else {
        printf("Aucun contact trouvé pour la recherche : %s\n", partialName);
    }
    //freeContactList(&contactList);
    free(foundContact);



*/
    return 0;
}