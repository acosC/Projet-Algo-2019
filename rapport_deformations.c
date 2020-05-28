#include "rapport_deformations.h"
#include <stdlib.h>
#include <stdio.h>

/** tire aléatoirement une valeur réelle selon une distribution triangulaire centrée en 1/2 et de largeur 1 **/
double distribution_triangulaire()
{
    int valeur;
    int accepte = 0;
    while (!accepte)
    {
        valeur = rand();
        if (valeur <= RAND_MAX/2)
            accepte = (rand() % RAND_MAX/2) <= valeur;
        else
            accepte = (rand() % RAND_MAX/2) <= RAND_MAX - valeur;
    }
    return valeur/(double) RAND_MAX;
}

/** tire aléatoirement une position selon une distribution triangulaire */
Position position_distr_triang(Position centre, int largeur)
{
    return centre - largeur/2 + (int) (largeur*distribution_triangulaire());
}

/** transformation d'un tableau de positions tirées uniformément en une distribution quasi-monotone */
/** fonction auxiliaire : ordonne les positions autour d'une valeur pivot */
int distribuer_pivot(Position* positions, int n)
{
    Position pivot = positions[0];
    int i = 1;
    int j = n;
    while (i < j)
    {
        if (positions[i] <= pivot)
            i++;
        else
        {
            j--;
            Position tmp = positions[j];
            positions[j] = positions[i];
            positions[i] = tmp;
        }
    }
    if (i == n)
    {
        positions[0] = positions[n - 1];
        positions[n - 1] = pivot;
        return n - 1;
    }
    return i;
}

/** transformation : tri partiel */
void transf_quasi_monotone(Position* deformations, int nombre_deformations,int arret)
{
    if (nombre_deformations < arret){ return; }
    int i = distribuer_pivot(deformations, nombre_deformations);
    transf_quasi_monotone(deformations, i, arret);
    transf_quasi_monotone(deformations + i, nombre_deformations - i, arret);
}

/** simulation des déformation **/

Position* simuler_deformations(Position nombre_positions,int nombre_deformations, Simulation simulation)
{
    printf("Simulation de %i deformations sur %i positions, configuration %i... ",NOMBRE_DEFORMATIONS, nombre_positions, simulation);

    Position* paquet = malloc(sizeof(Position)*nombre_deformations);
    if (!paquet)
    {
        fprintf(stderr, "Nombre de déformations trop grand, pas assez de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    int i;
    if (simulation == UNIFORME)
    {
        /* distribution uniforme */
        for (i = 0; i < nombre_deformations; i++)
            paquet[i] = rand() % nombre_positions;
    }
    else if (simulation == MONOMODALE)
    {
        /* distribution triangulaire centrée sur la position centrale,largeur quart */
        Position centre = nombre_positions/4;
        int largeur = nombre_positions/4;
        for (i = 0; i < nombre_deformations; i++)
            paquet[i] = position_distr_triang(centre, largeur);
    }
    else if (simulation == BIMODALE)
    {
        /* deux distributions triangulaires centrées sur les positions en premier et troisième quartile, largeur huitième */
        int largeur = nombre_positions/8;
        for (i = 0; i < nombre_deformations; i++)
        {
            Position centre = (rand() % 2) ?
                nombre_positions/4 : 3*nombre_positions/4;
            paquet[i] = position_distr_triang(centre, largeur);
        }
    }
    else if (simulation == QUASIMONOTONE)
    {
        for (i = 0; i < nombre_deformations; i++)
            paquet[i] = rand() % nombre_positions;

        /* une valeur d'arrêt assez grande assure des inversions */
        int arret = SEUIL_ALERTE;
        transf_quasi_monotone(paquet, nombre_deformations, arret);
    }
    else
    {
        fprintf(stderr, "Configuration %i invalide.\n", simulation);
        exit(EXIT_FAILURE);
    }
    printf("termine.\n");

    return paquet;
}

/** édition du rapport dans un fichier **/
void rapport (Position * tab,const char* nom_fichier)
{
    printf("Ecriture du paquet de deformations dans %s... ", nom_fichier);

    FILE* file = fopen(nom_fichier, "w"); // création du fichier qui va contenir les positions des déformations
    for (int i = 0; i < NOMBRE_DEFORMATIONS; i++) //écriture dans le fichier
    {
        fprintf(file, "%i ", tab[i]);
    }
    fclose(file); //fermeture du fichier

    printf("terminee.\n");
}
