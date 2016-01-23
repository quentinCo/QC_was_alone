#include "Stockage/Node.h"

/*----INITNODE----*/
Node *InitNode(Rectangle *obj){
	Node *node = (Node*)malloc(sizeof(Node));
	
	if(node == NULL){
		fprintf(stderr,"Erreur d'allocation memoire durant la creation de cellule.\n");
		exit(1);
	}
	
	node->after = NULL;
	node->obj = obj;
	
	return node;
}

/*----FREENODE----*/
void freeNode(Node *node){
	if(node){
		freeRectangle(node->obj);
		free(node);
	}
}