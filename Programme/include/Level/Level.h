#ifndef LEVEL_H_
#define LEVEL_H_

#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

#include "Parser/Parser.h"
#include "Stockage/List.h"
#include "Objets/Player.h"
#include "Collisions/Collision.h"
#include "Camera/Camera.h"
#include "Objets/Texture.h"

/*--------------------------------
LEVEL:
Structure contenant tous les éléments d'un niveau
et gerant leur intitialisation et affichage.
----------------------------------*/
typedef struct Level{
	int width;		/* Largeur du niveau en unité relative */
	int height;		/* Hauteur du niveau en unité relative */
	Camera camera;		
	List *listObstacle;	/* Liste des obstacles dans le niveau (murs, ...) */
	Player *playerTab[3];	/* Tableau contenant les différents joueurs */
	int numPlayer;
	Texture *background;	/* Image de fond */
	float rotation;		/* Rotation du fond */
	Texture *endText;	/* Image du texte de fin */
	int end;		/* Booléen : 1 si le niveau est réussi, 0 sinon.*/
}Level;


/*----INITLEVEL----*/
/*--------------------------------
Initialisation des différentes variables à partir d'un fichier .csv.
		pathFile : Chemin vers le fichier contenant les info sur le niveau.
		untiX, unitY : Unité relative en pixel.
----------------------------------*/
Level *initLevel(char *pathFile, float unitX, float unitY);


/*----LECTUREPARSE----*/
/*--------------------------------
Lecture du fichier .csv et initialisation des différentes variables du level.
		pathFile : Chemin vers le fichier contenant les info sur le niveau.
		level : Niveau à initisaliser.
----------------------------------*/
void lectureParse(char *pathFile, Level *level);


/*----DESSINLEVEL----*/
/*--------------------------------
Dessine les différents éléments d'un niveau.
	level : le niveau à dessiner.
	player : le joueur actuellement joué parmis les player du niveau.
	scaleX, scaleY : dimension de l'écran en unité relative, pour la gestion camera.
----------------------------------*/
void dessinLevel(Level *level, Player *player, int scaleX, int scaleY);


/*----DESSINOBSTACLE----*/
/*--------------------------------
Dessine les différents obstacle d'un niveau.
	list : liste des obstacles d'un niveau.
	r, v, b : les valeurs de rouge, vert, bleu, pour la couleur des obstacles.
----------------------------------*/
void dessinObstacles(List *list, int r, int v, int b);


/*----COLLISION----*/
/*--------------------------------
Verification et gestion des collisions dans un niveau.
	level : un niveau.
----------------------------------*/
void Collision(Level *level);


/*----VERIFVICTOIRE----*/
/*--------------------------------
Verifie si tous les joueurs sont arrivés dans leurs cases.
	level : un niveau.
----------------------------------*/
void verifVictoire(Level *level);


/*----FREELEVEL----*/
/*--------------------------------
Libert la mémoire alloué à un niveau.
----------------------------------*/
void freeLevel(Level *level);

#endif