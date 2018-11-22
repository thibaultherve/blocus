/*Thibault HERVE*/

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

#include "gagnant.h"

#define OFFSET 20

void main(int gagnant) {
	char* texte;

InitialiserGraphique();
CreerFenetre(OFFSET,OFFSET,500,200);
ChoisirTitreFenetre("Blocus");

if (gagnant==1)
	texte="Le joueur 1 a gagne !";
else
	texte="Le joueur 2 a gagne !";

EcrireTexte(20,40,texte,2);

while(1);

}