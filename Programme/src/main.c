#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Level/Level.h"
#include "Objets/Texture.h"

#define M_PI 3.14159265358979323846
#define BIT_PER_PIXEL 32



void reshape(int winWidth, int winHeight, float scaleX, float scaleY) {
	glViewport(0, 0, winWidth, winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-scaleX/2, scaleX/2, -scaleY/2, scaleY/2);
}


void setVideoMode(int winWidth, int winHeight, float scaleX, float scaleY) {
	if(NULL == SDL_SetVideoMode(winWidth, winHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}

	reshape(winWidth,winHeight,scaleX,scaleY);
}

int verifButton(float posXE, float posYE, Texture *button){
	float demiH = button->height/2;
	float demiW = button->width/2;
	
	int conditionY =  posYE <= button->posY + demiH && posYE >= button->posY - demiH;
	int conditionX = posXE <= button->posX + demiW && posXE >= button->posX - demiW;
	
	return conditionY && conditionX;
}

int main(int argc, char** argv) {
	const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
	unsigned int windowWidth  = 800;
	unsigned int windowHeight = 800;
	float scaleX = 20;
	float scaleY = 20;
	
	float unitX = windowWidth/scaleX;
	float unitY = windowHeight/scaleY;
	
	Texture *control;
	Texture *playButton;
	Texture *playButtonInit;
	Texture *playButtonDown;
	Texture *playButtonOver;
	int click = 0;
	int jeu = 0;
	
	Level *level;
	Player *player;
	int numPlayer = 0;
	int i;

	GLuint liste_dessin = glGenLists(10);	
	if(liste_dessin){
		fprintf(stderr,"Erreur dans la creation de la liste\n");
		exit(1);
	}

	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		exit(1);
	}

	setVideoMode(windowWidth, windowHeight,scaleX,scaleY);

	/*----Initialisation de l'API Mixer----*/
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		fprintf(stderr,"%s", Mix_GetError());
		exit(1);
	}
	/* ****** */
	
	SDL_WM_SetCaption("QC was alone", NULL);

	int loop = 1;
	
	/*----INIT PAGE D'ACCUEIL----*/
	control = initTexture("data/textures/controle-O.png",3, 1, 0.6, 0.6, unitX, unitY);
	playButtonInit = initTexture("data/textures/play-CB.png",4, 1, 1, 1, unitX, unitY);
	playButtonOver = initTexture("data/textures/play-CO.png",5, 1, 1, 1, unitX, unitY);
	playButtonDown = initTexture("data/textures/play-FO.png",5, 1, 1, 1, unitX, unitY);
	playButton = playButtonInit;
	
	/*----INIT LEVEL----*/	
	level = initLevel("data/niveaux/niveau_1.csv", unitX, unitY);
	if(!level->playerTab[0]){
		fprintf(stderr,"AUCUN PLAYER CREE.\n");
		exit(1);
	}
	
	player = level->playerTab[numPlayer];
	/* ****** */
	
	/*----LECTURE MUSIQUE----*/
	Mix_Music *musique;
	musique = Mix_LoadMUS("data/sons/Funambule1.mp3");
	Mix_PlayMusic(musique,-1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);		/* de 0 à 128 */
	/* ****** */
	
	

	while(loop) {
		/*----TEMPS DEB BOUCLE---*/
		Uint32 startTime = SDL_GetTicks();

		/*----DEB DESSIN----*/
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1,1,1,1);        
		
		glPointSize(4);
		glEnable(GL_LINE_SMOOTH);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		if(jeu)dessinLevel(level, player, scaleX, scaleY);
		else{
			dessinTexture(control, 0, 3);
			dessinTexture(playButton, 0, -5);
		}
		
		glColor3ub(0, 0, 0); 
		/***********/
		
		SDL_GL_SwapBuffers();
		/* ****** */

		/*----GESTION EVENT ET SAUT----*/
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				loop = 0;
				break;
			}
			switch(e.type) { 
				case SDL_MOUSEBUTTONUP:
					if(e.button.button==SDL_BUTTON_LEFT && !jeu && click ){	
						float posXE = e.button.x / unitX - scaleX/2;
						float posYE = -(e.button.y / unitY - scaleY/2);
						int overButton = verifButton(posXE, posYE, playButton);
						
						if(overButton){
							freeTexture(playButtonDown);
							freeTexture(playButtonInit);
							freeTexture(playButtonOver);
							jeu = 1;
						}
						else click = 0;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(e.button.button==SDL_BUTTON_LEFT && !jeu && !click ){
						float posXE = e.button.x / unitX - scaleX/2;
						float posYE = -(e.button.y / unitY - scaleY/2);
						int overButton = verifButton(posXE, posYE, playButton);
						
						if(overButton){
							playButton = playButtonDown;
							click = 1;
						}
					}
					break;
				 case SDL_MOUSEMOTION:
					if(!jeu && !click ){
						float posXE = e.motion.x / unitX - scaleX/2;
						float posYE = -(e.motion.y / unitY - scaleY/2);
						int overButton = verifButton(posXE, posYE, playButton);
						
						if(overButton) playButton = playButtonOver;
						else playButton = playButtonInit;
					}
                       			break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym){
						case 'q' : 
						case SDLK_ESCAPE : 
							loop = 0;
							break;
						case SDLK_UP:
							if(jeu && !player->jump && !player->chute && !level->end) Jump(player);
							break;
						case SDLK_SPACE:
							if(jeu && !level->end){
								numPlayer++;
								numPlayer = numPlayer % level->numPlayer;
								player = level->playerTab[numPlayer];
							}
							break;
						default : break;
				}
				break;

				default:
				break;
			}
		}
		/* ****** */
		if(jeu){
			/*----GESTION DEPLACEMENT X----*/
			if(!level->end){
				Uint8 *keystate = SDL_GetKeyState(NULL);
				if ( keystate[SDLK_RIGHT]) deplacementX(player,1,-level->width/2,level->width/2);
				else if ( keystate[SDLK_LEFT]) deplacementX(player,-1,-level->width/2,level->width/2);
				else player->move = 0;
			}
			/* ****** */

			/*----GESTION GRAVITE ET POSITION SAUT----*/
			for(i = 0; i<level->numPlayer; i++)gravite(level->playerTab[i], level->height/2, -level->height/2);
			
			/* ****** */
		
			/*----VERIF DES COLLISION----*/
			Collision(level);
			/* ****** */
		
			/*----VERIF FIN NIVEAU----*/
			verifVictoire(level);
			/* ****** */
		}
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if(elapsedTime < FRAMERATE_MILLISECONDS) {
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
	}

	freeLevel(level);
	
	/*----LIBERATION DE LA MEMOIRE ALLOUE A LA MUSIQUE----*/
	Mix_FreeMusic(musique);
	Mix_CloseAudio();
	/* ***** */
	
	SDL_Quit();

	return EXIT_SUCCESS;
}
