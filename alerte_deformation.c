#include "fonction.h"
#include <stdlib.h>
#include <stdio.h>


/**
        On simule des déformations sur un clable de longueur donnée et de précision donnée
        On définie le nombre de déformation que l'on veut
        Les déformation sont répartie, en fonction d'une loi, sur l'ensemble des positions du cable
        Pour chaque déformation une position sera atribué
        ainsi la fonction rapport_deformations renvoi un tableau de positions pour chaque déformation
        l'alerte est donné si il y a 100 déformations sur une position et les positions voisine (le seuil peut être modifié)
        les positions sont voisines si elle sont distante de 100m ou moins (cette variable peut être modifié)
        Soit si pos(200) est étudié, toute les position comprise entre pos(100) et pos(300) sont voisine
**/

int main()
{
    int choix =0;
    register int nombre_positions = LONGUEUR_CABLE/PRECISION;
    Simulation simulation = QUASIMONOTONE; /* type de loi suivie pour la simulation */

    /** simulation des déformation **/
    register Position* paquet = simuler_deformations(nombre_positions,NOMBRE_DEFORMATIONS, simulation);
    rapport(paquet,"simulation_deformations.dat"); /* ecriture des positions pour chaque déformation dans un fichier */

    /** menu **/
    while(choix != 4)
    {
        printf("\nquel version souhaitez vous executer?\n");
        printf("[1] premiere version\n");
        printf("[2] deuxieme version\n");
        printf("[3] troisieme version\n");
        printf("[4] exit\n");
        scanf(" %i",&choix);

        switch(choix)
        {
        case 1:
            Premiere_version(paquet, "rapport_premiere_version.dat");
            break;
        case 2:
            Deuxieme_version(paquet, "rapport_deuxieme_version.dat");
            break;
        case 3:
            Troisieme_version(paquet, "rapport_troisieme_version.dat");
            break;
        case 4:
            break;
        default :
            printf("choix invalide");
            break;
        }
    }

    free(paquet);
    return 0;
}
