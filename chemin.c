#include <stdio.h>
#include <stdlib.h>
#include "chemin.h"

Chemin *creerChemin(int stationSuivante, int ligneCorrespondante) {

    if(ligneCorrespondante < 1) {
        fprintf(stderr, "Nombre de ligne incorrect");
        return NULL;
    }

    Chemin *chemin = malloc(sizeof(Chemin));
    if (!chemin) {
        fprintf(stderr, "Probleme d'allocation !");
        return NULL;
    }

    chemin->stationSuivante = stationSuivante;
    chemin->ligneCorrespondante = ligneCorrespondante;
    chemin->suivant = NULL;
    return chemin;
}

void detruireChemin(Chemin **chemin) {
    if (!chemin || !(*chemin))
        return;

    free(*chemin);
    *chemin = NULL;
}