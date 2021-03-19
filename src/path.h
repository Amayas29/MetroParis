#ifndef __PATH_H_
#define __PATH_H_

typedef struct _path {
    int next_station;
    int corresponding_line;
    struct _path *next;
} Path;

Path *create_path(int next_station, int corresponding_line);
void destroy_paths(Path *path);
Path *add_path_list(Path *list, Path *new);

#endif