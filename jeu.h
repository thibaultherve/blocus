/*Thibault HERVE*/

#ifndef JEU_H
#define JEU_H

/* Déroulement du jeu, retourne le numéro du gagnant (1 ou 2) */
int Jeu (int joueur, int taille);

/* Permet de placer le pion d'un joueur */
void PlacePion(int taille, int joueur, int mode, int coord[][taille+1][4], int donnees[][taille+2], int initialisation);

/* Permet de placer la croix d'un joueur */
void PlaceCroix(int taille, int joueur, int mode, int coord[][taille+1][4], int donnees[][taille+2]);

/*Trouve la case qui vient d'être cliquée*/
void TrouveCaseCliquee(int taille, int piece, int initialisation, int joueur, int coord[][taille+1][4], int donnees[][taille+2], int* case_i, int* case_j);

/*Trouve la position du pion du joueur 1 ou 2*/
void TrouvePositionPion(int taille, int donnees[][taille+2], int joueur, int* save_case_i, int* save_case_j);

/*Affiche l'image des pions*/
void AfficheImagePion(int taille, int coord[][taille+1][4], int* case_i, int* case_j, int donnees[][taille+2], int joueur, int initialisation);

/*Affiche l'image des croix*/
void AfficheImageCroix(int taille, int coord[][taille+1][4], int* case_i, int* case_j, int donnees[][taille+2], int joueur);

/*Donne un nombre aléatoire entre 1 et (taille*taille) et donne les coordonnées d'une case aléatoire  correspondante en i et j*/
void TrouveUneCaseLibre(int taille, int donnees[][taille+2], int* case_i, int* case_j);

 /*Trouve une case aléatoire qui soit libre*/
void TrouveCaseAlea (int taille, int piece, int initialisation, int joueur, int coord[][taille+1][4], int donnees[][taille+2], int* case_i, int* case_j);

/* Test de victoire : renvoie 0 si le vainqueur n'est pas connu, 1 si c'est le joueur 1, 2 si c'est le joueur 2 */
int Victoire(int taille, int donnees[][taille+2], int joueur);

/* Affichage de la grille */
void ConstructionGrille(int taille);

/*Remplis un tableau contenant les coordonnées de chaque case de la grille*/
void RemplissageCoordGrille(int taille, int coord[][taille+1][4]);

/* Initialise les données de la grille à 0 (toutes les cases sont libres) */
void InitialisationDonnees(int taille, int donnees[][taille+2]);


#endif /* JEU_H */
