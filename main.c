/*Thibault HERVE*/

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <time.h>

#include "menu.h"
#include "jeu.h"
#include "gagnant.h"

int main(void) {    
   
    int taille, NbJoueurs, gagnant;
    
    /* Paramètres fenêtre */
    int posx=20, posy=20, longf=420, hautf=550;
    
    InitialiserGraphique();
    
    CreerFenetre(posx,posy,longf,hautf);  
    ChoisirTitreFenetre("Blocus");
    
    ChoixConfiguration(&taille, &NbJoueurs);
    FermerGraphique();
    
    InitialiserGraphique();
    gagnant=Jeu(NbJoueurs, taille);

    FermerGraphique();

    InitialiserGraphique();

    printf("zbeub\n");
    /*AfficheVictoire(gagnant);*/
   
    return EXIT_SUCCESS;
}
