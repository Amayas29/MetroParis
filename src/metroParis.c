#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metro.h"

int main(void) {
    int numbre = 0;
    ListStations *list = NULL;

    Line **lines = readLines("../ressources/lines.db", &numbre, &list);
    if(lines) {
        for(int i = 0; i < numbre; i++)
            destoryLine(lines[ i ]);
        free(lines);
    }

    int numberStations = 0;
    Station ** tab = buildMetroStructure(list, &numberStations);
    
    char buf[100];
    printf("Donner ville : ");
    fgets(buf, 100, stdin);
    buf[strlen(buf) - 1] = '\0';

    Station *s = getStation(list, buf);
    printf("%d %s\n", s->id, s->name);
    Station *m = tab[s->id];
    printf("%d %s\n", m->id, m->name);

    free(tab);
    destroyListStations(list);
    return 0;
}