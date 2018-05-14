//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
//#include <fcntl.h>
#include "funShell.h"



int main(int argc, char*argv[]) {


    while (1) {
        char comando[80];
        printf("$ ");
        scanf(" %[^\n]s", comando);
        if (!strcmp("exit", comando)) {
            break;
        }
        pid_t pid = fork();
        int salidaTexto = 0,doPipe = 0;//fd;
        FILE * fd;

        if (!pid) {
            char * myargs[100], * pipeArray[100];
            asignarArgumentos(myargs, comando, &salidaTexto, &doPipe, pipeArray);

			if (salidaTexto){
				if(prepararSalidaArchivo(salidaTexto,&fd,myargs))break;	
			}
			
            if (doPipe) { // Con pipe //
                ejecutarPipe(myargs,pipeArray);
                
            } else { // Sin pipe //
				ejecutarSinPipe(myargs);
            }
            cerrarArchivo(&fd,salidaTexto);
			
            break;
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}
