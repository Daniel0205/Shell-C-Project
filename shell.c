/***ARCHIVO MAIN
 * 
 * Nombre de Archivo: funcShell.h
 * integrantes:
 * -Daniel Alejandro Diaz Ocampo 1629338-3743
 * -Jem Pool Suarez Muñoz - 1630536-3743
 * 
**/

//Librerias usadas
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "funShell.h"



int main(int argc, char*argv[]) {


    while (1) {
        char comando[80];//variable que almacena la linea completa
        printf("$ ");
        scanf(" %[^\n]s", comando);
        if (!strcmp("exit", comando)) {
            break;
        }
        pid_t pid = fork();//creacion de proceso hijo
        int salidaTexto = 0,doPipe = 0;//variables "booleanas"
        FILE * fd; // archivo de salida

        if (!pid) {
            //arreglos para comando y pipe
            char * myargs[100], * pipeArray[100];
            
            asignarArgumentos(myargs, comando, &salidaTexto, &doPipe, pipeArray);
			
			if (salidaTexto){				
				if(prepararSalidaArchivo(salidaTexto,&fd,myargs))break;	
			}
			
            if (doPipe) { // Ejecucion con pipe //
                ejecutarPipe(myargs,pipeArray);
            } else { // Ejecucion sin pipe //
				ejecutarSinPipe(myargs);
            }
            cerrarArchivo(&fd,salidaTexto);
            break;//Muere el proceso hijo //
        } else {
            waitpid(pid, NULL, 0);//espera a que el proceso hijo muera
        }
    }
}
