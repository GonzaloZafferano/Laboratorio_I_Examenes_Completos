#include "Controller.h"

#define LEN_SONIDO 20
#define LEN_ENCABEZADO 100
#define LEN_NOMBRE 51
#define LEN_NOMBRE_ALFANUMERICO 64
#define VOLVER_ATRAS 2
#define ARCHIVO_VACIO_O_TERMINADO 1
#define MAXIMO_MENU_MOD 3
#define SI 1
#define NO 2
#define LISTA_DESCARTADA 1
#define MAXIMO_MENU_ORDEN 7
#define MOSTRAR_TODOS_LOS_DATOS 2
#define OPERACION_EXITOSA 0
#define ERROR_PUNTERO_NULL -1
#define ERROR_SIN_MAS_REINTENTOS -21
#define ERROR_NO_SE_PUDIERON_TOMAR_TODOS_LOS_DATOS -23
#define ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA -25
#define ERROR_AL_ACTUALIZAR -26
#define ERROR_NO_SE_PUDO_IMPRIMIR_TODO_EL_LISTADO -27
#define ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA -30
#define ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID -32
#define ERROR_NO_SE_DIO_ALTA -34
#define ERROR_AL_ORDENAR -39
#define ERROR_NO_SE_CARGARON_CORRECTAMENTE_LOS_DATOS_EN_ARCHIVO -40
#define ERROR_NO_SE_PUDO_CARGAR_ELEMENTO_A_LA_LISTA -41
#define ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA -42
#define ERROR_EN_CARGA_DE_ARCHIVO -44
#define ERROR_ARCHIVO_TEXTO_NO_EXISTE -45
#define ERROR_ARCHIVO_NO_EXISTE -48
#define ERROR -50
#define SALIR_APLICACION 15
#define ARCHIVO_ARCADE 1
#define ARCHIVO_ARCADE_BINARIO 2
#define ARCHIVO_JUEGOS 3
#define CRITERIO 1
#define OFRECER_CRITERIO 0
#define ORDEN 2
#define DAR_BAJA 1
#define CONFIRMAR_BAJA 2
#define MODIFICAR 1
#define MODIFICAR_CAMPOS 2
#define SALIR 1
#define MOSTRAR_LISTA 1
#define GUARDAR_LISTA 2
#define OBTENER_NUEVO_ULTIMO_ID 2
#define NO_SE_ENCONTRARON_ELEMENTOS 0
#define SE_ENCONTRARON_ELEMENTOS 1
#define MODIFICAR_NOMBRE_JUEGO 1

static int leerArchivo(char* pathArchivo, LinkedList* pLinkedListEnSistema, int tipoArchivo, int* pContadorCargas);
static int evaluarUnificacionDeListas(LinkedList* pLinkedListEnSistema, LinkedList* pListaArchivo, int operacion);
static int agregarElementoDeListaDeArchivoAListaDeSistema(LinkedList* pLinkedListOriginal, LinkedList* pListaArchivo);
static int imprimirListaDeArcades(LinkedList* pLinkedListArcades);
static int cargarListaEnArchivo(char* pathArchivo, LinkedList* pLinkedListEnSistema, int* contadorCargas, int tipoArchivo);
static int guardarListaEnArchivo(char* pathArchivo, LinkedList* pLinkedListEnSistema, int tipoArchivo);
static int descargarArchivo(char* pathArchivo, LinkedList* pLinkedListEnSistema, int tipoArchivo);
static int estaJuegoEnLaLista(LinkedList* pLinkedListAuxiliar, char* pJuego);

/** \brief Lee los datos de un archivo y los carga en una LinkedList
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param LinkedList* pLinkedListEnSistema - puntero a la linked list en sistema
 * \param int tipoArchivo - tipo de archivo que se desea trabajar, (cvs, txt, bin)
 * \param int* contadorCargas - puntero a variable que cuenta la cantidad de cargas realizadas desde el archivo
 * \return int - retorna 0 si opero correctamente o
 *               retorna -1 si el puntero es NULL o
 *               retorna -42 si ocurrio un error en la carga del archivo a la lista o
 *               retorna -48 si el archivo no exite
 */
static int leerArchivo(char* pathArchivo, LinkedList* pLinkedListEnSistema, int tipoArchivo, int* pContadorCargas)
{
	int estadoOperacion;
	FILE* fpArchivo;
	char encabezado[LEN_ENCABEZADO];
	int (*pFuncion)(FILE*, LinkedList*);
	int retorno = ERROR_PUNTERO_NULL;

	if(pathArchivo != NULL && pLinkedListEnSistema != NULL && pContadorCargas != NULL)
	{
		retorno = ERROR_ARCHIVO_NO_EXISTE;

		switch(tipoArchivo)
		{
			case ARCHIVO_ARCADE:
				fpArchivo = fopen(pathArchivo, "r");
				pFuncion = parser_ArcadeFromText;
				break;
			case ARCHIVO_ARCADE_BINARIO:
				fpArchivo = fopen (pathArchivo, "rb");
				pFuncion = parser_ArcadeFromBinary;
				break;
			case ARCHIVO_JUEGOS:
				fpArchivo = fopen (pathArchivo, "r");
				pFuncion = parser_AuxiliarFromText;
				break;
		}

		if(fpArchivo != NULL)
		{
			if(tipoArchivo != ARCHIVO_ARCADE_BINARIO)
			{
				fgets(encabezado, sizeof(encabezado), fpArchivo);
			}

			do
			{
				retorno = OPERACION_EXITOSA;
				estadoOperacion = pFuncion(fpArchivo, pLinkedListEnSistema);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && !estadoOperacion)
				{
					*pContadorCargas = *pContadorCargas +1;
				}
				else
				{
					if(estadoOperacion != ARCHIVO_VACIO_O_TERMINADO)
					{
						retorno = ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA;
						break;
					}
				}
			}while(!feof(fpArchivo));
			fclose(fpArchivo);
		}
	}
	return retorno;
}

/** \brief Evalua si la lista obtenida del archivo puede guardarse en la LinkedList del sistema
 *         o (ante un error) debe consultar con el usuario
 * \param  LinkedList* pLinkedListEnSistema - puntero a la linkedList en sistema
 * \param  LinkedList* pListaArchivo - puntero a la lista con los datos descargados del archivo
 * \return int - retorna 0 si opero correctamente o
 * 				 retorna 1 si decide NO guardar la lista (descarta la lista)
 *               retorna -1 si el puntero es NULL o
 *               retorna -25 si no se obtuvo una respuesta valida del usuario
 */
static int evaluarUnificacionDeListas(LinkedList* pLinkedListEnSistema, LinkedList* pListaArchivo, int operacion)
{
	int respuesta = NO;
	int retorno = ERROR_PUNTERO_NULL;
	int estadoOperacion;
	if(pLinkedListEnSistema != NULL && pListaArchivo != NULL)
	{
		if(operacion == ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA)
		{
			retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
			estadoOperacion = menu_ImprimirMenuGuardarListaArchivo(MOSTRAR_LISTA, &respuesta);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && respuesta == SI)
			{
				imprimirListaDeArcades(pListaArchivo);
			}

			estadoOperacion = menu_ImprimirMenuGuardarListaArchivo(GUARDAR_LISTA, &respuesta);
			if(!utn_comprobarEstadoDeOperacion(estadoOperacion) || respuesta == NO)
			{
				if(!eArcade_liberarListaDeMemoria(pListaArchivo))
				{
					retorno = LISTA_DESCARTADA;
					printf("\n\t\t<--Se descarto la lista descargada del archivo!-->\n");
				}
			}
		}

		if(operacion == OPERACION_EXITOSA || (estadoOperacion == OPERACION_EXITOSA && respuesta == SI))
		{
			estadoOperacion = agregarElementoDeListaDeArchivoAListaDeSistema(pLinkedListEnSistema, pListaArchivo);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				printf("\n\t\t<--Carga completada exitosamente!-->\n");
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/** \brief Carga los elementos que estan en la lista del archivo a la lista del sistema
 * \param  LinkedList* pLinkedListOriginal - puntero a la lista original
 * \param  LinkedList* pListaArchivo - puntero a la lista con los datos descargados del archivo
 * \return int - retorna 0 si opero correctamente o
 *               retorna -1 si el puntero es NULL o
 *               retorna -41 si no se pudo cargar el elemento a la lista
 */
static int agregarElementoDeListaDeArchivoAListaDeSistema(LinkedList* pLinkedListOriginal, LinkedList* pListaArchivo)
{
	int i;
	int len;
	void* pElemento;
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListOriginal != NULL && pListaArchivo != NULL)
	{
		len = ll_len(pListaArchivo);
		if(len >=0)
		{
			for(i = 0; i < len; i++)
			{
				pElemento = ll_get(pListaArchivo, i);
				if(pElemento != NULL)
				{
					retorno = OPERACION_EXITOSA;
					ll_add(pLinkedListOriginal, pElemento);
				}
				else
				{
					retorno = ERROR_NO_SE_PUDO_CARGAR_ELEMENTO_A_LA_LISTA;
					break;
				}
			}
		}
	}
	return retorno;
}

/** \brief imprime la lista de arcades
 * \param LinkedList* pLinkedListArcades - puntero a la lista de arcades
 * \return int 0 si la operacion resulto exitosa
 * 	       retorna -1 si el puntero apunta a NULL
 * 	       retorna -27 si no se pudieron imprimir todos los elementos
 * 	       retorna -30 si no hay elementos en la lista
 */
static int imprimirListaDeArcades(LinkedList* pLinkedListArcades)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListArcades != NULL)
	{
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
		if(!ll_isEmpty(pLinkedListArcades))
		{
			retorno = ERROR_NO_SE_PUDO_IMPRIMIR_TODO_EL_LISTADO;
			printf("\n\t\t<--Lista de Arcades-->");
			eArcade_ImprimirEncabezadoDeDatos(MOSTRAR_TODOS_LOS_DATOS);
			if(ll_map(pLinkedListArcades, eArcade_ImprimirTodosLosDatos) == ll_len(pLinkedListArcades))
			{
					retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/** \brief Guarda los datos de una LinkedList en la ruta y el tipo de archivo especificado.
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pLinkedListEnSistema - puntero a la lista en sistema
 * \param int* contadorCargas - puntero a variable que cuenta la cantidad de cargas realizadas desde la lista al archivo
* \param int tipoArchivo - tipo de archivo que se desea trabajar, texto o binario
 * \return int - Retorna   0 si opero correctamente o
 *   			 retorna  -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
static int cargarListaEnArchivo(char* pathArchivo, LinkedList* pLinkedListEnSistema, int* contadorCargas, int tipoArchivo)
{
	int i;
	int len;
	FILE* fpArchivo;
	void* pElemento;
	int (*pFuncion)(FILE*, void*);
	int retorno = ERROR_PUNTERO_NULL;

	if(pathArchivo != NULL && pLinkedListEnSistema != NULL && contadorCargas != NULL)
	{
		len = ll_len(pLinkedListEnSistema);
		retorno = OPERACION_EXITOSA;
		if(len >= 0)
		{
			switch(tipoArchivo)
			{
				case ARCHIVO_ARCADE:
					fpArchivo = fopen(pathArchivo, "w");
					pFuncion = parser_TextFromArcade;
					break;
				case ARCHIVO_ARCADE_BINARIO:
					fpArchivo = fopen(pathArchivo, "wb");
					pFuncion = parser_BinaryFromArcade;
					break;
				case ARCHIVO_JUEGOS:
					fpArchivo = fopen(pathArchivo, "w");
					pFuncion = parser_TextFromAuxiliar;
					break;
			}

			if(fpArchivo != NULL)
			{
				switch(tipoArchivo)
				{
					case ARCHIVO_ARCADE:
						fprintf(fpArchivo, "id,nacionalidad,tipo_sonido,cant_jug,fichas_max,salon,game\n");
						break;
					case ARCHIVO_JUEGOS:
						fprintf(fpArchivo, "Lista de Juegos\n");
						break;
				}

				for(i = 0; i < len ; i++)
				{
					retorno = ERROR_PUNTERO_NULL;
					pElemento = ll_get(pLinkedListEnSistema, i);
					if(pElemento != NULL)
					{
						retorno = ERROR_EN_CARGA_DE_ARCHIVO;
						if(!pFuncion(fpArchivo, pElemento))
						{
							*contadorCargas = *contadorCargas + 1;
							retorno = OPERACION_EXITOSA;
						}
					}

					if(!utn_comprobarEstadoDeOperacion(retorno))
					{
						retorno = ERROR_NO_SE_CARGARON_CORRECTAMENTE_LOS_DATOS_EN_ARCHIVO;
						break;
					}
				}
				fclose(fpArchivo);
			}
		}
	}
	return retorno;
}

/** \brief Guarda los datos de una linkedList en la ruta de archivo recibida
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pLinkedListEnSistema - puntero a la lista en sistema
 * \param int tipoArchivo - parametro que determina el tipo de archivo (arcade csv, arcade binario, auxiliar txt)
 * \return int - Retorna 0 si opero correctamente o
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
static int guardarListaEnArchivo(char* pathArchivo, LinkedList* pLinkedListEnSistema, int tipoArchivo)
{
	int estadoOperacion;
	int contador = 0;
	int len = ll_len(pLinkedListEnSistema);
	int retorno = ERROR_PUNTERO_NULL;

	if(pathArchivo != NULL && pLinkedListEnSistema != NULL)
	{
		estadoOperacion =  cargarListaEnArchivo(pathArchivo, pLinkedListEnSistema, &contador, tipoArchivo);
		retorno = estadoOperacion;

		if(contador > 0)
		{
			printf("\n\t\t<--Se genero / actualizo el archivo '%s'!-->", pathArchivo);
			printf("\n\t\t<--Se cargaron en el archivo '%s' %d / %d elementos-->\n", pathArchivo, contador, len);
		}
		else
		{
			if(retorno == OPERACION_EXITOSA)
			{
				printf("\n\t<--Se completo el guardado de la lista en el archivo '%s', pero la lista estaba vacia!-->\n", pathArchivo);
			}
		}
	}
	return retorno;
}

/** \brief Descarga los datos de un archivo a una linkedList.
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pLinkedListEnSistema - puntero a la linkedList
 * \param int tipoArchivo - parametro que determina el tipo de archivo (arcade csv, arcade binario, auxiliar txt)
 * \return int - Retorna 0 si opero correctamente o
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
static int descargarArchivo(char* pathArchivo, LinkedList* pLinkedListEnSistema, int tipoArchivo)
{
	int estadoOperacion;
	int contadorCargas = 0;
	LinkedList* pListaArchivo;
	int retorno = ERROR_PUNTERO_NULL;

	if(pathArchivo != NULL && pLinkedListEnSistema != NULL)
	{
		pListaArchivo = ll_newLinkedList();
		if(pListaArchivo != NULL)
		{
			retorno = OPERACION_EXITOSA;
			estadoOperacion = leerArchivo(pathArchivo, pListaArchivo, tipoArchivo, &contadorCargas);
			if(estadoOperacion == ERROR_ARCHIVO_NO_EXISTE || estadoOperacion == ERROR_PUNTERO_NULL)
			{
				retorno = ERROR_ARCHIVO_NO_EXISTE;
			}
			else
			{
				if(estadoOperacion == ERROR_EN_LA_CARGA_DE_ARCHIVO_A_LISTA || estadoOperacion ==  OPERACION_EXITOSA)
				{
					menu_imprimirCantidadCargasDesdeArchivo(contadorCargas, estadoOperacion);
					if(contadorCargas >0)
					{
						estadoOperacion = evaluarUnificacionDeListas(pLinkedListEnSistema, pListaArchivo, estadoOperacion);

						if(estadoOperacion != OPERACION_EXITOSA)
						{
							retorno = NO;
						}
					}
				}
			}
			if(estadoOperacion != LISTA_DESCARTADA)
			{
				ll_deleteLinkedList(pListaArchivo);
			}
		}
	}
    return retorno;
}

/**
* \brief evalua si el juego recibido por parametro se encuentra en la lista o no.
* \param eAuxiliar listaJuegos[] - Lista que contiene datos
* \param int len_eAuxiliar - tam del array
* \param char juego[] - juego que se revisara si esta en la lista
* \return Retorna INT. Retorna 1 si se encontro en la lista por lo menos 1 vez
* 		  retorna  0 si no se encontro en la lista
* 		  Retorna -1 si la direccion de memoria es NULL.
*/
static int estaJuegoEnLaLista(LinkedList* pLinkedListAuxiliar, char* pJuego)
{
	int i;
	eAuxiliar* pElemento;
	char auxiliarJuego[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListAuxiliar != NULL && pJuego != NULL)
	{
		retorno = NO_SE_ENCONTRARON_ELEMENTOS;
		for(i = 0; i < ll_len(pLinkedListAuxiliar); i++)
		{
			pElemento = ll_get(pLinkedListAuxiliar, i);
			if(pElemento != NULL && !eAuxiliar_getNombreDeJuego(pElemento, auxiliarJuego))
			{
				if(!strncmp(auxiliarJuego, pJuego, sizeof(auxiliarJuego)))
				{
					retorno = SE_ENCONTRARON_ELEMENTOS;
					break;
				}
			}
			else
			{
				retorno = ERROR;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Carga los datos de los arcades desde el archivo (modo texto).
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pLinkedListArcades - puntero a la linked list de arcades
 * \return int - retorna 0 si opero correctamente o
 * 				 retorna 1 si cancela la carga
 *               retorna -1 si el puntero es NULL o
 *               retorna -45 si el archivo no exite
 */
int controller_loadFromText(char* pathArchivo, LinkedList* pLinkedListArcades)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pathArchivo != NULL && pLinkedListArcades != NULL)
	{
		retorno = descargarArchivo(pathArchivo, pLinkedListArcades, ARCHIVO_ARCADE);
	}
    return retorno;
}

/** \brief Carga los datos de los arcades desde el archivo bin (modo binario).
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pLinkedListEnSistema - puntero a la LinkedList de arcades
 * \return int - retorna 0 si opero correctamente o
 * 				 retorna 1 si se cancela la carga
 *               retorna -1 si el puntero es NULL o
 *               retorna -47 si el archivo no exite
 */
int controller_loadFromBinary(char* pathArchivo, LinkedList* pLinkedListArcades)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pathArchivo != NULL && pLinkedListArcades != NULL)
	{
		retorno = descargarArchivo(pathArchivo, pLinkedListArcades, ARCHIVO_ARCADE_BINARIO);
	}
    return retorno;
}

/** \brief Carga los datos de los juegos desde el archivo txt.
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pLinkedListJuegos - puntero a la LinkedList de juegos
 * \return int - retorna 0 si opero correctamente o
 * 				 retorna 1 si se cancela la carga
 *               retorna -1 si el puntero es NULL o
 *               retorna -47 si el archivo no exite
 */
int controller_loadJuegosFromTxt(LinkedList* pLinkedListJuegos, char* pathArchivo)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pathArchivo != NULL && pLinkedListJuegos != NULL)
	{
		retorno = descargarArchivo(pathArchivo, pLinkedListJuegos, ARCHIVO_JUEGOS);
	}
    return retorno;
}

/** \brief Controlador para las altas de arcades
 * \param  LinkedList* pLinkedListArcades - puntero a la lista de arcades
 * \param  char* pathArchivo - ruta relativa o absoluta del archivo
 * \return int 0 si la operacion resulto exitosa o
 * 	       retorna  1 si el usuario decide volver atras o
 * 	       retorna -1 si el puntero apunta a NULL o
 * 	       retorna -23 si no se pudieron tomar todos los datos del arcade o
 * 	       retorna -25 si no se obtuvo una respuesta valida del usuario o
 * 	       retorna -34 si no se dio el alta
 */
int controller_addArcade(LinkedList* pLinkedListArcades, char* pathArchivo)
{
	int idArcade;
	int tipoDeSonido;
	int capacidadMaximaFichas;
	int cantidadJugadores;
	char nacionalidad[LEN_NOMBRE];
	char nombreSalon[LEN_NOMBRE_ALFANUMERICO];
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	int opcionElegida;
	int estadoOperacion;
	eArcade* pArcade = NULL;
	int retorno = ERROR_PUNTERO_NULL;

	if(pLinkedListArcades != NULL && pathArchivo != NULL)
	{
		retorno = VOLVER_ATRAS;
		estadoOperacion = menu_ImprimirMenuAltas(&opcionElegida);

		if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
		{
			retorno = ERROR_NO_SE_PUDIERON_TOMAR_TODOS_LOS_DATOS;
			estadoOperacion = eArcade_getDataToAddANewArcade(nombreJuego, nacionalidad, nombreSalon, &tipoDeSonido, &cantidadJugadores, &capacidadMaximaFichas);

			if(!estadoOperacion)
			{
				retorno = ERROR_NO_SE_DIO_ALTA;
				estadoOperacion = eArcade_getLastOrNextId(OBTENER_NUEVO_ULTIMO_ID);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					idArcade = estadoOperacion;
					pArcade = eArcade_newParametrosDiferenciandoTiposDeDatos(idArcade, nombreJuego, nacionalidad, nombreSalon, tipoDeSonido, cantidadJugadores, capacidadMaximaFichas);

					if(pArcade != NULL && !ll_add(pLinkedListArcades, pArcade))
					{
						printf("\n\t\t<--Alta Exitosa!-->");
						eArcade_imprimirUnSoloArcade(pArcade);
						retorno = ERROR_NO_SE_CARGARON_CORRECTAMENTE_LOS_DATOS_EN_ARCHIVO;
						if(!controller_saveAsText(pathArchivo , pLinkedListArcades))
						{
							retorno = OPERACION_EXITOSA;
						}
					}
				}
			}
		}
		else
		{
			if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
			{
				retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
			}
		}
	}
    return retorno;
}

/** \brief Controlador para las modificaciones de un arcade
 * \param  LinkedList* pLinkedListArcades - puntero a la lista de arcades
 * \param  char* pathArchivo - ruta relativa o absoluta del archivo
 * \return int 0 si la operacion resulto exitosa o
 * 	       retorna  1 si el usuario decide volver atras o
 * 	       retorna -1 si el puntero apunta a NULL o
 * 	       retorna -25 si no se obtuvo una respuesta valida del usuario o
 * 	       retorna -30 si no hay elementos en la lista o
 * 	       retorna -32 si el id no fue encontrado o
 */
int controller_editArcade(LinkedList* pLinkedListArcades, char* pathArchivo)
{
	int idElegido;
	int opcionElegida;
	int estadoOperacion;
	eArcade* pArcade;
	LinkedList* pListaJuegos = NULL;
	int retorno = ERROR_PUNTERO_NULL;

	if(pLinkedListArcades != NULL && pathArchivo != NULL)
	{
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
		if(!ll_isEmpty(pLinkedListArcades))
		{
			retorno = VOLVER_ATRAS;
			estadoOperacion = menu_ImprimirMenuModificacion(MODIFICAR, &opcionElegida);

			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
			{
				imprimirListaDeArcades(pLinkedListArcades);
				estadoOperacion = menu_imprimirMenuTomaDeId();

				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion)
				{
					idElegido = estadoOperacion;
					retorno = ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID;
					pArcade = eArcade_findPointerToeArcadeById(pLinkedListArcades, idElegido);

					if(pArcade != NULL)
					{
						retorno = VOLVER_ATRAS;
						printf("\n\t\t<--Arcade a modificar-->");
						eArcade_imprimirUnSoloArcade(pArcade);
						estadoOperacion = menu_ImprimirMenuModificacion(MODIFICAR_CAMPOS, &opcionElegida);

						if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida != MAXIMO_MENU_MOD)
						{
							if(opcionElegida == MODIFICAR_NOMBRE_JUEGO)
							{
								pListaJuegos = generarListaDeJuegosSinRepetir(pLinkedListArcades);
								if(pListaJuegos != NULL)
								{
									printf("\n\t\t<--Lista de juegos cargados en el sistema-->");
									ll_map(pListaJuegos, eAuxiliar_imprimirFilaDeDatos);
									if(!eAuxiliar_liberarListaDeMemoria(pListaJuegos))
									{
										pListaJuegos = NULL;
									}
								}
							}
							estadoOperacion = eArcade_getDataFromUserToEditAFiel(pArcade, opcionElegida);

							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								printf("\n\t\t<--Modificacion Exitosa!-->");
								eArcade_imprimirUnSoloArcade(pArcade);
								if(!controller_saveAsText(pathArchivo , pLinkedListArcades))
								{
									retorno = OPERACION_EXITOSA;
								}
							}
						}
					}
				}
			}

			if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
			{
				retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
			}
		}
	}
    return retorno;
}

/** \brief Controlador que se encarga de operar toda la baja de un arcade
 * \param  LinkedList* pLinkedListArcades - puntero a la lista de arcades
 * \param  char* pathArchivo - ruta relativa o absoluta del archivo
 * \return int 0 si la operacion resulto exitosa o
 * 	       retorna 1 si el usuario decide volver atras o
 * 	       retorna -1 si el puntero apunta a NULL o
 * 	       retorna -25 si no se obtuvo una respuesta valida del usuario o
 * 	       retorna -30 si no hay elementos en la lista o
 * 	       retorna -32 si el id no fue encontrado
 */
int controller_removeArcade(LinkedList* pLinkedListArcades, char* pathArchivo)
{
	int indice;
	int idElegido;
	int estadoOperacion;
	int opcionElegida;
	eArcade* pAuxiliar;
	int retorno = ERROR_PUNTERO_NULL;

	if(pLinkedListArcades != NULL)
	{
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
		if(!ll_isEmpty(pLinkedListArcades))
		{
			retorno = VOLVER_ATRAS;
			estadoOperacion = menu_ImprimirMenuBajas(DAR_BAJA, &opcionElegida);

			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
			{
				imprimirListaDeArcades(pLinkedListArcades);
				estadoOperacion = menu_imprimirMenuTomaDeId();

				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion)
				{
					retorno = ERROR_NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID;
					idElegido = estadoOperacion;
					pAuxiliar =  eArcade_findPointerToeArcadeById(pLinkedListArcades, idElegido);

					if(pAuxiliar != NULL)
					{
						retorno = VOLVER_ATRAS;
						printf("\n\t\t<--Arcade a eliminar-->");
						eArcade_imprimirUnSoloArcade(pAuxiliar);
						estadoOperacion = menu_ImprimirMenuBajas(CONFIRMAR_BAJA, &opcionElegida);

						if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
						{
							indice = ll_indexOf(pLinkedListArcades, pAuxiliar);
							if(indice >= 0 && !ll_remove(pLinkedListArcades, indice))
							{
								printf("\n\t\t<--Eliminacion Exitosa!-->");
								eArcade_delete(pAuxiliar);

								if(ll_isEmpty(pLinkedListArcades))
								{
									printf("\n\t\t<--Ya No hay mas Arcades en la lista!-->");
								}

								if(!controller_saveAsText(pathArchivo , pLinkedListArcades))
								{
									retorno = OPERACION_EXITOSA;
								}
							}
						}
					}
				}
			}

			if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
			{
				retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
			}
		}
	}
    return retorno;
}

/** \brief Controlador que se encarga listar los arcades ordenados por un criterio
 * \param LinkedList* pLinkedListArcades - puntero a la lista de arcades
 * \return int - retorna 0 si la operacion fue exitosa
 *               retorna 2 si el usuario decide volver atras
 *               retorna -1 si el puntero es NULL
 *               retorna -25 si no se obtuvo una respuesta valida del usuario
 *               retorna -27 si no se pudo imprimir
 *               retorna -30 si no hay elementos cargados en la lista
 *               retorna -39 si ocurrio un error al intentar ordenar la lista
 */
int controller_listarArcadesOrdenados(LinkedList* pLinkedListArcades)
{
	int len;
	int estadoOperacion;
	int opcionOrden;
	int respuesta;
	int opcionCriterio = 0;
    int retorno = ERROR_PUNTERO_NULL;

    if(pLinkedListArcades != NULL)
    {
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
    	if(!ll_isEmpty(pLinkedListArcades))
    	{
    		len = ll_len(pLinkedListArcades);
    		if(len > 1)
    		{
				retorno = VOLVER_ATRAS;
				estadoOperacion = menu_ImprimirMenuListarArcades(OFRECER_CRITERIO, &respuesta);
				if(!estadoOperacion && respuesta == SI )
				{
					estadoOperacion = menu_ImprimirMenuListarArcades(CRITERIO, &opcionCriterio);
				}

				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && respuesta != VOLVER_ATRAS && opcionCriterio != MAXIMO_MENU_ORDEN)
				{
					estadoOperacion = menu_ImprimirMenuListarArcades(ORDEN, &opcionOrden);

					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						retorno = ERROR_AL_ORDENAR;
						printf("\n\t\t<--Ordenando lista de Arcades. Esto puede demorar unos instantes...-->");
						switch(opcionCriterio)
						{
							case 0:
								estadoOperacion = ll_sort(pLinkedListArcades, eArcade_ordenarPorNombreDeJuego, opcionOrden);
								break;
							case 1:
								estadoOperacion = ll_sort(pLinkedListArcades, eArcade_ordenarPorId, opcionOrden);
								break;
							case 2:
								estadoOperacion = ll_sort(pLinkedListArcades, eArcade_ordenarPorNacionalidad, opcionOrden);
								break;
							case 3:
								estadoOperacion = ll_sort(pLinkedListArcades, eArcade_ordenarPorNombreDeSalon, opcionOrden);
								break;
							case 4:
								estadoOperacion = ll_sort(pLinkedListArcades, eArcade_ordenarPorTipoDeSonido, opcionOrden);
								break;
							case 5:
								estadoOperacion = ll_sort(pLinkedListArcades, eArcade_ordenarPorCantidadDeJugadores, opcionOrden);
								break;
							case 6:
								estadoOperacion = ll_sort(pLinkedListArcades, eArcade_ordenarPorCapacidadMaximaDeFichas, opcionOrden);
								break;
						}

					}
				}
				if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
				{
					retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
				}
    		}
    		if(len == 1 || (respuesta != VOLVER_ATRAS  && !estadoOperacion && opcionCriterio != MAXIMO_MENU_ORDEN))
    		{
    			retorno = imprimirListaDeArcades(pLinkedListArcades);
    		}
    	}
    }
    return retorno;
}

/**
* \brief Obtiene una lista sin repetir de los juegos cargados hasta el momento en el sistema.
* \param LinkedList* pLinkedListArcades - Linked list de arcades que contiene todos los datos
* \return Retorna LinkedList*. Retorna una direccion de memoria si opero correctamente
* 		  retorna NULL si ocurrio un error.
*/
LinkedList* generarListaDeJuegosSinRepetir(LinkedList* pLinkedListArcades)
{
	int i;
	int banderaExito = 0;
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	eArcade* pElemento;
	eAuxiliar* pElementoAuxiliar;
	LinkedList* pListaJuegos = NULL;
	if(pLinkedListArcades != NULL)
	{
		pListaJuegos = ll_newLinkedList();
		if(pListaJuegos != NULL && ll_len(pLinkedListArcades)>0)
		{
			for(i = 0; i < ll_len(pLinkedListArcades); i++)
			{
				banderaExito = 0;
				pElemento = ll_get(pLinkedListArcades, i);
				if(pElemento != NULL && !eArcade_getNombreDeJuego(pElemento, nombreJuego))
				{
					banderaExito = 1;
					if(!estaJuegoEnLaLista(pListaJuegos, nombreJuego))
					{
						pElementoAuxiliar = eAuxiliar_newParametrosTexto(nombreJuego);
						if(pElementoAuxiliar != NULL)
						{
							ll_add(pListaJuegos, pElementoAuxiliar);
						}
					}
				}
				if(!banderaExito)
				{
					eAuxiliar_liberarListaDeMemoria(pListaJuegos);
					pListaJuegos = NULL;
					break;
				}
			}
		}
	}
	return pListaJuegos;
}

/** \brief Controlador que se encarga de iniciar el proceso de guardado de la lista de los arcades en la ruta de archivo (modo texto).
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pLinkedListArcades - puntero a la lista de arcades
 * \return int - Retorna el estado recibido de la carga del archivo
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
int controller_saveAsText(char* pathArchivo , LinkedList* pLinkedListArcades)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pathArchivo != NULL && pLinkedListArcades != NULL)
	{
		retorno = guardarListaEnArchivo(pathArchivo, pLinkedListArcades, ARCHIVO_ARCADE);
	}
    return retorno;
}

/** \brief Controlador que se encarga de iniciar el proceso de guardado de la lista de los arcades en la ruta del archivo (modo binario).
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \param  LinkedList* pLinkedListArcades - puntero a la lista de arcades
 * \return int - Retorna 0 si opero correctamente o
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
int controller_saveAsBinary(char* pathArchivo, LinkedList* pLinkedListArcades)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pathArchivo != NULL && pLinkedListArcades != NULL)
	{
		retorno = guardarListaEnArchivo(pathArchivo, pLinkedListArcades, ARCHIVO_ARCADE_BINARIO);
	}
    return retorno;
}

/**
* \brief Genera un archivo de texto listando solo los juegos, sin repetir, uno por fila.
* \param LinkedList* pLinkedListArcades - Linked list de arcades que contiene todos los datos
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \return int - Retorna 0 si opero correctamente o
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -30 si no hay elementos en la lista
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
int controller_generarArchivoDeJuegos(LinkedList* pLinkedListArcades, char* pathArchivoJuegos)
{
	LinkedList* pLinkedListAuxiliar;
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListArcades != NULL && pathArchivoJuegos != NULL)
	{
		retorno = NO;
		if(!ll_isEmpty(pLinkedListArcades) || menu_cargarListaJuegosVacia() == SI)
		{
			pLinkedListAuxiliar = generarListaDeJuegosSinRepetir(pLinkedListArcades);
			if(pLinkedListAuxiliar != NULL)
			{
				retorno = guardarListaEnArchivo(pathArchivoJuegos, pLinkedListAuxiliar, ARCHIVO_JUEGOS);
				eAuxiliar_liberarListaDeMemoria(pLinkedListAuxiliar);
			}
		}
	}
	return retorno;
}

/** \brief Controlador que se encarga de generar un archivo con arcades multijugador
 * \param LinkedList* pListaArcades - puntero a la lista de arcades
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \return int - Retorna 0 si opero correctamente o
 * 				 retorna 2 si el usuario decide no guardar la lista
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -30 si no hay elementos en la lista
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
int controller_generarArchivoConArcadesMultijugador(LinkedList* pListaArcades, char* pathArchivo)
{
	int retorno = ERROR_PUNTERO_NULL;
	LinkedList* pLinkedListArcadesMultijugador;
	if(pListaArcades != NULL && pathArchivo != NULL)
	{
		retorno = OPERACION_EXITOSA;
		if(ll_len(pListaArcades)>=0)
		{
			pLinkedListArcadesMultijugador = ll_filterSinAlterarListaOriginal(pListaArcades, eArcade_filtrarCantidadDeJugadores);
			if(pLinkedListArcadesMultijugador != NULL)
			{
				retorno = NO;
				if(!ll_isEmpty(pLinkedListArcadesMultijugador) || menu_cargarListaMultijugadorVacia() == SI)
				{
					retorno = guardarListaEnArchivo(pathArchivo, pLinkedListArcadesMultijugador, ARCHIVO_ARCADE);
				}
				ll_deleteLinkedList(pLinkedListArcadesMultijugador);
			}
		}
	}
	return retorno;
}

/** \brief Controlador que se encarga de actualizar la capacidad de fichas de los arcades,
 * 		   y actualizar el archivo de arcades con la modificacion
 * \param LinkedList* pListaArcades - puntero a la lista de arcades
 * \param char* pathArchivo - Ruta absoluta o relativa del archivo
 * \return int - Retorna 0 si opero correctamente o
 *   			 retorna -1 si el puntero es NULL
 *   			 retorna -30 si no hay elementos cargados en la lista
 *   			 retorna -40 si no se cargaron correctamente todos los datos en el archivo
 *   			 retorna -44 si hay un error en la carga del archivo
 */
int controller_actualizarCantidadDeFichas(LinkedList* pLinkedListArcade, char* pathArchivo)
{
	int estadoOperacion;
	int cantidadDeActualizaciones;
	int respuesta = NO;
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListArcade != NULL && pathArchivo != NULL)
	{
		retorno = ERROR_NO_HAY_ELEMENTOS_CARGADOS_EN_LA_LISTA;
		if(ll_len(pLinkedListArcade) >= 0)
		{
			retorno = OPERACION_EXITOSA;
			cantidadDeActualizaciones = ll_map(pLinkedListArcade, eArcade_incrementarCapacidadDeFichas);
			if(cantidadDeActualizaciones > 0 && cantidadDeActualizaciones != ll_len(pLinkedListArcade))
			{
				printf("\n\t\t<--Un momento! Solo se pudieron actualizar %d / %d arcades!-->", cantidadDeActualizaciones, ll_len(pLinkedListArcade));
				printf("\n\t\t<--Hay %d arcades que estan proximos al limite de fichas-->\n\t\t<--Por lo que no se puede duplicar su cantidad de fichas!!-->", ll_len(pLinkedListArcade) - cantidadDeActualizaciones);
				estadoOperacion = menu_ImprimirMenuActualizacionArchivo(&respuesta);
			}
			else
			{
				if(cantidadDeActualizaciones < 0)
				{
					retorno = ERROR_AL_ACTUALIZAR;
				}
			}

			if(cantidadDeActualizaciones == ll_len(pLinkedListArcade) || (utn_comprobarEstadoDeOperacion(estadoOperacion) && respuesta == SI))
			{
				retorno = guardarListaEnArchivo(pathArchivo, pLinkedListArcade, ARCHIVO_ARCADE);
				if(!retorno)
				{
					printf("\n\t\t<--Se duplico la cantidad de fichas de %d arcades!-->\n", cantidadDeActualizaciones);
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Controlador que evalua el estado de los archivos antes de salir de la aplicacion
* \param LinkedList* pLinkedListArcades - Linked list de arcades que contiene todos los datos
* \param char* pathArchivoJuegos - Ruta absoluta o relativa del archivo de juegos
* \param char* pathArchivoMultijugador - Ruta absoluta o relativa del archivo multijugador
* \param int banderaArchivoJuegos - bandera que contiene el estado actual de carga del archivo de juegos
* \param int banderaArchivoMultijugador - bandera que contiene el estado actual de carga del archivo multijugador
* \return int - retorna 15 si el usuario decide Salir de la aplicacion
*               retorna 1 si el usuario decide volver atras
*               Retorna -1 si el puntero es NULL
*               retorna -25 si el usuario no ingresa una respuesta valida
*/
int controller_exitApp(LinkedList* pLinkedListArcades, char* pathArchivoJuegos, char* pathArchivoMultijugador, int banderaArchivoJuegos, int banderaArchivoMultijugador)
{
	int estadoCarga;
	int estadoOperacion;
	int opcionElegida;
	int retorno = ERROR_PUNTERO_NULL;

	if(pLinkedListArcades != NULL && pathArchivoJuegos != NULL && pathArchivoMultijugador != NULL)
	{
		retorno = VOLVER_ATRAS;
		estadoOperacion = menu_ImprimirMenuSalir(SALIR, &opcionElegida);
		if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
		{
			if(!banderaArchivoJuegos || !banderaArchivoMultijugador)
			{
				estadoCarga = menu_VerificarCargasDeArchivosParaSalir(banderaArchivoJuegos, banderaArchivoMultijugador);
				estadoOperacion = menu_ImprimirMenuSalir(estadoCarga, &opcionElegida);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == SI)
				{
					switch(estadoCarga)
					{
						case 2:
							controller_generarArchivoConArcadesMultijugador(pLinkedListArcades, pathArchivoMultijugador);
							break;
						case 3:
							controller_generarArchivoDeJuegos(pLinkedListArcades, pathArchivoJuegos);
							break;
						case 4:
							controller_generarArchivoDeJuegos(pLinkedListArcades, pathArchivoJuegos);
							controller_generarArchivoConArcadesMultijugador(pLinkedListArcades, pathArchivoMultijugador);
							break;
					}
				}
			}
			if(!estadoOperacion)
			{
				retorno = SALIR_APLICACION;
			}
		}
		if(estadoOperacion == ERROR_SIN_MAS_REINTENTOS)
		{
			retorno = ERROR_NO_SE_OBTUVO_RESPUESTA_VALIDA;
		}
	}
	return retorno;
}

/**
* \brief Controlador que evalua si un archivo existe o no
* \param char* pathArchivo - Ruta absoluta o relativa del archivo
* \return int - retorna 0 si el archivo existe
*               retorna -1 si el puntero es null o el archivo no existe
*/
int controller_existeArchivo(char* pathArchivo)
{
	FILE* fpArchivo;
	int retorno = ERROR_PUNTERO_NULL;
	fpArchivo = fopen(pathArchivo, "r");
	if(fpArchivo != NULL)
	{
		retorno = OPERACION_EXITOSA;
		fclose(fpArchivo);
	}
	return retorno;
}

/**
* \brief imprime una lista de elementos, sin repetir.
* \param LinkedList* pLinkedListElementos - linkedList de arcades
* \return Retorna INT. Retorna 0 si la operacion fue exitosa
* 		  Retorna -1 si la direccion de memoria es NULL.
*//*
int controller_imprimirListaJuegosSinRepetir(LinkedList* pLinkedListElementos)
{
	int i;
	int j;
	int banderaHayIgualdad;
	eArcade* pArcadeUno;
	eArcade* pArcadeDos;
	char nombreJuegoUno[LEN_NOMBRE_ALFANUMERICO];
	char nombreJuegoDos[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListElementos != NULL)
	{
		retorno = OPERACION_EXITOSA;
		for(i = 0; i < ll_len(pLinkedListElementos); i++)
		{
			pArcadeUno = (eArcade*)ll_get(pLinkedListElementos, i);
			if(pArcadeUno != NULL)
			{
				if(!eArcade_getNombreDeJuego(pArcadeUno, nombreJuegoUno))
				{
					banderaHayIgualdad = NO_SE_ENCONTRARON_ELEMENTOS;
					for(j = 0; j < i ; j++)
					{
						pArcadeDos = (eArcade*)ll_get(pLinkedListElementos, j);
						if(pArcadeDos != NULL)
						{
							if(!eArcade_getNombreDeJuego(pArcadeDos, nombreJuegoDos))
							{
								if(strncmp(nombreJuegoUno, nombreJuegoDos, sizeof(nombreJuegoUno)) == 0)
								{
									banderaHayIgualdad = SE_ENCONTRARON_ELEMENTOS;
									break;
								}
							}
						}
					}
					if(banderaHayIgualdad == NO_SE_ENCONTRARON_ELEMENTOS)
					{
						printf("\n%s", nombreJuegoUno);
					}
				}
			}
		}
	}
	return retorno;
}
*/
/**
* \brief imprime una lista de elementos, sin repetir.
* \param LinkedList* pLinkedListElementos - linkedList de arcades
* \param char* pathArchivo - Ruta absoluta o relativa del archivo de juegos
* \return Retorna INT. Retorna 0 si la operacion fue exitosa
* 		  Retorna -1 si la direccion de memoria es NULL.
*//*
int controller_cargarArchivoConListaJuegosSinRepetir(LinkedList* pLinkedListElementos, char* pathArchivo)
{
	int i;
	int j;
	int banderaHayIgualdad;
	eArcade* pArcadeUno;
	eArcade* pArcadeDos;
	FILE* fpArchivo;
	char nombreJuegoUno[LEN_NOMBRE_ALFANUMERICO];
	char nombreJuegoDos[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	if(pLinkedListElementos != NULL && pathArchivo != NULL)
	{
		fpArchivo = fopen(pathArchivo, "w");
		if(fpArchivo != NULL)
		{
			fprintf(fpArchivo, "Lista de Juegos\n");
			retorno = OPERACION_EXITOSA;
			for(i = 0; i < ll_len(pLinkedListElementos); i++)
			{

				pArcadeUno = (eArcade*)ll_get(pLinkedListElementos, i);
				if(pArcadeUno != NULL)
				{
					if(!eArcade_getNombreDeJuego(pArcadeUno, nombreJuegoUno))
					{
						banderaHayIgualdad = NO_SE_ENCONTRARON_ELEMENTOS;
						for(j = 0; j < i ; j++)
						{
							pArcadeDos = (eArcade*)ll_get(pLinkedListElementos, j);
							if(pArcadeDos != NULL)
							{
								if(!eArcade_getNombreDeJuego(pArcadeDos, nombreJuegoDos))
								{
									if(strncmp(nombreJuegoUno, nombreJuegoDos, sizeof(nombreJuegoUno)) == 0)
									{
										banderaHayIgualdad = SE_ENCONTRARON_ELEMENTOS;
										break;
									}
								}
							}
						}
						if(banderaHayIgualdad == NO_SE_ENCONTRARON_ELEMENTOS)
						{
							fprintf(fpArchivo,"%s\n", nombreJuegoUno);
						}
					}
				}
			}
			fclose(fpArchivo);
		}
	}
	return retorno;
}
*/
