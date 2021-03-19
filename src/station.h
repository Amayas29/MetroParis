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

Station *create_station(int id, char *name);
void add_path(Station *station, Path *path);
void destroy_station(Station *station);
Station *add_station_to_list(ListStations **list, char *station_name);
void destroy_list_stations(ListStations *list);
int get_number_stations(ListStations *list);
Station *get_station(ListStations *list, char *station_name);

#endif