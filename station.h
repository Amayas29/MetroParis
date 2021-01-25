#ifndef __STATION_H__
#define __STATION_H__

#include "chemin.h"

typedef struct _station {
    char *nom;
    struct _station *suivant;
} Station;

Station *creerStation(char *nom);
void ajouterChemin(Station *station, Chemin *chemin);
void detruireStation(Station **station);
void ajouterStationDansListe(Station **stations, char *station);

#endif