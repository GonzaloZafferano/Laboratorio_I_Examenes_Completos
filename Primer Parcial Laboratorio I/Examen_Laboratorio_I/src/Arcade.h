/*
 * Arcade.h
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#ifndef ARCADE_H_
#define ARCADE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ComprobarErrores.h"
#include "Utn_tomarDatos.h"

#define LEN_STRING 63

struct
{
	int id;
	int isEmpty;
	int idSalon;
	char nacionalidad[LEN_STRING];
	char nombreJuego[LEN_STRING];
	int tipoSonido;
	int cantidadJugadores;
	int capacidadMaximaFichas;

}typedef eArcade;

int eArcade_inicializarBanderas(eArcade lista[], int len);
int eArcade_verificarSiHayElementos(eArcade lista[], int len);
int eArcade_buscarIndiceLibre(eArcade lista[], int len);
int eArcade_encontrarElementoPorId(eArcade lista[], int len,int id);
int eArcade_eliminarElementoPorId(eArcade lista[], int len, int id);
int eArcade_eliminarElementoPorIndice(eArcade lista[], int indice);
int eArcade_imprimirIdsDisponibles(eArcade lista[], int len);
int eArcade_imprimirUnElemento(eArcade elemento);
int eArcade_imprimirTodosLosElementos(eArcade lista[], int len);
int eArcade_ordenarElementos(eArcade lista[], int len, int orden);
int eArcade_campoAModificar(eArcade* pAuxiliar, int opcion);
int eArcade_modificarElemento(eArcade* elemento, int opcion);
int eArcade_tomarDatos(eArcade lista[], int indiceLibre, int* idMaximo, int idSalon);
int eArcade_altaElemento(eArcade lista[], int indiceLibre, int id, char nacionalidad[],char nombreJuego[],int cantidadJugadores, int tipoSonido, int maximoFichas, int idSalon);
void eArcade_imprimirEncabezadoDeTabla(int opcion);
void eArcade_imprimirFilaDelElemento(eArcade elemento, int opcion);
int eArcade_forzarAltas(eArcade lista[], int len,int indice, int* idMaximo, int idSalon, char* nacionalidad, char* nombreJuego,int maximoFichas, int cantidadJugadores, int tipoSonido, int* bandera_eArcade_hayElementos);
int eArcade_convertirTipoATexto(eArcade arcade, char pTexto[], int lenTexto);
int eArcade_ContarArcadesQueContienenElJuegoEspecificado(eArcade lista[], int len, char juego[]);
int eArcade_ContarEImprimirArcadesQueContienenElJuegoEspecificado(eArcade lista[], int len, char juego[]);

#endif /* ARCADE_H_ */
