//
// Created by Maxime on 24/10/2023.
//

#ifndef DAYLIST_LEVELSLIST_H
#define DAYLIST_LEVELSLIST_H

typedef struct s_levels_cell
{
    int value;
    int levels;
    struct s_levels_cell **nexts;
} t_levels_cell;

typedef struct s_levels_list
{
    int levels;
    t_levels_cell **heads;
} t_levels_list;

t_levels_cell* createCell(int value, int levels); // Maxime
void freeCell(t_levels_cell* cell);
t_levels_list* createEmptyList(int levels); // Dimitri
void freeList(t_levels_list* list);
void displayListLevel(int level, t_levels_list list); // Maxime
void displayPrettyListLevel(int level, t_levels_list list); // Dimitri
void displayList(t_levels_list list); // Dimitri
void displayPrettyList(t_levels_list list); // Dimitri
void insertCellAtHead(t_levels_cell *cell,t_levels_list * list); // Maxime
void insertCell(t_levels_cell *cell,t_levels_list * list); // Nous deux
void insertCellWithRestrictedLevel(t_levels_cell *cell,t_levels_list * list, int restrictedLevel);
void insertCellNotFast(t_levels_cell *cell, t_levels_list *list);
t_levels_list* create2NLevelsSortedList(int n);
t_levels_cell* findCellInSortedList(int value, t_levels_list list);
t_levels_cell* findCellInSortedListWithRestrictedLevel(int value, t_levels_list list, int restrictedLevel);
t_levels_cell* findCellInSortedListNotFast(int value, t_levels_list list);
int findLastValue(t_levels_list list);

#endif //DAYLIST_LEVELSLIST_H
