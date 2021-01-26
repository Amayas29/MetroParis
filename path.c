#include <stdio.h>
#include <stdlib.h>
#include "path.h"

Path *createPath(int nextStation, int correspondingLine) {

    if(correspondingLine < 1) {
        fprintf(stderr, "Number of lines incorrect");
        return NULL;
    }

    Path *path = malloc(sizeof(Path));
    if (!path) {
        fprintf(stderr, "Allocation problem");
        return NULL;
    }

    path->correspondingLine = correspondingLine;
    path->nextStation = nextStation;
    path->next = NULL;
    return path;
}

void destroyPaths(Path *path) {

    Path *tmp = NULL;
    for(; path; ) {
        tmp = path->next;
        free(path);
        path = tmp;
    }
}

Path *addPathList(Path *list, Path *new) {
    if(!new) return list;
    
    for(Path *curr = list; curr; curr = curr->next)
        if(curr->nextStation == new->nextStation && curr->correspondingLine == new->correspondingLine)
            return list;

    new->next = list;
    return new;
}