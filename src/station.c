#include "station.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Station *create_station(int id, char *name) {
    if (!name) {
        fprintf(stderr, "The name of the station is not valid");
        return NULL;
    }

    Station *station = malloc(sizeof(Station));
    if (!station) {
        fprintf(stderr, "Allocation problem");
        return NULL;
    }

    station->id = id;
    station->name = strdup(name);
    station->paths = NULL;
    return station;
}

void add_path(Station *station, Path *path) {
    if (!station) {
        destroy_paths(path);
        return;
    }

    station->paths = add_path_list(station->paths, path);
}

void destroy_station(Station *station) {
    if (!station) return;

    free(station->name);
    destroy_paths(station->paths);
    free(station);
}

Station *add_station_to_list(ListStations **list, char *station_name) {
    if (!station_name) return NULL;

    int id = 0;
    ListStations *ls = *list;
    for (; ls; ls = ls->next, id++)
        if (strcmp(ls->station->name, station_name) == 0)
            return ls->station;

    ListStations *new = malloc(sizeof(ListStations));
    if (!new) return NULL;

    new->station = create_station(id, station_name);
    new->next = *list;
    *list = new;

    return new->station;
}

void destroy_list_stations(ListStations *list) {
    ListStations *tmp = NULL;
    for (; list;) {
        tmp = list->next;
        destroy_station(list->station);
        free(list);
        list = tmp;
    }
}

int get_number_stations(ListStations *list) {
    int number = 0;
    for (; list; list = list->next, number++)
        ;
    return number;
}

Station *get_station(ListStations *list, char *station_name) {
    for (; list; list = list->next)
        if (strcmp(list->station->name, station_name) == 0)
            return list->station;

    return NULL;
}