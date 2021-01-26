#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "line.h"

Line *createLine(char *name, int id, int averageDist, int averageTime) {

    if (!name) {
        fprintf(stderr, "The line name is not valid");
        return NULL;
    }

    if(id < 1) {
        fprintf(stderr, "The line id is not valid");
        return NULL;
    }

    Line *line = malloc(sizeof(Line));
    if (!line) {
        fprintf(stderr, "Allocation problem");
        return NULL;
    }

    line->name = strdup(name);
    line->id = id;
    line->averageDist = averageDist;
    line->averageTime = averageTime;
    return line;
}

void destoryLine(Line *line) {

    if (!line)
        return;

    free(line->name);
    free(line);
}

Line **readLines(char *fileName, int *numberLines, ListStations **list) {

    if(!list) return NULL;

    *list = NULL;
    *numberLines = -1;
    int id, avgTime, avgDist;
    char BUFFER[3000], lineName[100], stationName[100];
    int start, j, k, i = 0;

    FILE *f = fopen(fileName, "r");
    
    if(!f) {
        fprintf(stderr, "The file %s could not be opened", fileName);
        return NULL;
    }

    Line **lines = NULL;
    Station *st = NULL;

    if(!fgets(BUFFER, 3000, f)) {
        fprintf(stderr, "Reading problem");
        fclose(f);
        return NULL;
    }
  
    if(sscanf(BUFFER, " %d", numberLines) != 1) {
        *numberLines = -1;
        fprintf(stderr, "Reading problem : The number of lines is not specified in the file");
        fclose(f);
        return NULL;
    }

    lines = malloc(sizeof(Line *) * *numberLines);
    if(lines == NULL) {
        fprintf(stderr, "Allocation problem");
        *numberLines = -1;
        fclose(f);
        return NULL;
    }

    while(fgets(BUFFER, 3000, f) && i < *numberLines) {
        BUFFER[strlen(BUFFER) - 1] = '\0';

        if(sscanf(BUFFER, " %d %s ( %d , %d ) : ", &id, lineName, &avgTime, &avgDist) != 4) {
            fprintf(stderr, "Reading problem");
            continue;
        }

        if(id < i+1)
            i--;
        else
            lines[i] = createLine(lineName, id, avgDist, avgTime);
        
        for(j = 0; *(BUFFER+(j++)) != ':'; );

        start = j;
        for(; *(BUFFER+j); ) {
            
            start = j;
            while(*(BUFFER+j) && *(BUFFER+j) != '#' && *(BUFFER+j) != '|') j++;
            strncpy(stationName, BUFFER+start, j-start);
            stationName[j-start] = '\0';

            st = addStationToList(list, stationName);

            char nxt = *(BUFFER+j);
            if(!*(BUFFER+j)) continue;

            j++;
            start = j;
            k = j;

            while(*(BUFFER+k) && *(BUFFER+k) != '#' && *(BUFFER+k) != '|') k++;
            strncpy(stationName, BUFFER+start, k-start);
            stationName[k-start] = '\0';
         
            Station *next = addStationToList(list, stationName);
     
            addPath(st, createPath(next->id, lines[i]->id));
 
            if(nxt == '#')
                addPath(next, createPath(st->id, lines[i]->id));
        }
        i++;
    }

    fclose(f);
    return lines;
}

void printLigne(Line *line) {
    if(!line) return;
    printf("%s %d (%d, %d)\n", line->name, line->id, line->averageTime, line->averageDist);
}