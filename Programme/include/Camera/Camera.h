#ifndef CAMERA_H_
#define CAMERA_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Objets/Player.h"

/*--------------------------------
CAMERA:
Structure perettant la gestion d'un camera 2D
----------------------------------*/
typedef struct Camera{
	float posX;	/* Position sur l'axe X en unité relative. */
	float posY;	/* Position sur l'axe Y en unité relative. */
}Camera;


/*----INITCAMERA----*/
/*--------------------------------
Initialise les valeurs posX et posY d'une camera.
	cam : une camera.
	X : position en X.
	Y : position en Y.
----------------------------------*/
void initCamera(Camera *cam,float X, float Y);


/*----DEPCAMERA----*/
/*--------------------------------
Gestion du déplacement de la camera, recalcule la postion d'un camera
en fonction de la position du joueur actif.
	cam : camera à modifier
	player : joueur courrent.
	largeur, hauteur: dimension du niveau en unité relative.
	scaleX, scaleY : dimension de l'écran en unité relative.
----------------------------------*/
void depCamera(Camera *cam, Player *player, int largeur, int hauteur, int scaleX, int scaleY);


/*----VERIFSUIVI----*/
/*--------------------------------
Verifier si la camera doit suivre le player (latence).
La camera commence à suivre le joueur s'il dépasse + ou - 1/4 de la position camera.
	posCam : position, X ou Y, de la camera.
	pos: nouvelle position, X ou Y, supposée de la camera (position du joueur).
	scale : dimension, X ou Y, de l'écran en unité relative.
----------------------------------*/
void verifSuivi(float posCam, float *pos, int scale);


/*----VERIFSUIVI----*/
/*--------------------------------
Verifier si la camera arrive en bordure de niveau.
	pos: nouvelle position, X ou Y, supposée de la camera (position du joueur).
	dim : dimension, X ou Y, du niveau.
	scale : dimension, X ou Y, de l'écran en unité relative.
----------------------------------*/
void verifPosLimit(float *pos, int dim, int scale);

#endif