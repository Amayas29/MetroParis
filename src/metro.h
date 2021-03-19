#ifndef __METRO_H__
#define __METRO_H__

#include "line.h"

Station **build_metro_structure(ListStations *list, int *number);
void reduce_path(ListStations *list);

#endif