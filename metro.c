#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metro.h"

Station **buildMetroStructure(ListStations *list, int *number) {
    
    *number = numberStations(list);
    if(!*number) return NULL;

    Station **tab = malloc(sizeof(Station *) * *number);
    if(!tab) {
        fprintf(stderr, "Allocation problem");
        return NULL;
    }

    int i = *number - 1;
    for(; list; list = list->next, i--)
        tab[ i ] = list->station;

    return tab;
}