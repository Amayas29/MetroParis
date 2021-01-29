#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"

static Node *_djikstra(Station **stations, int numberStations, Line **lines, int src, int dest, int time);
static Node *createNode(int current, int previous, int value, int line);
static Node *_getMinimum(Node *queue, Node *old);
static Node *_addToQueue(Node *queue, Node *node);
static Node *_removeFromQueue(Node *queue, int current);
static Node *_getNode(Node *save, int curr);
static int _getValue(Line *line, int time);

Node *dijkstraDistance(Station **stations, int numberStations, Line **lines, int src, int dest) {
    return _djikstra(stations, numberStations, lines, src, dest, 0);
}

Node *dijkstraTime(Station **stations, int numberStations, Line **lines, int src, int dest) {
    return _djikstra(stations, numberStations, lines, src, dest, 1);
}

void destroyNodes(Node *nodes) {
    Node *tmp = NULL;
    while(nodes) {
        tmp = nodes->next;
        free(nodes);
        nodes = tmp;
    }
}

void printPath(Node *nodes, Station **stations, Line **lines) {

    int line = -1;
    int oldline = -1;

    Station *src = NULL;
    Station *curr = NULL;

    int value = -1;

    for(; nodes; nodes = nodes->next) {
        
        value = 0;

        if(!src) {
            src = stations[nodes->current];
            curr = src;
            oldline = line = nodes->line;
            value = nodes->value;
        }
        
        int cpt = 0;
        while(oldline == line && nodes && nodes->next) {
            nodes = nodes->next;
            curr = stations[nodes->current];
            oldline = nodes->line;
            value = nodes->value;
            cpt ++;
        }
        printf("%s to %s with %s :: %d --- %d s\n", src->name, curr->name, lines[line - 1]->name, value, cpt);
        src = NULL;
    }      
}

static Node *_djikstra(Station **stations, int numberStations, Line **lines, int src, int dest, int time) {
    if(!stations || !lines) return NULL;

    Node *djiksPath = NULL;
    Node *queue = NULL;
    Node *save = NULL;
    Path *paths = NULL;
    int *alreadyTreated = malloc(sizeof(int) * numberStations);
    if(!alreadyTreated) return NULL;

    for(int i = 0; i < numberStations; i++)
        alreadyTreated[i] = 0;

    save = _addToQueue(save, createNode(src, -1, 0, -1));
    queue = _addToQueue(queue, createNode(src, -1, 0, -1));
    Node *min = NULL;
    int value = 0;

    while(1) {
        min = _getMinimum(queue, min);
  
        if(!min || min->current == dest) break;

        alreadyTreated[min->current] = 1;
        paths = stations[min->current]->paths;

        for(; paths; paths = paths->next) {

            value = _getValue(lines[paths->correspondingLine - 1], time);

            if(alreadyTreated[paths->nextStation] == 0) {
                queue->line = paths->correspondingLine;
                save->line = paths->correspondingLine;

                queue = _addToQueue(queue, createNode(paths->nextStation, min->current, min->value + value, paths->correspondingLine));
                save = _addToQueue(save, createNode(paths->nextStation, min->current, min->value + value, paths->correspondingLine));
            }
        }
        queue = _removeFromQueue(queue, min->current);
    }

    if(min->current == dest) {
        Node *curr = min;
        Node *new = NULL;
        while(curr) {

            new = createNode(curr->current, curr->previous, curr->value, curr->line);
            new->next = djiksPath;
            djiksPath = new;
            curr = _getNode(save, curr->previous);
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

static Node *createNode(int current, int previous, int value, int line) {

    Node *node = malloc(sizeof(Node));
    if(!node) return NULL;

    node->current = current;
    node->previous = previous;
    node->value = value;
    node->line = line;
    node->next = NULL;
    return node;
}

static Node *_getMinimum(Node *queue, Node *old) {
    Node *min = NULL;

    for(; queue; queue = queue->next) {
    
        if(!min)
            min = queue;

        else if(queue->value <= min->value) {
            if(old && old->current == min->current)
                continue;
            min = queue;
        }
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
            curr->line = node->line;
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

static int _getValue(Line *line, int time) {
    if(time == 1) return line->averageTime;
    return line->averageDist;
}