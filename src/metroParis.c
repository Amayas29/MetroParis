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
    Station ** stations = buildMetroStructure(list, &numberStations);

    Node *nodes = dijkstraDistance(stations, numberStations, lines, 2, 190);
    Node *p = nodes;

    // for(; p; p = p->next)
    //     printf("%s - %s\n", stations[p->current]->name, lines[p->line - 1]->name);

    printPath(nodes, stations, lines);
    destroyNodes(nodes);
    
    free(stations);
    destroyListStations(list);

    if(lines) {
        for(int i = 0; i < numbre; i++)
            destoryLine(lines[ i ]);
        free(lines);
    }

    return 0;
}