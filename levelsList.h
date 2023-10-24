//
// Created by Maxime on 24/10/2023.
//

#ifndef DAYLIST_LEVELSLIST_H
#define DAYLIST_LEVELSLIST_H

typedef struct s_levels_cell
{
    int value;
    int levels;
    struct s_levels_cell *next[];
} t_levels_cell;

typedef struct s_levels_list
{
    int levels;
    t_levels_cell *head[];
} t_levels_list;

t_levels_cell createCell(int value, int levels);
t_levels_list createEmptyList(int levels);
void displayListLevel(int level, t_levels_list list);
void displayList(t_levels_list list);
void displayPrettyList(t_levels_list list);
void insertCellAtHead(t_levels_cell cell,t_levels_list * list);
void insertCell(t_levels_cell cell,t_levels_list * list);

#endif //DAYLIST_LEVELSLIST_H
