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
void Premiere_version(Position * paquet,const char* nom_fichier)
{
    /* d�marage du chronom�tre pour calculer le temps */
    redemarrer_chronometre();

    printf("premiere version en cours d'execution...\n");

    int temps_ecoule;

    /* utilisation d'une allocation dynamique pour g�rer une grande quantit� de valeur */
    int* tab_position = malloc((LONGUEUR_CABLE/PRECISION) * sizeof(int));

    /* cr�ation d'un tableau de transf�re */
    /* tab_position est tableau des d�formation en fonction des positions */
    /* pour chaque position on a le nombre de d�formation en cette position */
    /* c'est cette �tape qui prend le plus de temps car on parcours LONGUEUR_CABLE de fois NOMBRE_DEFORMATIONS d�formation */

    for(int position = 0; position < (LONGUEUR_CABLE/PRECISION); position++)
    {
        tab_position[position] = 0;

        for (int deformation = 0; deformation < NOMBRE_DEFORMATIONS; deformation++)
        {
            if (paquet[deformation] == position)
                tab_position[position] = tab_position[position] + 1;
        }
    }

    /* d�tection des alertes */
    /* pour chaque position on calcul un min et un max qui repr�sente les deux voisin extr�ma */
    /* cr�ation d'un rapport d'alerte */
    FILE * file = fopen(nom_fichier, "w+");

    int somme,somme_alerte = 0, min, max;

    /* on parcours le tableau cr�� au dessus */
    for(int position = 0; position < (LONGUEUR_CABLE/PRECISION); position++)
    {
        somme = 0;

        if (position > (LONGUEUR_CABLE/PRECISION) - DIST_MAX_VOISIN - 1)
            max = (LONGUEUR_CABLE/PRECISION) - 1; /* les case vont de 0 � long LONGUEUR_CABLE-1 soit LONGUEUR_CABLE case */
        else
            max = position + DIST_MAX_VOISIN;

        /* pour �viter que le min soit au en dessous de 0 car impossible */
        if (position < DIST_MAX_VOISIN)
            min = 0;
        else
            min = position - DIST_MAX_VOISIN;

        /* on parcours de tableau du min au max inclu et on fait la somme des d�formations */
        for(int i = min; i <= max; i++)
            somme = somme + tab_position[i];

        /* edition du rapport */

        /* si le seuil d'alerte est atteind */
        if(somme > SEUIL_ALERTE)
        {
            somme_alerte++;
            fprintf(file, "alerte position %i avec %i deformation\n", position, somme);
        }
    }
    fclose(file); //fermeture du fichier

    printf("termine\n");

    printf("nb d'alerte : %i\n", somme_alerte);

    free(tab_position);

    /* on recuperrer le temps �coul� pour cette version */
    temps_ecoule = relever_chronometre_ms();
    printf("Temps ecoule premiere version : %i ms.\n", temps_ecoule);
}

/** DEUXIEME VERSION **/
void Deuxieme_version(Position * paquet,const char* nom_fichier)
{
    redemarrer_chronometre();
    printf("deuxieme version en cours d'execution...\n");

    int temps_ecoule;

    /* utilisation d'une allocation dynamique pour g�rer une grande quantit� de valeur */
    int *tab_position = malloc(LONGUEUR_CABLE * sizeof(int));
    int nbre_alertes = 0;
    int min,max;

    /* On parcourt une premi�re fois le tableau */
    for(int i =0; i < LONGUEUR_CABLE; i++) /* On parcourt une premi�re fois le tableau */
    {
        /* On d�finit un intervalle de valeurs dans lequel les d�formations compteront */

        /* les cases vont de 0 � LONGUEUR_CABLE-1 soit LONGUEUR_CABLE case */
        if (i > (LONGUEUR_CABLE - DIST_MAX_VOISIN - 1))
            max = LONGUEUR_CABLE ;
        else
            max = i + DIST_MAX_VOISIN;

        /* pour �viter que le min soit au en dessous de 0 car impossible */
        if (i + 1 < DIST_MAX_VOISIN)
            min = 0;
        else
            min = i - DIST_MAX_VOISIN;

        int s = 0;

        /* On parcourt le paquet */
        for (int j =0; j < NOMBRE_DEFORMATIONS; j++)
        {
            /* Si une d�formation se situe dans l'intervalle d�fini */
            if ((paquet[j] >= min) && (paquet[j] <= max))
            {
                s = s + 1;

                if (s >= SEUIL_ALERTE)
                    tab_position[i] = 1;
                else
                    tab_position[i] = 0;
            }
        }

    }

    /* On affiche les points pour lesquels il y a une alerte */
    FILE* file = fopen(nom_fichier, "w+");

    for(int k =0; k < LONGUEUR_CABLE; k++)
    {
        if (tab_position[k] == 1 )
        {
            fprintf(file,"Alerte : Trop de d�formations au point %i\n",k );
            nbre_alertes ++;
        }
    }
    fclose(file);

    /* On affiche le nombre d'alertes */
    printf("nombre d'alertes : %i\n", nbre_alertes);

    printf("termine\n");

    /* on recupere le temps �coul� pour cette version */
    temps_ecoule = relever_chronometre_ms();
    printf("Temps ecoule deuxieme version : %i ms.\n", temps_ecoule);
}

/** TROISIEME VERSION **/
/** optimisation de la PREMIERE VERSION */
void Troisieme_version(Position * paquet, const char* nom_fichier)
{
    /* d�marage du chronom�tre pour calculer le temps */
    redemarrer_chronometre();

    printf("troisieme version en cours d'execution...\n");

    int temps_ecoule;

    /* utilisation d'une allocation dynamique pour g�rer une grande quantit� de valeur */
    register int * tab_position = malloc((LONGUEUR_CABLE/PRECISION) * sizeof(int));

    /* cr�ation d'un tableau de transf�re */
    /* tab_position est tableau des d�formation en fonction des positions */
    /* pour chaque position on a le nombre de d�formation en cette position */
    /* optimiser par rapport � la PREMIERE VERSION */

    /* on initilaise � 0 par s�curit� */
    for (int position = 0; position < (LONGUEUR_CABLE/PRECISION); position++)
        tab_position[position] = 0;

    for (int deformation = 0; deformation < NOMBRE_DEFORMATIONS; deformation++)
    {
        /* paquet[deformation] est une position donc on parcours le paquet de d�formation pour chaque position lu on ajoute +1 � la position correspondante */
        tab_position[paquet[deformation]] ++;
    }

    /* d�tection des alertes */
    /* pour chaque position on calcul un min et un max qui repr�sente les deux voisin extr�ma */
    /* cr�tion d'un rapport d'alerte */
    /* identique � la PREMIERE version */
    FILE* file = fopen(nom_fichier, "w+");

    int somme, somme_alerte = 0, min, max;

    for(int position = 0; position < (LONGUEUR_CABLE/PRECISION); position++)
    {
        somme = 0;

        if (position > ((LONGUEUR_CABLE/PRECISION) - DIST_MAX_VOISIN - 1))
            max = (LONGUEUR_CABLE/PRECISION) - 1;
        else
            max = position + DIST_MAX_VOISIN;

        if (position < DIST_MAX_VOISIN)
            min = 0;
        else
            min = position - DIST_MAX_VOISIN;

        for(int i = min; i <= max; i++)
            somme = somme + tab_position[i]; // tab_position[i] == le nombre de d�formation en un point

        /* edition du rapport */
        if(somme > SEUIL_ALERTE)
        {
            somme_alerte++;
            fprintf(file, "alerte position %i avec %i deformation\n", position, somme);
        }
    }
    fclose(file); //fermeture du fichier

    printf("termine\n");

    printf("nb d'alerte : %i\n",somme_alerte);

    free(tab_position);

    /* on recuperrer le temps �coul� pour cette version */
    temps_ecoule = relever_chronometre_ms();
    printf("Temps ecoule troisieme version : %i ms.\n", temps_ecoule);
}
