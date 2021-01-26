#include <stdio.h>
#include <stdlib.h>
#include "line.h"

int main(void) {
    int numbre = 0;
    ListStations *list = NULL;

    Line **lines = readLines("lines.db", &numbre, &list);
    if(lines) {

        for(int i = 0; i < numbre; i++)
            printLigne(lines[ i ]);

        for(int i = 0; i < numbre; i++)
            destoryLine(lines[ i ]);
        free(lines);
    }
    return 0;
}