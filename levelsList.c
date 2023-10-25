//
// Created by Maxime on 24/10/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "levelsList.h"

t_levels_cell* createCell(int value, int levels){
    t_levels_cell* cell = malloc(sizeof(t_levels_cell));
    cell->value = value;
    cell->nexts = (t_levels_cell**) malloc (levels*sizeof(t_levels_cell*));
    for (int i = 0; i < levels; i++){
        cell->nexts[i] = NULL;
    }
    return cell;
}

void displayListLevel(int level, t_levels_list* list){
    t_levels_cell* current = list->heads[level];
    printf("Level %d : ",level);
    while (current != NULL){
        printf("%d ", current->value);
        current = current->nexts[level];
    }
    printf("\n");
}

void insertCellAtHead(t_levels_cell * cell,t_levels_list * list){
    if (cell->levels > list->levels){
        printf("Out of range");
        return;
    }
    for (int i = 0; i <= cell->levels; i++){
        cell->nexts[i] = list->heads[i];
        list->heads[i] = cell;

    }
}

