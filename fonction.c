#include "fonction.h"
#include <stdlib.h>
#include <stdio.h>

/** fonctions pour meusurer le temps �coul� pour l'execution d'une version **/
static clock_t temps_cpu;
void redemarrer_chronometre()
{
    temps_cpu = clock();
}
int relever_chronometre_ms()
{
    return (clock() - temps_cpu)/((double) CLOCKS_PER_SEC)*1000;
}

/** PREMIERE VERSION **/
/** valeur limite: longueur 100 000 nb deformation 100 000 **/
/** temps de cr�ation du tableau tab_position beaucoup trop long au dela de la limite **/
void Premiere_version(Position * paquet,const char* nom_fichier)
{
    redemarrer_chronometre(); //d�marache du chronom�tre pour calculer le temps d'une possible alerte
    printf("premiere version en cours d'execution...");

    int temps_ecoule;
    int* tab_position = malloc(LONGUEUR_CABLE * sizeof(int));//utilisation d'une allocation dynamique pour g�rer une grande quantit� de valeur

    /* cr�ation d'un tableau de transf�re */
    /* tab_position est tableau des d�formation en fonction des positions */
    /* pour chaque position on a le nombre de d�formation en cette position */
    /* c'est cette �tape qui prend le plus de temps car on parcours 1 000 000 de fois 100 000 d�formation */

    for(int position =0; position<LONGUEUR_CABLE; position++)
    {
        tab_position[position] =0;
        for (int deformation =0; deformation<NOMBRE_DEFORMATIONS; deformation++)
        {
            if (paquet[deformation] == position)
                tab_position[position] = tab_position[position] + 1;
        }
    }

    /* d�tection des alertes */
    /* pour chaque position on calcul un min et un max qui repr�sente les deux voisin extr�ma */
    /* cr�ation d'un rapport d'alerte */
    FILE* file = fopen(nom_fichier, "w");
    int somme,somme_alerte=0, min, max;
    for(int position =0; position<LONGUEUR_CABLE; position++)//on parcours le tableau cr�� au dessus
    {
        somme =0;

        if (position>LONGUEUR_CABLE - DIST_MAX_VOISIN - 1)
            max =LONGUEUR_CABLE-1;// car les case vont de 0 � long LONGUEUR_CABLE-1 soit LONGUEUR_CABLE case
        else
            max = position + DIST_MAX_VOISIN;

        if (position<DIST_MAX_VOISIN)//pour �viter que le min soit au en dessous de 0 car impossible
            min =0;
        else
            min =position - DIST_MAX_VOISIN;

        for(int i =min; i<=max;i++)//on parcours de tableau du min au max inclu et on fait la somme des d�formations
            somme = somme + tab_position[i];

        /* edition du rapport */
        if(somme>SEUIL_ALERTE)//si le seuil d'alerte est atteind
        {
            somme_alerte++;
            fprintf(file,"alerte position %i avec %i deformation\n",position,somme);
        }
    }
    fclose(file); //fermeture du fichier

    printf("termine\n");
    printf("nb d'alerte : %i\n",somme_alerte);
    free(tab_position);

    temps_ecoule = relever_chronometre_ms(); //on recuperrer le temps �coul� pour cette version
    printf("Temps ecoule premiere version : %i ms.\n", temps_ecoule);
}

/** DEUXIEME VERSION **/
void Deuxieme_version(Position * paquet,const char* nom_fichier)
{
    redemarrer_chronometre();
    printf("deuxieme version en cours d'execution...");

    int temps_ecoule;

    /** CODE **/

    printf("termine\n");

    temps_ecoule = relever_chronometre_ms(); //on recuperrer le temps �coul� pour cette version
    printf("Temps ecoule deuxieme version : %i ms.\n", temps_ecoule);
}

/** TROISIEME VERSION **/
/** optimisation de la PREMIERE VERSION */
void Troisieme_version(Position * paquet,const char* nom_fichier)
{
    redemarrer_chronometre(); //d�marache du chronom�tre pour calculer le temps d'une possible alerte

    printf("troisieme version en cours d'execution\n");

    int temps_ecoule;
    int* tab_position = malloc(LONGUEUR_CABLE * sizeof(int));//utilisation d'une allocation dynamique pour g�rer une grande quantit� de valeur

    /* cr�ation d'un tableau de transf�re */
    /* tab_position est tableau des d�formation en fonction des positions */
    /* pour chaque position on a le nombre de d�formation en cette position */
    /* optimiser par rapport � la PREMIERE VERSION */

    for (int position =0; position<LONGUEUR_CABLE; position++) //on initilaise � 0 par s�curit�
        tab_position[position] =0;

    for (int deformation =0; deformation < NOMBRE_DEFORMATIONS; deformation++)
    {
        tab_position[paquet[deformation]]++; //paquet[deformation] est une position donc on parcours le paquet de d�formation pour chaque position lu on ajoute +1 � la position corespondante
    }

    /* d�tection des alertes */
    /* pour chaque position on calcul un min et un max qui repr�sente les deux voisin extr�ma */
    /* cr�tion d'un rapport d'alerte */
    /* identique � la premiere version */
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
            fprintf(file,"alerte position %i avec %i deformation\n",position,somme);
        }
    }
    fclose(file); //fermeture du fichier

    printf("termine\n");
    printf("nb d'alerte : %i\n",somme_alerte);
    free(tab_position);

    temps_ecoule = relever_chronometre_ms(); //on recuperrer le temps �coul� pour cette version
    printf("Temps ecoule troisieme version : %i ms.\n", temps_ecoule);
}
