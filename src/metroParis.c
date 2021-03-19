#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metro.h"
#include "dijkstra.h"

int main(void) {
    int numbre = 0;
    ListStations *list = NULL;

    Line **lines = read_lines("../ressources/lines.db", &numbre, &list);

    int number_stations = 0;
    Station ** stations = build_metro_structure(list, &number_stations);

    Node *nodes = dijkstra_distance(stations, number_stations, lines, 2, 190);
    Node *p = nodes;

    // for(; p; p = p->next)
    //     printf("%s - %s\n", stations[p->current]->name, lines[p->line - 1]->name);

    print_path(nodes, stations, lines);
    destroy_nodes(nodes);
    
    free(stations);
    destroy_list_stations(list);

    if(lines) {
        for(int i = 0; i < numbre; i++)
            destory_line(lines[ i ]);
        free(lines);
    }

    return 0;
}