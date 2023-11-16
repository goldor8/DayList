#include <stdio.h>
#include "levelsList.h"
#include "timer.h"

int main() {
    printf("Hello, World!\n");

    t_levels_list * list = create2NLevelsSortedList(32);

    t_levels_cell* celltest = createCell(1, 3);
    insertCell(celltest, list);

    //displayPrettyList(*list);
    startTimer();
    t_levels_cell* cell = findCellInSortedListNotFast(1000000, *list);
    startTimer();
    displayTime();
    if(cell != NULL){
        printf("Cell found: %d\n", cell->value);
    }
    else{
        printf("Cell not found\n");
    }

    freeList(list);

    return 0;
}
