#include <stdlib.h>
#include "dijkstra.h"

ListStations *dijkstraDistance(Station **stations, Line **lines, int src, int dest) {
    return _djikstra(stations, lines, src, dest, 0);
}

ListStations *dijkstraTime(Station **stations, Line **lines, int src, int dest) {
    return _djikstra(stations, lines, src, dest, 1);
}

static ListStations *_djikstra(Station **stations, Line **lines, int src, int dest, int time) {
    ListStations *djiksPath = NULL;
    Node *queue = NULL;
    Node *save = NULL;
    
    save = _addToQueue(save, createNode(src, -1, 0));
    queue = _addToQueue(save, createNode(src, -1, 0));

    while(1) {

    }

    return djiksPath;
}

static Node *createNode(int current, int previous, int value) {

    Node *node = malloc(sizeof(Node));
    if(!node) return NULL;

    node->current = current;
    node->previous = previous;
    node->value = value;
    node->next = NULL;
    return node;
}

static int _getMinimum(Node *queue, Station **stations, Line **lines, int time) {
    int min = -1;
    int minValue = 0;
    int value;

    for(; queue; queue = queue->next) {
        if(time == 1)
            value = lines[stations[queue->current]->id]->averageTime;
        else
            value = lines[stations[queue->current]->id]->averageDist;

        if(min = -1) {
            min = queue->current;
            minValue = value;
        }
        
        if(value < minValue) {
            min = queue->current;
            minValue = value;
        }
    }

    return min;
}

static Node *_addToQueue(Node *queue, Node *node) {
    Node *curr = queue;

    for(; curr; curr=curr->next)
        if(curr->current == node->current && node->value < curr->value) {
            curr->value = node->value;
            curr->previous = node->previous;
            free(node);
            return queue;
        }

    node->next = queue;
    return node;
}

static Node *_removeFromQueue(Node *queue, int current) {
    if(!queue) return NULL;

    Node *tmp = NULL;
    if(queue->current == current) {
        tmp = queue->next;
        free(queue);
        return tmp;
    }

    tmp = queue;
    for(; tmp->next && tmp->next->current != current; tmp = tmp->next);

    Node *del = tmp->next;
    if(!del) return queue;

    tmp->next = del->next;
    free(del);
    return queue;
}