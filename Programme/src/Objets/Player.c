#include "Objets/Player.h"

/*----CREATEPLAYER----*/
Player *CreatePlayer(float *value){
	if(!value) return NULL;

	Player *player = (Player*)malloc(sizeof(Player));

	if(!player){
		fprintf(stderr,"Erreur Player\n");
		exit(1);
	}
	
	/*Prepartion des tableaux pour CreateRectangle*/
	float valueForme[4];		
	float valueArrivee[4];
	
	valueForme[0] = value[0];
	valueForme[1] = value[1];
	valueForme[2] = value[2];
	valueForme[3] = value[3];
	
	valueArrivee[0] = value[0]+2*value[0]/10;
	valueArrivee[1] = value[1]+2*value[1]/10;
	valueArrivee[2] = value[8];
	valueArrivee[3] = value[9];
	

	player->forme = CreateRectangle(valueForme);
	player->arrive = CreateRectangle(valueArrivee);

	/*Initialisation des valeurs de saut*/
	player->hauteur = value[4];
	player->timeJump = value[5];

	/*Initialisation des variables de déplacement en X*/
	player->accelerationX = value[7];
	player->vitesseX = 0;
	player->limVitX = value[6];
	
	/*Initialisation des variables de déplacement en Y*/
	player->accelerationY = 0;
	player->vitesseY = 0;
	
	/*Initialisation des booléen de collision*/
	player->coHaut = 0;
	player->coBas = 0;
	player->coGauche = 0;
	player->coDroite = 0;

	/*Initialisation des booléen d'état*/
	player->jump = 0;
	player->move = 0;
	player->chute = 0;

	/*Initilisation du booléen d'arrivée*/
	player->arrValide = 0;

	return player;
}

/*----DESSINEPLAYER----*/
void dessinPlayer(Player *player, int filled, int r, int v, int b){
	int filledArr = 0;
	if(player->arrValide) filledArr = 1;

	dessinRect(player->arrive,filledArr,r,v,b);

	if(!player->arrValide) dessinRect(player->forme,filled,r,v,b);
	else dessinRect(player->forme,filled,255,255,255);
}

/*----INITDEPY----*/
void initDepY(Player *player){
	player->accelerationY = -1*player->hauteur / (2*(player->timeJump*player->timeJump));
	player->vitesseY = player->hauteur / player->timeJump - (player->accelerationY)*player->timeJump/2;
}

/*----GRAVITE----*/
void gravite(Player *player, int top, int bottom){
	if(/*!player->jump && */!player->coBas){
		
		if(!player->chute) player->chute = 1;
		
		player->forme->posY += player->vitesseY;

		/* Limite de vitesse en chute -1 */
		if(player->vitesseY > -1) player->vitesseY += player->accelerationY;
		
		/* Condition supplémentaire pour le saut */
		if(player->jump && player->coHaut) player->vitesseY = 0;
		
		/* Limite de terrain */
		if(player->forme->posY < bottom) player->forme->posY = top;		
	}
	else {
		player->chute = 0;
		player->jump = 0;
		player->vitesseY = 0;
	}
	verifArrive(player);
}

/*----JUMP----*/
void Jump(Player *player){
	if(player->coHaut==0){
		player->coBas = 0;
		player->chute = 0;
		player->jump = 1;
		initDepY(player);
		player->forme->posY += player->vitesseY;
	}
}

/*----DEPLACEMENTX----*/
void deplacementX(Player *player, int sens, int left, int right){
	float lim ;
	float gain ;
	float newPos = player->forme->posX;

	player->move = 1;

	lim = sens*player->limVitX;
	gain = sens*player->accelerationX;

	if(sens==-1 && player->coGauche==0){
		if(player->vitesseX>lim){
			if(player->vitesseX>0){
				player->vitesseX = 0;
			}
			player->vitesseX += gain;
		}
	}
	else if(sens==1 && player->coDroite==0){
		if(player->vitesseX<lim){
			if(player->vitesseX<0){
				player->vitesseX = 0;
			}
			player->vitesseX += gain;
		}
	}
	newPos += player->vitesseX;
	
	if(newPos-player->forme->width/2 < left){
		newPos = left + player->forme->width/2;
	}
	else if(newPos+player->forme->width/2 > right){
		newPos = right - player->forme->width/2;
	}

	player->forme->posX = newPos;

	verifArrive(player);
}

/*----VERIFARRIVE----*/
void verifArrive(Player *player){
	float zoneX = player->arrive->width/2;
	float zoneY = player->arrive->height/2;

	int conditionX = player->forme->posX < player->arrive->posX + zoneX && player->forme->posX > player->arrive->posX - zoneX;
	int conditionY = player->forme->posY < player->arrive->posY + zoneY && player->forme->posY > player->arrive->posY - zoneY;

	if(conditionX && conditionY){
		player->arrValide = 1;
	}
	else player->arrValide = 0;
}

/*----FREEPLAYER----*/
void freePlayer(Player *player){
	if(player){
		freeRectangle(player->forme);
		freeRectangle(player->arrive);
		free(player);
	}
}

