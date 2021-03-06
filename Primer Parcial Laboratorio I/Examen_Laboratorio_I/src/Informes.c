/*
 * Informes.c
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#include "Informes.h"

#define PUNTERO_NULL -1
#define LEN_INVALIDO -2
#define OPERACION_EXITOSA 0
#define VACIO 1
#define OCUPADO 0
#define JUGADORES 2
#define NO_SE_ENCONTRARON_ELEMENTOS 0
#define SE_ENCONTRARON_ELEMENTOS 1
#define MOSTRAR_TODOS_LOS_DATOS 1
#define MOSTRAR_ID_NOMBRE 2
#define NO_HAY_ELEMENTOS_CARGADOS -16
#define LEN_ARCADE 1000
#define LEN_SALONES 100
#define CANTIDAD_MINIMA_ARCADES_POR_SALON 4
#define MOSTRAR_TODO_VACIO 3
#define MOSTRAR_VACIO 4
#define LEN_STRING_JUEGO 63
#define LEN_MENSAJE 15
#define SHOPPING 1
#define LOCAL 2
#define HAY_IGUALDAD 0
#define FALSE 0
#define TRUE 1


static int informe_estaJuegoEnLaLista(eAuxiliar listaJuegos[], int len_eAuxiliar, char juego[]);
static int informes_poseeOchoArcadesDeMadDeDosJugadores(eArcade listaArcade[], int lenArcade, int idSalon);
static int informes_ContadorArcades(eArcade lista[], int lenArcade);
static int informes_ContadorSalones(eSalon lista[], int lenSalon);

/**
* \brief Elimina a todos los elementos que coindican con el ID especificado de otra estructura
* \param eArcade lista[] - Lista que contiene datos
* \param int len - tam del array
* \param int ID - ID de los elementos relacionados que se eliminaran
* \return Retorna INT. Retorna 1 si se aplico por lo menos 1 baja.
* 		  retorna  0 si no se aplico ninguna baja
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_eArcade_eliminarElementosConElIdEspecificado(eArcade lista[], int len, int id_eSalon)
{
	int i;
	int retorno = PUNTERO_NULL;
	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if( len > 0)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO && lista[i].idSalon == id_eSalon)
				{
					lista[i].isEmpty = VACIO;
					retorno = SE_ENCONTRARON_ELEMENTOS;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief imprime a todos los elementos que coindican con el ID especificado de otra estructura
* \param eArcade lista[] - Lista que contiene datos
* \param int len - tam del array
* \param int ID - ID de los elementos relacionados que se imprimiran
* \param int mostrar - indica que datos mostrar de los elementos
* \return Retorna INT. Retorna 1 si se encontro por lo menos un elemento para imprimir
* 		  retorna  0 si no se encontro ningun elemento
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_eArcade_imprimirElementosConElIdEspecificado(eArcade lista[], int len, int id_eSalon, int mostrar)
{
	int i;
	int retorno = PUNTERO_NULL;
	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if( len > 0)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			if(mostrar == MOSTRAR_ID_NOMBRE)
			{
				eArcade_imprimirEncabezadoDeTabla(MOSTRAR_ID_NOMBRE);
			}
			else
			{
				eArcade_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS);
			}
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO && lista[i].idSalon == id_eSalon)
				{
					retorno = SE_ENCONTRARON_ELEMENTOS;
					if(mostrar == MOSTRAR_ID_NOMBRE)
					{
						eArcade_imprimirFilaDelElemento(lista[i], MOSTRAR_ID_NOMBRE);
					}
					else
					{
						eArcade_imprimirFilaDelElemento(lista[i], MOSTRAR_TODOS_LOS_DATOS);
					}
				}
			}

			if(retorno == NO_SE_ENCONTRARON_ELEMENTOS)
			{
				if(mostrar == MOSTRAR_ID_NOMBRE)
				{
					eArcade_imprimirEncabezadoDeTabla(MOSTRAR_VACIO);
				}
				else
				{
					eArcade_imprimirEncabezadoDeTabla(MOSTRAR_TODO_VACIO);
				}
				printf("\n\t\t<--No hay arcades en este salon-->\n");
			}
		}
	}
	return retorno;
}

/**
* \brief imprime a todos los arcades disponibles junto con el salon al que pertenecen
* \param eArcade listaArcade[] - Lista que contiene datos
* \param int lenArcade - tam del array
* \param eSalon listaSalon[] - Lista que contiene datos
* \param int lenSalon - tam del array
* \return Retorna INT. Retorna 1 si se encontro por lo menos un elemento para imprimir
* 		  retorna  0 si no se encontro ningun elemento
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_imprimirArcadeConSuSalon(eArcade listaArcade[], int lenArcade, eSalon listaSalon[], int lenSalon)
{
	int retorno = PUNTERO_NULL;
	int indiceSalon;
	int contador = 1;
	int i;

	if(listaSalon != NULL && listaArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade >0 && lenSalon >0)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			for(i=0; i < lenArcade; i++)
			{
				if(listaArcade[i].isEmpty == OCUPADO)
				{
					printf("%30d) ID: %d - %-7s %-63s",contador,listaArcade[i].id,"Arcade:" ,listaArcade[i].nombreJuego);
					eArcade_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS);
					eArcade_imprimirFilaDelElemento(listaArcade[i], MOSTRAR_TODOS_LOS_DATOS);
					indiceSalon = eSalon_encontrarElementoPorId(listaSalon, lenSalon, listaArcade[i].idSalon);
					if(utn_comprobarEstadoDeOperacion(indiceSalon))
					{
						eSalon_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS);
						eSalon_imprimirFilaDelElemento(listaSalon[indiceSalon], MOSTRAR_TODOS_LOS_DATOS);
					}
					retorno = SE_ENCONTRARON_ELEMENTOS;
					printf("\n----------------------------------------------------------------------------------------------------------------\n");
					contador++;
				}
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
* 		  Retorna -2 si hay el largo del array es invalido
*/
static int informe_estaJuegoEnLaLista(eAuxiliar listaJuegos[], int len_eAuxiliar, char juego[])
{
	int i;
	int retorno = PUNTERO_NULL;
	if(listaJuegos != NULL && juego != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len_eAuxiliar > 0 && len_eAuxiliar <= LEN_ARCADE)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			for(i =0; i < len_eAuxiliar; i++)
			{
				if(listaJuegos[i].isEmpty == OCUPADO)
				{
					if(strncmp(listaJuegos[i].juego, juego, LEN_STRING_JUEGO) == HAY_IGUALDAD)
					{
						retorno = SE_ENCONTRARON_ELEMENTOS;
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene una lista sin repetir de los juegos cargados hasta el momento en el sistema.
* \param eAuxiliar listaJuegos[] - Lista que contiene datos
* \param int lenJuegos - tam del array
* \param eArcade listaArcade[] - Lista que contiene datos
* \param int lenArcade - tam del array
* \return Retorna INT. Retorna 0 si se pudo generar la lista
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  retorna  -16 si no hay elementos cargados en el sistema, por lo que no se puede hacer la lista
*/
int informe_generarListaDeJuegos(eAuxiliar listaJuegos[], int lenJuegos, eArcade listaArcade[], int lenArcade)
{
	int i;
	int contador = 0;
	int retorno = PUNTERO_NULL;
	if(listaArcade != NULL && listaJuegos != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenJuegos > 0 && lenJuegos <= LEN_ARCADE && lenArcade > 0 && lenArcade <= LEN_ARCADE)
		{
			eAuxiliar_inicializarBanderas(listaJuegos, lenJuegos);

			retorno = NO_HAY_ELEMENTOS_CARGADOS;
			for(i=0; i < lenArcade ;i++)
			{
				if(listaArcade[i].isEmpty == OCUPADO)
				{
					if(informe_estaJuegoEnLaLista(listaJuegos, lenJuegos, listaArcade[i].nombreJuego)==FALSE)
					{
						strncpy(listaJuegos[contador].juego, listaArcade[i].nombreJuego, LEN_STRING_JUEGO);
						listaJuegos[contador].isEmpty = OCUPADO;
						contador++;
						retorno = OPERACION_EXITOSA;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Imprime la lista de juegos cargados hasta el momento
* \param eArcade listaArcade[] - Lista que contiene datos
* \param int lenArcade - tam del array
* \return retorna INT. 0 si encontro elementos
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
* 		  retorna -16 si no se encontraron elementos para imprimir
*/
int informes_imprimirListaDeJuegos(eArcade listaArcade[], int lenArcade)
{
	int i;
	int contador=0;
	int retorno = PUNTERO_NULL;
	eAuxiliar listaAuxiliarJuegos[LEN_ARCADE];
	if(listaArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade <= LEN_ARCADE)
		{
			retorno = NO_HAY_ELEMENTOS_CARGADOS;
			if(informe_generarListaDeJuegos(listaAuxiliarJuegos, lenArcade, listaArcade, lenArcade)==OPERACION_EXITOSA)
			{
				for(i = 0; i < lenArcade; i++)
				{
					if(listaAuxiliarJuegos[i].isEmpty == OCUPADO)
					{
						contador++;
						printf("\n%d) %s", contador, listaAuxiliarJuegos[i].juego);
						retorno = OPERACION_EXITOSA;
					}
					else
					{
						break;
					}
				}
			}
			if(retorno == NO_HAY_ELEMENTOS_CARGADOS)
			{
				printf("\n\t\t<--Aun no hay juegos cargados-->");
			}
		}
	}
	return retorno;
}

/**
* \brief lista los salones que tengan mas de 4 arcades.
* \param eSalon listaSalones[] - lista de salones
* \param int lenSalon - len del listado de salones
* \param eArcade listaArcade[] - lista de arcades
* \param int lenArcade - len de lista de arcades
* \param int len - tam del array
* \param int ID - ID de los elementos relacionados que se contaran
* \return Retorna INT. Retorna 1 o mayor, que es la cantidad de salones que superan 4 arcades.
* 		  retorna  0 si ningun salon tiene mas de 4 arcades
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  retorna -16 si no hay elementos cargados
*/
int informes_listarSalonesConMasDeCuatroArcades(eSalon listaSalones[], int lenSalones, eArcade listaArcades[], int lenArcade)
{
	int i;
	int cantidadDeArcadesPorSalon;
	int contadorSalonesConMasDeCuatroArcades=0;
	int retorno = PUNTERO_NULL;

	if(listaSalones != NULL && listaArcades != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenSalones > 0 && lenSalones <= LEN_SALONES && lenArcade >0 && lenArcade <=LEN_ARCADE)
		{
			retorno = NO_HAY_ELEMENTOS_CARGADOS;
			for(i = 0; i < LEN_SALONES; i++)
			{
				if(listaSalones[i].isEmpty == OCUPADO)
				{
					cantidadDeArcadesPorSalon = informes_eArcade_contadorArcadePorSalon(listaArcades, lenArcade, listaSalones[i].id);
					if(utn_comprobarEstadoDeOperacion(cantidadDeArcadesPorSalon) && cantidadDeArcadesPorSalon > CANTIDAD_MINIMA_ARCADES_POR_SALON)
					{
						eSalon_imprimirFilaDelElemento(listaSalones[i], MOSTRAR_TODOS_LOS_DATOS);
						contadorSalonesConMasDeCuatroArcades++;
					}
				}
				else
				{
					break;
				}
			}
			retorno = contadorSalonesConMasDeCuatroArcades;
		}
	}
	return retorno;
}

/**
* \brief Cuenta a todos los arcades que coincidan con el ID especificado del salon
* \param eArcade listaArcade[] - Lista que contiene datos
* \param int len - tam del array
* \param int ID - ID de los elementos relacionados que se contaran
* \return Retorna INT. Retorna 1 o mayor, que es la cantidad de arcades que hay en ese salon.
* 		  retorna  0 si no hay arcades en ese salon
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_eArcade_contadorArcadePorSalon(eArcade listaArcade[], int len, int id_eSalon)
{
	int i;
	int contador=0;
	int retorno = PUNTERO_NULL;
	if(listaArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if( len > 0 && len <= LEN_ARCADE)
		{
			for(i = 0; i < len; i++)
			{
				if(listaArcade[i].isEmpty == OCUPADO && listaArcade[i].idSalon == id_eSalon)
				{
					contador++;
				}
			}
			retorno = contador;
		}
	}
	return retorno;
}

/**
* \brief Lista a todos los arcades que soporte mas de 2 jugadores.
* \param eArcade listaArcade[] - Lista que contiene los arcades
* \param int lenArcade - tam del array
* \param eSalon listaSalon - lista que contiene los salones
* \param int lenSalon - tam del array
* \return Retorna INT. Retorna 1 si encontro arcades que soporten mas de 2 jugadores
* 		  retorna  0 si no hay arcades que soporten mas de 2 jugadores
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_arcadesParaMasDeDosJugadores(eArcade listaArcade[], int lenArcade, eSalon listaSalon[], int lenSalon)
{
	int i;
	int indiceSalon;
	int estadoOperacion;
	int retorno = PUNTERO_NULL;

	if(listaArcade != NULL && listaSalon != NULL)
	{
		retorno = LEN_INVALIDO;
		if( lenArcade > 0 && lenArcade <= LEN_ARCADE && lenSalon >0 && lenSalon <= LEN_SALONES)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			printf("\n%9s  %15s   %-30.30s %-30s","ID Arcade" ,"Cant. Jugadores", "Nombre Juego", "Nombre Salon");
			for(i = 0; i < lenArcade; i++)
			{
				if(listaArcade[i].isEmpty == OCUPADO && listaArcade[i].cantidadJugadores > JUGADORES)
				{
					estadoOperacion = eSalon_encontrarElementoPorId(listaSalon, lenSalon, listaArcade[i].idSalon);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						indiceSalon = estadoOperacion;
						printf("\n%9d  %15d   %-30s %-30s", listaArcade[i].id, listaArcade[i].cantidadJugadores, listaArcade[i].nombreJuego, listaSalon[indiceSalon].nombre);
						retorno = SE_ENCONTRARON_ELEMENTOS;
					}
				}
			}
			if(retorno == NO_SE_ENCONTRARON_ELEMENTOS)
			{
				printf("\n%9s %16s %14s %30s","-" ,"-", "-", "-");
			}
		}
	}
	return retorno;
}

/**
* \brief Lista la informacion del salon especificado por id, junto con la cantidad de arcades que posee
* \param eSalon listaSalon[] - lista que contiene los salones
* \param int indiceSalon - indice del salon
* \param eArcade listaArcade[] - Lista que contiene los arcades
* \param int lenArcade - tam del array
* \param int idSalon - id unico correspondiente al salon
* \return Retorna INT. Retorna 1 si encontro el salon
* 		  retorna  0 si no encontro el salon
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_listarInfoDeSalonConCantidadDeArcades(eSalon listaSalon[], int indiceSalon, eArcade listaArcade[], int lenArcade, int idSalon)
{
	int cantidadArcades;
	int retorno = PUNTERO_NULL;
	char mensaje[LEN_MENSAJE];
	if(listaSalon != NULL && listaArcade !=NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade >0 && lenArcade <=LEN_ARCADE)
		{
			cantidadArcades = informes_eArcade_contadorArcadePorSalon(listaArcade, lenArcade, idSalon);
			if(cantidadArcades >=0)
			{
				if(eSalon_convertirTipoATexto(listaSalon[indiceSalon], mensaje, LEN_MENSAJE)==OPERACION_EXITOSA)
				{
					printf("\n%5s  %-15s   %-13s   %-15s  %13s", "Id", "Nombre Salon","Tipo de Salon","Direccion Salon", "Cant. Arcades");
					printf("\n%5d  %-15.15s   %-13s   %-15.15s  %13d", listaSalon[indiceSalon].id, listaSalon[indiceSalon].nombre, mensaje, listaSalon[indiceSalon].direccion, cantidadArcades);
					retorno = SE_ENCONTRARON_ELEMENTOS;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Lista la informacion del salon especificado por id, junto con la lista de arcades que posee
* \param eSalon salon - elemento de tipo salon
* \param eArcade listaArcade[] - Lista que contiene los arcades
* \param int lenArcade - tam del array
* \param int idSalon - id unico correspondiente al salon
* \return Retorna INT. Retorna 1 si encontro el salon
* 		  retorna  0 si no encontro el salon
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_listarSalonConListaDeSusArcades(eSalon salon, eArcade listaArcade[], int lenListaArcade, int idSalon)
{
	int retorno = PUNTERO_NULL;
	char mensaje[LEN_MENSAJE];
	if(listaArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenListaArcade >0 && lenListaArcade <= LEN_ARCADE)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			if(salon.isEmpty == OCUPADO)
			{
				if(eSalon_convertirTipoATexto(salon, mensaje, LEN_MENSAJE)==OPERACION_EXITOSA)
				{
					printf("\n   %-20s  %-15s", "Nombre del Salon", "Tipo del Salon");
					printf("\n   %-20.20s  %-15s", salon.nombre, mensaje);
					printf("\n\t\t<--Lista de arcades en el salon '%s'-->", salon.nombre);
					informes_eArcade_imprimirElementosConElIdEspecificado(listaArcade, lenListaArcade,salon.id ,MOSTRAR_TODOS_LOS_DATOS);
					retorno = SE_ENCONTRARON_ELEMENTOS;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Imprime el salon con mayor cantidad de Arcades, junto con la cantidad de arcades que posee
* \param eSalon listaSalones[] - lista de tipo salon
* \param int lenSalones - tam del array listaSalones
* \param eArcade listaArcades[] - Lista que contiene los arcades
* \param int lenArcades - tam del array
* \return Retorna INT. Retorna 0 si logro encontrar el salon con mas arcades
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  retorna -16 si no hay elementos cargados
*/
int informes_imprimirSalonConMasArcades(eSalon listaSalones[], int lenSalones, eArcade listaArcades[], int lenArcades)
{
	int indiceSalonConMasArcades;
	int mayorCantidadDeArcades;
	char mensaje[LEN_MENSAJE];
	int retorno = PUNTERO_NULL;
	if(listaArcades!= NULL && listaSalones != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenSalones >0 && lenSalones <=LEN_SALONES && lenArcades >0 && lenArcades <= LEN_ARCADE)
		{
			retorno = NO_HAY_ELEMENTOS_CARGADOS;
			indiceSalonConMasArcades = informes_CalcularSalonConMasArcades(listaSalones, lenSalones, listaArcades, lenArcades, &mayorCantidadDeArcades);
			if(utn_comprobarEstadoDeOperacion(indiceSalonConMasArcades))
			{
				eSalon_convertirTipoATexto(listaSalones[indiceSalonConMasArcades], mensaje, LEN_MENSAJE);
				printf("\n%5s  %-15s   %-13s   %-15s  %13s", "Id", "Nombre Salon","Tipo de Salon","Direccion Salon", "Cant. Arcades");
				printf("\n%5d  %-15.15s   %-13s   %-15.15s  %13d", listaSalones[indiceSalonConMasArcades].id, listaSalones[indiceSalonConMasArcades].nombre, mensaje, listaSalones[indiceSalonConMasArcades].direccion, mayorCantidadDeArcades);
				printf("\n\t\t<--Lista de juegos en el salon '%s'-->",listaSalones[indiceSalonConMasArcades].nombre);
				informes_eArcade_imprimirElementosConElIdEspecificado(listaArcades, lenArcades, listaSalones[indiceSalonConMasArcades].id, MOSTRAR_ID_NOMBRE);
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Calcula el salon con mayor cantidad de Arcades
* \param eSalon listaSalones[] - lista de tipo salon
* \param int lenSalones - tam del array listaSalones
* \param eArcade listaArcades[] - Lista que contiene los arcades
* \param int lenArcades - tam del array
* \param  int* mayorCantidadDeArcades - puntero donde guardara la mayor cantidad de arcades obtenida en un salon
* \return Retorna INT. Retorna 1 o mayor, que es la cantidad mas alta de arcades encontrada en un salon.
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  retorna -16 si no hay elementos cargados
*/
int informes_CalcularSalonConMasArcades(eSalon listaSalones[], int lenSalones, eArcade listaArcades[], int lenArcades, int* mayorCantidadDeArcades)
{
	int i;
	int indiceDelSalonConMasArcades;
	int mayorCantidadMasAltaDeArcades;
	int banderaDelPrimerSalon = VACIO;
	int cantidadArcadesDelSalon;
	int retorno = PUNTERO_NULL;
	if(listaArcades!= NULL && listaSalones != NULL && mayorCantidadDeArcades != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenSalones >0 && lenSalones <=LEN_SALONES && lenArcades >0 && lenArcades <= LEN_ARCADE)
		{
			retorno = NO_HAY_ELEMENTOS_CARGADOS;
			for(i = 0; i < lenSalones; i++)
			{
				if(listaSalones[i].isEmpty == OCUPADO)
				{
					cantidadArcadesDelSalon = informes_eArcade_contadorArcadePorSalon(listaArcades, lenArcades, listaSalones[i].id);

					if(utn_comprobarEstadoDeOperacion(cantidadArcadesDelSalon))
					{
						if(banderaDelPrimerSalon == VACIO || cantidadArcadesDelSalon > mayorCantidadMasAltaDeArcades)
						{
							mayorCantidadMasAltaDeArcades = cantidadArcadesDelSalon;
							indiceDelSalonConMasArcades = i;
							banderaDelPrimerSalon = OCUPADO;
						}
					}
				}
			}
			if(banderaDelPrimerSalon == OCUPADO)
			{
				retorno = indiceDelSalonConMasArcades;
				*mayorCantidadDeArcades = mayorCantidadMasAltaDeArcades;
			}
		}
	}
	return retorno;
}

/**
* \brief Calcula la cantidad total de fichas de un salon
* \param eArcade listaArcades[] - Lista que contiene los arcades
* \param int lenArcades - tam del array
* \param int idSalon - id unico identificatorio del salon
* \return Retorna INT. Retorna 1 o mas, que representa la cantidad total de fichas del salon.
* 		  Retorna  0 si no hay arcades en el salon
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_ContarFichasTotalesPorSalon(eArcade listaArcade[], int lenArcade, int idSalon)
{
	int i;
	int acumuladorFichas=0;
	int retorno = PUNTERO_NULL;
	if(listaArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade <=LEN_ARCADE)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			for(i=0; i < lenArcade; i++)
			{
				if(listaArcade[i].idSalon == idSalon)
				{
					acumuladorFichas = acumuladorFichas + listaArcade[i].capacidadMaximaFichas;
				}
			}
			retorno = acumuladorFichas;
		}
	}
	return retorno;
}

/**
* \brief Calcula el monto maximo que podria recaudar el salon, en base al total de fichas
* 		  de todos los arcades que posee y el precio por cada una de ellas.
* \param eArcade listaArcades[] - Lista que contiene los arcades
* \param int lenArcades - tam del array
* \param float precioPorFicha - precio por cada ficha
* \param int idSalon - id unico identificatorio del salon
* \param float* recaudacionTotal - puntero donde retornara la recaudacion total posible
* \return Retorna INT. Retorna 1 o mas, que representa la cantidad total de fichas del salon.
* 		  Retorna  0 si no hay arcades en el salon
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_CalcularTotalDeRecaudacionPosiblePorSalon(eArcade listaArcades[], int lenArcade, float precioPorFicha, int idSalon, float* recuadacionTotalPorSalon)
{
	float recaudacionPorSalon;
	int cantidadTotalDeFichas;
	int retorno = PUNTERO_NULL;
	if(listaArcades != NULL && recuadacionTotalPorSalon != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade <= LEN_ARCADE)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			cantidadTotalDeFichas = informes_ContarFichasTotalesPorSalon(listaArcades, lenArcade, idSalon);
			if(utn_comprobarEstadoDeOperacion(cantidadTotalDeFichas) && cantidadTotalDeFichas >0)
			{
				recaudacionPorSalon = cantidadTotalDeFichas * precioPorFicha;
				*recuadacionTotalPorSalon = recaudacionPorSalon;
				retorno = cantidadTotalDeFichas;
			}
		}
	}
	return retorno;
}

/**
* \brief imprime el monto maximo que podria recaudar el salon.
* \param eSalon salon - salon al cual se le calculo el monto maximo
* \param float montoMaximo - monto maximo que podria recaudar el salon
* \param int cantidadFichas - cantidad total de fichas del salon
* \param float precioPorFicha - precio por cada ficha*
* \return Retorna INT. Retorna 1 si encontro el salon
* 		  Retorna  0 si no existe el salon
*/
int informes_ImprimirMontoMaximoPorSalon(eSalon salon, float montoMaximo, int cantidadFichas, float precioPorFicha)
{
	int retorno = NO_SE_ENCONTRARON_ELEMENTOS;

	if(salon.isEmpty == OCUPADO)
	{
		printf("\n\t\t<--Recaudacion maxima posible de un salon-->");
		eSalon_imprimirUnElementoCompleto(salon);
		printf("\nTotal de fichas: %d \nPrecio por ficha: $ %.3f \nRecaudacion total posible: $ %.3f", cantidadFichas, precioPorFicha, montoMaximo);
		retorno = SE_ENCONTRARON_ELEMENTOS;
	}
	return retorno;
}

/**
* \brief imprime una lista de elementos, sin repetir.
* \param eArcade lista[] - lista de arcades
* \param  int lenArcade - tama?o del array
* \return Retorna INT. Retorna 0 si la operacion fue exitosa
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si el tama?o del array es invalido
*/
int informes_imprimirListaSinRepetir(eArcade lista[], int len)
{
	int i;
	int j;
	int banderaHayIgualdad;
	int retorno = PUNTERO_NULL;
	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0)
		{
			retorno = OPERACION_EXITOSA;
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					banderaHayIgualdad = NO_SE_ENCONTRARON_ELEMENTOS;
					for(j = 0; j < i ; j++)
					{
						if(lista[j].isEmpty == OCUPADO && strncmp(lista[j].nombreJuego, lista[i].nombreJuego, LEN_STRING_JUEGO) == HAY_IGUALDAD)
						{
							banderaHayIgualdad = SE_ENCONTRARON_ELEMENTOS;
							break;
						}
					}
					if(banderaHayIgualdad == NO_SE_ENCONTRARON_ELEMENTOS)
					{
						printf("\n%s", lista[i].nombreJuego);
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief imprime una lista de elementos, sin repetir.
* \param eArcade lista[] - lista de arcades
* \param  int lenArcade - tama?o del array
* \return Retorna INT. Retorna 0 si la operacion fue exitosa
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si el tama?o del array es invalido
*/
int informes_imprimirListaSinRepetirVolDos(eArcade lista[], int len)
{
	int i;
	int j;
	int banderaHayIgualdad;
	int retorno = PUNTERO_NULL;
	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0)
		{
			retorno = OPERACION_EXITOSA;
			for(i = 0; i < len; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					banderaHayIgualdad = NO_SE_ENCONTRARON_ELEMENTOS;
					for( j = i + 1; j < len; j++)
					{
						if(lista[j].isEmpty == OCUPADO && strncmp(lista[i].nombreJuego, lista[j].nombreJuego, LEN_STRING_JUEGO)==HAY_IGUALDAD)
						{
							banderaHayIgualdad = SE_ENCONTRARON_ELEMENTOS;
							break;
						}
					}
					if(banderaHayIgualdad == NO_SE_ENCONTRARON_ELEMENTOS)
					{
						printf("\n%s",lista[i].nombreJuego);
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Lista aquellos salones que se encuentre completos (minimo 8 arcades con mas de 2 jugadores)
* \param eSalon listaSalones[] - lista de tipo salon
* \param int lenSalones - tam del array listaSalones
* \param eArcade listaArcades[] - Lista que contiene los arcades
* \param int lenArcades - tam del array
* \return Retorna INT. Retorna 1 si encontro por lo menos 1 salon completo
* 		  retorna 0 si no encontro ningun salon completo
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_listarSalonesCompletos(eSalon listaSalon[], int lenSalon, eArcade listaArcades[], int lenArcades)
{
	int i;
	int salonEstaCompleto;
	int retorno = PUNTERO_NULL;
	if(listaSalon != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenSalon > 0 && lenSalon <= LEN_SALONES && lenArcades > 0 && lenArcades <=LEN_ARCADE)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			printf("\n\t\t<--Lista de salones completos (minimo 8 arcades de mas de 2 jugadores)-->");
			eSalon_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS);
			for(i = 0; i < lenSalon; i++)
			{
				if(listaSalon[i].isEmpty == OCUPADO)
				{
					salonEstaCompleto = informes_poseeOchoArcadesDeMadDeDosJugadores(listaArcades, lenArcades, listaSalon[i].id);
					if(utn_comprobarEstadoDeOperacion(salonEstaCompleto) && salonEstaCompleto == TRUE)
					{
						eSalon_imprimirFilaDelElemento(listaSalon[i], MOSTRAR_TODOS_LOS_DATOS);
						retorno= SE_ENCONTRARON_ELEMENTOS;
					}
				}
			}
			if(retorno == NO_SE_ENCONTRARON_ELEMENTOS)
			{
				eSalon_imprimirEncabezadoDeTabla(MOSTRAR_TODO_VACIO);
				printf("\n\t\t<--No se encontraron salones completos-->");
			}
		}
	}
	return retorno;
}

/**
* \brief Evalua si un salon esta completo (8 o mas arcades de mas de 2 jugadores)
* \param eArcade listaArcades[] - Lista que contiene los arcades
* \param int lenArcades - tam del array
* \param int idSalon - id del salon que se evaluara
* \return Retorna INT. Retorna 1 si el salon esta completo
* 		  retorna 0 si el salon no esta completo
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
static int informes_poseeOchoArcadesDeMadDeDosJugadores(eArcade listaArcade[], int lenArcade, int idSalon)
{
	int i;
	int contadorArcades=0;
	int retorno = PUNTERO_NULL;
	if(listaArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade <=LEN_ARCADE)
		{
			retorno = FALSE;
			for(i = 0; i < lenArcade; i++)
			{
				if(listaArcade[i].isEmpty == OCUPADO && listaArcade[i].idSalon == idSalon && listaArcade[i].cantidadJugadores > JUGADORES)
				{
					contadorArcades++;
				}
			}
			if(contadorArcades >= 8)
			{
				retorno = TRUE;
			}
		}
	}
	return retorno;
}

/**
* \brief Calcula el promedio de arcades por salon
* \param eSalon listaSalones[] - lista de tipo salon
* \param int lenSalones - tam del array listaSalones
* \param eArcade listaArcades[] - Lista que contiene los arcades
* \param int lenArcades - tam del array
* \param  int* pPromedioArcadesPorSalon - puntero donde guardara el promedio de arcades por salon.
* \return Retorna INT. Retorna 1 si pudo calcular el promedio
* 		  retorna 0 si no encontro ningun arcade o salon para calcular el promedio
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int informes_promedioArcadesPorSalon(eSalon listaSalones[], int lenSalon, eArcade listaArcades[], int lenArcades, float* pPromedioArcadesPorSalon)
{
	int cantidadSalones;
	int cantidadArcades;
	float promedioArcadesPorSalon;
	int retorno = PUNTERO_NULL;
	if(listaArcades != NULL && listaSalones != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenSalon > 0 && lenSalon <= LEN_SALONES && lenArcades > 0 && lenArcades <=LEN_ARCADE)
		{
			retorno = NO_SE_ENCONTRARON_ELEMENTOS;
			cantidadSalones = informes_ContadorSalones(listaSalones, lenSalon);
			if(utn_comprobarEstadoDeOperacion(cantidadSalones) && cantidadSalones > NO_SE_ENCONTRARON_ELEMENTOS)
			{
				cantidadArcades = informes_ContadorArcades(listaArcades, lenArcades);
				if(utn_comprobarEstadoDeOperacion(cantidadArcades) && cantidadArcades > NO_SE_ENCONTRARON_ELEMENTOS)
				{
					promedioArcadesPorSalon = (float)cantidadArcades / cantidadSalones;
					*pPromedioArcadesPorSalon = promedioArcadesPorSalon;
					printf("\nCantidad de Salones totales: %d", cantidadSalones);
					printf("\nCantidad de Arcades totales: %d", cantidadArcades);
					retorno = SE_ENCONTRARON_ELEMENTOS;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Cuenta los salones encontrados en el sistema
* \param eSalon lista[] - lista de tipo salon
* \param int lenSalones - tam del array listaSalones
* \return Retorna INT. Retorna 1 o mayor, que es la cantidad de salones encontrados en el sistema
* 		  retorna 0 si no encontro ningun salon
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
static int informes_ContadorSalones(eSalon lista[], int lenSalon)
{
	int i;
	int contadorSalones = 0;
	int retorno = PUNTERO_NULL;
	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenSalon > 0 && lenSalon<=LEN_SALONES)
		{
			for(i = 0; i < lenSalon; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					contadorSalones++;
				}
			}
			retorno = contadorSalones;
		}
	}
	return retorno;
}

/**
* \brief Cuenta los arcades encontrados en el sistema
* \param eArcade lista[] - Lista que contiene los arcades
* \param int lenArcades - tam del array
* \return Retorna INT. Retorna 1 o mayor, que es la cantidad de arcades encontrados en el sistema
* 		  retorna 0 si no encontro ningun arcade
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
static int informes_ContadorArcades(eArcade lista[], int lenArcade)
{
	int i;
	int contadorArcades = 0;
	int retorno = PUNTERO_NULL;
	if(lista != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade<=LEN_ARCADE)
		{
			for(i = 0; i < lenArcade; i++)
			{
				if(lista[i].isEmpty == OCUPADO)
				{
					contadorArcades++;
				}
			}
			retorno = contadorArcades;
		}
	}
	return retorno;
}
