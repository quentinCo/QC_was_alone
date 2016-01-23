#include "Objets/Rectangle.h"

/*----CREATERECTANGLE----*/
Rectangle *CreateRectangle(float *value){
	if(!value) return NULL;

	Rectangle *rect=(Rectangle*)malloc(sizeof(Rectangle));

	if(!rect){
		fprintf(stderr,"Erreur Allocation Rectangle\n");
		exit(1);
	}
	
	rect->width = value[0];
	rect->height = value[1];
	rect->posX = value[2];
	rect->posY = value[3];

	return rect;
}

/*----DESSINRECT----*/
void dessinRect(Rectangle *rect, int filled, int r, int v, int b){
	glColor3ub(r,v,b);
	glPushMatrix();
		glTranslatef(rect->posX,rect->posY,-1.);
		glScalef(rect->width,rect->height,0.);

		if (filled==1){
			glBegin(GL_QUADS);
		}
		else{
			glBegin(GL_LINE_LOOP);
		}

		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(-0.5, -0.5);
		glEnd();
	glPopMatrix();
}

/*----FREERECTANGLE----*/
void freeRectangle(Rectangle *rect){
	if(rect){
		free(rect);
	}
}