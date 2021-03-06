/*
 * EntidadAuxiliar.c
 *
 *  Created on: 20 nov 2021
 *      Author: GONZALO
 */

#include "EntidadAuxiliar.h"
#define ERROR_PUNTERO_NULL -1
#define OPERACION_EXITOSA 0
#define ERROR_DATO_INVALIDO -11
#define TRUE 1

static int eAuxiliar_limpiarElementosLista(LinkedList* pLinkedListAuxiliar);
static void eAuxiliar_delete(eAuxiliar* pElemento);
static eAuxiliar* eAuxiliar_new();

/**
* \brief Reserva un segmento de memoria con espacio suficiente para colocar un nuevo elemento auxiliar
* \param void -
* \return retorna un eAuxiliar* (direccion de memoria con espacio suficiente para el nuevo eAuxiliar)
*/
static eAuxiliar* eAuxiliar_new()
{
	eAuxiliar* pAuxiliar;
	pAuxiliar = (eAuxiliar*)malloc(sizeof(eAuxiliar));
	return pAuxiliar;
}

/*
* \brief Libera la memoria reservada de una direccion de memoria, obtenida con MALLOC.
* \param eAuxiliar* pElemento - direccion de memoria, a la cual se le liberara la memoria reservada
* \return VOID
* */
static void eAuxiliar_delete(eAuxiliar* pElemento)
{
	if(pElemento != NULL)
	{
		free(pElemento);
	}
}

/**
* \brief Obtiene la direccion de memoria de un nuevo Auxiliar, con su campo cargado
* \param char* pNombreJuego -  nombre del juego que se seteara en su campo
* \return retorna un eAuxiliar* (direccion de memoria disponible con espacio suficiente para el nuevo auxiliar)
* 		  retorna NULL si hubo un error.
*/
eAuxiliar* eAuxiliar_newParametrosTexto(char* pNombreJuego)
{
	eAuxiliar* pElemento = NULL;
	if(pNombreJuego != NULL)
	{
		pElemento = eAuxiliar_new();
		if(pElemento != NULL)
		{
			if(eAuxiliar_setNombreDeJuego(pElemento, pNombreJuego))
			{
				eAuxiliar_delete(pElemento);
				pElemento = NULL;
			}
		}
	}
	return pElemento;
}

/**
* \brief Setea el nombre del juego
* \param eAuxiliar* pElemento - puntero al elemento auxiliar
* \param char pNombre[] - nombre de juego que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -11 si el dato es invalido y no se puede setear
*/
int eAuxiliar_setNombreDeJuego(eAuxiliar* pElemento, char* pNombre)
{
	int lenCadena;
	char auxiliar[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;

	if(pElemento != NULL && pNombre != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pNombre, sizeof(auxiliar));
		if(lenCadena > 0)
		{
			strncpy(auxiliar, pNombre, sizeof(auxiliar));

			if(lenCadena == sizeof(auxiliar))
			{
				validar_cortarCadena(auxiliar, lenCadena);
			}

			if(validar_nombreAlfanumerico(auxiliar, sizeof(auxiliar))==TRUE)
			{
				strncpy(pElemento->juego, auxiliar, sizeof(pElemento->juego));
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene el nombre del juego
* \param eAuxiliar* pElemento - puntero al elemento auxiliar
* \param char* pNombre - puntero (direccion de memoria) donde se guardara el nombre del juego
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
int eAuxiliar_getNombreDeJuego(eAuxiliar* pElemento, char* pNombre)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pNombre != NULL)
	{
		strncpy(pNombre, pElemento->juego, LEN_NOMBRE_ALFANUMERICO);
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/** \brief Imprime los datos de un elemento
* \param void* pElemento - puntero que contiene el elemento quiere imprimir
* \return int - 1 si el puntero es NULL o hay un error. 0 si opero correctamente
*/
int eAuxiliar_imprimirFilaDeDatos(void* pElemento)
{
	char juego[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	eAuxiliar* pAuxiliar;
	if(pElemento != NULL)
	{
		pAuxiliar = (eAuxiliar*) pElemento;
		if(!eAuxiliar_getNombreDeJuego(pAuxiliar, juego))
		{
			printf("\n%s", juego);
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/*
* \brief Libera la memoria reservada en una lista
* \param LinkedList* pLinkedListAuxiliar - puntero a LinkedList de estructura auxiliar
* \return -1 si el puntero es NULL. 0 si opero correctamente.
* */
static int eAuxiliar_limpiarElementosLista(LinkedList* pLinkedListAuxiliar)
{
	int i;
	eAuxiliar* pElemento;
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListAuxiliar != NULL)
	{
		retorno = OPERACION_EXITOSA;
		for(i = 0; i < ll_len(pLinkedListAuxiliar); i++)
		{
			pElemento = (eAuxiliar*) ll_get(pLinkedListAuxiliar, i);
			eAuxiliar_delete(pElemento);
		}
	}
	return retorno;
}

/*
* \brief Libera toda la memoria reservada en una lista (elementos, nodos)
* \param LinkedList* pLinkedListAuxiliar - puntero a LinkedList
* \return -1 si el puntero es NULL. 0 si opero correctamente.
* */
int eAuxiliar_liberarListaDeMemoria(LinkedList* pLinkedListAuxiliar)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListAuxiliar != NULL)
	{
		if(!eAuxiliar_limpiarElementosLista(pLinkedListAuxiliar))
		{
			if(!ll_deleteLinkedList(pLinkedListAuxiliar))
			{
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}
