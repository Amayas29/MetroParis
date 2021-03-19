#include "metro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Station **build_metro_structure(ListStations *list, int *number_stations) {
    *number_stations = get_number_stations(list);
    if (!*number_stations) return NULL;

    Station **tab = malloc(sizeof(Station *) * *number_stations);
    if (!tab) {
        fprintf(stderr, "Allocation problem");
        return NULL;
    }

    for (; list; list = list->next)
        tab[list->station->id] = list->station;

    return tab;
}

void reduce_path(ListStations *list) {
}