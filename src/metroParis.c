#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metro.h"
#include "dijkstra.h"

int main(void) {
    int numbre = 0;
    ListStations *list = NULL;

    Line **lines = readLines("../ressources/lines.db", &numbre, &list);

    int numberStations = 0;
    Station ** tab = buildMetroStructure(list, &numberStations);
    
    // char buf[100];
    // printf("Donner ville : ");
    // fgets(buf, 100, stdin);
    // buf[strlen(buf) - 1] = '\0';

    // Station *s = getStation(list, buf);
    // printf("%d %s\n", s->id, s->name);
    // Station *m = tab[s->id];
    // printf("%d %s\n", m->id, m->name);

    ListStations *d = dijkstraTime(tab, numberStations, lines, 2, 190);

    for(ListStations *t = d; t; t = t->next) 
        printf("\t%s\n ", t->station->name);
    
    destroyListStations(d);
    
    free(tab);
    destroyListStations(list);

        if(lines) {
        for(int i = 0; i < numbre; i++)
            destoryLine(lines[ i ]);
        free(lines);
    }

    return 0;
}