#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void asignarArgumentos(char ** arrayArgs, char *linea, int *text, int *doPipe, char ** pipeArray) {
    char * aux;
    int contador = 0, contador2 = 0;
    aux = strtok(linea, " ");
	
    while (aux != NULL) {
        arrayArgs[contador] = strdup(aux);
        aux = strtok(NULL, " ");
        contador++;
        if (aux == NULL)break;
		
        if (!strcmp("|", aux)) {
            *doPipe = 1;
            contador2 = -1;
            while (aux != NULL ) {
                pipeArray[contador2] = strdup(aux);
                aux = strtok(NULL, " ");
                contador2++;
                
                if (aux == NULL || !strcmp(">", aux))break;
                if (!strcmp("|", aux)){
					pipeArray[contador2]=NULL;
					aux = strtok(NULL, " ");
					contador2++;
				}
				
            }
            
            pipeArray[contador2] = NULL;
			
        }
        
        if (aux == NULL)break;
        if (!strcmp(">", aux)) {
			
            *text = contador + 2;
            arrayArgs[contador] = NULL;
            contador++;
        }
    }

    arrayArgs[contador] = NULL;
}




void ejecutarPipe(char ** myargs, char ** pipeArray){
	char buf[512];
    int p[2]; 
    FILE *swap;
	
	if (pipe(p) < 0)   exit(1);
	pid_t frk1 = fork();
	if (frk1 == 0) {
		swap = freopen(" ", "w+", stdout);
		int aux = execvp(myargs[0], myargs);
		fclose(swap);
		if (aux == -1)printf("Este comando no pudo ser ejecutado 1 \n");
	} else {
			waitpid(frk1, NULL, 0);
			pid_t frk2 = fork();
			if (frk2 < 0) {
				fprintf(stderr, "fallo fork 2\n");
				exit(1);
			} else if (frk2 == 0) {
				int i = 0;
				while (1) {
					if (pipeArray[i] == NULL) {
						pipeArray[i] = " ";
						pipeArray[i + 1] = NULL;
						break;
					}
					i++;
				}
                    execvp(pipeArray[0], pipeArray);
                    close(p[1]);
                    read(p[0], buf, 512);
                    printf("%s\n", buf);
                    } else {
                        wait(NULL);
                    }
        }

}


void ejecutarSinPipe(char ** myargs){
	
	int aux = execvp(myargs[0], myargs);
	if (aux == -1)printf("Este comando no pudo ser ejecutado-2\n");

	
}

void cerrarArchivo(FILE ** fd,int salidaTexto){
	if (salidaTexto) fclose(*fd);
   /* if (fd < 0) {
		printf("%d  error!", *fd);
	}*/
	
}


int prepararSalidaArchivo(int posicion,FILE ** fd, char ** args) {
	
	FILE * fparchivo= fopen (args[posicion], "r"); 	
	if(fparchivo != NULL){
		printf("Error! el nombre del archivo ya exite\n");
		return 1;
	}
	else {
		*fd = freopen(args[posicion], "w+", stdout);
		return 0;
	}
	
}
