/*
 * Salon.c
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#include "Salon.h"

#define VACIO 1
#define OCUPADO 0
#define ORDENADO 1
#define DESORDENADO 0
#define ORDEN_ASCENDENTE 1
#define LEN_MAXIMO_SALON 100
#define SHOPPING 1
#define LOCAL 2
#define LEN_TEXTO 15
#define MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO 1
#define MOSTRAR_ID_DISPONIBLES 2
#define REINTENTOS 2
#define HAY_ELEMENTOS 1
#define OPERACION_EXITOSA 0
#define NO_HAY_ELEMENTOS 0
#define PUNTERO_NULL -1
#define LEN_INVALIDO -2
#define ID_INVALIDO -11
#define NO_HAY_ELEMENTOS_CARGADOS_CON_ESE_ID -12
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
#define LEN_STRING 51
#define HAY_ELEMENTOS_ESALON 2
#define NO_HAY_ELEMENTOS_ESALON 0
#define NO_HAY_ELEMENTOS_EARCADE 1

static int eSalon_generadorDeIds(void);
static int eSalon_swapElementos(eSalon lista[], int i, int j);

/**
 * \brief Imprime los encabezados de la tabla de datos.
* \param int opcion - Indica el encabezado que se quiere imprimir
* \param VOID -
* \return VOID
*/
void eSalon_imprimirEncabezadoDeTabla(int opcion)
{
	switch(opcion)
	{
		case 1:
			printf("\n%5s  %-25s   %-28s   %-13s", "Id", "Nombre de Salon", "Direccion de Salon","Tipo de Salon");
			break;
		case 2:
			printf("\n%5s  %-25s   %-28s", "Id", "Nombre de Salon", "Direccion de Salon");
			break;
		case 3:
			printf("\n%5s  %15s   %28s   %23s","-" ,"-" ,"-","-");
			break;
		case 4:
			printf("\n%5s  %15s   %28s","-" ,"-" ,"-");
			break;
	}
}

/** \brief Imprime los datos de un elemento, el cual ya fue validado previamente.
* \param eSalon elemento - Elemento cuyos datos se quieren imprimir
* \param int opcion - Indica la informacion que se quiere imprimir del elemento
* \return VOID
*/
void eSalon_imprimirFilaDelElemento(eSalon elemento, int opcion)
{
	char mensaje[LEN_TEXTO];

	if(eSalon_convertirTipoATexto(elemento, mensaje, LEN_TEXTO)==0)
	{
		switch(opcion)
		{
			case 1:
				printf("\n%5d  %-25.25s   %-28.28s   %-12s", elemento.id, elemento.nombre, elemento.direccion, mensaje);
				break;
			case 2:
				printf("\n%5d  %-25.25s   %-50.50s", elemento.id, elemento.nombre, elemento.direccion);
				break;
		}
	}
}

/** \brief Escribe en un array de char el texto que representa al tipo numerico del salon.
* \param eSalon salon - Elemento de tipo salon
* \param char pTexto[] - array de chars donde se escribira la representacion Textual del tipo numerico
* \param int lenTexto - largo del array de char
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*         retorna -26 si el salon recibido esta marcado como vacio
*/
int eSalon_convertirTipoATexto(eSalon salon, char pTexto[], int lenTexto)
{
	int retorno = PUNTERO_NULL;
	if(pTexto != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenTexto > 0 && lenTexto <= LEN_TEXTO)
		{
			retorno = ELEMENTO_VACIO;
			if(salon.isEmpty == OCUPADO)
			{
				switch(salon.tipoSalon)
				{
					case SHOPPING:
						strncpy(pTexto,"Shopping", lenTexto);
						break;
					case LOCAL:
						strncpy(pTexto,"Local", lenTexto);
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
static int eSalon_generadorDeIds(void)
{
	static int id = 0;
	id++;
	return id;
}





/**
* \brief Inicializa la bandera 'IsEmpty' en 1 en todas las posiciones,
*          indicando que todas las posiciones del array estan vacias.
* \param eSalon lista[] - lista que contiene los datos
* \param int len - largo del Array
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*/
int eSalon_inicializarBanderas(eSalon lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_SALON)
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
* \param eSalon lista[] - lista que contiene los datos
* \param int len - largo del Array
* \return Retorna INT. 1 si hay elementos.
* 		  Retorna  0 Si no hay elementos.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int eSalon_verificarSiHayElementos(eSalon lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= LEN_MAXIMO_SALON)
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
* \param eSalon lista[] - lista que contiene los datos
* \param int len - largo del array
* \return Retorna INT. 0 o un numero positivo, que es el indice libre encontrado
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*          retorno -21 si todos los espacios estan ocupados.
*/
int eSalon_buscarIndiceLibre(eSalon lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0  && len <= LEN_MAXIMO_SALON)
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
* \param eSalon lista[] - lista que contiene los datos
* \param int len - largo del array
* \param int Id - Id del elementos que se desea encontrar
* \return Retorna INT. Retorna el indice del elemento, si lo encuentra
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  Retorna -11 si el ID es invalido (fuera de rango)
* 		  retorna -12 si el Id es valido, pero no tiene ningun elemento cargado.
*/
int eSalon_encontrarElementoPorId(eSalon lista[], int len,int id)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_SALON)
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
* \brief Elimina a un elemento por su Id (se setea la bandera "isEmpty" en 1)
* \param eSalon lista[] - Lista que contiene datos
* \param int len - largo del array
* \param int id - Id del elemento que se eliminara
* \return Retorna INT. Retorna 0 si la eliminacion fue exitosa.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  Retorna -11 si el ID es invalido
* 		  retorna -19 si no se aplicaron bajas en el sistema (porque el ID no existe o ya esta de baja).
*/
int eSalon_eliminarElementoPorId(eSalon lista[], int len, int id)
{
	int indiceRecibido;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_SALON)
		{
			retorno = ID_INVALIDO;
			if(id > 0)
			{
				retorno = NO_SE_APLICARON_BAJAS;
				indiceRecibido = eSalon_encontrarElementoPorId(lista, len, id);
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
* \brief Elimina a un elemento por su Indice (se setea la bandera "isEmpty" en 1)
* \param eSalon lista[] - Lista que contiene datos
* \param int indice - Indice del elemento que se eliminara
* \return Retorna INT. Retorna 0 si la eliminacion fue exitosa.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  Retorna -11 si el ID es invalido
* 		  retorna -19 si no se aplicaron bajas en el sistema (porque el Indice no existe o ya esta de baja).
*/
int eSalon_eliminarElementoPorIndice(eSalon lista[], int indice)
{
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = ID_INVALIDO;
		if(indice >= 0 && indice < LEN_MAXIMO_SALON)
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
* \brief Imprime los ID de una lista recibida
* \param eSalon lista[] - lista que contiene datos
* \param int len - largo del array
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int eSalon_imprimirIdsDisponibles(eSalon lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista!= NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0 && len <= LEN_MAXIMO_SALON)
		{
			retorno = OPERACION_EXITOSA;
			printf("\n\t\t<--Lista de salones disponibles-->");
			eSalon_imprimirEncabezadoDeTabla(MOSTRAR_ID_DISPONIBLES);
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					eSalon_imprimirFilaDelElemento(lista[i], MOSTRAR_ID_DISPONIBLES);
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Imprime el contenido de un solo elemento recibido por parametro
* \param eSalon elemento - elemento para imprimir
* \return INT. 0 Si pudo operar correctamente
* 			 -20 si el elemento esta vacio o de baja.
*/
int eSalon_imprimirUnElementoCompleto(eSalon elemento)
{
	int retorno = NO_SE_ENCONTRARON_DATOS_ASOCIADOS_AL_ID_INDICADO;

	if(elemento.isEmpty == OCUPADO)
	{
		printf("\n\t\t<--Datos asociados al Salon '%s' de ID < %d >-->", elemento.nombre, elemento.id);
		eSalon_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
		eSalon_imprimirFilaDelElemento(elemento, MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief Imprime los datos de todos los elementos que esten habilitados de un array.
* \param eSalon lista[] - lista de elementos
* \param int len - largo del array
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int eSalon_imprimirTodosLosElementos(eSalon lista[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_SALON)
		{
			retorno = OPERACION_EXITOSA;

			printf("\n\t\t<--Mostrando lista de los salones-->");
			eSalon_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					eSalon_imprimirFilaDelElemento(lista[i], MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Ordena los elementos del array segun el criterio recibido (ascendente o descendente)
* \param eSalon lista[] - Lista de elementos
* \param int len - largo del array
* \param int orden - [1] Orden Ascendente - [0] orden Descendente
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -2 si el largo del array es invalido
*/
int eSalon_ordenarElementos(eSalon lista[], int len, int orden)
{
	int retornoCadena;
	int banderaOrdenado;
	int i = 0;
	int limite = len;
	int retorno = PUNTERO_NULL;
	int largoCadena = LEN_STRING;

	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_MAXIMO_SALON)
		{
			retorno = OPERACION_EXITOSA;
			do
			{
				banderaOrdenado = ORDENADO; //Asumimos que esta todo ordenado
				limite = limite - 1; //VOY REDUCIENDO EL LIMITE EN CADA VUELTA, asi no toma la ultima posicion que YA TIENE EL MAYOR O MENOR

				for(i = 0; i < limite; i++)
				{
					retornoCadena = strncmp(lista[i].direccion, lista[i+1].direccion, largoCadena);

					if(orden == ORDEN_ASCENDENTE)
					{
						if((retornoCadena > 0) || (retornoCadena == 0 && (lista[i].tipoSalon > lista[i+1].tipoSalon)))
						{
							banderaOrdenado = eSalon_swapElementos(lista, i, i+1);//Si el swap opera, quiere decir que esta desordenado
							utn_comprobarEstadoDeOperacion(banderaOrdenado);
						}
					}
					else
					{
						if((retornoCadena < 0) || (retornoCadena == 0 && (lista[i].tipoSalon < lista[i+1].tipoSalon)))
						{
							banderaOrdenado = eSalon_swapElementos(lista, i, i+1);//Si el swap opera, quiere decir que esta desordenado
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
* \param eSalon lista[] - Lista de elementos
* \param int i - Indice en el array, del elemento A
* \param int i - Indice en el array, del elemento B
* \return INT. 0 Si pudo operar correctamente
* 			  -1 si la direccion de memoria del array es NULL
* 			  -13 si el parametro i no es distinto del parametro j.
* 			  -23 si el indice de i o j estan fuera del rango.
*/
static int eSalon_swapElementos(eSalon lista[], int i, int j)
{
	int retorno = PUNTERO_NULL;
	eSalon auxiliar;

	if(lista != NULL)
	{
		retorno = I_O_J_ESTA_FUERA_DE_RANGO;
		if((i >= 0 && i < LEN_MAXIMO_SALON) && (j >= 0 && j < LEN_MAXIMO_SALON))// i y j son indices, por eso van de 0 a < maximo
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
* \param eSalon* pAuxiliar - auxiliar donde se cargara el dato
* \param int opcion - opcion que indica el dato que se tomara
* \return Retorna INT. 0 Si se opero correctamente,
*         retorna -14 si no se pudieron tomar los datos correctamente.
*/
int eSalon_campoAModificar(eSalon* pAuxiliar, int opcion)
{
	int estadoOperacion;
	int retorno = NO_SE_CARGARON_TODOS_LOS_CAMPOS;
	switch(opcion)
	{
		case 1:
			estadoOperacion = utn_getNombreOApellido(pAuxiliar->nombre, LEN_STRING, "Ingrese el nuevo nombre del salon", "Dato invalido!", REINTENTOS);
			break;
		case 2:
			estadoOperacion = utn_getDireccion(pAuxiliar->direccion, LEN_STRING, "Ingrese la nueva direccion del salon", "Dato invalido!", REINTENTOS);
			break;
		case 3:
			estadoOperacion = utn_getInt(&pAuxiliar->tipoSalon, "Ingrese el nuevo tipo de Salon de salon:\n\t1 >>Shopping\n\t2 >>Local", "Error, dato invalido!", SHOPPING, LOCAL, REINTENTOS);
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
* \param eSalon* elemento - referencia del elemento que se modificara
* \param int opcion - Opcion que indica que campo se modificara.
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -15 si no se pudo realizar la modificacion del salon.
*/
int eSalon_modificarElemento(eSalon* elemento, int opcion)
{
	eSalon auxiliar;
	int estadoOperacion;
	int retorno = PUNTERO_NULL;

	if(elemento != NULL)
	{
		estadoOperacion = eSalon_campoAModificar(&auxiliar, opcion);
		if(utn_comprobarEstadoDeOperacion(estadoOperacion))
		{
			switch(opcion)
			{
				case 1:
					strncpy(elemento->nombre, auxiliar.nombre, LEN_STRING);
					break;
				case 2:
					strncpy(elemento->direccion, auxiliar.direccion, LEN_STRING);
					break;
				case 3:
					elemento->tipoSalon = auxiliar.tipoSalon;
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
 * 			la funcion eSalon_altaElemento() quien se encargara de cargarlo en el sistema.
* \param eSalon lista[] - lista de elementos
* \param int indiceLibre - indice libre donde se puede cargar datos
* \param int idMaximo - puntero a variable donde se cargara el ultimo Id
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -14 si no se pudieron cargar correctamente todos los campos.
*          retorna -17 si el indice esta fuera de rango
*/
int eSalon_tomarDatos(eSalon lista[], int indiceLibre, int* idMaximo)
{
	eSalon auxiliar;
	int estadoOperacion;
	int iDGenerado;
	int retorno = PUNTERO_NULL;

	if(lista != NULL && idMaximo != NULL)
	{
		retorno = INDICE_FUERA_DE_RANGO;
		if(indiceLibre >= 0 && indiceLibre < LEN_MAXIMO_SALON)
		{
			retorno = NO_SE_CARGARON_TODOS_LOS_CAMPOS;
			estadoOperacion = utn_getNombreOApellido(auxiliar.nombre, LEN_STRING, "Ingrese el nombre del salon", "Error, dato invalido!", REINTENTOS);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				estadoOperacion = utn_getDireccion(auxiliar.direccion, LEN_STRING, "Ingrese la direccion del salon", "Error, dato invalido!", REINTENTOS);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					estadoOperacion = utn_getInt(&auxiliar.tipoSalon, "Ingrese el tipo de salon de salon:\n\t1 >>Shopping\n\t2 >>Local", "Error, dato invalido!", SHOPPING, LOCAL, REINTENTOS);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						iDGenerado = eSalon_generadorDeIds();
						*idMaximo = iDGenerado;
						estadoOperacion = eSalon_altaElemento(lista, indiceLibre, iDGenerado, auxiliar.nombre, auxiliar.direccion, auxiliar.tipoSalon);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							retorno = OPERACION_EXITOSA;
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
* \param eSalon lista[] - lista que contiene elementos
* \param int indiceLibre - Indice libre donde se cargara la informacion del elemento
* \param int id - id del elemento
* \param char nombre[] - Nombre del elemento
* \param char direccion[] - Apellido del elemento
* \param int tipoSalon - tipoSalon del elemento
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -11 si el ID es invalido
*          retorna -17 si el indice esta fuera de rango
*/
int eSalon_altaElemento(eSalon lista[], int indiceLibre, int id, char nombre[],char direccion[], int tipoSalon)
{
	int retorno = PUNTERO_NULL;

	if(lista != NULL && nombre != NULL && direccion != NULL)
	{
		retorno = ID_INVALIDO;
		if(id > 0 )
		{
			retorno = INDICE_FUERA_DE_RANGO;
			if(indiceLibre >= 0 && indiceLibre < LEN_MAXIMO_SALON)
			{
				lista[indiceLibre].id = id;
				lista[indiceLibre].tipoSalon = tipoSalon;
				strncpy(lista[indiceLibre].nombre, nombre, LEN_STRING);
				strncpy(lista[indiceLibre].direccion, direccion, LEN_STRING);
				lista[indiceLibre].isEmpty = OCUPADO;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Fuerza el alta de un elemento
* \param eSalon lista[] - Lista que contiene datos
* \param int len - tam del array
* \param int indice - indice donde se dara el alta
* \param int* idMaximo - puntero a variable donde se guardara el ultimo Id
* \param char* nombre - puntero a variable nombre
* \param char* direccion - puntero a variable direccion
* \param int tipoSalon - tipoSalon
* \param int* bandera_eSalon_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \param int* bandera_eArcade_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \return Retorna INT. Retorna 1 si se encontro por lo menos un elemento para imprimir
* 		  retorna  0 si OK
* 		  Retorna -1 si puntero apunta a direccion NULL.
* 		  retorna -2 si el len es invalido
*/
int eSalon_forzarAltas(eSalon lista[], int len,int indice, int* idMaximo,  char* nombre, char* direccion, int tipoSalon, int* bandera_eSalon_hayElementos, int* bandera_eArcade_hayElementos)
{
	int retorno = PUNTERO_NULL;
	if(lista != NULL && idMaximo != NULL && direccion != NULL && nombre!= NULL && bandera_eArcade_hayElementos != NULL && bandera_eSalon_hayElementos != NULL)
	{
		retorno = LEN_INVALIDO;
		if( len >0)
		{
			strncpy(lista[indice].nombre, nombre, 40);
			strncpy(lista[indice].direccion, direccion, 40);
			lista[indice].tipoSalon = tipoSalon;
			*idMaximo = eSalon_generadorDeIds();
			lista[indice].id = *idMaximo;
			lista[indice].isEmpty = OCUPADO;

			*bandera_eSalon_hayElementos = HAY_ELEMENTOS_ESALON;

			if(*bandera_eArcade_hayElementos == NO_HAY_ELEMENTOS_ESALON)
			{
				*bandera_eArcade_hayElementos = NO_HAY_ELEMENTOS_EARCADE;
			}
			retorno = OPERACION_EXITOSA;
		}
	}
	return retorno;
}
