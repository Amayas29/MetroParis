#ifndef __DJIKSTRA_H__
#define __DJIKSTRA_H__

#include "line.h"

ListStations *dijkstra(Station **stations, Line **lines, int src, int dest);

#endif