/*
 * EntidadAuxiliar.h
 *
 *  Created on: 20 nov 2021
 *      Author: GONZALO
 */

#ifndef ENTIDADAUXILIAR_H_
#define ENTIDADAUXILIAR_H_

#include "LinkedList.h"
#include "ValidarDatos.h"

#define LEN_NOMBRE_ALFANUMERICO 64

typedef struct
{
	char juego[LEN_NOMBRE_ALFANUMERICO];
}eAuxiliar;

int eAuxiliar_getNombreDeJuego(eAuxiliar* pElemento, char* pNombre);
int eAuxiliar_setNombreDeJuego(eAuxiliar* pElemento, char* pNombre);
eAuxiliar* eAuxiliar_newParametrosTexto(char* pNombreJuego);
int eAuxiliar_imprimirFilaDeDatos(void* pElemento);
int eAuxiliar_liberarListaDeMemoria(LinkedList* pLinkedListAuxiliar);

#endif /* ENTIDADAUXILIAR_H_ */
