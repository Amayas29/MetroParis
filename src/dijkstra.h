#ifndef __DJIKSTRA_H__
#define __DJIKSTRA_H__

#include "line.h"

typedef struct _node {
    int previous;
    int current;
    int value;
    struct _node *next;
} Node;

ListStations *dijkstraTime(Station **stations, int numberStations, Line **lines, int src, int dest);
ListStations *dijkstraDistance(Station **stations, int numberStations, Line **lines, int src, int dest);

#endif