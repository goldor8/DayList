#include <stdio.h>
#include "levelsList.h"

int main() {
    printf("Hello, World!\n");

    t_levels_list * list = createEmptyList(5);
    t_levels_cell * cell = createCell(1, 5);
    t_levels_cell * cell2 = createCell(2, 5);
    insertCellAtHead(cell, list);
    insertCellAtHead(cell2, list);
    displayListLevel(0, list);
    displayListLevel(1, list);

    for (int i = 0; i < 50; ++i) {
        t_levels_cell* cellTemp = createCell(i, 5);
        insertCell(cellTemp, &list);
    }

    displayList(*list);
    displayPrettyList(*list);

    return 0;
}
