#include "rapport_deformations.h"
#include <stdlib.h>
#include <stdio.h>
#define LONGUEUR_CABLE 100000 /* en m */
#define NOMBRE_DEFORMATIONS 100000 /* en nombre de d�formations */
#define PAS_VOISIN

/**
        On simule des d�formations sur un clable de longueur donn�e et de pr�cision donn�e
        On d�finie le nombre de d�formation que l'on veut
        Les d�formation sont r�partie, en fonction d'une loi, sur l'ensemble des positions du cable
        Pour chaque d�formation une position sera atribu�
        l'alerte est donn� si il y a 100 d�formations pour une position et les positions voisine
        Deux positions sont voisine si elle sont distante de 100m ou moins
        Soit si pos(200) est �tudi�, toute les position comprise entre pos(100) et pos(300) sont voisine
**/

int main()
{
    /* param�tres */
    int nombre_positions = LONGUEUR_CABLE/PRECISION;
    int nombre_deformations = NOMBRE_DEFORMATIONS;
    Simulation simulation = UNIFORME; //type de loi suivie pour la simulation

    int temps_ecoule; /* pour chronom�trer */

    /** simulation des d�formation **/
    printf("Simulation de %i deformations sur %i positions, configuration %i... ", nombre_deformations, nombre_positions, simulation);
    redemarrer_chronometre();//pour calculer le temps de la simulation
    Position* paquet = simuler_deformations(nombre_positions,nombre_deformations, simulation);
    printf("terminee.\n");

    const char* nom_fichier = "simulation_deformations.dat";
    printf("Ecriture du paquet de deformations dans %s... ", nom_fichier);

    FILE* file = fopen(nom_fichier, "w"); // cr�ation du fichier qui va contenir les positions des d�formations
    for (int i = 0; i < nombre_deformations; i++) //�criture dans le fichier
    {
        fprintf(file, "%i ", paquet[i]);
    }
    fclose(file); //fermeture du fichier
    printf("terminee.\n");

    temps_ecoule = relever_chronometre_ms();// on r�cup�re le temps pris pour cette op�ration
    printf("Temps ecoule pour la repartition des deformations : %i ms.\n", temps_ecoule);

    //detruire_deformations(paquet);

    /** premiere version **/

    redemarrer_chronometre(); //d�marache du chronom�tre pour calculer le temps d'une possible alerte
    int tab_position[LONGUEUR_CABLE];

    for(long position =0; position<LONGUEUR_CABLE; position++)
    {
        tab_position[position] =0;
        for (long deformation =0; deformation<NOMBRE_DEFORMATIONS; deformation++)
        {
            if (paquet[deformation] == position)
                tab_position[position] = tab_position[position] + 1;
        }
        printf("position %i nb deformation %i \n",position,tab_position[position]);
    }

    temps_ecoule = relever_chronometre_ms(); //on recuperrer le temps �coul� pour cette version
    printf("Temps ecoule premiere version : %i ms.\n", temps_ecoule);

    return 0;
}