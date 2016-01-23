#ifndef COLLISION_H_
#define COLLISION_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Objets/Player.h"
#include "Stockage/List.h"
/*--------------------------------
Regroupement de fonction permettant la gestion des collisions entre Player et Objet (Rectangle)
et entre Player.
----------------------------------*/


/*----COLLISIONOBSTACLE----*/
/*--------------------------------
Verifie la collision entre un joueur et les objets d'un niveau. 
		player : Un joueur.
		list : Liste des différents obstacle présent dans le niveau.
----------------------------------*/
void CollisionObstacle(Player *player,List *list);


/*----COLLISIONPLAYER----*/
/*--------------------------------
Verifie la collision entre joueurs. 
		player : Un joueur.
		playerTab : Tableau contenant l'ensemble des joueurs du niveau.
----------------------------------*/
void CollisionPlayer(Player *player, Player **playerTab, int size);


/*----INITCOLLISION----*/
/*--------------------------------
Réinisialise toute les collisions d'un joueur à O (pas de collision).
	player : Un joueur.
----------------------------------*/
void InitCollision(Player *player);


/*----VERIFCOLLISION----*/
/*--------------------------------
Verifie la collision entre un joueur et un objet. 
		player : Un joueur.
		objet : Un objet du niveau.
----------------------------------*/
void VerifCollision(Player *player, Rectangle *objet);


/*----COLLISIONOBSTACLE_G_D----*/
/*--------------------------------
Verifie la collision gauche-droite entre un joueur et un objet. 
		player : Un joueur.
		objet : Un objet du niveau.
		testD : Un booléen pour la collision droite du joueur.
		testG : Un booléen pour la collision gauche du joueur.
----------------------------------*/
void VerifCollision_G_D(Player *player, Rectangle *objet, int *testD, int *testG);


/*----COLLISIONOBSTACLE_H_B----*/
/*--------------------------------
Verifie la collision haut-bas entre un joueur et un objet. 
		player : Un joueur.
		objet : Un objet du niveau.
		testH : Un booléen pour la collision haute du joueur.
		testB : Un booléen pour la collision basse du joueur.
----------------------------------*/
void VerifCollision_H_B(Player *player, Rectangle *objet, int *testH, int *testB);


/*----AJUSTERPOS----*/
/*--------------------------------
Ajuste la position du joueur selon les collisions avec un objet.
		player : Un joueur.
		objet : Un objet du niveau.
		testH : Un booléen pour la collision haute du joueur.
		testB : Un booléen pour la collision basse du joueur.
		testD : Un booléen pour la collision droite du joueur.
		testG : Un booléen pour la collision gauche du joueur.
----------------------------------*/
void AjusterPos(Player *player,Rectangle *objet, int testH, int testB, int testD, int testG);


#endif