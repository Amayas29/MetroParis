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

Node *dijkstraTime(Station **stations, int numberStations, Line **lines, int src, int dest);
Node *dijkstraDistance(Station **stations, int numberStations, Line **lines, int src, int dest);
void destroyNodes(Node *nodes);
void printPath(Node *nodes, Station **stations, Line **lines);

#endif