#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station.h"

Station *createStation(int id, char *name) {
    if(!name) {
        fprintf(stderr, "The name of the station is not valid");
        return NULL;
    }

    Station *station = malloc(sizeof(Station));
    if(!station) {
        fprintf(stderr, "Allocation problem");
        return NULL;
    }

    station->id = id;
    station->name = strdup(name);
    station->paths = NULL;
    return station;
}

void addPath(Station *station, Path *path) {
    if(!station) return;

    station->paths = addPathList(station->paths, path);
}

void destroyStation(Station *station) {

    if(!station) return;

    free(station->name);
    destroyPaths(station->paths);
    free(station);
}

ListStations *addStationToList(ListStations *list, char *stationName) {
    if(!stationName) return list;
    int id = 0;

    ListStations *ls = list;
    for(; ls; ls = ls->next, id++)
        if(strcmp(ls->station->name, stationName))
            break;

    if(id) return list;

    ListStations *new = malloc(sizeof(ListStations));
    if(!new) return list;

    new->station = createStation(id, stationName);
    new->next = list;
    return new;
}

void destroyListStations(ListStations *list) {

    ListStations *tmp = NULL;
    for(; list; ) {
        tmp = list->next;
        destroyStation(list->station);
        free(list);
        list = tmp;
    }
}