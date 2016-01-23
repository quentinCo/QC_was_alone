#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>


/*--------------------------------
TEXTURE:
Structure contenant tous les éléments d'un niveau
et gerant leur intitialisation et affichage.
----------------------------------*/
typedef struct Texture{
	float width;		/* Largeur en unité relative */
	float height;		/* Hauteur en unité relative */
	float posX;		/* Position en unité relative */
	float posY;		/* Position en unité relative */
	GLuint texture;	/* Image de font */
	float ratio;
	int idTexture;
}Texture;

/*----INITTEXTURE----*/
/*--------------------------------
Initialise et charge une texure.
	pathFile : Chemin vers la texture.
	id : Identifient de la texture.
	typeSize : 1 si le support de la texture prend les dimensions de l'image, 0 sinon.
	sizeX, sizeY : Dimension en unité relative du support de la texture.
	unitX, unitY : Unité relative en pixel.
----------------------------------*/
Texture *initTexture(char *pathFile, int id, int typeSize, float sizeX, float sizeY, float unitX, float unitY);

/*----DESSINTEXTURE----*/
/*--------------------------------
Dessine un texture.
	texture : Une texture.
	posX, posY : Position en unité relative.
----------------------------------*/
void dessinTexture(Texture *texture, float posX, float posY);

/*----FREETEXTURE----*/
/*--------------------------------
Libert la mémoire alloué et la texture.
----------------------------------*/
void freeTexture(Texture *texture);

#endif