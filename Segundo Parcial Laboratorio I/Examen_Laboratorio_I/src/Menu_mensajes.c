/*
 * Menu.c
 *
 *  Created on: 5 nov 2021
 *      Author: GONZALO
 */

#include "Menu_mensajes.h"

#define AMBOS_ARCHIVOS_CARGADOS 0
#define ARCHIVO_MULTIJUGADOR_CARGADO 3
#define ARCHIVO_JUEGOS_CARGADO 2
#define NINGUN_ARCHIVO_CARGADO 4
#define OFRECER_CRITERIO 0
#define ORDENAR_POR_NOMBRE 0
#define ELEGIR_CRITERIO 1
#define ORDEN 2
#define SI 1
#define NO 2
#define VOLVER 2
#define ERROR_PUNTERO_NULL -1
#define DAR_BAJA 1
#define CONFIRMAR_BAJA 2
#define ASCENDENTE 1
#define DESCENDENTE 0
#define MINIMO_MENU_ORDEN 1
#define MAXIMO_MENU_ORDEN 7
#define MINIMO_MENU_MODIFICACION 1
#define MAXIMO_MENU_MODIFICACION 3
#define MODIFICAR 1
#define MODIFICAR_CAMPOS 2
#define MINIMO_OPCION_MENU_PRINCIPAL 1
#define MAXIMO_OPCION_MENU_PRINCIPAL 9
#define MOSTRAR_LISTA 1
#define GUARDAR_LISTA 2
#define ERROR_SIN_MAS_REINTENTOS -21
#define OBTENER_ACTUAL_ULTIMO_ID 1

/*
* \brief Imprime el menu principal y toma una respuesta
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuPrincipal(int* pRespuesta)
{
	int estadoOperacion;
	static int banderaMenu = 0;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
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
				"\n1 >>Leer Arcades desde archivo 'arcades.csv'"
				"\n2 >>Incorporar Arcades"
				"\n3 >>Modificar Arcade"
				"\n4 >>Eliminar Arcade"
				"\n5 >>Imprimir lista de Arcades"
				"\n6 >>Generar archivo con lista de juegos"
				"\n7 >>Generar archivo con lista de arcades 'Multijugador'"
				"\n8 >>Actualizar cantidad de fichas"
				"\n9 <<Salir");

    	estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, MINIMO_OPCION_MENU_PRINCIPAL, MAXIMO_OPCION_MENU_PRINCIPAL);
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de consulta para mostrar o guardar la lista clonada y toma una respuesta
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuGuardarListaArchivo(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Carga Archivos-->");
		switch(opcion)
		{
			case MOSTRAR_LISTA:
				printf("\nUn momento! No se pudieron cargar todos los elementos del archivo!"
						"\nDesea imprimir los elementos que se lograron cargar hasta el momento??\n\t1 >>Si, mostrar listado que se cargo correctamente del archivo\n\t2 <<No, no mostrar");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case GUARDAR_LISTA:
				printf("\n\nDesea guardar en la lista del sistema los elementos que se lograron cargar del archivo?\n\t1 >>Si, guardar la lista!\n\t2 <<No, descartar elementos y volver al menu!");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de altas y toma una respuesta
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuAltas(int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Altas-->");
		printf("\nDesea dar un alta? \n\t1 >>Si, dar una alta.\n\t2 <<No, volver al menu principal");
    	estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de modificacion y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuModificacion(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Modificacion-->");
		switch(opcion)
		{
			case MODIFICAR:
				printf("\nDesea realizar una modificacion? \n\t1 >>Si, hacer una modificacion.\n\t2 <<No, volver al menu principal");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case MODIFICAR_CAMPOS:
				printf("\nPor favor, seleccione el campo que desea modificar"
						"\n1 >>Nombre del Juego"
						"\n2 >>Cantidad de Jugadores"
						"\n3 >>Atras");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, MINIMO_MENU_MODIFICACION, MAXIMO_MENU_MODIFICACION);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de ordenamiento y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuListarArcades(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu listar Arcades-->");
		switch(opcion)
		{
			case OFRECER_CRITERIO:
				printf("\nPor defecto se imprimira el listado Ordenado por nombre de juego."
						"\nDesea ordenar por algun otro criterio??"
									"\n\t0 >>No, imprimir ordenado por nombre"
									"\n\t1 >>Si, ordenar por otro criterio"
									"\n\t2 <<Volver al menu principal");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, ORDENAR_POR_NOMBRE, VOLVER);
				break;
			case ELEGIR_CRITERIO:
				printf("\nIngrese criterio de ordenamiento"
					"\n1 >>Ordenar por ID"
					"\n2 >>Ordenar por Nacionalidad"
					"\n3 >>Ordenar por nombre de salon"
					"\n4 >>Ordenar por tipo de sonido"
					"\n5 >>Ordenar por cantidad de jugadores"
					"\n6 >>Ordenar por capacidad de fichas"
					"\n7 <<Volver al menu principal");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, MINIMO_MENU_ORDEN, MAXIMO_MENU_ORDEN);
				break;
			case ORDEN:
				printf("\nIngrese el orden en el que desea imprimir la lista\n0 >>Descendente \n1 >>Ascendente");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, DESCENDENTE, ASCENDENTE);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de Bajas y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuBajas(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Bajas-->");
		switch(opcion)
		{
			case DAR_BAJA:
				printf("\nDesea dar una baja? \n\t1 >>Si, dar una baja.\n\t2 <<No, volver al menu principal");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case CONFIRMAR_BAJA:
				printf("\nSeguro quiere eliminar este empleado?\n\t1 >>Si, eliminar\n\t2 <<No, volver al menu principal");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de actualizacion de archivo, para confirmar la actualizacion
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuActualizacionArchivo(int* pRespuesta)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Actualizacion de Archivo-->");
		printf("\nDesea guardar el archivo de todas formas, con las actualizaciones que se pudieron llevar a cabo??\n\t1 >>Si, guardar archivo\n\t2 <<No, no guardar y volver al menu principal");
		retorno = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
	}
	return retorno;
}

/*
* \brief Imprime el menu de SALIR y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuSalir(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Salir de Aplicacion-->");
		switch(opcion)
		{
			case 1:
				printf("\nSeguro desea salir?\n\t1 >>Si, salir de la aplicacion.\n\t2 <<No, no salir.");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case 2:
				printf("\nUn momento! El archivo de arcades Multijugador (opcion 7) no se ha generado / actualizado!"
						"\nDesea generarlo / actualizarlo? (Se recomienda actualizar ante Altas, bajas o modificaciones)"
						"\n\t1 >>Si, generar / actualizar archivo y salir de la aplicacion!"
						"\n\t2 <<No, deseo salir de la aplicacion!");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case 3:
				printf("\nUn momento! El archivo de juegos (opcion 6) no se ha generado / actualizado!"
						"\nDesea generarlo / actualizarlo? (Se recomienda actualizar ante Altas, bajas o modificaciones)"
						"\n\t1 >>Si, generar / actualizar archivo y salir de la aplicacion!"
						"\n\t2 <<No, deseo salir de la aplicacion!");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case 4:
				printf("\nUn momento! El archivo de arcades Multijugador y el archivo de Juegos no se han generado / actualizado!"
						"\nDesea generarlos / actualizarlos? (Se recomienda actualizar ante Altas, bajas o modificaciones)"
						"\n\t1 >>Si, generar / actualizar archivos y salir de la aplicacion!"
						"\n\t2 <<No, deseo salir de la aplicacion!");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Verifica el estado de cargas del archivo multijugador y de juegos.
* \param int banderaCargaArchivoJuegos - Valor que identifica el estado de carga del archivo de juegos
* \param int banderaCargaArchivoMultijugador - Valor que identifica el estado de carga del archivo multijugador
* \return retorna un INT. 0 si ambos archivos estan cargados
* 		  retorna 1 si solo esta cargado el archivo multijugador
* 		  retorna 2 si solo esta cargado el archivo juegos
* 		  retorna 4 si ningun archivo esta cargado
*/
int menu_VerificarCargasDeArchivosParaSalir(int banderaCargaArchivoJuegos, int banderaCargaArchivoMultijugador)
{
	int retorno = AMBOS_ARCHIVOS_CARGADOS;

	if(!banderaCargaArchivoMultijugador && !banderaCargaArchivoJuegos)
	{
		retorno = NINGUN_ARCHIVO_CARGADO;
	}
	else
	{
		if(!banderaCargaArchivoJuegos)
		{
			retorno = ARCHIVO_MULTIJUGADOR_CARGADO;
		}
		else
		{
			if(!banderaCargaArchivoMultijugador)
			{
				retorno = ARCHIVO_JUEGOS_CARGADO;
			}
		}
	}
	return retorno;
}

/*
* \brief Toma el Id del empleado con el que se quiere operar.
* \return Retorna INT. Retorna un numero positivo que es el ID ingresado por el usuario,
*         retorno -21 si se quedo sin reintentos para ingresar el ID
*/
int menu_imprimirMenuTomaDeId()
{
	int id;
	int estadoOperacion;
	int idMaximo = eArcade_getLastOrNextId(OBTENER_ACTUAL_ULTIMO_ID);
	int retorno = ERROR_SIN_MAS_REINTENTOS;

	if(idMaximo >0)
	{
		printf("\n\t\t<--Menu Toma de ID-->\n>>Ingrese un Id valido. \n<<O pulse '0' para Volver al menu");
		estadoOperacion = utn_ingreseUnaOpcion(&id, 0, idMaximo);
		if(!estadoOperacion)
		{
			retorno = id;
		}
	}
	return retorno;
}

/*
* \brief Evalua si es posible realizar una operacion del menu. Si es posible, no realiza acciones.
*        Si no es posible, informa el motivo.
* \param int bandera - Valor que identifica la posibilidad de realizar una operacion.
* \return retorna un INT. 1 si es posible realizar la operacion en base a la bandera recibida.
* 		  retorna 0 si la operacion no puede ser realizada.
*/
int menu_EsPosibleOperarMenu(int bandera)
{
	int retorno = 0;
	switch(bandera)
	{
		case 0:
			printf("\n\t\t<--Un momento! Para operar primero debe cargar el archivo 'arcades.csv'! (Op. 1)-->\n");
			break;
		case 1:
			printf("\n\t\t<--Un momento! Ya hay datos cargados en el sistema!-->\n");
			break;
		case 2:
			printf("\n\t\t<--Un momento! Para operar primero debe dar un alta en el sistema! (Op. 2)-->\n");
			break;
		case 3:
			printf("\n\t\t<--Un momento! Se detecto que el archivo 'arcades.csv' esta vacio!-->"
				"\n\t\t<--Se habilita el alta de arcades (Op. 2)-->\n");
			break;
		case 4:
			printf("\n\t\t<--Un momento! Se detecto que el archivo 'arcades.csv' no existe!-->"
				"\n\t\t<--Se habilita el alta de arcades (Op. 2)-->\n");
			break;
		case 5:
			printf("\n\t\t<--Un momento! Ya se ha cargado el archivo!!-->\n");
			break;
		default:
			retorno = 1;
			break;
	}
	return retorno;
}

/*
* \brief Imprime el menu de actualizacion de fichas y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \return Retorna INT. Retorna 2 ante una respueste negativa (por defecto)
* 					   retorna 1 ante una respuesta positiva
*/
int menu_actualizarFichas(int opcion)
{
	int opcionElegida;
	int retorno = NO;
	printf("\n\t\t<--Menu Actualizar Fichas-->");
	switch(opcion)
	{
	case 1:
		printf("\nDesea aplicar una actualizacion a la cantidad de fichas? "
				"El limite de fichas posibles es 10000."
				"\n\t1 >>Si, aplicar una actualizacion"
				"\n\t2 <<No, volver al menu principal");
		break;
	case 2:
		printf("\nUn momento! Ya aplic? la actualizacion de las fichas previamente!"
				"\nDesea aplicar una nueva actualizacion? (el limite de fichas posibles es 10000)"
				"\n\t1 >>Si, aplicar otra nueva actualizacion"
				"\n\t2 <<No, volver al menu principal");
		break;
	}
	if(utn_comprobarEstadoDeOperacion(utn_ingreseUnaOpcion(&opcionElegida, SI, NO)))
	{
		retorno = opcionElegida;
	}
	return retorno;
}

/*
* \brief Imprime la cantidad de cargas realizadas desde el archivo al sistema, con la opcion 1 o 2 del Menu
* \param int contador - Cantidad de cargas realizadas al sistema
* \param int estadoOperacion - estado de la operacion de cargas
* \return VOID
*/
void menu_imprimirCantidadCargasDesdeArchivo(int contador, int estadoOperacion)
{
	if(contador == 0 && !estadoOperacion)
	{
		printf("\n\t\t<--Se completo la carga del archivo, pero el mismo se encontraba vacio!-->\n");
	}
	else
	{
		if(contador >=0)
		{
			printf("\n\t\t<--Se han cargado %d elementos del archivo a la lista!-->\n", contador);
		}
	}
}

/*
* \brief Informa que no hay elementos para cargar en el informe,
* 		y consulta al usuario confirmacion para guardar una lista vacia
* \return INT - retorna 1 si se guardara una lista vacia, 2 si se decide no guardar (rta por defecto)
*/
int menu_cargarListaMultijugadorVacia()
{
	int respuesta;
	int retorno = NO;
	printf("\n\t\t<--Menu Carga Archivo de arcades Multijugador-->");
	printf("\nUn momento! No hay arcades multijugador, desea guardar una lista vacia?"
			"\n\t1 >>Si, guardar lista vacia"
			"\n\t2 <<No, no guardar lista vacia");
	if(utn_comprobarEstadoDeOperacion(utn_ingreseUnaOpcion(&respuesta, SI, NO)))
	{
		retorno = respuesta;
	}
	return retorno;
}

/*
* \brief Informa que no hay elementos para cargar en el informe,
* 		y consulta al usuario confirmacion para guardar una lista vacia
* \return INT - retorna 1 si se guardara una lista vacia, 2 si se decide no guardar (rta por defecto)
*/
int menu_cargarListaJuegosVacia()
{
	int respuesta;
	int retorno = NO;
	printf("\n\t\t<--Menu Carga Archivo de Juegos-->");
	printf("\nUn momento! No se encontraron juegos, desea guardar una lista vacia?"
			"\n\t1 >>Si, guardar lista vacia"
			"\n\t2 <<No, no guardar lista vacia");
	if(utn_comprobarEstadoDeOperacion(utn_ingreseUnaOpcion(&respuesta, SI, NO)))
	{
		retorno = respuesta;
	}
	return retorno;
}
