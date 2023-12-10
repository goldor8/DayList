//
// Created by dimgo on 10/12/2023.
//

#include <stdlib.h>
#include <string.h>
#include "stringUtil.h"

char* stringcpy(const char* original) {

    int size = strlen(original) ;
    char* copy = malloc(size + 1);

    int i;
    for(i = 0; original[i] != '\0'; i++) {
        copy[i] = original[i];
    }
    copy[i]='\0';
    return copy;
}

int isBefore(const char* first, const char* second) {
    int i;
    for(i = 0; first[i] != '\0' && second[i] != '\0'; i++) {
        if (first[i] < second[i]) {
            return 1;
        } else if (first[i] > second[i]) {
            return 0;
        }
    }
    return 0;
}

int isEqual(const char* first, const char* second) {
    int i;
    for(i = 0; first[i] != '\0' && second[i] != '\0'; i++) {
        if (first[i] != second[i]) {
            return 0;
        }
    }
    return 1;
}

char* getFirstChars(const char* string, int nbChars) {
    char* copy = malloc(nbChars + 1);
    int i = 0;
    while (i < nbChars && string[i] != '\0') {
        copy[i] = string[i];
        i++;
    }
    copy[i]='\0';
    return copy;
}