/*
 * Auxiliar.h
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#ifndef AUXILIAR_H_
#define AUXILIAR_H_

#include <stdio.h>
#include <stdlib.h>

#define LEN_STRING_JUEGO 63

typedef struct
{
	char juego[LEN_STRING_JUEGO];
	int isEmpty;

}eAuxiliar;

int eAuxiliar_inicializarBanderas(eAuxiliar lista[], int len);

#endif /* AUXILIAR_H_ */
