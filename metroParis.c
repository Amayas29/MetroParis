#include <stdio.h>
#include <stdlib.h>
#include "ligne.h"

int main(void) {
    int nombre = 0;
    Ligne **lignes = lireLignes("lignes.db", &nombre);
    if(lignes) {

        for(int i = 0; i < nombre; i++)
            printLigne(lignes[ i ]);

        for(int i = 0; i < nombre; i++)
            detruireLigne(&lignes[ i ]);
        free(lignes);
    }
    return 0;
}