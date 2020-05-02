#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include "rapport_deformations.h"
#include <time.h> /* pour la mesure du temps de calcul */

/** mesure du temps de calcul **/
void redemarrer_chronometre();
int relever_chronometre_ms();  /* en millisecondes */

void Premiere_version(Position * paquet,const char* nom_fichier);
void Deuxieme_version(Position * paquet,const char* nom_fichier);
void Troisieme_version(Position * paquet,const char* nom_fichier);

#endif // FONCTION_H_INCLUDED
