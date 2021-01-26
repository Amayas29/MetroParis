#ifndef __METRO_H__
#define __METRO_H__

#include "line.h"

Station **buildMetroStructure(ListStations *list, int *number);
void reducePath(ListStations *list);
#endif