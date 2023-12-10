#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "levelsList.h"
#include "timer.h"
#include "math.h"
#include "contact.h"
#include "calendarEvent.h"
#include "dateTime.h"
#include "contact.h"
#include "highRand.h"

#define RESEARCH_VALUE 100

int main() {
    printf("Hello, World!\n");
    printf("Entrer le nombre de niveau de la liste\n");
    int levels;
    scanf("%d", &levels);

    t_levels_list * list = create2NLevelsSortedList(levels);

    //t_levels_cell* celltest = createCell(2, 2);
    //insertCellWithRestrictedLevel(celltest, list, 1);

    printf("Last value: %d\n", findLastValue(*list));
    //displayPrettyList(*list);

    srand(time(NULL));
    int maxResearchValue = (int) pow(2,levels) - 1;

    startTimer();
    for (int i = 0; i < RESEARCH_VALUE; ++i) {
        int value = highRand() % maxResearchValue + 1;
        t_levels_cell* cell = findCellInSortedListWithRestrictedLevel(value, *list, 1);
        if(cell == NULL){
            printf("Cell not found while searching : %d\n", value);
        }
    }
    stopTimer();
    displayTime();


    startTimer();
    for (int i = 0; i < RESEARCH_VALUE; ++i) {
        int value = highRand() % maxResearchValue + 1;
        t_levels_cell* cell = findCellInSortedList(value, *list);
        if(cell == NULL){
            printf("Cell not found while searching : %d\n", value);
        }
    }
    stopTimer();
    displayTime();

    freeList(list);


    scanf("%d");

    for (int i = 0; i < 100; ++i) {
        printf("%d\n", highRand() % 10);
    }

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