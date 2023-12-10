//
// Created by Dimitri on 30/11/2023.
//

#ifndef DAYLIST_STRINGUTIL_H
#define DAYLIST_STRINGUTIL_H

char* stringcpy(const char* original);

int isBefore(const char* first, const char* second);

int isEqual(const char* first, const char* second);

char* getFirstChars(const char* string, int nbChars);

#endif //DAYLIST_STRINGUTIL_H
