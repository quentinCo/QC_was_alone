#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Rectangle.h"

/*--------------------------------
PLAYER:
Structure contenant toutes les caractéristiques et comportement d'un joueur.
----------------------------------*/
typedef struct Player{
	Rectangle *forme;	/* forme du joueur */
	
	Rectangle *arrive;	/* forme du cadre d'arrivé du joueur */

	float hauteur;		/* hauteur du saut */
	float timeJump;		/* temps pour faire le saut (nombre de frame) // A VOIR */

	/* variable de déplacement */
	float accelerationY;	/* acceleration en Y */
	float accelerationX;	/* acceleration en X */
	float vitesseY;		/* vitesse instantanée en Y */
	float vitesseX;		/* vitesse instantanée en X */
	float limVitX;		/* acceleration maximum en X */

	/* boolean de collision (0 : pas de collision, 1 : collision) */
	int coHaut;		/* collision haute */
	int coBas;		/* collision basse */
	int coGauche;		/* collision gauche */
	int coDroite;		/* collision droite */

	/* boolean d'état */
	int jump;		/* 1 : si en saut. */
	int move;		/* 1 : si en movement (deplacement en X). */
	int chute;		/* 1 : si entraint de tomber */

	int arrValide;		/* 1 : si le joueur est dans son cadre d'arrivé. */
}Player;


/*----CREATEPLAYER----*/
/*--------------------------------
Création d'un joueur.
		value : tableau contenant toutes les valeurs suivantes dans l'ordre suivant.
			Largeur du joueur.
			Hauteur du joueur.
			Position en X du joueur.
			Position en Y du joueur.
			Hauteur du saut possible par le joueur.
			Temps pour faire le saut.
			Vitesse maximum en X du joueur.
			Acceleration en X.
			Position X du cadre d'arrivé du joueur.
			Position Y du cadre d'arrivé du joueur.
----------------------------------*/
Player *CreatePlayer(float *value);


/*----DESSINEPLAYER----*/
/*--------------------------------
Dessine un joueur.
	player : le joueur à dessiner.
	filled : 1 si remplissage de la forme, 0 si vide.
	r, v, b : les valeurs de rouge, vert, bleu, pour la couleur du joueur.
----------------------------------*/
void dessinPlayer(Player *player, int filled, int r, int v, int b);


/*----INITDEPY----*/
/*--------------------------------
Initialise l'acceleration et la vitesse en Y selon la hauteur de saut.
	player : un joueur.
----------------------------------*/
void initDepY(Player *player);


/*----GRAVITE----*/
/*--------------------------------
Gestion de la chute des joueurs. Si le joueur sort du niveau en bas, il réapparé en haut.
	player : un joueur.
	top : limite haute du niveau.
	bottom : limite basse du niveau.
----------------------------------*/
void gravite(Player *player, int top, int bottom);


/*----JUMP----*/
/*--------------------------------
Initialise les varibles de déplacement en Y et jump du saut du personnage.
	player : un joueur.
----------------------------------*/
void Jump(Player *player);


/*----DEPLACEMENTX----*/
/*--------------------------------
Gestion du deplacement sur l'axe X.
	player : un joueur.
	sens : direction du deplacement (-1 : gauche, 1 : droite).
	left : limite gauche du niveau.
	right : limite droite du niveau.
----------------------------------*/
void deplacementX(Player *player, int sens, int left, int right);


/*----VERIFARRIVE----*/
/*--------------------------------
Verifie que le joueur est dans son cadre d'arrivé.
	player : un joueur.
----------------------------------*/
void verifArrive(Player *player);


/*----FREEPLAYER----*/
/*--------------------------------
Liberation de la mémoire alloué.
	player : un joueur.
----------------------------------*/
void freePlayer(Player *player);

#endif