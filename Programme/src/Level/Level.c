#include "Level/Level.h"

/*----INITLEVEL----*/
Level *initLevel(char *pathFile, float unitX, float unitY){
	Level *new = (Level*)malloc(sizeof(Level));
	if(!new){
		fprintf(stderr,"Erreur Allocation Level.\n");
		exit(1);
	}

	new->listObstacle = InitList();
	
	new->numPlayer = 0;
	
	lectureParse(pathFile, new);
		
	initCamera(&(new->camera), new->playerTab[0]->forme->posX, new->playerTab[0]->forme->posY);

	
	new->background = initTexture("data/textures/back-B.png",3, 1, 1, 1, unitX, unitY);
	new->rotation = 0;
	new->endText = initTexture("data/textures/fin.png", 2, 1, 2, 2, unitX, unitY);
	
	new->end = 0;
	
	return new;
}

/*----LECTUREPARSE----*/
void lectureParse(char *pathFile, Level *level){
	Parser *parser = parserFile(pathFile);
	int i,k;
	k = 0;
	
	char *temp;
	
	for(i = 0; i < 3; i++) level->playerTab[i] = NULL;
	
	for(i = 0; i < parser->size[0];i++){
		temp = parser->tab[i][0];
		if(!strcmp(temp,"Niveau")){
			level->width = atoi(parser->tab[i][1]);
			level->height = atoi(parser->tab[i][2]);
		}
		else if(!strcmp(temp,"Rectangle") || !strcmp(temp,"Player")){
			int j;
			float value[parser->size[i+1]];
			
			for(j = 0; j < parser->size[i+1]-1; j++) value[j] = atof(parser->tab[i][j+1]);
			
			if(!strcmp(temp,"Rectangle")){
				PutNode(level->listObstacle, CreateRectangle(value));
			}
			else if(!strcmp(temp,"Player") && k<3){
				level->playerTab[k] = CreatePlayer(value);
				k++;
				level->numPlayer = k;				
			}
		}
	}
	
	freeParser(parser);
}

/*----DESSINLEVEL----*/
void dessinLevel(Level *level, Player *player, int scaleX, int scaleY){
	int i;
	int filled = 1;

	glPushMatrix();
		glRotatef(level->rotation,0,0,1);
		dessinTexture(level->background, 0, 0);
	glPopMatrix();
	
	level->rotation += 0.025;
	
	depCamera(&(level->camera),player,level->width,level->height,scaleX,scaleY);
	gluLookAt(level->camera.posX, level->camera.posY,0,level->camera.posX,level->camera.posY,-1,0,1,0);

	glLineWidth(2);
	for(i = 0; i<level->numPlayer; i++){
		filled = 1;
		if(level->playerTab[i] && level->playerTab[i] != player){
			if(level->playerTab[i]->arrValide) filled = 0;
			dessinPlayer(level->playerTab[i],filled,255, 50, 30);
		}
	}
	filled = 1;
	
	if(player->arrValide) filled = 0;
	
	dessinPlayer(player,filled,255, 135, 30);
	
	dessinObstacles(level->listObstacle,200,200,200);
	
	if(level->end) dessinTexture(level->endText, level->camera.posX, level->camera.posY);

}

/*----DESSINOBSTACLE----*/
void dessinObstacles(List *list, int r, int v, int b){
	Node *temp = list->tete;
	
	int i;
	
	for(i=0; temp; i++){
		dessinRect(temp->obj, 1, r, v, b);
		temp = temp->after;
	}
}

/*----COLLISION----*/
void Collision(Level *level){
	int i;
	
	for(i = 0; i<level->numPlayer; i++){
		if(level->playerTab[i]){
			CollisionObstacle(level->playerTab[i], level->listObstacle);
			CollisionPlayer(level->playerTab[i], level->playerTab, level->numPlayer);
		}
	}
}

/*----VERIFVICTOIRE----*/
void verifVictoire(Level *level){
	int i;
	level->end = 1;
	
	for(i = 0; i<level->numPlayer && level->end; i++){
		level->end = level->playerTab[i]->arrValide;
	}
}

/*----FREELEVEL----*/
void freeLevel(Level *level){
	if(level){
		int i;
		
		freeTexture(level->background);
		freeTexture(level->endText);
		
		freeList(level->listObstacle);
		for(i = 0; i<level->numPlayer; i++) freePlayer(level->playerTab[i]);	
		free(level);
	}
}