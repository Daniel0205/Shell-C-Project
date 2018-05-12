#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void asignarArgumentos(char ** arrayArgs, char *linea,int *text){
	char * aux;
	int contador=0;
	aux= strtok (linea," ");
		
	while (aux!=NULL){
		arrayArgs[contador]=strdup(aux);
		aux= strtok (NULL," ");
		contador++;
		if(aux==NULL)break;
		if (!strcmp(">", aux)){
			*text=contador+2;
			arrayArgs[contador]=NULL;
			contador++;
		}
	}
	arrayArgs[contador]=NULL;	
}

void prepararSalidaArchivo(int posicion,int* archivo,char ** args){
	
	if (posicion){
		close(STDOUT_FILENO);
		char *filename=args[posicion];
		*archivo=open(filename,O_CREAT|O_WRONLY|O_TRUNC|S_IRWXU);		
		
	}
}

