#ifndef __PATH_H_
#define __PATH_H_

typedef struct _path {
   int nextStation;
   int correspondingLine;
   struct _path *next;
} Path;

Path *createPath(int nextStation, int correspondingLine);
void destroyPaths(Path *path);
Path *addPathList(Path *list, Path *new);

#endif