#include "line.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Line *create_line(char *name, int id, int average_dist, int average_time) {
    if (!name) {
        fprintf(stderr, "The line name is not valid");
        return NULL;
    }

    if (id < 1) {
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
    line->average_dist = average_dist;
    line->average_time = average_time;
    return line;
}

void destory_line(Line *line) {
    if (!line)
        return;

    free(line->name);
    free(line);
}

Line **read_lines(char *fileName, int *numberLines, ListStations **list) {
    if (!list) return NULL;

    *list = NULL;
    *numberLines = -1;
    int id, avgTime, avgDist;
    char BUFFER[3000], lineName[100], station_name[100];
    int start, j, k, i = 0;

    FILE *f = fopen(fileName, "r");

    if (!f) {
        fprintf(stderr, "The file %s could not be opened", fileName);
        return NULL;
    }

    Line **lines = NULL;
    Station *st = NULL;

    if (!fgets(BUFFER, 3000, f)) {
        fprintf(stderr, "Reading problem");
        fclose(f);
        return NULL;
    }

    if (sscanf(BUFFER, " %d", numberLines) != 1) {
        *numberLines = -1;
        fprintf(stderr, "Reading problem : The number of lines is not specified in the file");
        fclose(f);
        return NULL;
    }

    lines = malloc(sizeof(Line *) * *numberLines);
    if (lines == NULL) {
        fprintf(stderr, "Allocation problem");
        *numberLines = -1;
        fclose(f);
        return NULL;
    }

    while (fgets(BUFFER, 3000, f) && i < *numberLines) {
        BUFFER[strlen(BUFFER) - 1] = '\0';

        if (sscanf(BUFFER, " %d %s ( %d , %d ) : ", &id, lineName, &avgTime, &avgDist) != 4) {
            fprintf(stderr, "Reading problem");
            continue;
        }

        if (id < i + 1)
            i--;
        else
            lines[i] = create_line(lineName, id, avgDist, avgTime);

        for (j = 0; *(BUFFER + (j++)) != ':';)
            ;

        start = j;
        for (; *(BUFFER + j);) {
            start = j;
            while (*(BUFFER + j) && *(BUFFER + j) != '#' && *(BUFFER + j) != '|') j++;
            strncpy(station_name, BUFFER + start, j - start);
            station_name[j - start] = '\0';

            st = add_station_to_list(list, station_name);

            char nxt = *(BUFFER + j);
            if (!*(BUFFER + j)) continue;

            j++;
            start = j;
            k = j;

            while (*(BUFFER + k) && *(BUFFER + k) != '#' && *(BUFFER + k) != '|') k++;
            strncpy(station_name, BUFFER + start, k - start);
            station_name[k - start] = '\0';

            Station *next = add_station_to_list(list, station_name);

            add_path(st, create_path(next->id, lines[i]->id));

            if (nxt == '#')
                add_path(next, create_path(st->id, lines[i]->id));
        }
        i++;
    }

    fclose(f);
    return lines;
}

void print_ligne(Line *line) {
    if (!line) return;
    printf("%s %d (%d, %d)\n", line->name, line->id, line->average_time, line->average_dist);
}