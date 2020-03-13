#include <time.h> /* pour la mesure du temps de calcul */
#define PRECISION 1 /* en m */
#define DIST_MAX_VOISIN 100 /* en m */
#define SEUIL_ALERTE 100 /* en nombre de déformations */

/** trie **/

void permuter(int *a, int *b);
void triRapid(int tab[], int first, int last);
/***  mesure du temps de calcul  ***/
void redemarrer_chronometre();
int relever_chronometre_ms();  /* en millisecondes */

/***  simulation d'un paquet de deformations  ***/
typedef int Position; //une position est un entier
/* différentes configurations des déformations */

typedef enum Simulation {UNIFORME, MONOMODALE, BIMODALE, QUASIMONOTONE};
typedef enum Simulation Simulation;

/* Simulation proprement dite
 *
 *     ENTREES
 * nombres_positions : le nombre de positions possibles (les positions sont
 *     repérées par des entiers entre 0 et nombre_positions - 1)
 * nombre_deformations : le nombre de déformations simulées
 * simulation : configuration des déformations considérées
 *
 *     SORTIE
 * pointeur sur un paquet de deformations, c'est-à-dire un tableau de positions
 * comprises entre 0 et nombres_positions - 1, de taille nombre_deformations */
Position* simuler_deformations(Position nombre_positions,int nombre_deformations, Simulation simulation);

/* Libère la mémoire utilisée par un paquet de déformations */
void detruire_deformations(Position* paquet);
