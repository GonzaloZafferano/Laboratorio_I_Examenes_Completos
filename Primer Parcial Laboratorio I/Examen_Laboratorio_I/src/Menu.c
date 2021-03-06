/*
 * Menu.c
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#include "ComprobarErrores.h"
#include "Arcade.h"
#include "Salon.h"
#include "Informes.h"
#include "Menu.h"

#define TRUE 1
#define FALSE 0
#define LEN_JUEGO 63
#define TAM_ESALON 100
#define TAM_EARCADE 1000
#define OPERACION_EXITOSA 0
#define REINTENTOS 2
#define VOLVER_AL_MENU 2
#define MINIMO_PRECIO_FICHAS 1
#define MAXIMO_PRECIO_FICHAS 100
#define VACIO 0
#define MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO 1
#define MOSTRAR_ID_NOMBRE_DEL_ELEMENTO 2
#define MOSTRAR_TODO_VACIO 3
#define MOSTRAR_VACIO 4
#define LEN_INVALIDO -2
#define PUNTERO_NULL -1
#define NO_SE_OBTUVO_UNA_RESPUESTA_VALIDA -22

#define HAY_ELEMENTOS_ESALON 2
#define VACIO 0
#define SI 1
#define NO 0
#define ATRAS 0
#define NO_HAY_ELEMENTOS_EARCADE 1
#define HAY_ELEMENTOS_EARCADE 3
#define NO_HAY_ELEMENTOS_ESALON 0
#define MENU_ARCADE_MODIFICACION_MINIMO 1
#define MENU_ARCADE_MODIFICACION_MAXIMO 3
#define MENU_ARCADE_MODIFICAR_JUEGO 1
#define NO_ELIMINAR 2
/*
* \brief Imprime el menu principal.
* \param VOID -
* \return Retorna VOID.
*/
void menu_ImprimirMenuPrincipal(void)
{
	static int banderaMenu = 0;

	if(banderaMenu)
	{
		printf("\n\t\t<--Volviendo al Menu Principal-->\n");
	}
	else
	{
		printf("\n\t<--Bienvenido al sistema de carga de datos-->\n");
		banderaMenu = 1;
	}
	printf("\n\t\t<--Menu Principal-->"
			"\n1 >>Alta de Salon"
			"\n2 >>Eliminar Salon"
			"\n3 >>Imprimir lista de salones"
			"\n4 >>Incorporar Arcade"
			"\n5 >>Modificar Arcade"
			"\n6 >>Eliminar Arcade"
			"\n7 >>Imprimir Arcades "
			"\n8 >>Imprimir juegos"
			"\n9 >>Informes"
			"\n10 <<Salir");
}

/*
* \brief Imprime el menu de informes
* \param VOID -
* \return Retorna VOID.
*/
void menu_ImprimirMenuInformes(void)
{
	printf("\n\n\t\t<--Menu Informes-->\nA >>Listar los salones con m?s de 4 arcades."
			"\nB >>Listar los arcades para m?s de 2 jugadores"
			"\nC >>Listar toda la informaci?n de un sal?n por ID"
			"\nD >>Listar todos los arcades de un sal?n, por su ID."
			"\nE >>Imprimir el sal?n con m?s cantidad de arcades"
			"\nF >>Monto maximo que puede recaudar un salon"
			"\nG >>Ingresar el nombre de un juego e imprimir cuantos arcades lo contienen."
			"\nH >>Listar los salones que estan completos (minimo 8 arcades de mas de 2 jugadores)"
			"\nI >>Promedio de arcades por salon (total arcades/ total salones)"
			"\nJ <<Volver al menu Principal");
}

/*
* \brief Evalua si es posible realizar una operacion. Si es posible, no realiza acciones.
*        Si no es posible, informa el motivo.
* \param int bandera - Valor que identifica la posibilidad de realizar una operacion.
* \return retorna un INT. 1 si es posible realizar la operacion en base a la bandera recibida.
* 		  retorna 0 si la operacion no puede ser realizada.
*/
int menu_EsPosibleOperarMenu(int bandera)
{
	int retorno = FALSE;
	switch(bandera)
	{
		case 0:
			printf("\n\t\t<--Un momento, no se puede operar! Necesita cargar al menos un salon!-->\n");
			break;
		case 1:
			printf("\n\t\t<--Un momento, no se puede operar! Necesita cargar al menos un arcade!-->\n");
			break;
		case 2:
		case 3:
			retorno = TRUE;
			break;
	}
	return retorno;
}

/**
* \brief Opera el menu de altas de salones
* \param eSalon lista_eSalon[] - Lista que contiene los salones
* \param int lenSalon - tam del array
* \param int* idMaximo_eSalon - puntero a variable id maximo de salon donde se guardara el ultimo id generado
* \param int* bandera_eSalon_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \param int* bandera_eArcade_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \return Retorna INT. Retorna  0 si opero correctamente.
* 		  Retorna 2 si el usuario decide volver al menu, o si ocurrio un error que forzo volver al menu principal
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int menu_OperarMenuAltaDeSalon(eSalon lista_eSalon[], int lenSalon, int* idMaximo_eSalon, int* bandera_eSalon_hayElementos, int* bandera_eArcade_hayElementos)
{
	int estadoOperacion;
	int opcionIngresada;
	int indiceLibre_eSalon;
	int retorno = PUNTERO_NULL;

	if(lista_eSalon != NULL && idMaximo_eSalon != NULL && bandera_eArcade_hayElementos != NULL && bandera_eSalon_hayElementos != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenSalon > 0 && lenSalon <= TAM_ESALON)
		{
			retorno = VOLVER_AL_MENU;
			estadoOperacion = eSalon_buscarIndiceLibre(lista_eSalon, lenSalon);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				indiceLibre_eSalon = estadoOperacion;
				estadoOperacion = utn_getInt(&opcionIngresada, "\nDesea dar un alta de salon? \n\t1 >>Si\n\t2 <<Volver al menu principal", "Error, dato invalido!", SI, VOLVER_AL_MENU, REINTENTOS);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada != VOLVER_AL_MENU)
				{
					printf("\n\t\t<--Menu altas de Salones-->\n");
					estadoOperacion = eSalon_tomarDatos(lista_eSalon, indiceLibre_eSalon, idMaximo_eSalon);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						estadoOperacion = eSalon_imprimirUnElementoCompleto(lista_eSalon[indiceLibre_eSalon]);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							printf("\n\t\t<--Alta de Salon exitosa!!-->\n");
							*bandera_eSalon_hayElementos = HAY_ELEMENTOS_ESALON;
							if(*bandera_eArcade_hayElementos == NO_HAY_ELEMENTOS_ESALON)
							{
								*bandera_eArcade_hayElementos = NO_HAY_ELEMENTOS_EARCADE;
							}
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
* \brief Opera el menu de eliminacion de salones
* \param eSalon lista_eSalon[] - Lista que contiene los salones
* \param int lenSalon - tam del array
* \param eArcade lista_eArcade[] - Lista que contiene los arcades
* \param int lenArcade - tam del array
* \param int* bandera_eArcade_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \param int* bandera_eSalon_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \param int idMaximo_eSalon - id maximo de salon conseguido hasta el momento
* \return Retorna INT. Retorna  0 si opero correctamente.
* 		  Retorna 2 si el usuario decide volver al menu, o si ocurrio un error que forzo volver al menu principal
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int menu_OperarMenuEliminacionDeSalon(eSalon lista_eSalon[], int lenSalon, eArcade lista_eArcade[], int lenArcade, int* bandera_eArcade_hayElementos, int* bandera_eSalon_hayElementos, int idMaximo_eSalon)
{
	int estadoOperacion;
	int opcionIngresada;
	int idIngresado_eSalon;
	int indiceEncontrado_eSalon;
	int banderaEliminarArcades;
	int retorno = PUNTERO_NULL;

	if(lista_eSalon != NULL && lista_eArcade != NULL && bandera_eArcade_hayElementos != NULL && bandera_eSalon_hayElementos != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade <= TAM_EARCADE && lenSalon >0 && lenSalon <= TAM_ESALON)
		{
			retorno = VOLVER_AL_MENU;
			estadoOperacion = utn_getInt(&opcionIngresada, "Desea eliminar un salon?\n\t1 >>Si, mostrar lista de salones disponibles\n\t2 <<Volver al menu principal", "Error. Dato invalido!", SI, VOLVER_AL_MENU, REINTENTOS);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada != VOLVER_AL_MENU)
			{
				printf("\n\t\t<--Menu Bajas de Salones-->\n");
				eSalon_imprimirIdsDisponibles(lista_eSalon, lenSalon);
				idIngresado_eSalon = utn_tomarID(idMaximo_eSalon);
				if(utn_comprobarEstadoDeOperacion(idIngresado_eSalon) && idIngresado_eSalon != ATRAS)
				{
					indiceEncontrado_eSalon = eSalon_encontrarElementoPorId(lista_eSalon, TAM_ESALON, idIngresado_eSalon);
					if(utn_comprobarEstadoDeOperacion(indiceEncontrado_eSalon))
					{
						printf("\n\t\t|||--Esta por eliminar un Salon!!--|||");
						estadoOperacion = eSalon_imprimirUnElementoCompleto(lista_eSalon[indiceEncontrado_eSalon]);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							banderaEliminarArcades = SI;
							printf("\n\n<---Lista de arcades asociados al salon '%s', que se perderan si se elimina el ID <%d>--->", lista_eSalon[indiceEncontrado_eSalon].nombre,idIngresado_eSalon);
							estadoOperacion = informes_eArcade_imprimirElementosConElIdEspecificado(lista_eArcade, lenArcade, idIngresado_eSalon, MOSTRAR_ID_NOMBRE_DEL_ELEMENTO);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion == VACIO)
							{
								banderaEliminarArcades = NO;
							}
							estadoOperacion = utn_getInt(&opcionIngresada, "\nSeguro desea eliminar el Id especificado?"
									"\n\t>>1 Si \n\t<<2 Volver al menu principal",
									"Error, opcion invalida", SI, VOLVER_AL_MENU, REINTENTOS);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada == SI)
							{
								estadoOperacion = eSalon_eliminarElementoPorIndice(lista_eSalon, indiceEncontrado_eSalon);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									printf("\n\t\t<--Eliminacion de Salon exitosa!!-->\n");
									if(banderaEliminarArcades == SI)
									{
										estadoOperacion = informes_eArcade_eliminarElementosConElIdEspecificado(lista_eArcade, lenArcade, idIngresado_eSalon);
										if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion == SI)
										{
											printf("\n\t\t<--Arcades eliminados!-->\n");

											if(eArcade_verificarSiHayElementos(lista_eArcade, lenArcade) == VACIO)
											{
												printf("\n\t\t<--No hay mas Arcades cargados!-->\n");
												*bandera_eArcade_hayElementos = NO_HAY_ELEMENTOS_EARCADE;
											}
										}
									}
									estadoOperacion = eSalon_verificarSiHayElementos(lista_eSalon, lenSalon);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion == VACIO)
									{
										printf("\n\t\t<--No quedan mas salones cargados!!-->\n");
										*bandera_eSalon_hayElementos = NO_HAY_ELEMENTOS_ESALON;
										*bandera_eArcade_hayElementos = NO_HAY_ELEMENTOS_ESALON;
									}
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
* \brief Opera el menu de altas de arcades
* \param eArcade lista_eArcade[] - Lista que contiene los arcades
* \param int lenArcade - tam del array
* \param eSalon lista_eSalon[] - Lista que contiene los salones
* \param int lenSalon - tam del array
* \param int idMaximo_eSalon - id maximo de salon conseguido hasta el momento
* \param int* bandera_eArcade_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \param int* idMaximo_eArcade - puntero a variable id maximo de arcades donde se guardara el ultimo id generado
* \return Retorna INT. Retorna  0 si opero correctamente.
* 		  Retorna 2 si el usuario decide volver al menu, o si ocurrio un error que forzo volver al menu principal
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int menu_OperarMenuAltaDeArcade(eArcade lista_eArcade[], int lenArcade, eSalon lista_eSalon[], int lenSalon, int idMaximo_eSalon, int* bandera_eArcade_hayElementos, int* idMaximo_eArcade)
{
	int estadoOperacion;
	int indiceLibre_eArcade;
	int idIngresado_eSalon;
	int opcionIngresada;
	int indiceEncontrado_eSalon;
	int retorno = PUNTERO_NULL;
	if(lista_eArcade != NULL && lista_eSalon != NULL && bandera_eArcade_hayElementos != NULL && idMaximo_eArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade <= TAM_EARCADE && lenSalon > 0 && lenSalon <= TAM_ESALON)
		{
			retorno = VOLVER_AL_MENU;
			estadoOperacion = eArcade_buscarIndiceLibre(lista_eArcade, TAM_EARCADE);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				indiceLibre_eArcade = estadoOperacion;
				estadoOperacion = utn_getInt(&opcionIngresada, "\nDesea dar un alta de Arcade? \n\t1 >>Si\n\t2 <<Volver al menu principal", "Error, dato invalido!", SI, VOLVER_AL_MENU, REINTENTOS);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada != VOLVER_AL_MENU)
				{
					printf("\n\t\t<--Menu altas de Arcades-->\n");
					printf("\nA continuacion indique, a traves del id, a que salon pertenece el Arcade que desea dar de alta:");
					eSalon_imprimirIdsDisponibles(lista_eSalon, TAM_ESALON);
					estadoOperacion = utn_tomarID(idMaximo_eSalon);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion != ATRAS)
					{
						idIngresado_eSalon = estadoOperacion;
						estadoOperacion = eSalon_encontrarElementoPorId(lista_eSalon, TAM_ESALON, idIngresado_eSalon);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							indiceEncontrado_eSalon = estadoOperacion;
							eSalon_imprimirUnElementoCompleto(lista_eSalon[indiceEncontrado_eSalon]);
							printf("\nA continuacion, complete los datos solicitados del Arcade:\n");
							estadoOperacion = eArcade_tomarDatos(lista_eArcade, indiceLibre_eArcade, idMaximo_eArcade, idIngresado_eSalon);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								eArcade_imprimirUnElemento(lista_eArcade[indiceLibre_eArcade]);
								printf("\n\t\t<--Alta de Arcade exitosa!!-->\n");
								*bandera_eArcade_hayElementos = HAY_ELEMENTOS_EARCADE;
								retorno = OPERACION_EXITOSA;
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
* \brief Opera el menu de modificacion de arcades
* \param eArcade lista_eArcade[] - Lista que contiene los arcades
* \param int lenArcade - tam del array
* \param int idMaximo_eArcade - id maximo de arcades conseguido hasta el momento
* \return Retorna INT. Retorna  0 si opero correctamente.
* 		  Retorna 2 si el usuario decide volver al menu, o si ocurrio un error que forzo volver al menu principal
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int menu_OperarMenuModificacionDeArcade(eArcade lista_eArcade[], int lenArcade, int idMaximo_eArcade)
{
	int estadoOperacion;
	int opcionIngresada;
	int idIngresado_eArcade;
	int indiceEncontrado_eArcade;
	int retorno = PUNTERO_NULL;

	if(lista_eArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade <= TAM_EARCADE)
		{
			retorno = VOLVER_AL_MENU;
			estadoOperacion = utn_getInt(&opcionIngresada, "Desea modificar un arcade?\n\t1 >>Si, mostrar lista de Arcades\n\t2 <<Volver al menu principal", "Error. Dato invalido!", SI, VOLVER_AL_MENU, REINTENTOS);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada != VOLVER_AL_MENU)
			{
				printf("\n\t\t<--Menu Modificacion de Arcade-->");
				eArcade_imprimirIdsDisponibles(lista_eArcade, lenArcade);
				idIngresado_eArcade = utn_tomarID(idMaximo_eArcade);
				if(utn_comprobarEstadoDeOperacion(idIngresado_eArcade) && idIngresado_eArcade != ATRAS)
				{
					indiceEncontrado_eArcade = eArcade_encontrarElementoPorId(lista_eArcade, lenArcade, idIngresado_eArcade);
					if(utn_comprobarEstadoDeOperacion(indiceEncontrado_eArcade))
					{
						printf("\n\t\t<--Elemento a modificar-->");
						estadoOperacion = eArcade_imprimirUnElemento(lista_eArcade[indiceEncontrado_eArcade]);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							estadoOperacion = utn_getInt(&opcionIngresada, "\nElija el campo que desea modificar:"
									"\n\t1 >>Juego   \n\t2 >>Cantidad de jugadores \n\t3 <<Volver al menu principal",
									"Error, opcion invalida", MENU_ARCADE_MODIFICACION_MINIMO, MENU_ARCADE_MODIFICACION_MAXIMO, REINTENTOS);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada != MENU_ARCADE_MODIFICACION_MAXIMO)
							{
								if(opcionIngresada == MENU_ARCADE_MODIFICAR_JUEGO)
								{
									printf("\n\t\t<--Lista de juegos cargados en el sistema-->");
									informes_imprimirListaDeJuegos(lista_eArcade, lenArcade);
								}

								estadoOperacion = eArcade_modificarElemento(&lista_eArcade[indiceEncontrado_eArcade], opcionIngresada);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									estadoOperacion = eArcade_imprimirUnElemento(lista_eArcade[indiceEncontrado_eArcade]);
									printf("\n\n\t\t<--Modificacion de Arcade exitosa!!-->\n");
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
* \brief Opera el menu de eliminacion de arcades
* \param eArcade lista_eArcade[] - Lista que contiene los arcades
* \param int lenArcade - tam del array
* \param eSalon lista_eSalon[] - Lista que contiene los salones
* \param int lenSalon - tam del array
* \param int idMaximo_eArcade - id maximo de arcades conseguido hasta el momento
* \param int* bandera_eArcade_hayElementos - puntero a bandera a traves de la cual se indica si hay elementos o no.
* \return Retorna INT. Retorna  0 si opero correctamente.
* 		  Retorna 2 si el usuario decide volver al menu, o si ocurrio un error que forzo volver al menu principal
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
*/
int menu_OperarMenuEliminacionDeArcade(eArcade lista_eArcade[], int lenArcade, eSalon lista_eSalon[], int lenSalon, int idMaximo_eArcade, int* bandera_eArcade_hayElementos)
{
	int estadoOperacion;
	int opcionIngresada;
	int respuestaEliminarArcade;
	int indiceEncontrado_eArcade;
	int idIngresado_eArcade;
	int indiceEncontrado_eSalon;
	int retorno = PUNTERO_NULL;

	if(lista_eArcade != NULL && lista_eSalon != NULL && bandera_eArcade_hayElementos != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade > 0 && lenArcade <= TAM_EARCADE && lenSalon > 0 && lenSalon <= TAM_ESALON)
		{
			retorno = VOLVER_AL_MENU;
			estadoOperacion = utn_getInt(&opcionIngresada, "Desea dar de baja un arcade?\n\t1 >>Si, mostrar lista de Arcades\n\t2 <<Volver al menu principal", "Error. Dato invalido!", SI, VOLVER_AL_MENU, REINTENTOS);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada != VOLVER_AL_MENU)
			{
				do
				{
					respuestaEliminarArcade = ATRAS;
					printf("\n\t\t<--Menu Bajas de Arcade-->\n");
					printf("\n\t\t<--Lista de Arcades con su salon correspondiente-->\n");
					estadoOperacion = informes_imprimirArcadeConSuSalon(lista_eArcade, lenArcade, lista_eSalon, lenSalon);
					if(utn_comprobarEstadoDeOperacion(estadoOperacion)==1)
					{
						printf("A continuacion ingrese el ID del Arcade que desea dar de baja:");
						idIngresado_eArcade = utn_tomarID(idMaximo_eArcade);
						if(utn_comprobarEstadoDeOperacion(idIngresado_eArcade) && idIngresado_eArcade != ATRAS)
						{
							indiceEncontrado_eArcade = eArcade_encontrarElementoPorId(lista_eArcade, TAM_EARCADE, idIngresado_eArcade);
							if(utn_comprobarEstadoDeOperacion(indiceEncontrado_eArcade))
							{
								estadoOperacion = eSalon_encontrarElementoPorId(lista_eSalon, TAM_ESALON, lista_eArcade[indiceEncontrado_eArcade].idSalon);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									indiceEncontrado_eSalon = estadoOperacion;
									printf("\n\t\t|||--Esta por eliminar un Arcade!!--|||\nEs este el arcade que desea dar de baja??\n");
									estadoOperacion = eArcade_imprimirUnElemento(lista_eArcade[indiceEncontrado_eArcade]);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										printf("\n\t\t<--Datos del Salon al que pertenece el Arcade-->");
										eSalon_imprimirUnElementoCompleto(lista_eSalon[indiceEncontrado_eSalon]);
										estadoOperacion = utn_getInt(&respuestaEliminarArcade, "\n\n1 >>Si, es este mismo arcade \n2 <<No, elegir otro id", "Error. Dato invalido!", SI, NO_ELIMINAR, REINTENTOS);

										if(utn_comprobarEstadoDeOperacion(estadoOperacion) && respuestaEliminarArcade == SI)
										{
											estadoOperacion = utn_getInt(&opcionIngresada, "\nSeguro desea eliminar el arcade especificado?"
													"\n1 >>Si, eliminar! \n2 <<Volver al menu principal",
													"Error, opcion invalida", SI, VOLVER_AL_MENU, REINTENTOS);
											if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada == SI)
											{
												estadoOperacion = eArcade_eliminarElementoPorIndice(lista_eArcade, indiceEncontrado_eArcade);
												if(utn_comprobarEstadoDeOperacion(estadoOperacion))
												{
													printf("\n\t\t<--Eliminacion de Arcade exitosa!!-->\n");
													estadoOperacion = eArcade_verificarSiHayElementos(lista_eArcade, TAM_EARCADE);
													if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion == VACIO)
													{
														printf("\n\t\t<--No quedan mas arcades cargados!!-->\n");
														*bandera_eArcade_hayElementos = NO_HAY_ELEMENTOS_EARCADE;
													}
													retorno = OPERACION_EXITOSA;
												}
											}
										}
									}
								}
							}
						}
					}
				}while(respuestaEliminarArcade == NO_ELIMINAR);
			}
		}
	}
	return retorno;
}

/**
* \brief Opera el menu de informes
* \param eSalon lista_eSalon[] - lista de salones
* \param int lenSalon - len del listado de salones
* \param eArcade lista_eArcade[] - lista de arcades
* \param int lenArcade - len de lista de arcades
* \param int idMaximo_eSalon - id maximo cargado hasta el momento
* \return Retorna INT. Retorna 1 o mayor, que es la cantidad de salones que superan 4 arcades.
* 		  retorna  0 si ningun salon tiene mas de 4 arcades
* 		  Retorna -1 si la direccion de memoria es NULL.
* 		  Retorna -2 si hay el largo del array es invalido
* 		  retorna -22 si no se pudo obtener una respuesta valida al interactuar con el menu.
*/
int menu_OperarMenuInformes(eSalon lista_eSalon[], int lenSalon, eArcade lista_eArcade[], int lenArcade, int idMaximo_eSalon)
{
	char letra;
	char juego[LEN_JUEGO];
	int estadoOperacion;
	int indiceEncontrado_eSalon;
	int idIngresado_eSalon;
	float precioPorFicha;
	int cantidadDeArcadesQueContienenElJuego;
	int cantidadTotalFichas;
	int opcionIngresada;
	float recaudacionTotalPorSalon;
	float promedioArcadePorSalon;
	int retorno = PUNTERO_NULL;

	if(lista_eSalon != NULL && lista_eArcade != NULL)
	{
		retorno = LEN_INVALIDO;
		if(lenArcade >0 && lenArcade <=TAM_EARCADE && lenSalon > 0 && lenSalon <= TAM_ESALON)
		{
			do
			{
				menu_ImprimirMenuInformes();
				letra = 'H';
				retorno = NO_SE_OBTUVO_UNA_RESPUESTA_VALIDA;
				estadoOperacion = utn_getLetra(&letra, "\nIngrese una opcion", "Error. Dato invalido!", 'A', 'J', REINTENTOS);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					retorno = OPERACION_EXITOSA;
					switch(letra)
					{
						case 'A':
							printf("\n\t\t<--Lista de salones con mas de 4 arcades-->");
							eSalon_imprimirEncabezadoDeTabla(MOSTRAR_TODOS_LOS_DATOS_DEL_ELEMENTO);
							estadoOperacion = informes_listarSalonesConMasDeCuatroArcades(lista_eSalon, lenSalon, lista_eArcade, lenArcade);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion == VACIO)
							{
								eSalon_imprimirEncabezadoDeTabla(MOSTRAR_TODO_VACIO);
								printf("\n\t\t<--No hay salones con mas de 4 arcades-->\n");
							}
							break;
						case 'B':
							printf("\n\t\t<--Lista de Arcades para mas de 2 jugadores-->");
							estadoOperacion = informes_arcadesParaMasDeDosJugadores(lista_eArcade, lenArcade, lista_eSalon, lenSalon);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion == VACIO)
							{
								printf("\n\t\t<--No hay arcades para mas de 2 jugadores-->\n");
							}
							break;
						case 'C':
							eSalon_imprimirIdsDisponibles(lista_eSalon, lenSalon);
							estadoOperacion = utn_tomarID(idMaximo_eSalon);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion != ATRAS)
							{
								idIngresado_eSalon = estadoOperacion;
								estadoOperacion = eSalon_encontrarElementoPorId(lista_eSalon, lenSalon, idIngresado_eSalon);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									indiceEncontrado_eSalon = estadoOperacion;
									printf("\n\t\t<--Informacion del salon '%s'-->", lista_eSalon[indiceEncontrado_eSalon].nombre);
									informes_listarInfoDeSalonConCantidadDeArcades(lista_eSalon, indiceEncontrado_eSalon, lista_eArcade, lenArcade, idIngresado_eSalon);
									printf("\n\t\t<--Lista de arcades en el salon '%s'-->", lista_eSalon[indiceEncontrado_eSalon].nombre);
									estadoOperacion = informes_eArcade_imprimirElementosConElIdEspecificado(lista_eArcade, lenArcade, idIngresado_eSalon, MOSTRAR_ID_NOMBRE_DEL_ELEMENTO);
									utn_comprobarEstadoDeOperacion(estadoOperacion);
								}
							}
							break;
						case 'D':
							eSalon_imprimirIdsDisponibles(lista_eSalon, lenSalon);
							estadoOperacion = utn_tomarID(idMaximo_eSalon);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion != ATRAS)
							{
								idIngresado_eSalon = estadoOperacion;
								estadoOperacion = eSalon_encontrarElementoPorId(lista_eSalon, lenSalon, idIngresado_eSalon);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									indiceEncontrado_eSalon = estadoOperacion;
									printf("\n\t\t<--Informacion del salon '%s'-->", lista_eSalon[indiceEncontrado_eSalon].nombre);
									informes_listarSalonConListaDeSusArcades(lista_eSalon[indiceEncontrado_eSalon], lista_eArcade, lenArcade, idIngresado_eSalon);
								}
							}
							break;
						case 'E':
							printf("\n\t\t<--Salon con mas cantidad de arcades-->");
							estadoOperacion = informes_imprimirSalonConMasArcades(lista_eSalon, lenSalon, lista_eArcade, lenArcade);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
							break;
						case 'F':
							printf("\n\t\t<--Recaudacion maxima posible de un salon-->");
							eSalon_imprimirIdsDisponibles(lista_eSalon, lenSalon);
							estadoOperacion = utn_tomarID(idMaximo_eSalon);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion != ATRAS)
							{
								idIngresado_eSalon = estadoOperacion;
								estadoOperacion = informes_eArcade_contadorArcadePorSalon(lista_eArcade, lenArcade, idIngresado_eSalon);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion >VACIO)
								{
									estadoOperacion = eSalon_encontrarElementoPorId(lista_eSalon, lenSalon, idIngresado_eSalon);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										indiceEncontrado_eSalon = estadoOperacion;
										estadoOperacion = utn_getFloat(&precioPorFicha, "Ingrese el precio por cada ficha $(1 - 100)", "Error,  dato invalido",MINIMO_PRECIO_FICHAS ,MAXIMO_PRECIO_FICHAS, REINTENTOS);

										if(utn_comprobarEstadoDeOperacion(estadoOperacion))
										{
											estadoOperacion = informes_CalcularTotalDeRecaudacionPosiblePorSalon(lista_eArcade, lenArcade, precioPorFicha, idIngresado_eSalon, &recaudacionTotalPorSalon);
											if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion > VACIO)
											{
												cantidadTotalFichas = estadoOperacion;
												informes_ImprimirMontoMaximoPorSalon(lista_eSalon[indiceEncontrado_eSalon], recaudacionTotalPorSalon, cantidadTotalFichas, precioPorFicha);
											}
										}
									}
								}
								else
								{
									if(estadoOperacion == VACIO)
									{
										printf("\n\t\t<--No hay arcades en el salon seleccionado!-->");
									}
								}
							}
							break;
						case 'G':
							estadoOperacion = utn_getInt(&opcionIngresada, "\nDesea buscar un juego?\n\t1 >>Si, ingresar nombre de un juego e imprimir los arcades que lo contienen\n\t2 <<No, volver al menu", "Error. Dato invalido!", SI, VOLVER_AL_MENU, REINTENTOS);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada != VOLVER_AL_MENU)
							{
								estadoOperacion = utn_getNombreAlfanumerico(juego, LEN_JUEGO, "Ingrese el juego que desea buscar", "Error, dato invalido!", REINTENTOS);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									estadoOperacion = eArcade_ContarArcadesQueContienenElJuegoEspecificado(lista_eArcade, lenArcade, juego);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion > VACIO)
									{
										cantidadDeArcadesQueContienenElJuego = estadoOperacion;
										printf("\nLa cantidad de arcades que contienen el juego '%s' es: %d", juego, cantidadDeArcadesQueContienenElJuego);
										eArcade_ContarEImprimirArcadesQueContienenElJuegoEspecificado(lista_eArcade, lenArcade, juego);
									}
									else
									{
										if(estadoOperacion == VACIO)
										{
											printf("\n\t\t<--Por el momento, ningun arcade contiene al juego '%s'-->\n", juego);
										}
									}
								}
							}
							break;
						case 'H':
							estadoOperacion = informes_listarSalonesCompletos(lista_eSalon, lenSalon, lista_eArcade, lenArcade);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
							break;
						case 'I':
							estadoOperacion = informes_promedioArcadesPorSalon(lista_eSalon, lenSalon, lista_eArcade, lenArcade, &promedioArcadePorSalon);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion > 0)
							{
								printf("\nEl promedio de arcades por salon es %.2f", promedioArcadePorSalon);
							}
							else
							{
								printf("\n\t\t<--No hay arcades cargados en el sistema para calcular el promedio-->");
							}
							break;
					}
				}
			}while(letra != 'J');
		}
	}
	return retorno;
}
