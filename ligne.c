#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligne.h"
#include "station.h"

Ligne *creerLigne(char *nom, int id, int distanceMoyenne, int tempsMoyen) {

    if (!nom) {
        fprintf(stderr, "Le nom de la ligne n'est pas valide");
        return NULL;
    }

    if(id < 1) {
        fprintf(stderr, "Le numero de la ligne n'est pas valide");
        return NULL;
    }

    Ligne *ligne = malloc(sizeof(Ligne));
    if (!ligne) {
        fprintf(stderr, "Probleme d'allocation !");
        return NULL;
    }

    ligne->nom = strdup(nom);
    ligne->id = id;
    ligne->distanceMoyenne = distanceMoyenne;
    ligne->tempsMoyen = tempsMoyen;
    ligne->stations = NULL;

    return ligne;
}

void detruireLigne(Ligne **ligne) {

    if (!ligne || !(*ligne))
        return;

    free((*ligne)->nom);
    detruireStation(&(*ligne)->stations);

    free(*ligne);
    *ligne = NULL;
}

void ajouterStation(Ligne *ligne, char *station) {
    if(!station || !ligne)
        return;

    ajouterStationDansListe(&(ligne->stations), station);
}

Ligne **lireLignes(char *fileName, int *nombreLignes) {

    *nombreLignes = 0;
    int id, tempsMoyen, distanceMoyenne;
    char BUFFER[3000], nom[100], stationNom[100];
    int start, j, len, i = 0;

    FILE *f = fopen(fileName, "r");
    
    if(!f) {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert", fileName);
        return NULL;
    }

    Ligne **lignes = NULL;

    if(!fgets(BUFFER, 3000, f)) {
        fprintf(stderr, "Probleme de lecture");
        fclose(f);
        return NULL;
    }
  
    if(sscanf(BUFFER, " %d", nombreLignes) != 1) {
        *nombreLignes = 0;
        fprintf(stderr, "Probleme de lecture : Le nombre de lignes n'est pas specifier dans le fichier");
        fclose(f);
        return NULL;
    }

    lignes = malloc(sizeof(Ligne *) * *nombreLignes);
    if(lignes == NULL) {
        fprintf(stderr, "Probleme d'allocation");
        *nombreLignes = 0;
         fclose(f);
        return NULL;
    }

    while(fgets(BUFFER, 3000, f) && i < *nombreLignes) {
        len = strlen(BUFFER);
        if(BUFFER[len - 1] == '\n')
            len--;
        BUFFER[len] = '\0';

        if(sscanf(BUFFER, " %d %s ( %d , %d ) : ", &id, nom, &tempsMoyen, &distanceMoyenne) != 4) {
            fprintf(stderr, "Probleme de lecture : à la ligne %d ", i);
            continue;
        }
 
        lignes[i] = creerLigne(nom, id, distanceMoyenne, tempsMoyen);
        for(j = 0; *(BUFFER+(j++)) != ':'; );

        len = 0;
        start = j;
        for(; *(BUFFER+j); ) {
            
            start = j;
            while(*(BUFFER+j) && *(BUFFER+j) != '<' && *(BUFFER+j) != '-') j++;
            strncpy(stationNom, BUFFER+start, j-start);
            stationNom[j-start] = '\0';

            ajouterStation(lignes[i], stationNom);

            while(*(BUFFER+j) && (*(BUFFER+j) == '<' || *(BUFFER+j) == '>' || *(BUFFER+j) == '-')) j++;
        }
        i++;
    }

    fclose(f);
    return lignes;
}

void printLigne(Ligne *ligne) {
    if(!ligne)
        return;
    
    printf("%d : %s (%d, %d)\n", ligne->id, ligne->nom, ligne->tempsMoyen, ligne->distanceMoyenne);
    for(Station *station = ligne->stations; station; station = station->suivant)
        printf("\t - %s\n", station->nom);
}