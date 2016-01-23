#include "Parser/Parser.h"


/*----OPENFILE----*/
FILE *openFile(const char* pathFile){
	FILE *file = fopen(pathFile,"r");
	if(!file){
		fprintf(stderr,"ERROR OPEN FILE\n");
		exit(1);
	}
	
	return file;
}


/*----PARSERFILE----*/
Parser *parserFile(const char *pathFile){
	FILE *file = openFile(pathFile);
	
	int i;
	int j;
	int sizeTab = SIZE_PARSER;
	int sizeLine = SIZE_PARSER;
	
	Parser *newParser = (Parser*)malloc(sizeof(Parser));
	if(!newParser){
		fprintf(stderr,"ERROR MALLOC PARSER\n");
		exit(1);
	}


	newParser->tab = (char***)malloc(sizeTab*sizeof(char**));
	if(!newParser->tab){
		fprintf(stderr,"ERROR MALLOC PARSER\n");
		exit(1);
	}
	for(i = 0; i <sizeTab; i++){
		newParser->tab[i] = (char**)calloc(sizeLine,sizeof(char*));
		if(!newParser->tab[i]){
			fprintf(stderr,"ERROR CALLOC PARSER\n");
			exit(1);
		}
	}
	
	char line[1024];
	char *word;
	for(i = 0;fgets(line,1024,file); i++){
		if(i>= sizeTab-1){
			sizeTab = reallocTab(newParser, sizeTab);
				
		}
		for (j = 0, word = strtok(line, ","); word && *word; word = strtok(NULL, ",\n"), j++)
		{
			if(j >= sizeLine){
				sizeLine = reallocLine(&(newParser->tab[i]),sizeLine);
			}
			
			newParser->tab[i][j] = (char*)malloc((strlen(word)+1)*sizeof(char));
			
			if(!newParser->tab[i][j]){
				fprintf(stderr,"ERROR ALLOC CPY\n");
				exit(1);
			}
			strcpy(newParser->tab[i][j],word);
		}
		newParser->size[i+1] = j;
		sizeLine = SIZE_PARSER;
	}
	newParser->size[0] = i;
	
	fclose(file);
	
	return newParser;
}

/*----REALLOCLINE----*/
int reallocLine(char ***line, int size){
	int newSize = 2*size;
	int i;	
	char **newLine = (char**)realloc(*line,newSize*sizeof(char*));
	
	if(!newLine){
		free(line);
		fprintf(stderr,"ERROR REALLOC LINE\n");
		exit(1);
	}
	
	for(i = size; i<newSize; i++){
		newLine[i] = NULL;
	}
	
	*line = newLine;
	
	return newSize;
}

/*----REALLOCTAB----*/
int reallocTab(Parser *parser, int size){
	int newSize = 2*size;
	int i;
	char ***newTab = (char***)realloc(parser->tab,newSize*sizeof(char**));
	
	if(!newTab){
		freeParser(parser);
		fprintf(stderr,"ERROR REALLOC TAB\n");
		exit(1);
	}

	for(i = size; i <newSize; i++){
		newTab[i] = (char**)calloc(SIZE_PARSER,sizeof(char*));
		if(!newTab[i]){
			fprintf(stderr,"ERROR CALLOC REALLOC TAB\n");
			exit(1);
		}
	}
	
	parser->tab = newTab;
	
	return newSize;
}

/*----FREEPARSER----*/
void freeParser(Parser *parser){
	int i;
	int j;
	
	for(i = 0; i < parser->size[0]; i++){
		for(j = 0; j <parser->size[i+1]; j++){
			free(parser->tab[i][j]);
		}
		free(parser->tab[i]);
	}
	free(parser->tab);
	free(parser);
}
