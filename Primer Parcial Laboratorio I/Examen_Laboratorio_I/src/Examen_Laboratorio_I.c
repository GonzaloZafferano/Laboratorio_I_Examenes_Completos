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
#include "Salon.h"
#include "Arcade.h"
#include "ComprobarErrores.h"
#include "menu.h"
#include "Utn_tomarDatos.h"
#include "Informes.h"

#define TAM_ESALON 100
#define TAM_EARCADE 1000
#define SALIR 1
#define MOSTRAR_ID_NOMBRE_DEL_ELEMENTO 2
#define SI 1
#define NO 0
#define VACIO 0
#define ATRAS 0
#define NO_ELIMINAR 2
#define OPCION_SALIR 10
#define MENU_ARCADE_MODIFICAR_JUEGO 1
#define MENU_ARCADE_MODIFICACION_MINIMO 1
#define MENU_ARCADE_MODIFICACION_MAXIMO 3
#define VOLVER_AL_MENU 2
#define NO_HAY_ELEMENTOS_ESALON 0
#define NO_HAY_ELEMENTOS_EARCADE 1
#define HAY_ELEMENTOS_ESALON 2
#define HAY_ELEMENTOS_EARCADE 3
#define ALTA_SALON 1
#define ELIMINAR_SALON 2
#define IMPRIMIR_SALONES 3
#define INCORPORAR_ARCADE 4
#define MODIFICAR_ARCADE 5
#define ELIMINAR_ARCADE 6
#define IMPRIMIR_ARCADES 7
#define IMPRIMIR_JUEGOS 8
#define INFORMES 9
#define REINTENTOS 2

int main(void)
{
	setbuf(stdout, NULL);
	int opcionIngresada;
	int estadoOperacion;
	int idMaximo_eSalon;
	int idMaximo_eArcade;
	int salirDelPrograma;
	eSalon lista_eSalon[TAM_ESALON];
	eArcade lista_eArcade[TAM_EARCADE];
	int bandera_eSalon_hayElementos = NO_HAY_ELEMENTOS_ESALON;
	int bandera_eArcade_hayElementos = NO_HAY_ELEMENTOS_ESALON;

	estadoOperacion = eSalon_inicializarBanderas(lista_eSalon, TAM_ESALON);
	if(utn_comprobarEstadoDeOperacion(estadoOperacion))
	{
		estadoOperacion = eArcade_inicializarBanderas(lista_eArcade, TAM_EARCADE);
		if(utn_comprobarEstadoDeOperacion(estadoOperacion))
		{
/*
			eSalon_forzarAltas(lista_eSalon, TAM_ESALON, 0, &idMaximo_eSalon, "Gonzalo", "Calle 123", 1, &bandera_eSalon_hayElementos, &bandera_eArcade_hayElementos);
			eSalon_forzarAltas(lista_eSalon, TAM_ESALON, 1, &idMaximo_eSalon, "Sila", "Av mayo 1500",  1, &bandera_eSalon_hayElementos, &bandera_eArcade_hayElementos);
			eSalon_forzarAltas(lista_eSalon, TAM_ESALON, 2, &idMaximo_eSalon, "Las Toscas", "Av 888",  1, &bandera_eSalon_hayElementos, &bandera_eArcade_hayElementos);
			eSalon_forzarAltas(lista_eSalon, TAM_ESALON, 3, &idMaximo_eSalon, "La Casa Del Juego", "Barrio 123", 2, &bandera_eSalon_hayElementos, &bandera_eArcade_hayElementos);
			eSalon_forzarAltas(lista_eSalon, TAM_ESALON, 4, &idMaximo_eSalon, "Juego Magno", "San Martin 1789", 2, &bandera_eSalon_hayElementos, &bandera_eArcade_hayElementos);

			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 0, &idMaximo_eArcade, 3, "Argentina", "Dragon Ball", 33,2, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 1, &idMaximo_eArcade, 1, "Uruguay", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 2, &idMaximo_eArcade, 2, "Usa", "Dark Souls", 40, 6,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 3, &idMaximo_eArcade, 1, "Usa", "Dark Souls", 50,4 ,1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 4, &idMaximo_eArcade, 2, "Italia", "Dungeons And Dragons", 60, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 5, &idMaximo_eArcade, 3, "Brasil", "Mortal Kombat", 90, 3,1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 6, &idMaximo_eArcade, 4, "Argentina", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 7, &idMaximo_eArcade, 5, "Usa", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 8, &idMaximo_eArcade, 3, "Uruguay", "Dragon Ball", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 9, &idMaximo_eArcade, 3, "Argentina", "Dark Souls", 40, 6,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 10, &idMaximo_eArcade, 2, "Brasil", "Dark Souls", 50,4 ,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 11, &idMaximo_eArcade, 1, "Chile", "Dungeons And Dragons", 60, 2,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 12, &idMaximo_eArcade, 2, "Espania", "Mortal Kombat", 90, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 13, &idMaximo_eArcade, 1, "Argentina", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 14, &idMaximo_eArcade, 3, "Espania", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 15, &idMaximo_eArcade, 5, "Canada", "Dark Souls", 40, 6,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 16, &idMaximo_eArcade, 5, "Francia", "Dark Souls", 50,4 ,1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 17, &idMaximo_eArcade, 2, "Inglaterra", "Dungeons And Dragons", 60, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 18, &idMaximo_eArcade, 4, "Francia", "Mortal Kombat", 90, 3,1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 19, &idMaximo_eArcade, 2, "Espania", "Contra", 33,4, 2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 20, &idMaximo_eArcade, 4, "Brasil", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 21, &idMaximo_eArcade, 4, "Francia", "Dark Souls", 40, 6,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 22, &idMaximo_eArcade, 1, "Usa", "Dragon Ball", 50,4 ,1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 23, &idMaximo_eArcade, 5, "Italia", "Dungeons And Dragons", 60, 2,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 24, &idMaximo_eArcade, 5, "Italia", "Mortal Kombat", 90, 3,1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 25, &idMaximo_eArcade, 2, "Brasil", "Dark Souls", 50,2 ,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 26, &idMaximo_eArcade, 1, "Chile", "Dungeons And Dragons", 60, 2,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 27, &idMaximo_eArcade, 2, "Espania", "Mortal Kombat", 90, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 28, &idMaximo_eArcade, 3, "Argentina", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 29, &idMaximo_eArcade, 3, "Brasil", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 30, &idMaximo_eArcade, 4, "Canada", "Contra", 33,4, 1, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 31, &idMaximo_eArcade, 2, "Canada", "Contra", 33,4, 2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 32, &idMaximo_eArcade, 4, "Usa", "Dark Souls", 40, 6,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 33, &idMaximo_eArcade, 4, "Italia", "Dungeons And Dragons", 60, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 34, &idMaximo_eArcade, 4, "Brasil", "Dark Souls", 50,4 ,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 35, &idMaximo_eArcade, 3, "Espania", "Contra", 33,4, 2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 36, &idMaximo_eArcade, 4, "Canada", "Contra", 33,4, 2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 37, &idMaximo_eArcade, 4, "Brasil", "Dark Souls", 50,3 ,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 38, &idMaximo_eArcade, 4, "Espania", "Mortal Kombat", 90, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 39, &idMaximo_eArcade, 4, "Inglaterra", "Dungeons And Dragons", 60, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 40, &idMaximo_eArcade, 2, "Espania", "Mortal Kombat", 90, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 41, &idMaximo_eArcade, 2, "Usa", "Dark Souls", 40, 6,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 42, &idMaximo_eArcade, 2, "Italia", "Dungeons And Dragons", 60, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 43, &idMaximo_eArcade, 2, "Brasil", "Dark Souls", 50,4 ,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 44, &idMaximo_eArcade, 2, "Espania", "Contra", 33,4, 2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 45, &idMaximo_eArcade, 2, "Canada", "Contra", 33,4, 2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 46, &idMaximo_eArcade, 2, "Brasil", "Dark Souls", 50,2 ,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 47, &idMaximo_eArcade, 2, "Espania", "Mortal Kombat", 90, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 48, &idMaximo_eArcade, 2, "Inglaterra", "Dungeons And Dragons", 60, 3,2, &bandera_eArcade_hayElementos);
			eArcade_forzarAltas(lista_eArcade, TAM_EARCADE, 49, &idMaximo_eArcade, 4, "Espania", "Mortal Kombat", 90, 3,2, &bandera_eArcade_hayElementos);
*/
			do
			{
				menu_ImprimirMenuPrincipal();
				estadoOperacion = utn_ingreseUnaOpcion(&opcionIngresada, ALTA_SALON, OPCION_SALIR);
				if(utn_comprobarEstadoDeOperacion(estadoOperacion))
				{
					switch(opcionIngresada)
					{
						case ALTA_SALON:
							estadoOperacion = menu_OperarMenuAltaDeSalon(lista_eSalon, TAM_ESALON, &idMaximo_eSalon, &bandera_eSalon_hayElementos, &bandera_eArcade_hayElementos);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
							break;
						case ELIMINAR_SALON:
							if(menu_EsPosibleOperarMenu(bandera_eSalon_hayElementos))
							{
								estadoOperacion = menu_OperarMenuEliminacionDeSalon(lista_eSalon, TAM_ESALON, lista_eArcade, TAM_EARCADE, &bandera_eArcade_hayElementos, &bandera_eSalon_hayElementos, idMaximo_eSalon);
								utn_comprobarEstadoDeOperacion(estadoOperacion);
							}
							break;
						case IMPRIMIR_SALONES:
							if(menu_EsPosibleOperarMenu(bandera_eSalon_hayElementos))
							{
								estadoOperacion = eSalon_imprimirTodosLosElementos(lista_eSalon, TAM_ESALON);
								utn_comprobarEstadoDeOperacion(estadoOperacion);
							}
							break;
						case INCORPORAR_ARCADE:
							if(menu_EsPosibleOperarMenu(bandera_eSalon_hayElementos))
							{
								estadoOperacion = menu_OperarMenuAltaDeArcade(lista_eArcade, TAM_EARCADE, lista_eSalon, TAM_ESALON, idMaximo_eSalon, &bandera_eArcade_hayElementos, &idMaximo_eArcade);
								utn_comprobarEstadoDeOperacion(estadoOperacion);
							}
							break;
						case MODIFICAR_ARCADE:
							if(menu_EsPosibleOperarMenu(bandera_eArcade_hayElementos))
							{
								estadoOperacion = menu_OperarMenuModificacionDeArcade(lista_eArcade, TAM_EARCADE,idMaximo_eArcade);
								utn_comprobarEstadoDeOperacion(estadoOperacion);
							}
							break;
						case ELIMINAR_ARCADE:
							if(menu_EsPosibleOperarMenu(bandera_eArcade_hayElementos))
						    {
								estadoOperacion = menu_OperarMenuEliminacionDeArcade(lista_eArcade, TAM_EARCADE, lista_eSalon, TAM_ESALON, idMaximo_eArcade,&bandera_eArcade_hayElementos);
								utn_comprobarEstadoDeOperacion(estadoOperacion);
							}
							break;
						case IMPRIMIR_ARCADES:
						    if(menu_EsPosibleOperarMenu(bandera_eArcade_hayElementos))
							{
								eArcade_imprimirTodosLosElementos(lista_eArcade, TAM_EARCADE);
							}
							break;
						case IMPRIMIR_JUEGOS:
							if(menu_EsPosibleOperarMenu(bandera_eArcade_hayElementos))
							{
								printf("\n\t\t<--Lista de juegos cargados en el sistema-->");
								informes_imprimirListaDeJuegos(lista_eArcade, TAM_EARCADE);
							}
							break;
						case INFORMES:
							if(menu_EsPosibleOperarMenu(bandera_eArcade_hayElementos))
							{
								menu_OperarMenuInformes(lista_eSalon, TAM_ESALON, lista_eArcade, TAM_EARCADE, idMaximo_eSalon);
							}
							break;
						case OPCION_SALIR:
							estadoOperacion = utn_getInt(&opcionIngresada, "\nSeguro desea salir?\n\t1 >>Si, finalizar el programa\n\t2 <<Volver al menu principal", "Error. Dato invalido", SI, VOLVER_AL_MENU, REINTENTOS);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionIngresada == SI)
							{
								salirDelPrograma = SALIR;
							}
							break;
					}
				}
			}while(salirDelPrograma != SALIR);
		}
	}
	printf("\n\n\t\t<--Fin del Programa-->");

	return EXIT_SUCCESS;
}
