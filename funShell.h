#ifndef __SHELL__
#define __SHELL__

#include <stdio.h>
void asignarArgumentos(char ** arrayArgs, char *linea, int *text, int *doPipe, char ** pipeArray);
void ejecutarPipe(char ** myargs, char ** pipeArray);
void ejecutarSinPipe(char ** myargs);
void cerrarArchivo(FILE ** fd,int salidaTexto);
int prepararSalidaArchivo(int posicion,FILE ** fd, char ** args);
#endif
