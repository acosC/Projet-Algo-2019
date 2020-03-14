#include "rapport_deformations.h"
#include <stdlib.h>
#include <stdio.h>
#define LONGUEUR_CABLE 1000000 /* en m */
#define NOMBRE_DEFORMATIONS 100000 /* en nombre de déformations */

/**
        On simule des déformations sur un clable de longueur donnée et de précision donnée
        On définie le nombre de déformation que l'on veut
        Les déformation sont répartie, en fonction d'une loi, sur l'ensemble des positions du cable
        Pour chaque déformation une position sera atribué
        ainsi la fonction simuler_deformations renvoi un tableau des déformations en fonction des positions
        l'alerte est donné si il y a 100 déformations pour une position et les positions voisine
        Deux positions sont voisine si elle sont distante de 100m ou moins
        Soit si pos(200) est étudié, toute les position comprise entre pos(100) et pos(300) sont voisine
**/

int main()
{
    //printf("debut");
    //fflush(stdout);

    /* paramètres */
    int nombre_positions = LONGUEUR_CABLE/PRECISION;
    int nombre_deformations = NOMBRE_DEFORMATIONS;
    Simulation simulation = UNIFORME; //type de loi suivie pour la simulation

    int temps_ecoule; /* pour chronométrer */

    /** simulation des déformation **/
    printf("Simulation de %i deformations sur %i positions, configuration %i... ", nombre_deformations, nombre_positions, simulation);
    redemarrer_chronometre();//pour calculer le temps de la simulation
    Position* paquet = simuler_deformations(nombre_positions,nombre_deformations, simulation);
    printf("terminee.\n");

    const char* nom_fichier = "simulation_deformations.dat";
    printf("Ecriture du paquet de deformations dans %s... ", nom_fichier);

    FILE* file = fopen(nom_fichier, "w"); // création du fichier qui va contenir les positions des déformations
    for (int i = 0; i < nombre_deformations; i++) //écriture dans le fichier
    {
        fprintf(file, "%i ", paquet[i]);
        //printf("paquet %i  ",paquet[i]);
    }
    fclose(file); //fermeture du fichier
    printf("terminee.\n");

    temps_ecoule = relever_chronometre_ms();// on récupère le temps pris pour cette opération
    printf("Temps ecoule pour la repartition des deformations : %i ms.\n", temps_ecoule);

    //detruire_deformations(paquet);


    /** troisieme version **/
    /** optimisation de la création du tableau du nombre de déformation en fontion des position */

    redemarrer_chronometre(); //démarache du chronomètre pour calculer le temps d'une possible alerte

    int* tab_position;//utilisation d'une allocation dynamique pour gérer une grande quantité de valeur
    tab_position = malloc(LONGUEUR_CABLE * sizeof(int));

    /*  création d'un tableau de transfère
        tab_position est tableau des positions en fonction des déformations
        pour chaque position on a le nombre de déformation
    */
    for (int position =0; position<LONGUEUR_CABLE; position++)
        tab_position[position] =0;

    for (int deformation =0; deformation < NOMBRE_DEFORMATIONS; deformation++)
    {
        tab_position[paquet[deformation]] = tab_position[paquet[deformation]] + 1;
    }

    /*  détection des alertes
        pour chaque position on calcul un min et un max qui représente les deux voisin extréma
    */
    int somme,somme_alerte=0, min, max;
    for(int position =0; position<LONGUEUR_CABLE; position++)
    {
        somme =0;

        if (position>LONGUEUR_CABLE - DIST_MAX_VOISIN - 1)
            max =LONGUEUR_CABLE-1;
        else
            max = position + DIST_MAX_VOISIN;

        if (position<DIST_MAX_VOISIN)
            min =0;
        else
            min =position - DIST_MAX_VOISIN;

        for(int i =min; i<=max;i++)
            somme = somme + tab_position[i];

        if (somme >= SEUIL_ALERTE)
            somme_alerte++;
    }

    temps_ecoule = relever_chronometre_ms(); //on recuperrer le temps écoulé pour cette version
    printf("Temps ecoule troisieme version : %i ms.\n", temps_ecoule);
    printf("nb d'alerte : %i\n",somme_alerte);
    free(tab_position);

free(paquet);
    return 0;
}
