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
t_levels_list* createEmptyList(int levels); // Dimitri
void displayListLevel(int level, t_levels_list* list); // Maxime
void displayList(t_levels_list list); // Dimitri
void displayPrettyList(t_levels_list list); // Dimitri
void insertCellAtHead(t_levels_cell * cell,t_levels_list * list); // Maxime
void insertCell(t_levels_cell * cell,t_levels_list * list); // Nous deux

#endif //DAYLIST_LEVELSLIST_H
