#include <stdio.h>
#include "levelsList.h"

int main() {
    printf("Hello, World!\n");

    t_levels_list * list = createEmptyList(5);

    for (int i = 0; i < 50; ++i) {
        t_levels_cell* cellTemp = createCell(i, i%6);
        insertCellAtHead(cellTemp, list);
    }

    displayPrettyList(*list);

    freeList(list);

    return 0;
}
