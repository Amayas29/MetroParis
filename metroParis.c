#include <stdio.h>
#include <stdlib.h>
#include "line.h"

int main(void) {
    int numbre = 0;
    ListStations *list = NULL;

    Line **lines = readLines("lines.db", &numbre, &list);
    if(lines) {

        //for(int i = 0; i < numbre; i++)
            //printLigne(lines[ i ]);

        for(int i = 0; i < numbre; i++)
            destoryLine(lines[ i ]);
        free(lines);
    }

    for(ListStations *l = list; l; l = l->next) {
        printf("%s %d: \n", l->station->name, l->station->id);
        for(; l->station->paths; l->station->paths = l->station->paths->next)
            printf("\t %d - %d\n", l->station->paths->nextStation, l->station->paths->correspondingLine);
        
    }

    destroyListStations(list);
    return 0;
}