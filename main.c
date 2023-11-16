#include <stdio.h>
#include "levelsList.h"

int main() {
    printf("Hello, World!\n");

    t_levels_list * list = create2NLevelsSortedList(5);

    t_levels_cell* celltest = createCell(32, 3);
    insertCell(celltest, list);

    displayPrettyList(*list);

    t_levels_cell* cell = findCellInSortedList(11, *list);
    if(cell != NULL){
        printf("Cell found: %d\n", cell->value);
    }
    else{
        printf("Cell not found\n");
    }

    freeList(list);

    return 0;
}
