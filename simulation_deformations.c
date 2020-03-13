#include "rapport_deformations.h"
#include <stdio.h>
#define LONGUEUR_CABLE 1000000 /* en m */
#define NOMBRE_DEFORMATIONS 100000 /* en nombre de déformations */

int main()
{
    /* paramètres */
    int nombre_positions = LONGUEUR_CABLE/PRECISION;
    int nombre_deformations = NOMBRE_DEFORMATIONS;
    Simulation simulation = UNIFORME;

    int temps_ecoule; /* pour chronométrer */
    
    printf("Simulation de %i déformations sur %i positions, configuration "
        "%i... ", nombre_deformations, nombre_positions, simulation);
    redemarrer_chronometre();
    Position* paquet = simuler_deformations(nombre_positions,
        nombre_deformations, simulation);
    printf("terminée.\n");

    const char* nom_fichier = "simulation_deformations.dat";
    printf("Écriture du paquet de déformations dans %s... ", nom_fichier);
    int i;
    FILE* file = fopen(nom_fichier, "w");
    for (i = 0; i < nombre_deformations; i++){
        fprintf(file, "%i ", paquet[i]);
    }
    fclose(file);
    printf("terminée.\n");

    temps_ecoule = relever_chronometre_ms();
    printf("Temps écoulé : %i ms.\n", temps_ecoule);

    detruire_deformations(paquet);

    return 0; 
}
