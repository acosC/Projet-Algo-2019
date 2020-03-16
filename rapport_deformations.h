#ifndef RAPPORT_DEFORMATIONS_H_INCLUDED
#define RAPPORT_DEFORMATIONS_H_INCLUDED

#include "parametres.h"

typedef int Position; //une position est un entier

/* différentes configurations des déformations */
enum Simulation {UNIFORME, MONOMODALE, BIMODALE, QUASIMONOTONE};
typedef enum Simulation Simulation;

double distribution_triangulaire();
Position position_distr_triang(Position centre, int largeur);
int distribuer_pivot(Position* positions, int n);
void transf_quasi_monotone(Position* deformations, int nombre_deformations,int arret);

/** simulation d'un paquet de deformations
 *
 *     ENTREES
 * nombres_positions : le nombre de positions possibles (les positions sont
 *     repérées par des entiers entre 0 et nombre_positions - 1)
 * nombre_deformations : le nombre de déformations simulées
 * simulation : configuration des déformations considérées
 *
 *     SORTIE
 * pointeur sur un paquet de deformations, c'est-à-dire un tableau de positions
 * comprises entre 0 et nombres_positions - 1, de taille nombre_deformations
 **/
Position* simuler_deformations(Position nombre_positions,int nombre_deformations, Simulation simulation);

void rapport (Position * paquet,const char* nom_fichier);

#endif // RAPPORT_DEFORMATIONS_H_INCLUDED
