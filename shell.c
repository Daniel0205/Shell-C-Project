#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

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

int main(int argc, char*argv[]) {

	while(1) {
		char comando[80];
		printf("$ ");
		scanf(" %[^\n]s",comando);
		if(!strcmp("exit", comando)){
			break;
		}		
		pid_t pid = fork();
		int salidaTexto=0;
		int fd;

		if(!pid){
			char * myargs[100];                
			asignarArgumentos(myargs,comando,&salidaTexto);
			//prepararSalidaArchivo(salidaTexto,&fd,myargs);			
				
			if (salidaTexto){	
				printf(". ");		
				close(STDOUT_FILENO);
				char *filename=myargs[salidaTexto];
				fd=open(filename,O_CREAT|O_WRONLY|O_TRUNC|S_IRWXU|S_IXOTH);		
			}
  			int aux = execvp(myargs[0],myargs); 
  			if (aux==-1)printf("Este comando no pudo ser ejecutado\n");
  			if (salidaTexto) close(fd);
  			if (fd<0){
				printf("%d  error!",fd);
				
			}
  			printf("%d  error!",fd);
				
  			break;
  		}else{
  			wait(NULL);
  		} 	  
  	}  
  }
