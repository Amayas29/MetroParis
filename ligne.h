#ifndef __LIGNE_H__
#define __LIGNE_H__

#include "station.h"

typedef struct _ligne {
    char *nom;
    int id;
    int distanceMoyenne;
    int tempsMoyen;
    Station *stations;
} Ligne;

Ligne *creerLigne(char *nom, int id, int distanceMoyenne, int tempsMoyen);
Ligne **lireLignes(char *fileName, int *nombre);
void detruireLigne(Ligne **ligne);
void ajouterStation(Ligne *ligne, char *station);
void printLigne(Ligne *ligne);

#endif