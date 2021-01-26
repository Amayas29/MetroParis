#ifndef __STATION_H__
#define __STATION_H__

#include "path.h"

typedef struct _station {
    char *name;
    Path *paths;
} Station;

typedef struct _listStations {
    Station *station;
    struct _listStations *next;
} ListStations;

Station *createStation(char *name);
void addPath(Station *station, Path *path);
void destroyStation(Station *station);
ListStations *addStationToList(ListStations *list, Station *station);
void destroyListStations(ListStations *list);

#endif