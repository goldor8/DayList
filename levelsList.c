//
// Created by Maxime on 24/10/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "levelsList.h"
#include <math.h>

t_levels_list* createEmptyList(int levels){
    t_levels_list* list = (t_levels_list*) malloc(sizeof(t_levels_list));
    list->levels = levels;
    list->heads = (t_levels_cell**) malloc(sizeof(t_levels_cell*) * levels);
    for (int i = 0; i < levels; ++i) {
        list->heads[i] = NULL;
    }

    return list;
}

void freeList(t_levels_list* list){
    t_levels_cell* current = list->heads[0];
    t_levels_cell* next = NULL;
    while (current != NULL){
        next = current->nexts[0];
        freeCell(current);
        current = next;
    }
    free(list->heads);
    free(list);
}

void displayList(t_levels_list list){
    for (int i = 0; i < list.levels; ++i) {
        displayListLevel(i, list);
    }
}

void displayPrettyListLevel(int level, t_levels_list list){
    int maxDigitCount = 4;
    char format[12]; // set it to "%" + maxDigitCount + "d"
    sprintf(format, "[%%0%dd | @]", maxDigitCount);
    //maxDigitCount = 4;
    t_levels_cell* cell = list.heads[level];
    t_levels_cell* lowPrevious = list.heads[0];
    printf("Level %d : [HEAD | @]", level);
    while (cell != NULL){
        while (lowPrevious != cell){
            for (int i = 0; i < 9 + maxDigitCount; ++i) {
                printf("-");
            }
            lowPrevious = lowPrevious->nexts[0];
        }
        printf("-->");
        printf(format, cell->value);
        cell = cell->nexts[level];
        lowPrevious = lowPrevious->nexts[0];
    }
    while (lowPrevious != cell){
        for (int i = 0; i < 9 + maxDigitCount; ++i) {
            printf("-");
        }
        lowPrevious = lowPrevious->nexts[0];
    }
    printf("-->NULL\n");
}

void displayPrettyList(t_levels_list list){
    printf("List with %d levels\n", list.levels);
    for (int i = 0; i < list.levels; ++i) {
        displayPrettyListLevel(i, list);
    }
}
t_levels_cell* createCell(int value, int levels){
    if(levels < 1 ) {
        printf("Error : trying to create cell with level < 1\n");
        return NULL;
    }
    t_levels_cell* cell = (t_levels_cell*) malloc(sizeof(t_levels_cell));
    cell->value = value;
    cell->levels = levels;
    t_levels_cell **nexts = (t_levels_cell**) malloc(sizeof(t_levels_cell*) * levels);
    cell->nexts = nexts;
    for (int i = 0; i < levels; i++){
        cell->nexts[i] = NULL;
    }
    return cell;
}

void freeCell(t_levels_cell* cell){
    free(cell->nexts);
    free(cell);
}

void displayListLevel(int level, t_levels_list list){
    t_levels_cell* current = list.heads[level];
    printf("Level %d : ",level);
    while (current != NULL){
        printf("%d ", current->value);
        current = current->nexts[level];
    }
    printf("\n");
}

void insertCellAtHead(t_levels_cell * cell,t_levels_list * list){
    if(cell == NULL || list == NULL) {
        printf("Error: cell or list is NULL\n");
        return;
    }
    if (cell->levels > list->levels){
        printf("Error: cell level is higher than list level\n");
        return;
    }
    for (int i = 0; i < cell->levels; i++){
        cell->nexts[i] = list->heads[i];
        list->heads[i] = cell;
    }
}

t_levels_list* create2NLevelsSortedList(int n) {
    t_levels_list* list = createEmptyList(n);
    int size = pow(2, n) - 1;
    for (int i = size; i > 0; i--) {
        int level = 1;
        for (int j = 1; j < n; ++j) {
            if (i % (int) pow(2, j) == 0) level++;
        }
        t_levels_cell* cell = createCell(i, level);
        insertCellAtHead(cell, list);
    }
    return list;
}

int findListHeadLevelWithInferiorValue(int value, t_levels_list list){
    int searchingLevel = list.levels-1;
    while (list.heads[searchingLevel] == NULL || list.heads[searchingLevel]->value >= value){
        searchingLevel--;
        if(searchingLevel < 0){
            return -1;
        }
    }
    return searchingLevel;
}

t_levels_cell *findCellInSortedList(int value, t_levels_list list) {
    int searchingLevel = findListHeadLevelWithInferiorValue(value, list);
    if(searchingLevel == -1) return NULL;

    t_levels_cell* current = list.heads[searchingLevel];

    while (current != NULL && current->value != value){
        t_levels_cell* nextOnSearchingLevel = current->nexts[searchingLevel];
        if (nextOnSearchingLevel != NULL && nextOnSearchingLevel->value <= value) {
            current = nextOnSearchingLevel;
        } else {
            searchingLevel--;
            if (searchingLevel < 0) {
                return NULL;
            }
        }
    }
    return current;
}

void insertCell(t_levels_cell *cell, t_levels_list *list) {
    if(cell == NULL || list == NULL) {
        printf("Error: cell or list is NULL\n");
        return;
    }
    if (cell->levels > list->levels){
        printf("Error: cell level is higher than list level\n");
        return;
    }
    int searchingLevel = findListHeadLevelWithInferiorValue(cell->value, *list);
    if(searchingLevel == -1){
        insertCellAtHead(cell, list);
        return;
    }
    for (int i = searchingLevel + 1; i < cell->levels; ++i) {
        cell->nexts[i] = list->heads[i];
        list->heads[i] = cell;
    }
    t_levels_cell* current = list->heads[searchingLevel];
    while (current != NULL && current->value != cell->value){
        t_levels_cell* nextOnSearchingLevel = current->nexts[searchingLevel];
        if (nextOnSearchingLevel != NULL && nextOnSearchingLevel->value < cell->value) {
            current = nextOnSearchingLevel;
        } else {
            if (searchingLevel < cell->levels) {
                cell->nexts[searchingLevel] = current->nexts[searchingLevel];
                current->nexts[searchingLevel] = cell;
            }
            searchingLevel--;
            if (searchingLevel < 0) {
                return;
            }
        }
    }
}

