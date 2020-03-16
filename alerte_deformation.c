#include "fonction.h"
#include <stdlib.h>
#include <stdio.h>


/**
        On simule des d�formations sur un clable de longueur donn�e et de pr�cision donn�e
        On d�finie le nombre de d�formation que l'on veut
        Les d�formation sont r�partie, en fonction d'une loi, sur l'ensemble des positions du cable
        Pour chaque d�formation une position sera atribu�
        ainsi la fonction simuler_deformations renvoi un tableau de positions pour chaque d�formation
        l'alerte est donn� si il y a 100 d�formations pour une position et les positions voisine (le seuil peut �tre modifi�)
        Deux positions sont voisine si elle sont distante de 100m ou moins (cette variable peut �tre modifi�)
        Soit si pos(200) est �tudi�, toute les position comprise entre pos(100) et pos(300) sont voisine
**/

int main()
{
    int choix =0;
    int nombre_positions = LONGUEUR_CABLE/PRECISION;
    Simulation simulation = BIMODALE; //type de loi suivie pour la simulation

    /** simulation des d�formation **/
    Position* paquet = simuler_deformations(nombre_positions,NOMBRE_DEFORMATIONS, simulation);
    rapport(paquet,"simulation_deformations.dat"); //ecriture des positions pour chaque d�formation dans un fichier


    while(choix != 4)
    {
        /** menu **/
        printf("\nquel version souhaitez vous executer?\n");
        printf("[1] premiere version\n");
        printf("[2] deuxieme version\n");
        printf("[3] troisieme version\n");
        printf("[3] exit\n");
        scanf(" %i",&choix);

        switch(choix)
        {
        case 1:
            Premiere_version(paquet,"rapport_premiere_version.dat");
            break;
        case 2:
            Deuxieme_version(paquet,"rapport_deuxieme_version.dat");
            break;
        case 3:
            Troisieme_version(paquet,"rapport_troisieme_version.dat");
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
