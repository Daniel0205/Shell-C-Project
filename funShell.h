/***ARCHIVO CABECERA  DE LIBRERIA
 * 
 * Nombre de Archivo: funcShell.h
 * integrantes:
 * -Daniel Alejandro Diaz Ocampo 1629338-3743
 * -Jem Pool Suarez Muñoz - 1630536-3743
 * 
**/

#ifndef __SHELL__
#define __SHELL__

#include <stdio.h>
//declaracion de funciones
void asignarArgumentos(char ** arrayArgs, char *linea, int *text, int *doPipe, char ** pipeArray);
void ejecutarPrimerPipe(FILE * swap,char ** myargs);
void ponerNull(char **pipeArray);
void ejecutarSegundoPipe(char * buf,char ** pipeArray,int * p);
void ejecutarPipe(char ** myargs, char ** pipeArray);
void ejecutarSinPipe(char ** myargs);
void cerrarArchivo(FILE ** fd,int salidaTexto);
int prepararSalidaArchivo(int posicion,FILE ** fd, char ** args);
#endif
