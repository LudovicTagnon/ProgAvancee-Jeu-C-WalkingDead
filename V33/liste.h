//
// Created by ludovic on 29/09/2021.
//

#ifndef V1_LISTE_H
#define V1_LISTE_H




#include "constants.h"
#include "data.h"


list_t ajouterEnTete(list_t liste, sprite_t valeur);

list_t ajouterEnFin(list_t liste, sprite_t valeur);

bool estVide(list_t liste);

list_t supprimerElementEnTete(list_t liste);

list_t supprimerElementEnFin(list_t liste);

void afficherListe(list_t liste);

list_t l_vide();

int tailleListe(list_t liste);

#endif //V1_LISTE_H
