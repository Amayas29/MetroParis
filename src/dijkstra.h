#ifndef __DJIKSTRA_H__
#define __DJIKSTRA_H__

#include "line.h"

typedef struct _node {
    int previous;
    int current;
    int value;
    int line;
    struct _node *next;
} Node;

Node *dijkstra_time(Station **stations, int number_stations, Line **lines, int src, int dest);
Node *dijkstra_distance(Station **stations, int number_stations, Line **lines, int src, int dest);
void destroy_nodes(Node *nodes);
void print_path(Node *nodes, Station **stations, Line **lines);

#endif