/*
 * Auxiliar.c
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#include "Auxiliar.h"

#define PUNTERO_NULL -1
#define LEN_INVALIDO -2
#define LEN_MAXIMO 1000
#define OPERACION_EXITOSA 0
#define VACIO 1

/**
* \brief Inicializa la bandera 'IsEmpty' en 1 en todas las posiciones,
*          indicando que todas las posiciones del array estan vacias.
* \param eAuxiliar lista[] - lista que contiene los datos
* \param int len - largo del Array
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*/
int eAuxiliar_inicializarBanderas(eAuxiliar lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO)
		{
			for(i = 0; i < len; i++)
			{
				lista[i].isEmpty = VACIO;
			}
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

