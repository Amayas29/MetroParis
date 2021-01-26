#ifndef __STATION_H__
#define __STATION_H__

#include "path.h"

typedef struct _station {
    int id;
    char *name;
    Path *paths;
} Station;

typedef struct _listStations {
    Station *station;
    struct _listStations *next;
} ListStations;

Station *createStation(int id, char *name);
void addPath(Station *station, Path *path);
void destroyStation(Station *station);
Station *addStationToList(ListStations **list, char *stationName);
void destroyListStations(ListStations *list);
int numberStations(ListStations *list);
Station *getStation(ListStations *list, char *stationName);

#endif