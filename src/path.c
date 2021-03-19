#include "path.h"

#include <stdio.h>
#include <stdlib.h>

Path *create_path(int next_station, int corresponding_line) {
    if (corresponding_line < 1) {
        fprintf(stderr, "Number of lines incorrect");
        return NULL;
    }

    Path *path = malloc(sizeof(Path));
    if (!path) {
        fprintf(stderr, "Allocation problem");
        return NULL;
    }

    path->corresponding_line = corresponding_line;
    path->next_station = next_station;
    path->next = NULL;
    return path;
}

void destroy_paths(Path *path) {
    Path *tmp = NULL;
    for (; path;) {
        tmp = path->next;
        free(path);
        path = tmp;
    }
}

Path *add_path_list(Path *list, Path *new) {
    if (!new) return list;

    for (Path *curr = list; curr; curr = curr->next)
        if (curr->next_station == new->next_station && curr->corresponding_line == new->corresponding_line) {
            destroy_paths(new);
            return list;
        }

    new->next = list;
    return new;
}