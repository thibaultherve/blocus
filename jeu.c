/*Thibault HERVE */

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <unistd.h>

#include "jeu.h"
#include "gagnant.h"

/*Taille d'une case*/
#define T_CASE 70

/*Distance entre le bord de la fenêtre et la grille de jeu*/
#define OFFSET 20
#define BORDURE 40

/*Définie le mode du joueur (humain ou IA)*/
#define AUTO 0
#define MANUEL 1

/*Caracterise les joueurs*/
#define JOUEUR_1 1
#define JOUEUR_2 2

/*Caracterise le pion du joueur 1 ou 2*/
#define PION 0
#define CROIX 1


int Jeu(int NbJoueurs, int taille) {
    srand(time(NULL));

    /* Paramètres fenêtre */
    int tailleFenetre=(T_CASE*taille)+BORDURE;
    
    /* Tableau des coordonnées de chaque case de la grille*/
    int coord[taille+1][taille+1][4];
    
    /* Tableau des données de la grille*/
    int donnees[taille+2][taille+2];

    int modeJ2, joueur, mode, gagnant=0;
    
    CreerFenetre(OFFSET,OFFSET,tailleFenetre,tailleFenetre);
    ChoisirTitreFenetre("Blocus");
    ConstructionGrille(taille);
    RemplissageCoordGrille(taille,coord);
    InitialisationDonnees(taille,donnees);

    if (NbJoueurs==1)
        modeJ2=AUTO;

    else
        modeJ2=MANUEL;

    PlacePion(taille, JOUEUR_1, MANUEL, coord, donnees, 1);
    PlacePion(taille, JOUEUR_2, modeJ2, coord, donnees, 1);
    
    joueur=JOUEUR_1;
    mode=MANUEL;

    while (gagnant==0) {
        PlacePion(taille, joueur, mode, coord, donnees, 0);
        PlaceCroix(taille, joueur, mode, coord, donnees);
        

        if (joueur==JOUEUR_1) {
            joueur=JOUEUR_2;
            mode=modeJ2;
        }
        else {
            joueur=JOUEUR_1;
            mode=MANUEL;
        }
        gagnant=Victoire(taille, donnees, joueur);
    }
    
    return gagnant;
}


void PlacePion(int taille, int joueur, int mode, int coord[][taille+1][4], int donnees[][taille+2], int initialisation) {
    /*Case selectionée*/
    int case_i=0, case_j=0;

    if (mode==MANUEL) {

        TrouveCaseCliquee(taille, PION, initialisation, joueur, coord, donnees, &case_i, &case_j);
    }
    else if (mode==AUTO) {
        TrouveCaseAlea(taille, PION, initialisation, joueur, coord, donnees, &case_i, &case_j);
    }
    
    
    AfficheImagePion(taille, coord, &case_i, &case_j, donnees, joueur, initialisation);

        int i,j=1;

        printf(" X");
        for (i=1; i<taille+1; i++) {
            printf(" %d", i);
        }

        printf("\n");   

        for (i=1; i<taille+1; i++) {
            printf(" %d", i);
            for (j=1; j<taille+1; j++) {
                printf(" %d", donnees[i][j]);
            }
            printf("\n");
        }
        printf("\n");
           
 
}


void PlaceCroix(int taille, int joueur, int mode, int coord[][taille+1][4], int donnees[][taille+2]) {
    /*Case selectionée*/
    int case_i=0, case_j=0;

    if (mode==MANUEL) {

        TrouveCaseCliquee(taille, CROIX, 0, joueur, coord, donnees, &case_i, &case_j);
    }
    else if (mode==AUTO) {
        TrouveCaseAlea(taille, CROIX, 0, joueur, coord, donnees, &case_i, &case_j);
    }

    
    AfficheImageCroix(taille, coord, &case_i, &case_j, donnees, joueur);

         int i,j=1;

        printf(" X");
        for (i=1; i<taille+1; i++) {
            printf(" %d", i);
        }

        printf("\n");   

        for (i=1; i<taille+1; i++) {
            printf(" %d", i);
            for (j=1; j<taille+1; j++) {
                printf(" %d", donnees[i][j]);
            }
            printf("\n");
        }
        printf("\n");
}


void ConstructionGrille(int taille) {
    /*parametres cube*/
    int posx=OFFSET, posy=OFFSET;   
    int i, j;
    
    for (i=0; i<taille; i++, posy=posy+T_CASE) {
        for (j=0; j<taille; j++, posx=posx+T_CASE ) {
            DessinerRectangle(posx, posy, T_CASE, T_CASE);
            if (j==taille-1) {
                posx=-T_CASE+OFFSET;
            }
        }
    }    
}

void RemplissageCoordGrille(int taille, int coord[][taille+1][4]) {    
    int i,j,k,a=0;
    int basex=OFFSET, basey=OFFSET;
    
    /*Mise à 0 de toutes les cases du tableau*/
    for (i=0; i<taille+1; i++) {
        for (j=0; j<taille+1; j++) {
            for (k=0; k<4; k++) {
                coord[i][j][k]=0;
            }
        }
    }
    
    /*Remplissage du tableau avec les coordonnées de chaque case de la grille */
    for (i=1; i<taille+1; i++) {
        for (j=1; j<taille+1; j++) {
            for (k=0; k<4; k++) {
                if (k==0)
                    a=basex;
                
                if (k==1)
                    a=basey;
                
                if (k==2) {
                    a=OFFSET+(j*T_CASE);
                    basex=a;
                }                
                if (k==3) {
                    a=OFFSET+(i*T_CASE);                    
                }
                
                coord[i][j][k]=a;
            }
        }
        basex=OFFSET;
        basey=OFFSET+(i*T_CASE);
    }    
}

void TrouveCaseCliquee(int taille, int piece, int initialisation, int joueur, int coord[][taille+1][4], int donnees[][taille+2], int* case_i, int* case_j) 
{
    int i,j,k;

    /*Position actuel du pion du joueur*/
    int save_case_i, save_case_j;

    if ((initialisation==1) || (piece==CROIX)) {
        do {           
            while (!SourisCliquee());

            for (i=1; i<taille+1; i++) {
                for (j=1; j<taille+1; j++) {                
                    if (_X > coord[i][j][0] && _X < coord[i][j][2] && _Y > coord[i][j][1] && _Y < coord[i][j][3]) {
                        *case_i=i;
                        *case_j=j;
                    }
                }
            }
        }   while(donnees[*case_i][*case_j]!=0);
    }

else {

    TrouvePositionPion(taille, donnees, joueur, &save_case_i, &save_case_j);

    do {
        while (!SourisCliquee());

        for (i=1; i<taille+1; i++) {
            for (j=1; j<taille+1; j++) {                
                if (_X > coord[i][j][0] && _X < coord[i][j][2] && _Y > coord[i][j][1] && _Y < coord[i][j][3]) {
                    *case_i=i;
                    *case_j=j;
                }
            }
        }

    } while(donnees[*case_i][*case_j]!=0 || *case_i>save_case_i+1 || *case_i<save_case_i-1 || *case_j>save_case_j+1 || *case_j<save_case_j-1);
}


}


void TrouvePositionPion(int taille, int donnees[][taille+2], int joueur, int* save_case_i, int* save_case_j) {
    int i, j;

    for (i=0; i<taille+2; i++) {
        for (j=0; j<taille+2; j++) {
            if (donnees[i][j]==joueur) {
                *save_case_i=i;
                *save_case_j=j;                
            }
        }
    }
}


void TrouveUneCaseLibre(int taille, int donnees[][taille+2], int* case_i, int* case_j) {
  int k, n_alea, a;

    do {
    /* Nombre aléatoire entre 1 et taille au carré*/
        n_alea=rand()%(taille*taille)+1;

        a=n_alea/taille;

        if (n_alea%taille==0) {
            *case_i=a;
            *case_j=taille;
        }
        else {
            *case_i=a+1;
            *case_j=n_alea-(a*taille);
        }

        
    }   while(donnees[*case_i][*case_j]!=0);

}
 

void TrouveCaseAlea (int taille, int piece, int initialisation, int joueur, int coord[][taille+1][4], int donnees[][taille+2], int* case_i, int* case_j) {
   /*Position actuel du pion du joueur*/
 int save_case_i, save_case_j;

 int i,j;

 TrouvePositionPion(taille, donnees, joueur, &save_case_i, &save_case_j);

 if ((initialisation==1) || (piece==CROIX)) {

    TrouveUneCaseLibre(taille, donnees, &i, &j);

}

else {

    do {

        TrouveUneCaseLibre(taille, donnees, &i, &j);
        
    } while(i>save_case_i+1 || i<save_case_i-1 || j>save_case_j+1 || j<save_case_j-1);
}



*case_i=i;
*case_j=j;

    usleep(600000);

}


void AfficheImagePion(int taille, int coord[][taille+1][4], int* case_i, int* case_j, int donnees[][taille+2], int joueur, int initialisation) {


    /* decalage permettant de bien centrer les images sur une case*/
    int stark_decalage_x=1, stark_decalage_y=12, lannister_decalage_x=1, lannister_decalage_y=19;

    int save_case_i, save_case_j;

    TrouvePositionPion(taille, donnees, joueur, &save_case_i, &save_case_j);

    if(initialisation==0) {
    /*Place une case blanche à l'ancienne position du pion*/
    ChargerImage("rsc/case_blanche.png", coord[save_case_i][save_case_j][0]+1, coord[save_case_i][save_case_j][1]+1, 0, 0, 69, 69);
    /* La case blanche devient libre*/
    donnees[save_case_i][save_case_j]=0;
    }


    if (joueur==JOUEUR_1) {
        ChargerImage("rsc/j1_stark.png", coord[*case_i][*case_j][0]+stark_decalage_x, coord[*case_i][*case_j][1]+stark_decalage_y, 0, 0, 69, 51);
        donnees[*case_i][*case_j]=JOUEUR_1;
    }

    else if (joueur==JOUEUR_2) {
        ChargerImage("rsc/j2_lannister.png", coord[*case_i][*case_j][0]+lannister_decalage_x, coord[*case_i][*case_j][1]+lannister_decalage_y, 0,0,69,51);
        donnees[*case_i][*case_j]=JOUEUR_2;
    }

}
 

void AfficheImageCroix(int taille, int coord[][taille+1][4], int* case_i, int* case_j, int donnees[][taille+2], int joueur){


    /* decalage permettant de bien centrer les images sur une case*/
    int croix_decalage_x=1, croix_decalage_y=1;

    
    char* nom_image;
    
    if (joueur==JOUEUR_1) {
        nom_image="rsc/j1_croix.png";
    }

    else if (joueur==JOUEUR_2) {
        nom_image="rsc/j2_croix.png";
    }

ChargerImage(nom_image,
           coord[*case_i][*case_j][0]+croix_decalage_x,
           coord[*case_i][*case_j][1]+croix_decalage_y,
           0,0,69,69);
        donnees[*case_i][*case_j]=3;
}

void InitialisationDonnees(int taille, int donnees[][taille+2]) {    
    int i,j=0;
    int basex=OFFSET, basey=OFFSET;


    /*Mise à 3 de toutes les cases non visibles de la grille (=1 croix)*/
    for (i=0, j=0; i<taille+2; i++) {
        donnees[i][j]=3;
    }

    for (i=0, j=0; j<taille+2; j++) {
        donnees[i][j]=3;
    }

    for (i=0, j=taille+1; i<taille+2; i++) {
        donnees[i][j]=3;
    }

    for (i=taille+1, j=0; j<taille+2; j++) {
        donnees[i][j]=3;
    }

    /*Mise à 0 des paramètres de chaque case visible de la grille (=case libre)*/
    for (i=1; i<taille+1; i++) {
        for (j=1; j<taille+1; j++) {
            donnees[i][j]=0;
        }
    }
}

int Victoire(int taille, int donnees[][taille+2], int joueur) {
    int i,j, gagnant=0;
    int  j1_i, j1_j, j2_i, j2_j;


    for (i=0; i<taille+2; i++) {
        for (j=0; j<taille+2; j++) {
            if (donnees[i][j]==1) {
                j1_i=i;
                j1_j=j;                
            }
            if (donnees[i][j]==2) {
                j2_i=i;
                j2_j=j;                
            }
        }
    }


    if (joueur==JOUEUR_1 && donnees[j1_i][j1_j-1]!=0 && donnees[j1_i][j1_j+1]!=0 && donnees[j1_i-1][j1_j]!=0 && donnees[j1_i-1][j1_j+1]!=0 && donnees[j1_i-1][j1_j-1]!=0 && donnees[j1_i+1][j1_j]!=0 && donnees[j1_i+1][j1_j+1]!=0  && donnees[j1_i+1][j1_j-1]!=0) {
       gagnant=2;
       printf("victoire du joueur 2\n");

   } 

   else if (joueur==JOUEUR_2 && donnees[j2_i][j2_j-1]!=0 && donnees[j2_i][j2_j+1]!=0 && donnees[j2_i-1][j2_j]!=0 && donnees[j2_i-1][j2_j+1]!=0 && donnees[j2_i-1][j2_j-1]!=0 && donnees[j2_i+1][j2_j]!=0 && donnees[j2_i+1][j2_j+1]!=0 && donnees[j2_i+1][j2_j-1]!=0) {
       gagnant=1;
       printf("victoire du joueur 1\n");
   }

   return gagnant;
} 
