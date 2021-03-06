#include "parser.h"

#define ARCHIVO_VACIO_O_TERMINADO 1
#define LEN_SONIDO 20
#define LEN_ENCABEZADO 100
#define LEN_NOMBRE 51
#define LEN_NOMBRE_ALFANUMERICO 64
#define LEN_INT 10
#define LEN_FLOAT 20
#define OPERACION_EXITOSA 0
#define ERROR_PUNTERO_NULL -1
#define ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS -38
#define ERROR_NO_PUDO_CARGAR_ARCADE_A_LA_LISTA -41
#define ERROR_DATOS_INVALIDOS -43

/** \brief Parsea los datos de los Arcades desde el archivo data.csv (modo texto).
 * \param FILE* pFile - puntero al archivo de texto
 * \param  LinkedList* pLinkedListArcades - puntero a la lista de Arcades
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna 1 si es fin del archivo
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -41 si no se puede cargar Arcade a la lista
 * 				retorna -43 si se detectan datos invalidos
 *
 */
int parser_ArcadeFromText(FILE* pFile, LinkedList* pArrayListArcades)
{
	char idArcade [LEN_INT];
	char tipoDeSonido [LEN_INT];
	char cantidadDeJugadores [LEN_INT];
	char capacidadMaximaDeFichas [LEN_INT];
	char nombreJuego [LEN_NOMBRE_ALFANUMERICO];
	char nombreSalon[LEN_NOMBRE_ALFANUMERICO];
	char nacionalidad[LEN_NOMBRE];
	int retorno = ERROR_PUNTERO_NULL;
	eArcade* pArcade;

	if(pFile != NULL && pArrayListArcades != NULL)
	{
		retorno = ARCHIVO_VACIO_O_TERMINADO;
		if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idArcade, nacionalidad, tipoDeSonido, cantidadDeJugadores, capacidadMaximaDeFichas, nombreSalon, nombreJuego) == 7)
		{
			retorno = ERROR_DATOS_INVALIDOS;
			pArcade = eArcade_newParametrosTexto(idArcade, nombreJuego, nacionalidad, nombreSalon, tipoDeSonido, cantidadDeJugadores, capacidadMaximaDeFichas);
			if(pArcade != NULL)
			{
				retorno = ERROR_NO_PUDO_CARGAR_ARCADE_A_LA_LISTA;
				if(!ll_add(pArrayListArcades, pArcade))
				{
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
    return retorno;
}

/** \brief Parsea los datos desde el archivo txt (modo texto).
 * \param FILE* pFile - puntero al archivo de texto
 * \param  LinkedList* pArrayListAuxiliar - puntero a la lista auxiliar
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna 1 si es fin del archivo
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -41 si no se puede cargar Arcade a la lista
 * 				retorna -43 si se detectan datos invalidos
 */
int parser_AuxiliarFromText(FILE* pFile, LinkedList* pArrayListAuxiliar)
{
	char nombreJuego [LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	eAuxiliar* pAuxiliar;

	if(pFile != NULL && pArrayListAuxiliar != NULL)
	{
		retorno = ARCHIVO_VACIO_O_TERMINADO;
		if(fscanf(pFile,"%[^\n]\n", nombreJuego) == 1)
		{
			retorno = ERROR_DATOS_INVALIDOS;
			pAuxiliar = eAuxiliar_newParametrosTexto(nombreJuego);
			if(pAuxiliar != NULL)
			{
				retorno = ERROR_NO_PUDO_CARGAR_ARCADE_A_LA_LISTA;
				if(!ll_add(pArrayListAuxiliar, pAuxiliar))
				{
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
    return retorno;
}

/** \brief Parsea los datos de los Arcades desde el archivo data.csv (modo binario).
 * \param FILE* pFile - puntero al archivo binario
 * \param  LinkedList* pLinkedListArcades - puntero a la lista de Arcades
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna 1 si es fin del archivo
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 * 				retorna -41 si no se puede cargar Arcade a la lista
 * 				retorna -43 si se detectan datos invalidos
 */
int parser_ArcadeFromBinary(FILE* pFile, LinkedList* pLinkedListArcades)
{
	int id;
	int cantidadJugadores;
	int capacidadMaximaFichas;
	int tipoSonido;
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	char nombreSalon[LEN_NOMBRE_ALFANUMERICO];
	char nacionalidad[LEN_NOMBRE];
	eArcade* pArcade;
	int retorno = ERROR_PUNTERO_NULL;

	if(pFile != NULL && pLinkedListArcades != NULL)
	{
		retorno = ARCHIVO_VACIO_O_TERMINADO;
		if(fread(&id, sizeof(int), 1, pFile) == 1 &&
		   fread(nacionalidad, sizeof(nacionalidad), 1, pFile) == 1 &&
		   fread(&tipoSonido, sizeof(int), 1, pFile) == 1 &&
		   fread(&cantidadJugadores, sizeof(int), 1, pFile) == 1 &&
		   fread(&capacidadMaximaFichas, sizeof(int), 1, pFile) == 1 &&
		   fread(nombreSalon, sizeof(nombreSalon), 1, pFile) == 1 &&
		   fread(nombreJuego, sizeof(nombreJuego), 1, pFile) == 1)
		{
			retorno = ERROR_DATOS_INVALIDOS;
			pArcade = eArcade_newParametrosDiferenciandoTiposDeDatos(id, nombreJuego, nacionalidad, nombreSalon, tipoSonido, cantidadJugadores, capacidadMaximaFichas);
			if(pArcade != NULL)
			{
				retorno = ERROR_NO_PUDO_CARGAR_ARCADE_A_LA_LISTA;
				if(!ll_add(pLinkedListArcades, pArcade))
				{
					retorno = OPERACION_EXITOSA;
				}
			}
		}
	}
    return retorno;
}

/** \brief Carga los datos de un arcade* al archivo de texto.
 * \param FILE* pFile - puntero al archivo de texto
 * \param  void* pElemento - puntero void
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 */
int parser_TextFromArcade(FILE* pFile, void* pElemento)
{
	int idArcade;
	int cantidadJugadores;
	int capacidadMaximaFichas;
	char tipoSonido[LEN_SONIDO];
	char nacionalidad[LEN_NOMBRE];
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	char nombreSalon[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	eArcade* pArcade;

	if(pElemento != NULL && pFile != NULL)
	{
		pArcade = (eArcade*) pElemento;
		retorno = ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS;
		if(!eArcade_gettersFromArcade(pArcade, &idArcade, nombreJuego, nacionalidad, nombreSalon, tipoSonido, &cantidadJugadores, &capacidadMaximaFichas))
		{
			fprintf(pFile,"%d,%s,%s,%d,%d,%s,%s\n",idArcade,nacionalidad, tipoSonido, cantidadJugadores, capacidadMaximaFichas, nombreSalon, nombreJuego);
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/** \brief Carga los datos de un Auxiliar* al archivo de texto.
 * \param FILE* pFile - puntero al archivo de texto
 * \param  void* pElemento - puntero void
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 */
int parser_TextFromAuxiliar(FILE* pFile, void* pElemento)
{
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	eAuxiliar* pAuxiliar;

	if(pElemento != NULL && pFile != NULL)
	{
		pAuxiliar = (eAuxiliar*) pElemento;
		retorno = ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS;
		if(!eAuxiliar_getNombreDeJuego(pAuxiliar, nombreJuego))
		{
			fprintf(pFile,"%s\n",nombreJuego);
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}

/** \brief Carga los datos de un arcade* al archivo Binario.
 * \param FILE* pFile - puntero al archivo de texto
 * \param  void* pElemento - puntero void
 * \return int. Retorna 0 si la Operacion es exitosa
 * 				retorna -1 si el puntero apunta a NULL.
 * 				retorna -38 si no se pudieron obtener todos los datos
 */
int parser_BinaryFromArcade(FILE* pFile, void* pElemento)
{
	int idArcade;
	int tipoSonido;
	int cantidadJugadores;
	int capacidadMaximaDeFichas;
	char nacionalidad[LEN_NOMBRE];
	char nombreSalon[LEN_NOMBRE_ALFANUMERICO];
	char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
	int retorno = ERROR_PUNTERO_NULL;
	eArcade* pArcade;

	if(pElemento != NULL && pFile != NULL)
	{
		pArcade = (eArcade*)pElemento;
		retorno = ERROR_NO_SE_PUDIERON_OBTENER_TODOS_LOS_DATOS;

		if(!eArcade_getCantidadDeJugadores(pArcade, &cantidadJugadores) &&
		   !eArcade_getCapacidadMaximaDeFichas(pArcade, &capacidadMaximaDeFichas) &&
		   !eArcade_getId(pArcade, &idArcade) &&
		   !eArcade_getNacionalidad(pArcade, nacionalidad) &&
		   !eArcade_getNombreDeJuego(pArcade, nombreJuego) &&
		   !eArcade_getNombreDeSalon(pArcade, nombreSalon) &&
		   !eArcade_getTipoDeSonido(pArcade, &tipoSonido))
		{
			if(fwrite(&idArcade, sizeof(int), 1, pFile) == 1 &&
			   fwrite(nacionalidad, sizeof(nacionalidad), 1, pFile) == 1 &&
			   fwrite(&tipoSonido, sizeof(int), 1, pFile) == 1 &&
			   fwrite(&cantidadJugadores, sizeof(int), 1, pFile) == 1 &&
			   fwrite(&capacidadMaximaDeFichas, sizeof(int), 1, pFile) == 1 &&
			   fwrite(nombreSalon, sizeof(nombreSalon), 1, pFile) == 1 &&
			   fwrite(nombreJuego, sizeof(nombreJuego), 1, pFile) == 1)
			{
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}
