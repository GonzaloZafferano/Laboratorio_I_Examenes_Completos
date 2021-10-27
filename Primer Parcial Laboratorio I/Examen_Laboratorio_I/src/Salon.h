/*
 * Salon.h
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#ifndef SALON_H_
#define SALON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ComprobarErrores.h"
#include "Utn_tomarDatos.h"

#define TAM 51

struct
{
	int id;
	int isEmpty;
	char nombre[TAM];
	char direccion[TAM];
	int tipoSalon;
}typedef eSalon;

int eSalon_inicializarBanderas(eSalon lista[], int len);
int eSalon_verificarSiHayElementos(eSalon lista[], int len);
int eSalon_buscarIndiceLibre(eSalon lista[], int len);
int eSalon_encontrarElementoPorId(eSalon lista[], int len,int id);
int eSalon_eliminarElementoPorId(eSalon lista[], int len, int id);
int eSalon_imprimirIdsDisponibles(eSalon lista[], int len);
int eSalon_imprimirUnElementoCompleto(eSalon elemento);
int eSalon_imprimirTodosLosElementos(eSalon lista[], int len);
int eSalon_ordenarElementos(eSalon lista[], int len, int orden);
int eSalon_campoAModificar(eSalon* pAuxiliar, int opcion);
int eSalon_modificarElemento(eSalon* elemento, int opcion);
int eSalon_tomarDatos(eSalon lista[], int len, int* idMaximo);
int eSalon_altaElemento(eSalon lista[], int indiceLibre, int id, char nombre[],char direccion[], int tipoSalon);
int eSalon_eliminarElementoPorIndice(eSalon lista[], int indice);
void eSalon_imprimirEncabezadoDeTabla(int opcion);
void eSalon_imprimirFilaDelElemento(eSalon elemento, int opcion);
int eSalon_forzarAltas(eSalon lista[], int len,int indice, int* idMaximo,  char* nombre, char* direccion, int tipoSalon, int* bandera_eSalon_hayElementos, int* bandera_eArcade_hayElementos);
int eSalon_convertirTipoATexto(eSalon salon, char pTexto[], int lenTexto);

#endif /* SALON_H_ */
