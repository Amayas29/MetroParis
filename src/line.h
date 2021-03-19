#ifndef __LINE_H__
#define __LINE_H__

#include "station.h"

typedef struct _line {
    char *name;
    int id;
    int average_dist;
    int average_time;
} Line;

Line *create_line(char *name, int id, int average_dist, int average_time);
Line **read_lines(char *fileName, int *number, ListStations **list);
void destory_line(Line *line);
void print_ligne(Line *line);

#endif