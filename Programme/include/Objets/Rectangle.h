#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

/*--------------------------------
RECTANCLE:
Structure de forme pour les obstacles et les joueurs.
----------------------------------*/
typedef struct Rectangle{
	float width;
	float height;
	float posX;
	float posY;
}Rectangle;


/*----CREATERECTANGLE----*/
/*--------------------------------
Création d'un rectangle.
		value : tableau contenant toutes les valeurs suivantes dans l'ordre suivant.
			Largeur du rectangle.
			Hauteur du rectangle.
			Position en X du rectangle.
			Position en Y du rectangle.
----------------------------------*/
Rectangle *CreateRectangle(float *value);


/*----DESSINRECT----*/
/*--------------------------------
Dessine un rectangle.
	rect : la forme à dessiner.
	filled : 1 si remplissage de la forme, 0 si vide.
	r, v, b : les valeurs de rouge, vert, bleu, pour la couleur du rectangle.
----------------------------------*/
void dessinRect(Rectangle *rect, int filled, int r, int v, int b);


/*----FREERECTANGLE----*/
/*--------------------------------
Libert la mémoire alloué.
----------------------------------*/
void freeRectangle(Rectangle *rect);

#endif