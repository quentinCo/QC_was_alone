#include "Collisions/Collision.h"

/*----COLLISIONOBSTACLE----*/
void CollisionObstacle(Player *player,List *list){
	int i;
	Node *temp = list->tete;
	
	InitCollision(player);
	for(i=0; i<list->size; i++){
		VerifCollision(player, temp->obj);
		temp = temp->after;
	}

}

/*----COLLISIONPLAYER----*/
void CollisionPlayer(Player *player, Player **playerTab, int size){
	int i;
	
	int testH = 0;
	int testB = 0;
	
	float minDY;
	for(i=0; i<size; i++){
		testH = 0;
		testB = 0;
		if(player != playerTab[i]){
			VerifCollision_H_B(player, playerTab[i]->forme, &testH, &testB);
			if(testB){
				minDY = player->forme->height/2 + playerTab[i]->forme->height/2;
				player->forme->posY = playerTab[i]->forme->posY + minDY;
				player->coBas = 1;
			}
			else if(testH){
				player->vitesseX = 0;
				player->coHaut = 1;
			}
		}
	}
}

/*----INITCOLLISION----*/
void InitCollision(Player *player){
	player->coHaut = 0;
	player->coBas = 0;
	player->coDroite = 0;
	player->coGauche = 0;
}

/*----VERIFCOLLISION----*/
void VerifCollision(Player *player, Rectangle *objet){

	int testH = 0;
	int testB = 0;
	int testD = 0;
	int testG = 0;
	VerifCollision_H_B(player, objet, &testH, &testB);
	if(!testB && !testH){
		VerifCollision_G_D(player, objet, &testD, &testG);
	}

	AjusterPos(player, objet, testH, testB, testD, testG);
}

/*----COLLISIONOBSTACLE_G_D----*/
void VerifCollision_G_D(Player *player, Rectangle *objet, int *testD, int *testG){
	float DistY = fabs(player->forme->posY - objet->posY);
	float MinDistY = player->forme->height/2 + objet->height/2;

	float droiteP = player->forme->posX + player->forme->width/2;
	float gaucheP = player->forme->posX - player->forme->width/2;

	float droiteO = objet->posX + objet->width/2;
	float gaucheO = objet->posX - objet->width/2;

	if(DistY<MinDistY){
		if(droiteP >= gaucheO && droiteP<droiteO) *testD = 1;
		else if(gaucheP <= droiteO && gaucheP>gaucheO) *testG = 1;
	}
}

/*----COLLISIONOBSTACLE_H_B----*/
void VerifCollision_H_B(Player *player, Rectangle *objet, int *testH, int *testB){
	float DistX = fabs(player->forme->posX - objet->posX);
	float MinDistX = player->forme->width/2 + objet->width/2;

	float hautP = player->forme->posY + player->forme->height/2;
	float basP = player->forme->posY - player->forme->height/2;

	float hautO = objet->posY + objet->height/2;
	float basO = objet->posY - objet->height/2;

	if(DistX<MinDistX){
		if(basP <= hautO && basP > basO && hautP > hautO && player->vitesseY<=0) *testB = 1;
		else if(hautP >= basO && hautP<hautO && basO > basP && player->vitesseY>0) *testH = 1;
	}
}

/*----AJUSTERPOS----*/
void AjusterPos(Player *player,Rectangle *objet, int testH, int testB, int testD, int testG){
	
	float minDX = player->forme->width/2 + objet->width/2;
	float minDY = player->forme->height/2 + objet->height/2;
	if(testB){
		player->forme->posY = objet->posY + minDY;
		player->coBas = 1;
	}
	else if(testH){
		player->forme->posY = objet->posY - minDY;
		player->vitesseY = 0;
		player->coHaut = 1;
		
	}

	if(testG){
		player->forme->posX = objet->posX + minDX;
		player->vitesseX = 0;
		player->coGauche = 1;
	}
	else if(testD){
		player->forme->posX = objet->posX - minDX;
		player->vitesseX = 0;
		player->coDroite = 1;
	}
}