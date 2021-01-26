#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metro.h"

Station **buildMetroStructure(ListStations *list, int *numberStations) {
    
    *numberStations = getNumberStations(list);
    if(!*numberStations) return NULL;

    Station **tab = malloc(sizeof(Station *) * *numberStations);
    if(!tab) {
        fprintf(stderr, "Allocation problem");
        return NULL;
    }

    for(; list; list = list->next)
        tab[ list->station->id ] = list->station;

    return tab;
}

void reducePath(ListStations *list) {
    
}