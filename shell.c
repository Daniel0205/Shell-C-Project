#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "funShell.h"



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
