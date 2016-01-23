#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

/*--------------------------------
LIST:
Structure de stockage de rectangle.
----------------------------------*/
typedef struct List{
	Node *tete;		/* Première cellule de la liste.*/
	Node *queue;		/* Dernière cellule de la liste.*/
	int size;		/* Taille de la liste.*/
}List;


/*----INITLIST----*/
/*--------------------------------
Initialisation d'une liste vide.
----------------------------------*/
List *InitList();


/*----PUTNODE----*/
/*--------------------------------
Ajout dans rectangle dans la liste.
	list : liste où ajouter.
	obj : rectangle à ajouter.
----------------------------------*/
void PutNode(List *list,Rectangle *obj);


/*----FREELIST----*/
/*--------------------------------
Libert la mémoire alloué.
----------------------------------*/
void freeList(List *list);

#endif