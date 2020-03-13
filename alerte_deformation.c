#include "rapport_deformations.h"
#include <stdlib.h>
#include <stdio.h>
#define LONGUEUR_CABLE 10000 /* en m */
#define NOMBRE_DEFORMATIONS 50000 /* en nombre de d�formations */
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


    /** deuxième version **/
  int i=0;
  int position,position2,max,min,k,limite_deformation=0;
  printf("c'est chiant.\n");
  for(i=0;i<LONGUEUR_CABLE;i++)
  {
    position = paquet[i];
    if (position>900)
      max=LONGUEUR_CABLE-1;
    else
      max=position+100;
    if (position<100)
      min=0;
    else
      min=position-100;
    for(k=0;k<LONGUEUR_CABLE;k++)
    {
      position2=paquet[k];
      if ((min<position2) && (position2<max))
      {
        limite_deformation++;
        if (limite_deformation ==100)
          printf("Alerte : position %i\n",i);
      }
    }
  }

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
/*
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
*/







}
