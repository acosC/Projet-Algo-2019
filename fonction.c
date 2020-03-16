#include "fonction.h"
#include <stdlib.h>
#include <stdio.h>

/** fonctions pour meusurer le temps écoulé **/
static clock_t temps_cpu;
void redemarrer_chronometre()
{
    temps_cpu = clock();
}
int relever_chronometre_ms()
{
    return (clock() - temps_cpu)/((double) CLOCKS_PER_SEC)*1000;
}

/** premiere version **/
/** valeur limite: longueur 100 000 nb deformation 100 000 **/
/** temps de création du tableau tab_position beaucoup trop long au dela de la limite **/
void Premiere_version(Position * paquet,const char* nom_fichier)
{
    int temps_ecoule;
    redemarrer_chronometre(); //démarache du chronomètre pour calculer le temps d'une possible alerte

    int* tab_position;//utilisation d'une allocation dynamique pour gérer une grande quantité de valeur
    tab_position = malloc(LONGUEUR_CABLE * sizeof(int));

    /*  création d'un tableau de transfère
        tab_position est tableau des positions en fonction des déformations
        pour chaque position on a le nombre de déformation
        cette étape prend énormément de temps
    */
    for(int position =0; position<LONGUEUR_CABLE; position++)
    {
        tab_position[position] =0;
        for (int deformation =0; deformation<NOMBRE_DEFORMATIONS; deformation++)
        {
            if (paquet[deformation] == position)
                tab_position[position] = tab_position[position] + 1;
        }
        //printf("position %i nb deformation %i \n",position,tab_position[position]);
    }

    /*  détection des alertes
        pour chaque position on calcul un min et un max qui représente les deux voisin extréma
    */
    int somme, min, max;
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
            printf("ALERTE SUR LA POSITION %i avec %i deformation\n",position,somme);
    }
    free(tab_position);

    temps_ecoule = relever_chronometre_ms(); //on recuperrer le temps écoulé pour cette version
    printf("Temps ecoule premiere version : %i ms.\n", temps_ecoule);
}

/** troisieme version **/
/** optimisation de la création du tableau du nombre de déformation en fontion des position */
void Troisieme_version(Position * paquet,const char* nom_fichier)
{
    int temps_ecoule;
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

    /* détection des alertes */
    /* pour chaque position on calcul un min et un max qui représente les deux voisin extréma */
    /* crétion d'un rapport d'alerte */
    FILE* file = fopen(nom_fichier, "w");
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

        /* edition du rapport */
        if(somme>SEUIL_ALERTE)
        {
            somme_alerte++;
            fprintf(file,"alerte position %i avec %i deformation",position,somme);
        }
    }
    fclose(file); //fermeture du fichier

    temps_ecoule = relever_chronometre_ms(); //on recuperrer le temps écoulé pour cette version
    printf("Temps ecoule troisieme version : %i ms.\n", temps_ecoule);
    printf("nb d'alerte : %i\n",somme_alerte);
    free(tab_position);
}
