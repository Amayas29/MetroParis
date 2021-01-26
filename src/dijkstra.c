#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"

static ListStations *_djikstra(Station **stations, int numberStations, Line **lines, int src, int dest, int time);
static Node *createNode(int current, int previous, int value);
static Node *_getMinimum(Node *queue);
static Node *_addToQueue(Node *queue, Node *node);
static Node *_removeFromQueue(Node *queue, int current);
static Node *_getNode(Node *save, int curr);

ListStations *dijkstraDistance(Station **stations, int numberStations, Line **lines, int src, int dest) {
    return _djikstra(stations, numberStations, lines, src, dest, 0);
}

ListStations *dijkstraTime(Station **stations, int numberStations, Line **lines, int src, int dest) {
    return _djikstra(stations, numberStations, lines, src, dest, 1);
}

static ListStations *_djikstra(Station **stations, int numberStations, Line **lines, int src, int dest, int time) {
    if(!stations || !lines) return NULL;

    ListStations *djiksPath = NULL;
    Node *queue = NULL;
    Node *save = NULL;
    Path *paths = NULL;
    int *alreadyTreated = malloc(sizeof(int) * numberStations);
    if(!alreadyTreated) return NULL;

    for(int i = 0; i < numberStations; i++)
        alreadyTreated[i] = 0;

    save = _addToQueue(save, createNode(src, -1, 0));
    queue = _addToQueue(queue, createNode(src, -1, 0));
    Node *min = NULL;
    int value = 0;

    while(1) {
        min = _getMinimum(queue);
        printf("%d\n", min->current);
        if(!min || min->current == dest) break;

        alreadyTreated[min->current] = 1;
        paths = stations[min->current]->paths;

        for(; paths; paths = paths->next) {

            if(time == 1)
                value = lines[paths->correspondingLine - 1]->averageTime;
            else
                value = lines[paths->correspondingLine - 1]->averageDist;

            if(alreadyTreated[paths->nextStation] == 0) {
                queue = _addToQueue(queue, createNode(paths->nextStation, min->current, min->value + value));
                save = _addToQueue(save, createNode(paths->nextStation, min->current, min->value + value));
            }
        }
        queue = _removeFromQueue(queue, min->current);
    }

    if(min->current == dest) {
        int curr = min->current;
        while(curr != -1) {
            addStationToList(&djiksPath, stations[curr]->name);
            curr = _getNode(save, curr)->previous;
        }
    }

    Node *tmp = NULL;
    while(queue) {
        tmp = queue->next;
        free(queue);
        queue = tmp;
    }

    while(save) {
        tmp = save->next;
        free(save);
        save = tmp;
    }

    free(alreadyTreated);
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

static Node *_getMinimum(Node *queue) {
    Node *min = NULL;

    for(; queue; queue = queue->next) {
    
        if(!min)
            min = queue;

        else if(queue->value < min->value)
            min = queue;
    }

    return min;
}

static Node *_addToQueue(Node *queue, Node *node) {
    if(!node) return queue;

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

static Node *_getNode(Node *save, int curr) {
    for(; save; save = save->next) {
        if(save->current == curr)  
            return save;
    }

    return NULL;
}