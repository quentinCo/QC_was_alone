#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>

#include "Objets/Rectangle.h"

/*--------------------------------
NODE:
Structure contenant un rectangle (Rect).
----------------------------------*/
typedef struct Node{
	struct Node *after;	/* Pointeur sur la Node suivante. */
	Rectangle *obj;		/* Rectangle */
}Node;


/*----INITNODE----*/
/*--------------------------------
Initialisation une cellule contenant un rectangle.
	obj : un rectangle.
----------------------------------*/
Node *InitNode(Rectangle *obj);


/*----FREENODE----*/
/*--------------------------------
Libert la mémoire alloué.
----------------------------------*/
void freeNode(Node *node);

#endif