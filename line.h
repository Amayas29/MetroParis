#ifndef __LINE_H__
#define __LINE_H__

#include "station.h"

typedef struct _line {
    char *name;
    int id;
    int averageDist;
    int averageTime;
    ListStations *stations;
} Line;

Line *createLine(char *name, int id, int averageDist, int averageTime);
Line **readLines(char *fileName, int *number);
void destoryLine(Line *line);
void addStation(Line *line, Station *station);
void printLigne(Line *line);

#endif