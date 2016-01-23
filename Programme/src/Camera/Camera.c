#include "Camera/Camera.h"

/*----INITCAMERA----*/
void initCamera(Camera *cam,float X, float Y){
	cam->posX = X;
	cam->posY = Y;
}

/*----DEPCAMERA----*/
void depCamera(Camera *cam, Player *player, int largeur, int hauteur, int scaleX, int scaleY){
	float newPosX = player->forme->posX;
	float newPosY = player->forme->posY;

	verifSuivi(cam->posY, &newPosY, scaleY);
	verifSuivi(cam->posX, &newPosX, scaleX);

	verifPosLimit(&newPosY, hauteur, scaleY);
	verifPosLimit(&newPosX, largeur, scaleX);

	
	cam->posX = newPosX;
	cam->posY = newPosY;
}

/*----VERIFSUIVI----*/
void verifSuivi(float posCam, float *pos, int scale){
	if(*pos >= posCam + scale/4) *pos -= scale/4;
	else if(*pos <= posCam - scale/4) *pos += scale/4;
	else *pos = posCam;
}

/*----VERIFSUIVI----*/
void verifPosLimit(float *pos, int dim, int scale){
	if(*pos > dim/2-scale/2) *pos = dim/2-scale/2;
	else if(*pos < -dim/2+scale/2) *pos = -dim/2+scale/2;
}