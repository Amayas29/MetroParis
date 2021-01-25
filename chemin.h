#ifndef __CHEMIN_H_
#define __CHEMIN_H__

typedef struct _chemin {
   int stationSuivante;
   int ligneCorrespondante;
   struct _chemin *suivant;
} Chemin;

Chemin *creerChemin(int stationSuivante, int ligneCorrespondante);
void detruireChemin(Chemin **chemin);

#endif