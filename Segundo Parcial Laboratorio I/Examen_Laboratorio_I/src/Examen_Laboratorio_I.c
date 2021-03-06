/*
 ============================================================================
 Name        : Examen_Laboratorio_I.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Arcade.h"
#include "Controller.h"

#define LEN_ARCHIVO 51
#define PRIMER_INGRESO 1
#define ARCHIVO_CARGADO 5
#define ARCHIVO_VACIO 3
#define ARCHIVO_NO_EXISTE 4
#define NO_HAY_ARCHIVO_EN_SISTEMA 0
#define SE_PUEDE_CARGAR_ARCHIVO 10
#define SE_PUEDE_OPERAR 10
#define NO_SE_PUEDE_OPERAR 2
#define HAY_DATOS_EN_SISTEMA 1
#define SALIR_APLICACION 15
#define SE_PUEDE_ACTUALIZAR 0
#define YA_SE_ACTUALIZARON_FICHAS 1
#define ARCHIVO_SIN_ACTUALIZAR 0
#define ARCHIVO_ACTUALIZADO 1
#define SI 1
#define SALIR 9
#define APLICAR_ACTUALIZACION 1
#define APLICAR_NUEVA_ACTUALIZACON 2
#define NO 2

int main(void)
{
	setbuf(stdout, NULL);
	int opcionElegida;
	int estadoOperacion;
	int banderaCargarJuegosYMultijugador = NO_HAY_ARCHIVO_EN_SISTEMA;
	int banderaCargarArchivo = SE_PUEDE_CARGAR_ARCHIVO;
	int banderaOperarAltas = NO_HAY_ARCHIVO_EN_SISTEMA;
	int banderaOperarMenu = NO_HAY_ARCHIVO_EN_SISTEMA;
	int banderaJuegosActualizados = ARCHIVO_ACTUALIZADO;
	int banderaMultijugador = ARCHIVO_ACTUALIZADO;
	int banderaActualizarFichas = SE_PUEDE_ACTUALIZAR;
	char pathArchivoJuegos[LEN_ARCHIVO] = "juegos.txt";
	char pathArchivoArcades[LEN_ARCHIVO] = "arcades.csv";
	char pathArchivoArcadesMultijugador[LEN_ARCHIVO] = "multijugador.csv";
	LinkedList* punteroALinkedlistArcade;

	punteroALinkedlistArcade = ll_newLinkedList();
	if(punteroALinkedlistArcade != NULL && eArcade_getLastOrNextId(PRIMER_INGRESO) >= 0)
	{
		do{
			estadoOperacion = menu_ImprimirMenuPrincipal(&opcionElegida);
			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				switch(opcionElegida)
				{
					case 1:
						if(menu_EsPosibleOperarMenu(banderaCargarArchivo))
						{
							if(!controller_existeArchivo(pathArchivoArcades))
							{
								estadoOperacion = controller_loadFromText(pathArchivoArcades, punteroALinkedlistArcade);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion) && !estadoOperacion)
								{
									banderaCargarArchivo = ARCHIVO_CARGADO;
									banderaOperarAltas = SE_PUEDE_OPERAR;
									banderaCargarJuegosYMultijugador = SE_PUEDE_OPERAR;
									banderaOperarMenu = SE_PUEDE_OPERAR;
									if(ll_isEmpty(punteroALinkedlistArcade))
									{
										menu_EsPosibleOperarMenu(ARCHIVO_VACIO);
										banderaOperarMenu = NO_SE_PUEDE_OPERAR;
										banderaCargarJuegosYMultijugador = NO_SE_PUEDE_OPERAR;
										banderaCargarArchivo = ARCHIVO_VACIO;
									}
								}
							}
							else
							{
								menu_EsPosibleOperarMenu(ARCHIVO_NO_EXISTE);
								banderaOperarAltas = SE_PUEDE_OPERAR;
								banderaOperarMenu = NO_SE_PUEDE_OPERAR;
								banderaCargarArchivo = ARCHIVO_NO_EXISTE;
								banderaCargarJuegosYMultijugador = NO_SE_PUEDE_OPERAR;

							}
						}
						break;
					case 2:
						if(menu_EsPosibleOperarMenu(banderaOperarAltas))
						{
							estadoOperacion = controller_addArcade(punteroALinkedlistArcade, pathArchivoArcades);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && !estadoOperacion)
							{
								banderaOperarMenu = SE_PUEDE_OPERAR;
								banderaCargarArchivo = HAY_DATOS_EN_SISTEMA;
								banderaJuegosActualizados = ARCHIVO_SIN_ACTUALIZAR;
								banderaMultijugador = ARCHIVO_SIN_ACTUALIZAR;
								banderaCargarJuegosYMultijugador = SE_PUEDE_OPERAR;
							}
						}
						break;
					case 3:
						if(menu_EsPosibleOperarMenu(banderaOperarMenu))
						{
							estadoOperacion= controller_editArcade(punteroALinkedlistArcade, pathArchivoArcades);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								banderaJuegosActualizados = ARCHIVO_SIN_ACTUALIZAR;
								banderaMultijugador = ARCHIVO_SIN_ACTUALIZAR;
							}
						}
						break;
					case 4:
						if(menu_EsPosibleOperarMenu(banderaOperarMenu))
						{
							estadoOperacion = controller_removeArcade(punteroALinkedlistArcade, pathArchivoArcades);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								banderaMultijugador = ARCHIVO_SIN_ACTUALIZAR;
								banderaJuegosActualizados = ARCHIVO_SIN_ACTUALIZAR;
								if(ll_isEmpty(punteroALinkedlistArcade))
								{
									banderaOperarMenu = NO_SE_PUEDE_OPERAR;
									banderaCargarArchivo = ARCHIVO_VACIO;
								}
							}
						}
						break;
					case 5:
						if(menu_EsPosibleOperarMenu(banderaOperarMenu))
						{
							estadoOperacion = controller_listarArcadesOrdenados(punteroALinkedlistArcade);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
						}
						break;
					case 6:
						if(menu_EsPosibleOperarMenu(banderaCargarJuegosYMultijugador))
						{
							estadoOperacion = controller_generarArchivoDeJuegos(punteroALinkedlistArcade, pathArchivoJuegos);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion != NO)
							{
								banderaJuegosActualizados = ARCHIVO_ACTUALIZADO;
							}
						}
						break;
					case 7:
						if(menu_EsPosibleOperarMenu(banderaCargarJuegosYMultijugador))
						{
							estadoOperacion = controller_generarArchivoConArcadesMultijugador(punteroALinkedlistArcade, pathArchivoArcadesMultijugador);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion != NO)
							{
								banderaMultijugador = ARCHIVO_ACTUALIZADO;
							}
						}
						break;
					case 8:
						if(menu_EsPosibleOperarMenu(banderaOperarMenu))
						{
							if(menu_actualizarFichas(APLICAR_ACTUALIZACION) == SI)
							{
								if(!banderaActualizarFichas || menu_actualizarFichas(APLICAR_NUEVA_ACTUALIZACON)== SI)
								{
									estadoOperacion = controller_actualizarCantidadDeFichas(punteroALinkedlistArcade, pathArchivoArcades);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										banderaActualizarFichas = YA_SE_ACTUALIZARON_FICHAS;
									}
								}
							}
						}
						break;
					case SALIR:
						if(banderaCargarArchivo != SE_PUEDE_CARGAR_ARCHIVO && controller_existeArchivo(pathArchivoArcadesMultijugador))
						{
							banderaMultijugador = ARCHIVO_SIN_ACTUALIZAR;
						}
						if(banderaCargarArchivo != SE_PUEDE_CARGAR_ARCHIVO && controller_existeArchivo(pathArchivoJuegos))
						{
							banderaJuegosActualizados = ARCHIVO_SIN_ACTUALIZAR;
						}
						estadoOperacion = controller_exitApp(punteroALinkedlistArcade, pathArchivoJuegos, pathArchivoArcadesMultijugador, banderaJuegosActualizados, banderaMultijugador);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion) && estadoOperacion == SALIR_APLICACION)
						{
							eArcade_liberarListaDeMemoria(punteroALinkedlistArcade);
							opcionElegida = SALIR_APLICACION;
						}
						break;
				}
			}
		}while(opcionElegida != SALIR_APLICACION);
	}
	printf("\n\t\t<--Fin del Programa-->");
	return EXIT_SUCCESS;
}
