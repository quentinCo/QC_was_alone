#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE_PARSER 5

/*--------------------------------
PARSER:
Structure permettant de parser, sous la forme d'un tableau à 2 dimensions de chaine de caractère, un fichier .csv.
----------------------------------*/
typedef struct Parser{
	int size[100];		/* Tableau contenant les tailles du tableau tab, et des ligne tab[i].*/
	char ***tab;		/* Tableau à 2 dimensions de chaine de caratère. */
}Parser;


/*----OPENFILE----*/
/*--------------------------------
Ouvre le fichier indiqué.
	pathFile : chemin du fichier .csv.
----------------------------------*/
FILE *openFile(const char *pathFile);


/*----PARSERFILE----*/
/*--------------------------------
Créer un objet parser et parse le fichier indiqué.
Chaque ligne du fichier correspond à une ligne de tab.
	pathFile : chemin du fichier .csv.
----------------------------------*/
Parser *parserFile(const char *pathFile);


/*----REALLOCLINE----*/
/*--------------------------------
Gestion du redimensionnement des lignes de tab, si dépassement de la taille initial.
Retourne la nouvelle taille de la ligne de tab.
	line : pointeur sur tableau de chaine de carctère.
	size : taille actuel de la ligne.
----------------------------------*/
int reallocLine(char ***line, int size);


/*----REALLOCTAB----*/
/*--------------------------------
Gestion du redimensionnement de tab, si dépassement de la taille initial (nombre de ligne).
Retourne la nouvelle taille de tab.
	parser : le parser
	size : taille actuel de tab.
----------------------------------*/
int reallocTab(Parser *parser, int size);


/*----FREEPARSER----*/
/*--------------------------------
Libert la mémoire alloué.
----------------------------------*/
void freeParser(Parser *parser);
#endif