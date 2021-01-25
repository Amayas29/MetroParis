#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station.h"

Station *creerStation(char *nom) {
    
    if(!nom) {
        fprintf(stderr, "Le nom de la stattion n'est pas valide");
        return NULL;
    }

    Station *station = malloc(sizeof(Station));
    if(!station) {
        fprintf(stderr, "Probleme d'allocation !");
        return NULL;
    }

    station->nom = strdup(nom);
    station->suivant = NULL;
    return station;
}

void detruireStation(Station **station) {

    if(!station || !(*station))
        return;
    
    for(Station *s = *station; s; ) {
       Station *t = s;
       s = s->suivant;
       free(t->nom);
       free(t);
    }

    *station = NULL;
}

void ajouterStationDansListe(Station **stations, char *stationNom) {

    if(!stations || !stationNom)
        return;
    
    if(!*stations) {
       *stations = creerStation(stationNom);
       return;
    }

    for(Station *station = *stations; station ; station = station->suivant) {
        if(strcmp(station->nom, stationNom) == 0)
            return;
        if(!station->suivant) {
            station->suivant = creerStation(stationNom);
            return;
        }
    }
}