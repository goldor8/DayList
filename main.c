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
    t_contact contactList;

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

    t_contact *foundContact = searchContact(partialName, &contactList);

    if (foundContact != NULL) {
        printf("Contact trouvé : %s %s\n", foundContact->firstname, foundContact->lastname);
    } else {
        printf("Aucun contact trouvé pour la recherche : %s\n", partialName);
    }
    //freeContactList(&contactList);
    free(foundContact);

    return 0;
}