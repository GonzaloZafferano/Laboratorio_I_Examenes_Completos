/*
 * Arcade.c
 *
 *  Created on: 17 nov 2021
 *      Author: GONZALO
 */
#include "Arcade.h"

#define ERROR -50
#define LEN_INT 10
#define TRUE 1
#define MONO 1
#define STEREO 2
#define MOSTRAR_ID_NOMBRE 1
#define REINTENTOS 2
#define MOSTRAR_TODOS_LOS_DATOS 2
#define LEN_SONIDO 20
#define LEN_NOMBRE 51
#define LEN_NOMBRE_ALFANUMERICO 64
#define LEN_ARCHIVO 50
#define LEN_TEXTO 200
#define ERROR_PUNTERO_NULL_AL_COMPARAR -10
#define MAXIMO_TIPO_SONIDO 2
#define MINIMO_TIPO_SONIDO 1
#define MINIMO_CANTIDAD_JUGADORES 1
#define MAXIMO_CANTIDAD_JUGADORES 10
#define MINIMO_CANTIDAD_FICHAS 1
#define MAXIMO_CANTIDAD_FICHAS 10000
#define OPERACION_EXITOSA 0
#define NO_CUMPLE_CON_CRITERIO 1
#define ERROR_PUNTERO_NULL -1
#define ERROR_DATO_FUERA_DE_RANGO -9
#define ERROR_DATO_INVALIDO -11
#define ERROR_NO_SE_PUDIERON_TOMAR_TODOS_LOS_DATOS -23
#define ERROR_ID_INVALIDO -24
#define ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID -32
#define ERROR_NO_SE_DIO_MODIFICACION -35
#define ERROR_NO_SE_PUDO_IMPRIMIR -37
#define ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS -38
#define ERROR_NO_SE_PUDO_GUARDAR_ULTIMO_ID_EN_ARCHIVO -49
#define IGUALDAD 0
#define PRIMERO_ES_MAYOR 1
#define SEGUNDO_ES_MAYOR -1
#define OBTENER_ACTUAL_ULTIMO_ID 1
#define OBTENER_NUEVO_ULTIMO_ID 2
#define SIN_INGRESOS 0
#define PRIMER_INGRESO_OK 1
#define NO_SE_ENCONTRO_ARCHIVO_DE_ID 2
#define ARCHIVO_ID_CREADO_O_ACTUALIZADO 3

static int eArcade_abrirArchivoConUltimoId(char* path, int* pUltimoId);
static int eArcade_guardarUltimoIdEnArchivo(char* path, int ultimoId);
static int eArcade_buscarUltimoId(char* pPathListado, int* pUltimoId);
static int eArcade_limpiarElementosLista(LinkedList* pLinkedListArcades);
static eArcade* eArcade_new();

/**
* \brief Reserva un segmento de memoria con espacio suficiente para colocar un nuevo Arcade
* \param void -
* \return retorna un eArcade* (direccion de memoria con espacio suficiente para el nuevo Arcade)
*/
static eArcade* eArcade_new()
{
	eArcade* pArcade;
	pArcade = (eArcade*)malloc(sizeof(eArcade));

	return pArcade;
}

/*
* \brief Libera la memoria reservada de una direccion de memoria, obtenida con MALLOC.
* \param eArcade* pElemento - direccion de memoria, a la cual se le liberara la memoria reservada
* \return VOID
* */
void eArcade_delete(eArcade* pElemento)
{
	if(pElemento != NULL)
	{
		free(pElemento);
	}
}

/**
* \brief Obtiene la direccion de memoria de un nuevo arcade, cargando todos sus campos con los parametros recibidos
* 		 Recibe todos los campos en tipo char.
* \param char* pIdArcade - id del arcade
* \param char* pNombreJuego -  nombre del juego del arcade
* \param char* pNacionalidad -  nacionalidad del arcade
* \param char* pNombreSalon -  nombre del salon del arcade
* \param char* pTipoDeSonido - tipo de sonido del arcade
* \param char* pCantidadJugadores - cantidad de jugadores del arcade
* \param char* pCapacidadMaximaDeFichas - capacidad de fichas del arcade
* \return retorna un eArcade* (direccion de memoria disponible con espacio suficiente para el nuevo Arcade)
* 		  retorna NULL si hubo un error.
*/
eArcade* eArcade_newParametrosTexto(char* pIdArcade, char* pNombreJuego, char* pNacionalidad, char* pNombreSalon, char* pTipoDeSonido, char* pCantidadJugadores, char* pCapacidadMaximaDeFichas)
{
	eArcade* pElemento = NULL;
	if(pIdArcade != NULL && pNombreJuego != NULL && pNacionalidad != NULL && pNombreSalon != NULL && pTipoDeSonido != NULL && pCantidadJugadores != NULL && pCapacidadMaximaDeFichas != NULL)
	{
		pElemento = eArcade_new();
		if(pElemento != NULL)
		{
			if(eArcade_setIdTexto(pElemento, pIdArcade) ||
			   eArcade_setNombreDeJuego(pElemento, pNombreJuego) ||
			   eArcade_setNacionalidad(pElemento, pNacionalidad) ||
			   eArcade_setNombreDeSalon(pElemento, pNombreSalon) ||
			   eArcade_setTipoDeSonidoTexto(pElemento, pTipoDeSonido) ||
			   eArcade_setCantidadMaximaDeJugadoresTexto(pElemento, pCantidadJugadores) ||
			   eArcade_setCapacidadMaximaDeFichasTexto(pElemento, pCapacidadMaximaDeFichas))
			{
				eArcade_delete(pElemento);
				pElemento = NULL;
			}
		}
	}
	return pElemento;
}

/**
* \brief Obtiene la direccion de memoria de un nuevo elemento, cargando todos sus campos con los parametros recibidos
* \param int idArcade - id del arcade
* \param char nombreJuego[] -  nombre del juego del arcade
* \param char nacionalidad[] -  nacionalidad del arcade
* \param char nombreSalon[] -  nombre del salon del arcade
* \param int tipoDeSonido - tipo de sonido del arcade
* \param  int cantidadJugadores - cantidad de jugadores del arcade
* \param int capacidadMaximaDeFichas - capacidad de fichas del arcade
* \return retorna un eArcade* (direccion de memoria disponible con espacio suficiente para el nuevo arcade)
* 		  o retorna NULL en caso de ERROR
*/
eArcade* eArcade_newParametrosDiferenciandoTiposDeDatos(int idArcade, char nombreJuego[], char nacionalidad[], char nombreSalon[], int tipoDeSonido, int cantidadDeJugadores, int capacidadMaximaDeFichas)
{
	eArcade* pElemento = NULL;
	if(nombreJuego != NULL && nombreSalon != NULL && nacionalidad != NULL)
	{
		pElemento = eArcade_new();
		if(pElemento != NULL)
		{
			if(eArcade_setId(pElemento, idArcade) ||
			   eArcade_setNombreDeJuego(pElemento, nombreJuego) ||
			   eArcade_setNacionalidad(pElemento, nacionalidad) ||
			   eArcade_setNombreDeSalon(pElemento, nombreSalon) ||
			   eArcade_setTipoDeSonido(pElemento, tipoDeSonido) ||
			   eArcade_setCantidadDeJugadores(pElemento, cantidadDeJugadores) ||
			   eArcade_setCapacidadMaximaDeFichas(pElemento, capacidadMaximaDeFichas))
			{
				eArcade_delete(pElemento);
				pElemento = NULL;
			}
		}
	}
	return pElemento;
}

/**
* \brief Obtiene los datos de un Arcade
* \param char nombreJuego[] -  array de caracteres donde se guardara el nombre del juego del arcade
* \param char nacionalidad[] -  array de caracteres donde se guardara la nacionalidad del arcade
* \param char nombreSalon[] -  array de caracteres donde se guardara el nombre del salon del arcade
* \param int* pTipoDeSonido - puntero a variable donde se guardara el tipo de sonido del arcade
* \param  int* pCantidadJugadores - puntero a variable donde se guardara la cantidad de jugadores del arcade
* \param int* pCapacidadMaximaDeFichas - puntero a variable donde se guardara la capacidad de fichas del arcade
* \return Retorna Int. Retorna -1 si alguno de los punteros es NULL o
*                  	   Retorna el estado de la ultima operacion realizada de toma de datos,
*                  	   Si el retorno es 0, opero correctamente. Si es negativo, ocurrio un error.
*/
int eArcade_getDataToAddANewArcade(char nombreJuego[], char nacionalidad[], char nombreSalon[], int* pTipoDeSonido, int* pCantidadDeJugadores, int* pCapacidadMaximaDeFichas)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;
	if(nombreJuego != NULL && nombreSalon != NULL && nacionalidad != NULL && pTipoDeSonido != NULL && pCapacidadMaximaDeFichas != NULL && pCantidadDeJugadores != NULL)
	{
		estadoOperacion = utn_getNombreAlfanumerico(nombreJuego, LEN_NOMBRE_ALFANUMERICO, "\nIngrese el nombre del juego que contiene el Arcade", "Error. Dato invalido", REINTENTOS);
		if(utn_comprobarEstadoDeOperacion(estadoOperacion))
		{
			estadoOperacion = utn_getNombreOApellido(nacionalidad, LEN_NOMBRE, "Ingrese la nacionalidad del arcade", "Error. Dato invalido", REINTENTOS);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				estadoOperacion = utn_getNombreAlfanumerico(nombreSalon, LEN_NOMBRE_ALFANUMERICO, "Ingrese el nombre del salon donde esta el arcade", "Error. Dato invalido", REINTENTOS);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					estadoOperacion = utn_getInt(pTipoDeSonido, "Ingrese el tipo de sonido del arcade: \n\t1 >>Mono\n\t2 >>Estereo", "Error. Dato invalido", MINIMO_TIPO_SONIDO, MAXIMO_TIPO_SONIDO, REINTENTOS);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						estadoOperacion = utn_getInt(pCantidadDeJugadores, "Ingrese la cantidad de jugadores que soporta el arcade (1 - 10)", "Error. Dato invalido", MINIMO_CANTIDAD_JUGADORES, MAXIMO_CANTIDAD_JUGADORES, REINTENTOS);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							estadoOperacion = utn_getInt(pCapacidadMaximaDeFichas, "Ingrese la capacidad maxima de fichas que soporta el arcade (1 - 10000)", "Error. Dato invalido", MINIMO_CANTIDAD_FICHAS, MAXIMO_CANTIDAD_FICHAS, REINTENTOS);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
						}
					}
				}
			}
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Toma los datos de la modificacion, y los carga en una direccion de memoria recibida por parametro
* \param eArcade* pElemento - direccion de memoria del elemento, al cual se le realizaran las modificaciones
* \param int opcion - opcion que representa el campo que se desea modificar
* \return retorna INT. 0 si opero correctamente
* 	      retorna -1 si algun puntero apunta a NULL
* 	      retorna -23 si no se pudieron tomar todos los datos correctamente
* 	      retorna -35 si no se pudo aplicar la modificacion

* */
int eArcade_getDataFromUserToEditAFiel(eArcade* pElemento, int opcion)
{
	int estadoOperacion;
	int cantidadDeJugadores;
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && (opcion == 1 || opcion == 2))
	{
		retorno = ERROR_NO_SE_PUDIERON_TOMAR_TODOS_LOS_DATOS;
		switch(opcion)
		{
			case 1:
				estadoOperacion = utn_getNombreAlfanumerico(nombreJuego, sizeof(nombreJuego), "\nIngrese el nuevo nombre del juego", "\nError. Dato invalido", REINTENTOS);
				break;
			case 2:
				estadoOperacion = utn_getInt(&cantidadDeJugadores, "Ingrese la nueva cantidad de jugadores (1 - 10)", "Error. Dato invalido", MINIMO_CANTIDAD_JUGADORES, MAXIMO_CANTIDAD_JUGADORES, REINTENTOS);
				break;
		}

		if(utn_comprobarEstadoDeOperacion(estadoOperacion))
		{
			retorno = ERROR_NO_SE_DIO_MODIFICACION;
			switch(opcion)
			{
				case 1:
					estadoOperacion = eArcade_setNombreDeJuego(pElemento, nombreJuego);
					break;
				case 2:
					estadoOperacion = eArcade_setCantidadDeJugadores(pElemento, cantidadDeJugadores);
					break;
			}
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

///////////////////////////////////ELIMINAR LISTA DE SISTEMA/////////////////////////////////////////////////////////
/*
* \brief Libera la memoria reservada en una lista
* \param LinkedList* pLinkedListAuxiliar - puntero a LinkedList de Arcade
* \return -1 si el puntero es NULL. 0 si opero correctamente.
* */
static int eArcade_limpiarElementosLista(LinkedList* pLinkedListArcades)
{
	int i;
	eArcade* pElemento;
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListArcades != NULL)
	{
		retorno = OPERACION_EXITOSA;
		for(i = 0; i < ll_len(pLinkedListArcades); i++)
		{
			pElemento = (eArcade*) ll_get(pLinkedListArcades, i);
			eArcade_delete(pElemento);
		}
	}
	return retorno;
}

/*
* \brief Libera toda la memoria reservada en una lista (elementos, nodos)
* \param LinkedList* pLinkedListAuxiliar - puntero a LinkedList
* \return -1 si el puntero es NULL. 0 si opero correctamente.
* */
int eArcade_liberarListaDeMemoria(LinkedList* pLinkedListArcades)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListArcades != NULL)
	{
		if(!eArcade_limpiarElementosLista(pLinkedListArcades))
		{
			if(!ll_deleteLinkedList(pLinkedListArcades))
			{
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

///////////////////////////////////FUNCIONES DE BUSCAR POR ID O ULTIMO ID/////////////////////////////////////////////////////////
/** \brief abre el archivo que contiene el ultimo ID
* \param  char* pathArchivoUltimoId - ruta absoluta o relativa del archivo
* \param  int* pUltimoId - puntero a variable que espera guardar el ultimo id
* \return int. Retorna 0 si opero exitosamente
* 			   retorna -50 si hay un error.
*/
static int eArcade_abrirArchivoConUltimoId(char* pathArchivoUltimoId, int* pUltimoId)
{
	FILE* fpArchivoId;
	int auxiliarUltimoIdEntero;
	char auxiliarUltimoIdChar[LEN_INT];
	int retorno = ERROR;
	if(pathArchivoUltimoId != NULL && pUltimoId != NULL)
	{
		fpArchivoId = fopen(pathArchivoUltimoId, "r");
		if(fpArchivoId != NULL)
		{
			if(fscanf(fpArchivoId, "%[^\n]\n", auxiliarUltimoIdChar) == 1)
			{
				if(validar_numeroEntero(auxiliarUltimoIdChar, sizeof(auxiliarUltimoIdChar)) == TRUE)
				{
					auxiliarUltimoIdEntero = atoi(auxiliarUltimoIdChar);
					if(auxiliarUltimoIdEntero >= 0)
					{
						*pUltimoId = auxiliarUltimoIdEntero;
						retorno = OPERACION_EXITOSA;
					}
				}
			}
			fclose(fpArchivoId);
		}
	}
	return retorno;
}

/** \brief Busca el ID mas grande en el Archivo con la lista de datos, y lo guarda en el puntero pUltimoId
* \param  char* pPathListado - ruta absoluta o relativa del archivo donde buscara el id mas grande.
* \param  int* pUltimoId - puntero a variable que espera guardar el ultimo id
* \return int. Retorna 0 si opero exitosamente o
* 			   retorna -50 si hay un error.
*/
static int eArcade_buscarUltimoId(char* pPathListado, int* pUltimoId)
{
	int idEntero;
	int idMasGrande;
	FILE* fpAuxiliar;
	char idTexto[LEN_INT];
	char texto[LEN_TEXTO];
	int banderaPrimerIngreso = 0;
	int retorno = ERROR;

	if(pPathListado != NULL && pUltimoId != NULL)
	{
		fpAuxiliar = fopen(pPathListado, "r");
		if(fpAuxiliar != NULL)
		{
			do
			{
				if(fscanf(fpAuxiliar,"%[^,],%[^\n]\n", idTexto, texto) == 2)
				{
					if(validar_numeroEntero(idTexto, sizeof(idTexto)) == TRUE)
					{
						idEntero = atoi(idTexto);
						if(banderaPrimerIngreso == 0 || idEntero > idMasGrande)
						{
							idMasGrande = idEntero;
							banderaPrimerIngreso = 1;
						}
					}
				}
			}while(!feof(fpAuxiliar));
			fclose(fpAuxiliar);
			if(banderaPrimerIngreso)
			{
				*pUltimoId = idMasGrande;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/** \brief guarda el ultimo ID en el archivo de IDs
* \param  char* pPathArchivoId - ruta absoluta o relativa del archivo.
* \param  int ultimoId - ultimo id hasta el momento
* \return int. Retorna 0 si opero exitosamente
* 			   retorna -50 si hay un error.
*/
static int eArcade_guardarUltimoIdEnArchivo(char* pPathArchivoId, int ultimoId)
{
	FILE* fpArchivoId;
	int retorno = ERROR;
	if(pPathArchivoId != NULL)
	{
		fpArchivoId = fopen(pPathArchivoId, "w");
		if(fpArchivoId != NULL)
		{
			fprintf(fpArchivoId, "%d\n", ultimoId);
			fclose(fpArchivoId);
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/** \brief obtiene el ultimo ID o el proximo, segun el parametro recibido
* \param  int opcion - opcion que determina si se obtiene el ultimo ID (1) o el proximo ID (2)
* \return int. Retorna 0 o positivo, que es el ID obtenido o
* 			   retorna -49 si hay un error y no se pudo guardar ultimo ID en archivo de Ids.
* 			   retorna -50 si hay un error general.
*/
int eArcade_getLastOrNextId(int opcion)
{
	int estadoOperacion;
	int auxiliarUltimoId;
	static int banderaPrimerIngreso = SIN_INGRESOS;
	static int ultimoIdActual = 0;
	char pathArchivoTexto [LEN_ARCHIVO] = "arcades.csv";
	char pathArchivoUltimoId [LEN_ARCHIVO] = "ArchivoUltimoId.csv";
	int retorno = ERROR;

	if(!banderaPrimerIngreso)
	{
		banderaPrimerIngreso = PRIMER_INGRESO_OK;
		estadoOperacion = eArcade_abrirArchivoConUltimoId(pathArchivoUltimoId, &auxiliarUltimoId);
		if(estadoOperacion)
		{
			banderaPrimerIngreso = NO_SE_ENCONTRO_ARCHIVO_DE_ID;
			estadoOperacion = eArcade_buscarUltimoId(pathArchivoTexto, &auxiliarUltimoId);
			if(estadoOperacion)
			{
				auxiliarUltimoId = 0;
			}
		}
		ultimoIdActual = auxiliarUltimoId;
	}

	switch(opcion)
	{
		case OBTENER_ACTUAL_ULTIMO_ID:
			retorno = ultimoIdActual;
			break;
		case OBTENER_NUEVO_ULTIMO_ID:
			ultimoIdActual++;
			break;
	}

	if(banderaPrimerIngreso == NO_SE_ENCONTRO_ARCHIVO_DE_ID || opcion == OBTENER_NUEVO_ULTIMO_ID)
	{
		retorno = ERROR_NO_SE_PUDO_GUARDAR_ULTIMO_ID_EN_ARCHIVO;
		if(!eArcade_guardarUltimoIdEnArchivo(pathArchivoUltimoId, ultimoIdActual))
		{
			banderaPrimerIngreso = ARCHIVO_ID_CREADO_O_ACTUALIZADO;
			retorno = ultimoIdActual;
		}
	}
	return retorno;
}

/**
* \brief Obtiene el nodo en el que se encuentra un arcade segun su id
* \param LinkedList* pArrayListeArcade - puntero a lista de arcades
* \param int id - id del arcade
* \return Retorna INT. Retorna 0 o positivo, que es el indice del arcade
* 		  Retorna -1 si el segundo elemento es mayor que el primero
* 		  retorna -32 si no se encontraron datos asociados al id
*/
int eArcade_findeArcadeById(LinkedList* pArrayListeArcade, int id)
{
	int i;
	int len;
	int idObtenido;
	eArcade* pAuxiliar;
	int retorno = ERROR_PUNTERO_NULL;
	if(pArrayListeArcade != NULL)
	{
		retorno =  ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID;
		len = ll_len(pArrayListeArcade);
		for(i = 0; i < len; i++)
		{
			pAuxiliar = (eArcade*)ll_get(pArrayListeArcade, i);
			if(pAuxiliar != NULL)
			{
				if(!eArcade_getId(pAuxiliar, &idObtenido))
				{
					if(idObtenido == id)
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
* \brief Obtiene el puntero en el que se encuentra un arcade segun su id
* \param LinkedList* pArrayListeArcade - puntero a lista de arcades
* \param int id - id del arcade
* \return Retorna eArcade*. Retorna la direccion de memoria del arcade,
*                 o NULL si no lo encontro o hubo un error.
*/
eArcade* eArcade_findPointerToeArcadeById(LinkedList* pArrayListeArcade, int id)
{
	int i;
	int len;
	int idObtenido;
	eArcade* pAuxiliar;
	eArcade* retorno = NULL;
	if(pArrayListeArcade != NULL)
	{
		len = ll_len(pArrayListeArcade);
		for(i = 0; i < len; i++)
		{
			pAuxiliar = (eArcade*)ll_get(pArrayListeArcade, i);
			if(pAuxiliar != NULL)
			{
				if(!eArcade_getId(pAuxiliar, &idObtenido))
				{
					if(idObtenido == id)
					{
						retorno = pAuxiliar;
						break;
					}
				}
			}
		}
	}
	return retorno;
}

///////////////////////////////////FUNCIONES IMPRIMIR/////////////////////////////////////////////////////////
/**
* \brief Imprime los encabezados para la tabla de datos de Arcades
* \param int opcion - opcion que determina el encabezado que se va a imprimir
* \return retorna VOID
*/
void eArcade_ImprimirEncabezadoDeDatos(int opcion)
{
	switch(opcion)
	{
		case MOSTRAR_ID_NOMBRE:
			printf("\n%5s   %-30s   %-20s","Id", "Nombre del Juego", "Cant. de jugadores");
			break;
		case MOSTRAR_TODOS_LOS_DATOS:
			printf("\n%5s   %-30s   %-20s %-20s   %-15s   %-15s   %-15s","Id", "Nombre del Juego", "Nacionalidad", "Nombre de Salon", "Tipo de Sonido", "Cant. Jugadores", "Cap. max. fichas");
			break;
	}
}

/**
* \brief Imprime una fila vacia.
* \param int opcion - opcion que determina el formato de fila vacia que se va a imprimir
* \return retorna VOID
*/
void eArcade_ImprimirFilaVaciaDeDatos(int opcion)
{
	switch(opcion)
	{
		case MOSTRAR_ID_NOMBRE:
			printf("\n%5s   %-30s   %18s","-", "-", "-");
			break;
		case MOSTRAR_TODOS_LOS_DATOS:
			printf("\n%5s   %-30s   %-20s %-20s   %14s   %16s   %16s","-", "-", "-", "-", "-", "-", "-");
			break;
	}
}

/**
* \brief Imprime todos los datos de un arcade
* \param void* pElemento - puntero que contiene el elemento quiere imprimir
* \return retorna INT. 0 si opero correctamente
* 	      retorna -1 si algun puntero apunta a NULL
* 	      retorna -37 si no se pudieron obtener todos los datos para imprimir la fila de datos
*/
int eArcade_ImprimirTodosLosDatos(void* pElemento)
{
	int idArcade;
	int cantidadJugadores;
	int capacidadMaximaDeFichas;
	char tipoSonido[LEN_SONIDO];
	char nacionalidad[LEN_NOMBRE];
	char nombreSalon[LEN_NOMBRE_ALFANUMERICO];
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	eArcade* pArcade;

	if(pElemento != NULL)
	{
		retorno = ERROR_NO_SE_PUDO_IMPRIMIR;
		pArcade = (eArcade*) pElemento;
		if(!eArcade_gettersFromArcade(pArcade, &idArcade, nombreJuego, nacionalidad, nombreSalon, tipoSonido, &cantidadJugadores, &capacidadMaximaDeFichas))
		{
			printf("\n%5d   %-30.30s   %-20.20s %-20.20s   %14s   %16d   %16d", idArcade, nombreJuego, nacionalidad, nombreSalon, tipoSonido, cantidadJugadores, capacidadMaximaDeFichas);
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief Imprime el Id, el nombre del juego y la cantidad de jugadores del arcade
* \param void* pElemento - puntero que contiene el elemento quiere imprimir
* \return retorna INT. 0 si opero correctamente
* 	      retorna -1 si algun puntero apunta a NULL
* 	      retorna -37 si no se pudieron obtener todos los datos para imprimir la fila de datos
*/
int eArcade_ImprimirIdNombreYCantidadJugadores(void* pElemento)
{
	int idArcade;
	int cantidadJugadores;
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	eArcade* pArcade;

	if(pElemento != NULL)
	{
		pArcade = (eArcade*) pElemento;
		retorno = ERROR_NO_SE_PUDO_IMPRIMIR;
		if(!eArcade_getId(pArcade, &idArcade) &&
		   !eArcade_getNombreDeJuego(pArcade, nombreJuego) &&
		   !eArcade_getCantidadDeJugadores(pArcade, &cantidadJugadores))
		{
			printf("\n%5d   %-30.30s  %19d",idArcade , nombreJuego, cantidadJugadores);
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief Imprime el encabezado y todos los datos de un solo arcade
* \param eArcade* pElemento - puntero del arcade que se quiere imprimir
* \return retorna INT. 0 si opero correctamente
* 	      retorna -1 si algun puntero apunta a NULL
* 	      retorna -37 si no se pudieron obtener todos los datos para imprimir la fila de datos
*/
int eArcade_imprimirUnSoloArcade(eArcade* this)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(this != NULL)
	{
		retorno = ERROR_NO_SE_PUDO_IMPRIMIR;
		eArcade_ImprimirEncabezadoDeDatos(MOSTRAR_TODOS_LOS_DATOS);
		if(!eArcade_ImprimirTodosLosDatos(this))
		{
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

///////////////////////////////////GETTERS Y SETTERS/////////////////////////////////////////////////////////
/**
* \brief setea el id del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param int id - id que se seteara
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  retorna -24 si el id es invalido
*/
int eArcade_setId(eArcade* pElemento, int idArcade)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL)
	{
		retorno = ERROR_ID_INVALIDO;
		if(idArcade > 0)
		{
			pElemento->idArcade = idArcade;
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief setea el id del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char* pId - id que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -11 si el dato no se pudo cargar
* 		  retorna -24 si el id es invalido
*/
int eArcade_setIdTexto(eArcade* pElemento, char* pId)
{
	int lenCadena;
	int auxiliarEntero;
	char cadenaAuxiliarEntero[LEN_INT];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pId != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pId, sizeof(cadenaAuxiliarEntero));
		if(lenCadena > 0)
		{
			strncpy(cadenaAuxiliarEntero, pId, sizeof(cadenaAuxiliarEntero));
			if(lenCadena == sizeof(cadenaAuxiliarEntero))
			{
				validar_cortarCadena(cadenaAuxiliarEntero, lenCadena);
			}

			if(validar_numeroEntero(cadenaAuxiliarEntero, sizeof(cadenaAuxiliarEntero)) == TRUE)
			{
				retorno = ERROR_ID_INVALIDO;
				auxiliarEntero = atoi(cadenaAuxiliarEntero);
				if(auxiliarEntero > 0)
				{
					pElemento->idArcade = auxiliarEntero;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene el id del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param int* pIdArcade - puntero (direccion de memoria) donde se guardara el id de eArcade
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
int eArcade_getId(eArcade* pElemento, int* pIdArcade)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pIdArcade != NULL)
	{
		*pIdArcade = pElemento->idArcade;
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea el tipo de sonido del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param int tipoSonido - sonido que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -9 si el dato esta fuera de rango
*/
int eArcade_setTipoDeSonido(eArcade* pElemento, int tipoSonido)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL)
	{
		retorno = ERROR_DATO_FUERA_DE_RANGO;
		if(tipoSonido >= MINIMO_TIPO_SONIDO && tipoSonido <= MAXIMO_TIPO_SONIDO)
		{
			pElemento->tipoDeSonido = tipoSonido;
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief setea el tipo de sonido (desde texto) del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char* pTipoDeSonido - tipo de sonido que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  retorna -9 si el dato esta fuera de rango
* 	      retorna -11 si el dato no se pudo cargar
*/
int eArcade_setTipoDeSonidoTexto(eArcade* pElemento, char* pTipoDeSonido)
{
	int lenCadena;
	char cadenaAuxiliarEntero[LEN_SONIDO];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pTipoDeSonido != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pTipoDeSonido, sizeof(cadenaAuxiliarEntero));
		if(lenCadena > 0)
		{
			strncpy(cadenaAuxiliarEntero, pTipoDeSonido, sizeof(cadenaAuxiliarEntero));
			if(lenCadena == sizeof(cadenaAuxiliarEntero))
			{
				validar_cortarCadena(cadenaAuxiliarEntero, lenCadena);
			}

			if(validar_nombre(cadenaAuxiliarEntero, sizeof(cadenaAuxiliarEntero)) == TRUE)
			{
				retorno = ERROR_DATO_FUERA_DE_RANGO;
				if(!strncmp(cadenaAuxiliarEntero,"Mono",sizeof(cadenaAuxiliarEntero)))
				{
					pElemento->tipoDeSonido = 1;
					retorno = OPERACION_EXITOSA;
				}
				else
				{
					if(!strncmp(cadenaAuxiliarEntero,"Stereo",sizeof(cadenaAuxiliarEntero)))
					{
						pElemento->tipoDeSonido = 2;
						retorno = OPERACION_EXITOSA;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene el tipo de sonido del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param int* tipoDeSonido - puntero (direccion de memoria) donde se guardara el tipo de sonido del eArcade
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
int eArcade_getTipoDeSonido(eArcade* pElemento, int* tipoDeSonido)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && tipoDeSonido != NULL)
	{
		*tipoDeSonido = pElemento->tipoDeSonido;
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/** \brief Escribe en un array de char el texto que representa al tipo numerico de sonido del arcade.
* \param eArcade* pArcade - direccion de memoria de un arcade
* \param char* pTexto - array de chars donde se escribira la representacion Textual del tipo numerico
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si la direccion de memoria del array es NULL.
*/
int eArcade_getTipoDeSonidoDeNumeroATexto(eArcade* pArcade, char* pTexto)
{
	int tipoDeSonido;
	int retorno = ERROR_PUNTERO_NULL;
	if(pArcade != NULL && pTexto != NULL)
	{
		if(!eArcade_getTipoDeSonido(pArcade, &tipoDeSonido))
		{
			switch(tipoDeSonido)
			{
				case MONO:
					strncpy(pTexto,"MONO", LEN_SONIDO);
					break;
				case STEREO:
					strncpy(pTexto,"STEREO", LEN_SONIDO);
					break;
			}
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief setea la cantidad de jugadores del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param int cantidadDeJugadores - cantidad de jugadores que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -9 si el dato esta fuera de rango
*/
int eArcade_setCantidadDeJugadores(eArcade* pElemento, int cantidadDeJugadores)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL)
	{
		retorno = ERROR_DATO_FUERA_DE_RANGO;
		if(cantidadDeJugadores >= MINIMO_CANTIDAD_JUGADORES && cantidadDeJugadores <= MAXIMO_CANTIDAD_JUGADORES)
		{
			pElemento->cantidadJugadores = cantidadDeJugadores;
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief setea la cantidad maxima de jugadores (desde texto) del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char* pCantidadMaximaDeJugadores - cantidad maxima de jugadores del arcade.
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  retorna -9 si el dato esta fuera de rango
* 	      retorna -11 si el dato no se pudo cargar
*/
int eArcade_setCantidadMaximaDeJugadoresTexto(eArcade* pElemento, char* pCantidadMaximaDeJugadores)
{
	int lenCadena;
	int auxiliarEntero;
	char cadenaAuxiliarEntero[LEN_INT];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pCantidadMaximaDeJugadores != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pCantidadMaximaDeJugadores, sizeof(cadenaAuxiliarEntero));
		if(lenCadena > 0)
		{
			strncpy(cadenaAuxiliarEntero, pCantidadMaximaDeJugadores, sizeof(cadenaAuxiliarEntero));
			if(lenCadena == sizeof(cadenaAuxiliarEntero))
			{
				validar_cortarCadena(cadenaAuxiliarEntero, lenCadena);
			}

			if(validar_numeroEntero(cadenaAuxiliarEntero, sizeof(cadenaAuxiliarEntero)) == TRUE)
			{
				retorno = ERROR_DATO_FUERA_DE_RANGO;
				auxiliarEntero = atoi(cadenaAuxiliarEntero);
				if(auxiliarEntero >= MINIMO_CANTIDAD_JUGADORES && auxiliarEntero <= MAXIMO_CANTIDAD_JUGADORES)
				{
					pElemento->cantidadJugadores = auxiliarEntero;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene la cantidad de jugadores del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param int* cantidadDeJugadores - puntero (direccion de memoria) donde se guardara la cantidad de jugadores del eArcade
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
int eArcade_getCantidadDeJugadores(eArcade* pElemento, int* cantidadDeJugadores)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && cantidadDeJugadores != NULL)
	{
		*cantidadDeJugadores = pElemento->cantidadJugadores;
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea la capacidad maxima de fichas del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param int capacidadMaximaDeFichas - capacidad de fichas que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -9 si el dato esta fuera de rango
*/
int eArcade_setCapacidadMaximaDeFichas(eArcade* pElemento, int capacidadMaximaDeFichas)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL)
	{
		retorno = ERROR_DATO_FUERA_DE_RANGO;
		if(capacidadMaximaDeFichas >= MINIMO_CANTIDAD_FICHAS && capacidadMaximaDeFichas <= MAXIMO_CANTIDAD_FICHAS)
		{
			pElemento->capacidadMaximaDeFichas = capacidadMaximaDeFichas;
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief setea la capacidad maxima de fichas (desde texto) del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char* pCapacidadMaximaDeFichas - Capacidad Maxima de fichas que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  retorna -9 si el dato esta fuera de rango
* 	      retorna -11 si el dato no se pudo cargar
*/
int eArcade_setCapacidadMaximaDeFichasTexto(eArcade* pElemento, char* pCapacidadMaximaDeFichas)
{
	int lenCadena;
	int auxiliarEntero;
	char cadenaAuxiliarEntero[LEN_INT];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pCapacidadMaximaDeFichas != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pCapacidadMaximaDeFichas, sizeof(cadenaAuxiliarEntero));
		if(lenCadena > 0)
		{
			strncpy(cadenaAuxiliarEntero, pCapacidadMaximaDeFichas, sizeof(cadenaAuxiliarEntero));
			if(lenCadena == sizeof(cadenaAuxiliarEntero))
			{
				validar_cortarCadena(cadenaAuxiliarEntero, lenCadena);
			}

			if(validar_numeroEntero(cadenaAuxiliarEntero, sizeof(cadenaAuxiliarEntero)) == TRUE)
			{
				retorno = ERROR_DATO_FUERA_DE_RANGO;
				auxiliarEntero = atoi(cadenaAuxiliarEntero);
				if(auxiliarEntero >= MINIMO_CANTIDAD_FICHAS && auxiliarEntero <= MAXIMO_CANTIDAD_FICHAS)
				{
					pElemento->capacidadMaximaDeFichas = auxiliarEntero;
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene la capacidad maxima de fichas del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param int* capacidadMaximaDeFichas - puntero (direccion de memoria) donde se guardara la capacidad maxima de fichas del eArcade
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
int eArcade_getCapacidadMaximaDeFichas(eArcade* pElemento, int* capacidadMaximaDeFichas)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && capacidadMaximaDeFichas != NULL)
	{
		*capacidadMaximaDeFichas = pElemento->capacidadMaximaDeFichas;
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea el nombre de juego del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char pNombre[] - nombre de juego que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -11 si el dato es invalido y no se puede setear
*/
int eArcade_setNombreDeJuego(eArcade* pElemento, char* pNombre)
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
				strncpy(pElemento->nombreJuego, auxiliar, sizeof(pElemento->nombreJuego));
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene el nombre del juego del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char* pNombre - puntero (direccion de memoria) donde se guardara el nombre del juego del eArcade
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el tam del array es invalido
*/
int eArcade_getNombreDeJuego(eArcade* pElemento, char* pNombre)
{
	int lenCadena = sizeof(pElemento->nombreJuego);
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pNombre != NULL)
	{
		strncpy(pNombre, pElemento->nombreJuego, lenCadena);
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea el nombre de salon del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char pNombre[] - nombre de salon que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -11 si el dato es invalido y no se puede setear
*/
int eArcade_setNombreDeSalon(eArcade* pElemento, char* pNombre)
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
				strncpy(pElemento->nombreSalon, auxiliar, sizeof(pElemento->nombreSalon));
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene el nombre del salon del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char* pNombre - puntero (direccion de memoria) donde se guardara el nombre del salon del eArcade
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el tam del array es invalido
*/
int eArcade_getNombreDeSalon(eArcade* pElemento, char* pNombre)
{
	int lenCadena = sizeof(pElemento->nombreSalon);
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pNombre != NULL)
	{
		strncpy(pNombre, pElemento->nombreSalon, lenCadena);
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief setea la nacionalidad del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char pNacionalidad[] - nombre de salon que se quiere setear
* \return Retorna INT. Retorna 0 si seteo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 	      retorna -11 si el dato es invalido y no se puede setear
*/
int eArcade_setNacionalidad(eArcade* pElemento, char* pNacionalidad)
{
	int lenCadena;
	char auxiliar[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL;

	if(pElemento != NULL && pNacionalidad != NULL)
	{
		retorno = ERROR_DATO_INVALIDO;
		lenCadena = strnlen(pNacionalidad, sizeof(auxiliar));
		if(lenCadena > 0)
		{
			strncpy(auxiliar, pNacionalidad, sizeof(auxiliar));

			if(lenCadena == sizeof(auxiliar))
			{
				validar_cortarCadena(auxiliar, lenCadena);
			}

			if(validar_nombre(auxiliar, sizeof(auxiliar))==TRUE)
			{
				strncpy(pElemento->nacionalidadArcade, auxiliar, sizeof(pElemento->nacionalidadArcade));
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene el nombre del salon del eArcade
* \param eArcade* pElemento - puntero al elemento eArcade
* \param char* pNombre - puntero (direccion de memoria) donde se guardara la nacionalidad del eArcade
* \return Retorna INT. Retorna 0 si obtuvo el dato correctamente
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el tam del array es invalido
*/
int eArcade_getNacionalidad(eArcade* pElemento, char* pNacionalidad)
{
	int lenCadena = sizeof(pElemento->nacionalidadArcade);
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pNacionalidad != NULL)
	{
		strncpy(pNacionalidad, pElemento->nacionalidadArcade, lenCadena);
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/** \brief Obtiene los datos de un Arcade, y los carga en variables.
* \param eArcade* pElemento - puntero al arcade
* \param int* pIdArcade - puntero donde se guardara el id del arcade
* \param char* pNombreJuego - puntero donde se guardara el nombre del juego del arcade
* \param char* pNacionalidad - puntero donde se guardara el nacionalidad del arcade
* \param char* pNombreSalon - puntero donde se guardara el nombre del salon del arcade
* \param int* pTipoDeSonido - puntero donde se guardara el tipo de sonido del arcade
* \param int* pCantidadJugadores - puntero donde se guardara la cantidad de jugadores del arcade
* \param int* pCapacidadMaximaDeFichas - puntero donde se guardara la capacidad de fichas del arcade
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 */
int eArcade_gettersFromArcade(eArcade* pElemento, int* pIdArcade, char* pNombreJuego, char* pNacionalidad, char* pNombreSalon, char* pTipoDeSonido, int* pCantidadJugadores, int* pCapacidadMaximaDeFichas)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL && pIdArcade != NULL && pNombreJuego != NULL && pNacionalidad != NULL && pNombreSalon != NULL && pTipoDeSonido != NULL && pCantidadJugadores != NULL && pCapacidadMaximaDeFichas != NULL)
	{
		retorno = ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS;
		if(!eArcade_getId(pElemento, pIdArcade) &&
		   !eArcade_getNombreDeJuego(pElemento, pNombreJuego) &&
		   !eArcade_getNombreDeSalon(pElemento, pNombreSalon) &&
		   !eArcade_getNacionalidad(pElemento, pNacionalidad) &&
		   !eArcade_getTipoDeSonidoDeNumeroATexto(pElemento, pTipoDeSonido) &&
		   !eArcade_getCantidadDeJugadores(pElemento, pCantidadJugadores) &&
		   !eArcade_getCapacidadMaximaDeFichas(pElemento, pCapacidadMaximaDeFichas))
			{
				retorno = OPERACION_EXITOSA;
			}
	}
	return retorno;
}

///////////////////////////////////FUNCIONES DE ORDENAR/////////////////////////////////////////////////////////
/*
* \brief determina si un elemento es mayor que otro por el nombre del juego
* \param void* pElementoUno - puntero a un elemento
* \param void* pElementoDos - puntero a un segundo elemento
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero o si el puntero es NULL
*/
int eArcade_ordenarPorNombreDeJuego(void* pElementoUno, void* pElementoDos)
{
	int respuesta;
	char cadenaUno[LEN_NOMBRE_ALFANUMERICO];
	char cadenaDos[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!eArcade_getNombreDeJuego(pElementoUno, cadenaUno) &&
		   !eArcade_getNombreDeJuego(pElementoDos, cadenaDos))
		{
			retorno = IGUALDAD;
			respuesta = strncmp(cadenaUno, cadenaDos, sizeof(cadenaUno));
			if(respuesta > 0)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(respuesta < 0)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief determina si un elemento es mayor que otro por el nombre
* \param void* pElementoUno - puntero a un Arcade
* \param void* pElementoDos - puntero a un segundo Arcade
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero o si el puntero es NULL
*/
int eArcade_ordenarPorNombreDeSalon(void* pElementoUno, void* pElementoDos)
{
	int respuesta;
	char cadenaUno[LEN_NOMBRE_ALFANUMERICO];
	char cadenaDos[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!eArcade_getNombreDeSalon(pElementoUno, cadenaUno) &&
		   !eArcade_getNombreDeSalon(pElementoDos, cadenaDos))
		{
			retorno = IGUALDAD;
			respuesta = strncmp(cadenaUno, cadenaDos, sizeof(cadenaUno));
			if(respuesta > 0)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(respuesta < 0)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief determina si un elemento es mayor que otro por el nombre
* \param void* pElementoUno - puntero a un Arcade
* \param void* pElementoDos - puntero a un segundo Arcade
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero o si el puntero es NULL
*/
int eArcade_ordenarPorNacionalidad(void* pElementoUno, void* pElementoDos)
{
	int respuesta;
	char cadenaUno[LEN_NOMBRE];
	char cadenaDos[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL_AL_COMPARAR;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!eArcade_getNacionalidad(pElementoUno, cadenaUno) &&
		   !eArcade_getNacionalidad(pElementoDos, cadenaDos))
		{
			retorno = IGUALDAD;
			respuesta = strncmp(cadenaUno, cadenaDos, sizeof(cadenaUno));
			if(respuesta > 0)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(respuesta < 0)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief determina si un elemento es mayor que otro por el tipo de sonido
* \param void* pElementoUno - puntero a un elemento
* \param void* pElementoDos - puntero a un segundo elemento
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero o si el puntero es NULL
*/
int eArcade_ordenarPorTipoDeSonido(void* pElementoUno, void* pElementoDos)
{
	int respuesta;
	char cadenaUno[LEN_SONIDO];
	char cadenaDos[LEN_SONIDO];
	int retorno = ERROR_PUNTERO_NULL;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!eArcade_getTipoDeSonidoDeNumeroATexto(pElementoUno, cadenaUno) &&
		   !eArcade_getTipoDeSonidoDeNumeroATexto(pElementoDos, cadenaDos))
		{
			retorno = IGUALDAD;
			respuesta = strncmp(cadenaUno, cadenaDos, sizeof(cadenaUno));
			if(respuesta > 0)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(respuesta < 0)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief determina si un elemento es mayor que otro por el id
* \param void* pElementoUno - puntero a un arcade
* \param void* pElementoDos - puntero a un segundo arcade
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero o si el puntero es NULL
*/
int eArcade_ordenarPorId(void* pElementoUno, void* pElementoDos)
{
	int numenoUno;
	int numeroDos;
	int retorno = ERROR_PUNTERO_NULL;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!eArcade_getId(pElementoUno, &numenoUno) &&
		   !eArcade_getId(pElementoDos, &numeroDos))
		{
			retorno = IGUALDAD;
			if(numenoUno > numeroDos)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(numeroDos > numenoUno)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief determina si un elemento es mayor que otro por la cantidad de jugadores
* \param void* pElementoUno - puntero a un arcade
* \param void* pElementoDos - puntero a un segundo arcade
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero o si el puntero es NULL
*/
int eArcade_ordenarPorCantidadDeJugadores(void* pElementoUno, void* pElementoDos)
{
	int numeroUno;
	int numeroDos;
	int retorno = ERROR_PUNTERO_NULL;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!eArcade_getCantidadDeJugadores(pElementoUno, &numeroUno) &&
		   !eArcade_getCantidadDeJugadores(pElementoDos, &numeroDos))
		{
			retorno = IGUALDAD;
			if(numeroUno > numeroDos)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(numeroDos > numeroUno)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief determina si un elemento es mayor que otro por la capacidad de fichas
* \param void* pElementoUno - puntero a un arcade
* \param void* pElementoDos - puntero a un segundo arcade
* \return Retorna INT. Retorna 1 si el primer elemento es mayor que el segundo
* 	      retorna 0 si ambos elementos son iguales
* 		  Retorna -1 si el segundo elemento es mayor que el primero o si el puntero es NULL
*/
int eArcade_ordenarPorCapacidadMaximaDeFichas(void* pElementoUno, void* pElementoDos)
{
	int numeroUno;
	int numeroDos;
	int retorno = ERROR_PUNTERO_NULL;
	if(pElementoUno != NULL && pElementoDos != NULL)
	{
		if(!eArcade_getCapacidadMaximaDeFichas(pElementoUno, &numeroUno) &&
		   !eArcade_getCapacidadMaximaDeFichas(pElementoDos, &numeroDos))
		{
			retorno = IGUALDAD;
			if(numeroUno > numeroDos)
			{
				retorno = PRIMERO_ES_MAYOR;
			}
			else
			{
				if(numeroDos > numeroUno)
				{
					retorno = SEGUNDO_ES_MAYOR;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Determina si un elemento cumple o no con la cantidad de jugadores requerida
* \param void* pElemento - puntero a un elemento
* \return Retorna INT. Retorna 0 si el elemento cumple con el criterio
* 		  retorna 1 si NO cumple con el criterio
* 		  Retorna -1 si el puntero es NULL
*/
int eArcade_filtrarCantidadDeJugadores(void* pElemento)
{
	int cantidadJugadores;
	eArcade* pArcade;
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL)
	{
		retorno = NO_CUMPLE_CON_CRITERIO;
		pArcade = (eArcade*) pElemento;
		if(!eArcade_getCantidadDeJugadores(pArcade, &cantidadJugadores) && cantidadJugadores > 1)
		{
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/**
* \brief Setea el campo Fichas de los arcades, asignando un nuevo valor
* \param void* pElemento - puntero a un elemento
* \return Retorna INT. Retorna 0 si el elemento fue correctamente seteado
* 		  Retorna -1 si el puntero es NULL o si ocurrio un error en la operacion
*/
int eArcade_incrementarCapacidadDeFichas(void* pElemento)
{
	int capacidadFichas;
	eArcade* pArcade;
	int retorno = ERROR_PUNTERO_NULL;
	if(pElemento != NULL)
	{
		pArcade = (eArcade*) pElemento;
		if(!eArcade_getCapacidadMaximaDeFichas(pArcade, &capacidadFichas))
		{
			capacidadFichas = capacidadFichas * 2;
			if(!eArcade_setCapacidadMaximaDeFichas(pArcade, capacidadFichas))
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}
