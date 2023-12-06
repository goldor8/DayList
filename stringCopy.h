//
// Created by Dimitri on 30/11/2023.
//

#ifndef DAYLIST_STRINGCOPY_H
#define DAYLIST_STRINGCOPY_H
#include <stdlib.h>
#include <string.h>

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

#endif //DAYLIST_STRINGCOPY_H
