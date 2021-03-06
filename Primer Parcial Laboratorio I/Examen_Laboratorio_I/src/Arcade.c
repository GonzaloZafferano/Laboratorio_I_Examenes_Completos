/*
 * Arcade.c
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#include "Arcade.h"

#define VACIO 1
#define OCUPADO 0
#define ORDENADO 1
#define DESORDENADO 0
#define ORDEN_ASCENDENTE 1
#define LEN_TEXTO 15
#define LEN_MAXIMO_ARCADE 1000
#define MINIMO_JUGADORES 1
#define MAXIMO_JUGADORES 6
#define MINIMO_FICHAS 1
#define MAXIMO_FICHAS 10000
#define MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO 1
#define MOSTRAR_ID_DISPONIBLES 2
#define REINTENTOS 2
#define HAY_ELEMENTOS 1
#define OPERACION_EXITOSA 0
#define NO_HAY_ELEMENTOS 0
#define PUNTERO_NULL -1
#define LEN_INVALIDO -2
#define ID_INVALIDO -11
#define NO_HAY_ELEMENTOS_CARGADOS_CON_ESE_ID -18
#define PARAMETRO_I_NO_ES_DISTINTO_DE_J -13
#define NO_SE_CARGARON_TODOS_LOS_CAMPOS -14
#define NO_SE_APLICARON_CAMBIOS_SOBRE_EL_ELEMENTO -15
#define INDICE_FUERA_DE_RANGO -17
#define NO_SE_APLICARON_BAJAS -19
#define NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID_INDICADO -20
#define ARRAY_COMPLETO -21
#define I_O_J_ESTA_FUERA_DE_RANGO -23
#define NO_SE_CARGO_NINGUN_ALTA -25
#define ELEMENTO_VACIO -26
#define LEN_STRING_JUEGO 63
#define MONO 1
#define ESTEREO 2
#define HAY_ELEMENTOS_EARCADE 3

static int eArcade_generadorDeIds(void);
static int eArcade_swapElementos(eArcade lista[], int i, int j);

/**
 * \brief Imprime los encabezados de la tabla de datos.
* \param int opcion - Indica el encabezado que se quiere imprimir
* \param VOID -
* \return VOID
*/
void eArcade_imprimirEncabezadoDeTabla(int opcion)
{
	switch(opcion)
	{
		case 1:
			printf("\n%5s  %-25s   %-30s %21s  %14s  %11s  %8s", "Id", "Nacionalidad", "Nombre del Juego", "Cantidad de Jugadores", "Tipo de sonido", "Max. fichas", "Id Salon");
			break;
		case 2:
			printf("\n%5s  %-25s   %-30s", "Id", "Nacionalidad", "Nombre del Juego");
			break;
		case 3:
			printf("\n%5s  %12s   %29s %35s  %14s  %11s  %8s","-" ,"-" ,"-","-","-", "-", "-");
			break;
		case 4:
			printf("\n%5s  %12s   %29s", "-", "-", "-");
			break;
	}
}

/** \brief Imprime los datos de un elemento, el cual ya fue validado previamente.
* \param eArcade elemento - Elemento cuyos datos se quieren imprimir
* \param int opcion - Indica la informacion que se quiere imprimir del elemento
* \return VOID
*/
void eArcade_imprimirFilaDelElemento(eArcade elemento, int opcion)
{
	char mensaje[LEN_TEXTO];

	if(eArcade_convertirTipoATexto(elemento, mensaje, LEN_TEXTO)==0)
	{
		switch(opcion)
		{
			case 1:
				printf("\n%5d  %-25.25s   %-30.30s %21d  %-10s  %15d  %8d", elemento.id, elemento.nacionalidad, elemento.nombreJuego, elemento.cantidadJugadores, mensaje, elemento.capacidadMaximaFichas, elemento.idSalon);
				break;
			case 2:
				printf("\n%5d  %-25.25s   %-63.63s", elemento.id, elemento.nacionalidad, elemento.nombreJuego);
				break;
		}
	}
}

/** \brief Escribe en un array de char el texto que representa al tipo numerico de sonido del arcade.
* \param eArcade arcade - Elemento de tipo salon
* \param char pTexto[] - array de chars donde se escribira la representacion Textual del tipo numerico
* \param int lenTexto - largo del array de char
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*         retorna -26 si el arcade recibido esta marcado como vacio
*/
int eArcade_convertirTipoATexto(eArcade arcade, char pTexto[], int lenTexto)
{
	int retorno = PUNTERO_NULL;
	if(pTexto != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenTexto > 0 && lenTexto <= LEN_TEXTO)
		{
			retorno = ELEMENTO_VACIO;
			if(arcade.isEmpty == OCUPADO)
			{
				switch(arcade.tipoSonido)
				{
					case MONO:
						strncpy(pTexto,"Mono", lenTexto);
						break;
					case ESTEREO:
						strncpy(pTexto,"Estereo", lenTexto);
						break;
				}
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Genera un ID unico, que es acumulativo.
* \param VOID -
* \return retorna INT. Un entero positivo que es el ID unico generado
*/
static int eArcade_generadorDeIds(void)
{
	static int id = 0;
	id++;
	return id;
}

/**
* \brief Inicializa la bandera 'IsEmpty' en 1 en todas las posiciones,
*          indicando que todas las posiciones del array estan vacias.
* \param eArcade lista[] - lista que contiene los datos
* \param int len - largo del Array
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*/
int eArcade_inicializarBanderas(eArcade lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_ARCADE)
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

/*
* \brief Evalua si hay elementos en la lista (ante una eliminacion o falta de carga).
* \param eArcade lista[] - lista que contiene los datos
* \param int len - largo del Array
* \return Retorna INT. 1 si hay elementos.
* 		  Retorna  0 Si no hay elementos.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int eArcade_verificarSiHayElementos(eArcade lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = NO_HAY_ELEMENTOS;
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					retorno = HAY_ELEMENTOS;
					break;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Busca un indice libre dentro de un array, basandose en la bandera isEmpty.
* \param eArcade lista[] - lista que contiene los datos
* \param int len - largo del array
* \return Retorna INT. 0 o un numero positivo, que es el indice libre encontrado
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*          retorno -21 si todos los espacios estan ocupados.
*/
int eArcade_buscarIndiceLibre(eArcade lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0  && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = ARRAY_COMPLETO;
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == VACIO)
				{
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Encuentra un elemento por su Id, y retorna el indice del array donde se encuentra.
* \param eArcade lista[] - lista que contiene los datos
* \param int len - largo del array
* \param int Id - Id del elementos que se desea encontrar
* \return Retorna INT. Retorna el indice del elemento, si lo encuentra
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  Retorna -11 si el ID es invalido (fuera de rango)
* 		  retorna -18 si el Id es valido, pero no tiene ningun elemento cargado (fue dado de baja).
*/
int eArcade_encontrarElementoPorId(eArcade lista[], int len,int id)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = ID_INVALIDO;
			if(id >0)
			{
				retorno = NO_HAY_ELEMENTOS_CARGADOS_CON_ESE_ID;
				for(i = 0; i< len ; i++)
				{
					if(lista[i].id == id && lista[i].isEmpty == OCUPADO)
					{
						retorno = i;
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Elimina a un elemento por su Indice (se setea la bandera "isEmpty" en 1)
* \param eArcade lista[] - Lista que contiene datos
* \param int indice - Indice del elemento que se eliminara
* \return Retorna INT. Retorna 0 si la eliminacion fue exitosa.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  Retorna -11 si el ID es invalido
* 		  retorna -19 si no se aplicaron bajas en el sistema (porque el Indice no existe o ya esta de baja).
*/
int eArcade_eliminarElementoPorIndice(eArcade lista[], int indice)
{
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = ID_INVALIDO;
		if(indice >= 0 && indice < LEN_MAXIMO_ARCADE)
		{
			retorno = NO_SE_APLICARON_BAJAS;
			if(lista[indice].isEmpty == OCUPADO)
			{
				lista[indice].isEmpty = VACIO;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Elimina a un elemento por su Id (se setea la bandera "isEmpty" en 1)
* \param eArcade lista[] - Lista que contiene datos
* \param int len - largo del array
* \param int id - Id del elemento que se eliminara
* \return Retorna INT. Retorna 0 si la eliminacion fue exitosa.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  Retorna -11 si el ID es invalido
* 		  retorna -19 si no se aplicaron bajas en el sistema (porque el ID no existe o ya esta de baja).
*/
int eArcade_eliminarElementoPorId(eArcade lista[], int len, int id)
{
	int indiceRecibido;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = ID_INVALIDO;
			if(id > 0)
			{
				retorno = NO_SE_APLICARON_BAJAS;
				indiceRecibido = eArcade_encontrarElementoPorId(lista, len, id);
				if(utn_comprobarEstadoDeOperacion(indiceRecibido))
				{
					lista[indiceRecibido].isEmpty = VACIO;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Imprime los ID de una lista recibida
* \param eArcade lista[] - lista que contiene datos
* \param int len - largo del array
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int eArcade_imprimirIdsDisponibles(eArcade lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista!= NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = OPERACION_EXITOSA;
			printf("\n\t\t<--Lista de arcades disponibles-->");
			eArcade_imprimirEncabezadoDeTabla(MOSTRAR_ID_DISPONIBLES);
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					eArcade_imprimirFilaDelElemento(lista[i], MOSTRAR_ID_DISPONIBLES);
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Imprime el contenido de un solo elemento recibido por parametro
* \param eArcade elemento - elemento para imprimir
* \return INT. 0 Si pudo operar correctamente
* 			 -20 si el elemento esta vacio o de baja.
*/
int eArcade_imprimirUnElemento(eArcade elemento)
{
	int retorno = NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID_INDICADO;

	if(elemento.isEmpty == OCUPADO)
	{
		printf("\n\t\t<--Datos asociados al juego '%s' de ID < %d >-->", elemento.nombreJuego, elemento.id);
		eArcade_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
		eArcade_imprimirFilaDelElemento(elemento, MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief Imprime los datos de todos los elementos que esten habilitados de un array.
* \param eArcade lista[] - lista de elementos
* \param int len - largo del array
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int eArcade_imprimirTodosLosElementos(eArcade lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = OPERACION_EXITOSA;

			printf("\n\t\t<--Mostrando lista de los Arcades-->");
			eArcade_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					eArcade_imprimirFilaDelElemento(lista[i], MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Ordena los elementos del array segun el criterio recibido (ascendente o descendente)
* \param eArcade lista[] - Lista de elementos
* \param int len - largo del array
* \param int orden - [1] Orden Ascendente - [0] orden Descendente
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int eArcade_ordenarElementos(eArcade lista[], int len, int orden)
{
	int retornoCadena;
	int banderaOrdenado;
	int i = 0;
	int limite = len;
	int retorno = PUNTERO_NULL;
	int largoCadena = LEN_STRING_JUEGO;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = OPERACION_EXITOSA;
			do
			{
				banderaOrdenado = ORDENADO; //Asumimos que esta todo ordenado
				limite = limite - 1; //VOY REDUCIENDO EL LIMITE EN CADA VUELTA, asi no toma la ultima posicion que YA TIENE EL MAYOR O MENOR

				for(i = 0; i < limite; i++)
				{
					retornoCadena = strncmp(lista[i].nombreJuego, lista[i+1].nombreJuego, largoCadena);

					if(orden == ORDEN_ASCENDENTE)
					{
						if((retornoCadena > 0) || (retornoCadena == 0 && (lista[i].tipoSonido > lista[i+1].tipoSonido)))
						{
							banderaOrdenado = eArcade_swapElementos(lista, i, i+1);//Si el swap opera, quiere decir que esta desordenado
							utn_comprobarEstadoDeOperacion(banderaOrdenado);
						}
					}
					else
					{
						if((retornoCadena < 0) || (retornoCadena == 0 && (lista[i].tipoSonido < lista[i+1].tipoSonido)))
						{
							banderaOrdenado = eArcade_swapElementos(lista, i, i+1);//Si el swap opera, quiere decir que esta desordenado
							utn_comprobarEstadoDeOperacion(banderaOrdenado);
						}
					}
				}
			}while(banderaOrdenado == DESORDENADO);
		}
	}
	return retorno;
}

/**
* \brief Cambia la posicion de 2 elementos
* \param eArcade lista[] - Lista de elementos
* \param int i - Indice en el array, del elemento A
* \param int i - Indice en el array, del elemento B
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -13 si el parametro i no es distinto del parametro j.
* 			  -23 si el indice de i o j estan fuera del rango.
*/
static int eArcade_swapElementos(eArcade lista[], int i, int j)
{
	int retorno = PUNTERO_NULL;
	eArcade auxiliar;

	if(lista != NULL)
	{
		retorno = I_O_J_ESTA_FUERA_DE_RANGO;
		if((i >= 0 && i < LEN_MAXIMO_ARCADE) && (j >= 0 && j < LEN_MAXIMO_ARCADE))// i y j son indices, por eso van de 0 a < maximo
		{
			retorno = PARAMETRO_I_NO_ES_DISTINTO_DE_J;
			if(i != j)
			{
				auxiliar = lista[i];
				lista[i] = lista[j];
				lista[j] = auxiliar;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/*
* \brief Obtiene el nuevo dato que se le quiere otorgar a un determinado campo, el cual es indicado con el parametro.
* \param eArcade* pAuxiliar - auxiliar donde se cargara el dato
* \param int opcion - opcion que indica el dato que se tomara
* \return Retorna INT. 0 Si se opero correctamente,
*         retorna -14 si no se pudieron tomar los datos correctamente.
*/
int eArcade_campoAModificar(eArcade* pAuxiliar, int opcion)
{
	int estadoOperacion;
	int retorno = NO_SE_CARGARON_TODOS_LOS_CAMPOS;
	switch(opcion)
	{
		case 1:
			estadoOperacion = utn_getNombreAlfanumerico(pAuxiliar->nombreJuego, LEN_STRING_JUEGO, "\nA continuacion, ingrese el nuevo nombre del juego", "Error. Dato invalido!", REINTENTOS);
			break;
		case 2:
			estadoOperacion = utn_getInt(&pAuxiliar->cantidadJugadores, "A continuacion, actualice la cantidad de jugadores (1 - 6):", "Error. Dato invalido!", MINIMO_JUGADORES, MAXIMO_JUGADORES, REINTENTOS);
			break;
	}

	if(utn_comprobarEstadoDeOperacion(estadoOperacion))
	{
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/*
* \brief Modifica un campo del elemento recibido por parametro.
* \param eArcade* elemento - referencia del elemento que se modificara
* \param int opcion - Opcion que indica que campo se modificara.
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -15 si no se pudo realizar la modificacion del elemento.
*/
int eArcade_modificarElemento(eArcade* elemento, int opcion)
{
	eArcade auxiliar;
	int estadoOperacion;
	int retorno = PUNTERO_NULL;

	if(elemento != NULL)
	{
		estadoOperacion = eArcade_campoAModificar(&auxiliar, opcion);
		if(utn_comprobarEstadoDeOperacion(estadoOperacion))
		{
			switch(opcion)
			{
				case 1:
					strncpy(elemento->nombreJuego, auxiliar.nombreJuego, LEN_STRING_JUEGO);
					break;
				case 2:
					elemento->cantidadJugadores = auxiliar.cantidadJugadores;
					break;
			}
			retorno = OPERACION_EXITOSA;
		}

		if(estadoOperacion <0)
		{
			retorno = NO_SE_APLICARON_CAMBIOS_SOBRE_EL_ELEMENTO;
		}
	}
	return retorno;
}

/** \brief Toma los datos de un ELEMENTO para posteriormente enviarselos a
 * 			la funcion eArcade_altaElemento() quien se encargara de cargarlo en el sistema.
* \param eArcade lista[] - lista de elementos
* \param int indiceLibre - indice libre donde se puede cargar datos
* \param int idMaximo - puntero a variable donde se cargara el ultimo Id
* \param int idSalor - Id del salon al que esta asociado
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -14 si no se pudieron cargar correctamente todos los campos.
*          retorna -17 si el indice esta fuera de rango
*/
int eArcade_tomarDatos(eArcade lista[], int indiceLibre, int* idMaximo, int idSalon)
{
	eArcade auxiliar;
	int estadoOperacion;
	int iDGenerado;
	int retorno = PUNTERO_NULL;

	if(lista != NULL && idMaximo != NULL)
	{
		retorno = INDICE_FUERA_DE_RANGO;
		if(indiceLibre >= 0 && indiceLibre < LEN_MAXIMO_ARCADE)
		{
			retorno = NO_SE_CARGARON_TODOS_LOS_CAMPOS;
			estadoOperacion = utn_getNombreOApellido(auxiliar.nacionalidad, LEN_STRING_JUEGO, "Ingrese la Nacionalidad del Arcade", "Error, dato invalido!", REINTENTOS);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				estadoOperacion = utn_getNombreAlfanumerico(auxiliar.nombreJuego, LEN_STRING_JUEGO, "Ingrese el nombre del juego", "Error, dato invalido!", REINTENTOS);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					estadoOperacion = utn_getInt(&auxiliar.cantidadJugadores, "Ingrese la cantidad de jugadores (1 - 6)", "Error, dato invalido!", MINIMO_JUGADORES, MAXIMO_JUGADORES,REINTENTOS);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						estadoOperacion = utn_getInt(&auxiliar.capacidadMaximaFichas, "Ingrese la cantidad maxima de fichas (1 - 10000)", "Error, dato invalido", MINIMO_FICHAS, MAXIMO_FICHAS, REINTENTOS);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							estadoOperacion = utn_getInt(&auxiliar.tipoSonido, "Ingrese el tipo se sonido: \n\t1 >>Mono\n\t2 >>Estereo", "Error, dato invalido!", MONO, ESTEREO,REINTENTOS);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								iDGenerado = eArcade_generadorDeIds();
								*idMaximo = iDGenerado;
								estadoOperacion = eArcade_altaElemento(lista, indiceLibre, iDGenerado, auxiliar.nacionalidad, auxiliar.nombreJuego, auxiliar.cantidadJugadores, auxiliar.tipoSonido, auxiliar.capacidadMaximaFichas, idSalon);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									retorno = OPERACION_EXITOSA;
								}
							}
						}

					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Da el alta de un elemento, cargando en el los datos recibidos por parametro.
*        La carga se realiza en la primer posicion vacia que este disponible en la lista.
* \param eArcade lista[] - lista que contiene elementos
* \param int indiceLibre - Indice libre donde se cargara la informacion del elemento
* \param int id - id del elemento
* \param char nacionalidad[] - Nacionalidad del arcade
* \param char nombreJuego[] - nombre de juego
* \param int cantidadJugadores - cantidad maxima de jugadores soportada
* \param int tipoSonido - tipo de Sonido del elemento
* \param int maximoFichas - cantidad  maximo de fichas soportadas
* \param int idSalon - id del salon asociado
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -11 si el ID es invalido
*          retorna -17 si el indice esta fuera de rango
*/
int eArcade_altaElemento(eArcade lista[], int indiceLibre, int id, char nacionalidad[],char nombreJuego[],int cantidadJugadores, int tipoSonido, int maximoFichas, int idSalon)
{
	int retorno = PUNTERO_NULL;

	if(lista != NULL && nacionalidad != NULL && nombreJuego != NULL)
	{
		retorno = ID_INVALIDO;
		if(id > 0 && idSalon >0)
		{
			retorno = INDICE_FUERA_DE_RANGO;
			if(indiceLibre >= 0 && indiceLibre < LEN_MAXIMO_ARCADE)
			{
				lista[indiceLibre].id = id;
				strncpy(lista[indiceLibre].nacionalidad, nacionalidad, LEN_STRING_JUEGO);
				strncpy(lista[indiceLibre].nombreJuego, nombreJuego, LEN_STRING_JUEGO);
				lista[indiceLibre].cantidadJugadores = cantidadJugadores;
				lista[indiceLibre].capacidadMaximaFichas = maximoFichas;
				lista[indiceLibre].tipoSonido = tipoSonido;
				lista[indiceLibre].idSalon = idSalon;
				lista[indiceLibre].isEmpty = OCUPADO;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Fuerza el alta de un elemento
* \param eArcade lista[] - Lista que contiene datos
* \param int len - tam del array
* \param int indice - indice donde se dara el alta
* \param int* idMaximo - puntero a variable donde se guardara el ultimo Id
* \param char* nacionalidad - puntero a variable nacionalidad
* \param char* nombreJuego - puntero a variable nombreJuego
* \param int maximoFichas - maximo de fichas que soporta el arcade
* \param int cantidadJugadores - cantidad de jugadores que soporta el arcade
* \param int tipoSonido - tipoSonido
* \param int* bandera_eArcade_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \return Retorna INT. Retorna 1 si se encontro por lo menos un elemento para imprimir
* 		  retorna  0 si OK
* 		  Retorna -1 si puntero apunta a direccion NULL.
* 		  retorna -2 si el len es invalido
*/
int eArcade_forzarAltas(eArcade lista[], int len,int indice, int* idMaximo, int idSalon, char* nacionalidad, char* nombreJuego,int maximoFichas, int cantidadJugadores, int tipoSonido, int* bandera_eArcade_hayElementos)
{
	int retorno = PUNTERO_NULL;
	if(lista != NULL && idMaximo != NULL && nombreJuego != NULL && nacionalidad!= NULL)
	{
		retorno = LEN_INVALIDO;
		if( len >0)
		{
			strncpy(lista[indice].nacionalidad, nacionalidad, LEN_STRING_JUEGO);
			strncpy(lista[indice].nombreJuego, nombreJuego, LEN_STRING_JUEGO);
			lista[indice].idSalon = idSalon;
			lista[indice].tipoSonido = tipoSonido;
			lista[indice].cantidadJugadores = cantidadJugadores;
			lista[indice].capacidadMaximaFichas = maximoFichas;
			*idMaximo = eArcade_generadorDeIds();
			lista[indice].id = *idMaximo;
			lista[indice].isEmpty = OCUPADO;
			*bandera_eArcade_hayElementos = HAY_ELEMENTOS_EARCADE;
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}


/**
* \brief Cuenta los arcades que tienen el juego especificado por parametro
* \param eArcade lista[] - Lista que contiene arcades
* \param int len - tam del array
* \param char juego - juego que se esta buscando en los arcades
* \return Retorna INT. Retorna 1 o mas, que es la cantidad de arcades que contienen el juego
* 		  retorna  0 si no hay coincidencias
* 		  Retorna -1 si puntero apunta a direccion NULL.
* 		  retorna -2 si el len es invalido
*/
int eArcade_ContarArcadesQueContienenElJuegoEspecificado(eArcade lista[], int len, char juego[])
{
	int i;
	int contador=0;
	int retorno = PUNTERO_NULL;
	if(lista != NULL && juego != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = NO_HAY_ELEMENTOS;
			for(i =0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO && strncmp(lista[i].nombreJuego, juego, LEN_STRING_JUEGO) == 0)
				{
					contador++;
				}
			}
			if(contador >0)
			{
				retorno = contador;
			}
		}
	}
	return retorno;
}

/**
* \brief Imprime los datos de los arcades que tienen el juego especificado por parametro
* \param eArcade lista[] - Lista que contiene arcades
* \param int len - tam del array
* \param char juego - juego que se esta buscando en los arcades
* \return Retorna INT. Retorna 1 o mas, que es la cantidad de arcades que contienen el juego
* 		  retorna  0 si no hay coincidencias
* 		  Retorna -1 si puntero apunta a direccion NULL.
* 		  retorna -2 si el len es invalido
*/
int eArcade_ContarEImprimirArcadesQueContienenElJuegoEspecificado(eArcade lista[], int len, char juego[])
{
	int i;
	int contador=0;
	int retorno = PUNTERO_NULL;
	if(lista != NULL && juego != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= LEN_MAXIMO_ARCADE)
		{
			retorno = NO_HAY_ELEMENTOS;
			eArcade_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
			for(i =0; i < len; i++)
			{
				if(strncmp(lista[i].nombreJuego, juego, LEN_STRING_JUEGO) == 0)
				{
					eArcade_imprimirFilaDelElemento(lista[i], MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
					contador++;
				}
			}
			if(contador >0)
			{
				retorno = contador;
			}
		}
	}
	return retorno;
}
