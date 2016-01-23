#include "Objets/Texture.h"

Texture *initTexture(char *pathFile, int id, int typeSize, float sizeX, float sizeY, float unitX, float unitY){
	Texture *new = (Texture*)malloc(sizeof(Texture));
	if(!new){
		fprintf(stderr,"ERROR ALLOCATION TEXTURE\n");
		exit(1);
	}

	SDL_Surface *image = IMG_Load(pathFile);				/* Chargement de l'image donnée en argument */
	if(image == NULL) {
		fprintf(stderr, "Impossible de charger l'image \n");
		exit(1);
	}
	
	glGenTextures(id, &(new->texture));						/* Chargement de la texture sur la carte graph */
	glBindTexture(GL_TEXTURE_2D, new->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	/* Gestion rapport taille image/objet */

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);					/* Dé-bind de la texture */

	new->idTexture = id;

	if(typeSize){
		new->width = sizeX*image->w / ((float)unitX);
		new->height = sizeX*image->h / ((float)unitY);
		new->ratio = 1;
	}
	else{
		new->width = sizeX;
		new->height = sizeY;
		new->ratio = ((float)sizeX*unitX)/image->w;
	}


	SDL_FreeSurface(image);	
	
	return new;						/* Libert l'image de mémoire */
}

void dessinTexture(Texture *texture, float posX, float posY){
	texture->posX = posX;
	texture->posY = posY;

	glEnable(GL_TEXTURE_2D);			/* Annoncer l'intention d'utiliser des textures */

        glBindTexture(GL_TEXTURE_2D, texture->texture);	/* Chargement Texture */
		
	glPushMatrix();
		glTranslatef(posX,posY,-1);	
		glBegin(GL_QUADS);
		
		glColor3f(1, 1, 1);
		
		/* Liaison repère Texture/ point objet */
		glTexCoord2f(0, texture->ratio);
		glVertex2f(-texture->width/2, -texture->height/2);
		
		glTexCoord2f(texture->ratio, texture->ratio);
		glVertex2f(texture->width/2, -texture->height/2);
		
		glTexCoord2f(texture->ratio, 0);
		glVertex2f(texture->width/2, texture->height/2);
		
		glTexCoord2f(0, 0);
		glVertex2f(-texture->width/2, texture->height/2);
		
		glEnd();
		
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        
}

void freeTexture(Texture *texture){
	glDeleteTextures(texture->idTexture, &(texture->texture));
	free(texture);
}