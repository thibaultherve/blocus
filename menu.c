/*Thibault HERVE*/

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

void ChoixConfiguration(int* taille, int* NbJoueurs) {
  

  *taille=0;
  *NbJoueurs=0;
  int PermissionClose=0; 


  EcrireTexte(20,40,"Taille de la grille :",1);
  ChargerImage("rsc/choixtaille.jpg",20,50,0,0,179,473);
  EcrireTexte(220,40,"Nombre de joueurs :",1);
  ChargerImage("rsc/joueur.jpg",220,52,0,0,177,133);
  ChargerImage("rsc/logo.png",207,250,0,0,210,151);

  while(PermissionClose==0) {
    if (SourisCliquee()) { 
      printf("x=%d\ny=%d\n",_X,_Y);
     
      /*joueur1*/
      if ((_X > 222 && _X < 395) && (_Y > 55 && _Y < 116)) {
        ChargerImage("rsc/joueur1.jpg",220,52,0,0,177,133);
	*NbJoueurs=1;
      }
     
      /*joueur2*/
      if ((_X > 222 && _X < 395) && (_Y > 121 && _Y < 185)) {
        ChargerImage("rsc/joueur2.jpg",220,52,0,0,177,133);
	*NbJoueurs=2;
      }
     
      /*Taille3*/
      if ((_X > 23 && _X < 195) && (_Y > 55 && _Y < 116)) {
        ChargerImage("rsc/choixtaille3.jpg",20,50,0,0,179,473);
	*taille=3;
      }
    
      /*Taille4*/
      if ((_X > 23 && _X < 195) && (_Y > 121 && _Y < 185)) {
        ChargerImage("rsc/choixtaille4.jpg",20,50,0,0,179,473);
	*taille=4;
      }
      
      /*Taille5*/
      if ((_X > 23 && _X < 195) && (_Y > 188 && _Y < 250)) {
        ChargerImage("rsc/choixtaille5.jpg",20,50,0,0,179,473);
	*taille=5;
      }
      
      /*Taille6*/
      if ((_X > 23 && _X < 195) && (_Y > 255 && _Y < 318)) {
        ChargerImage("rsc/choixtaille6.jpg",20,50,0,0,179,473);
	*taille=6;
      }
      
      /*Taille7*/
      if ((_X > 23 && _X < 195) && (_Y > 323 && _Y < 385)) {
        ChargerImage("rsc/choixtaille7.jpg",20,50,0,0,179,473);
	*taille=7;
      }
      
      /*Taille8*/
      if ((_X > 23 && _X < 195) && (_Y > 390 && _Y < 453)) {
        ChargerImage("rsc/choixtaille8.jpg",20,50,0,0,179,473);
	*taille=8;
      }
      
      /*Taille9*/
      if ((_X > 23 && _X < 195) && (_Y > 458 && _Y < 522)) {
        ChargerImage("rsc/choixtaille9.jpg",20,50,0,0,179,473);
	*taille=9;
      }

      /*bouton jouer*/
      if(*taille != 0 && *NbJoueurs != 0) {
        ChargerImage("rsc/jouer.jpg",220,450,0,0,178,68);
        if((_X > 223 && _X < 396) && (_Y > 452 && _Y < 516)) {    
	  /*Permet de savoir si la fenêtre peut-être fermer*/
	  PermissionClose=1;
        }
      }
    }
  }     
}
