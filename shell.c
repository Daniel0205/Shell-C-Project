#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void asignarArgumentos(char ** arrayArgs, char *linea){
	char * aux;
	int contador=0;
	aux= strtok (linea," ");
		
	while (aux!=NULL){
		arrayArgs[contador]=strdup(aux);
		aux= strtok (NULL," ");
		contador++;
		
	}
	arrayArgs[contador]=NULL;	
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

		if(!pid){
			char * myargs[100];                
			asignarArgumentos(myargs,comando); 
  			int aux = execvp(myargs[0],myargs); 
  			if (aux==-1)printf("Este comando no pudo ser ejecutado\n");
  			break;
  		}else{
  			wait(NULL);
  		} 	  
  	}  
  }
