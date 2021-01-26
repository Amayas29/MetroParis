#include <stdio.h>
#include <stdlib.h>
#include "line.h"

int main(void) {
    int numbre = 0;
    Line **lines = readLines("lines.db", &numbre);
    if(lines) {

        for(int i = 0; i < numbre; i++)
            printLigne(lines[ i ]);

        for(int i = 0; i < numbre; i++)
            destoryLine(lines[ i ]);
        free(lines);
    }
    return 0;
}