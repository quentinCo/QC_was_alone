#include "Stockage/List.h"

/*----INITLIST----*/
List *InitList(){
	List *list = (List*)malloc(sizeof(List));
	if(list == NULL){
		fprintf(stderr,"Erreur d'allocation memoire durant la creation de liste.\n");
		exit(1);
	}
	
	list->tete = NULL;
	list->queue = NULL;
	list->size = 0;
	
	return list;
}

/*----PUTNODE----*/
void PutNode(List *list,Rectangle *obj){
	Node *node = InitNode(obj);

	if(list->size == 0){
		list->tete = node;
	}
	else{
		Node *temp = list->queue;
		temp->after = node;
	}
	list->queue = node;
	
	list->size++;
}

/*----FREELIST----*/
void freeList(List *list){
	if(list){
		Node *temp;
		Node *sup;
		if(list->size>0){
			sup = list->tete;
			while(list->size && sup){
				temp = sup->after;
				freeNode(sup);
				sup = temp;
				list->size--;
			}
		}
		free(list);
	}
}