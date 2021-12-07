/*
 * Menu.h
 *
 *  Created on: 5 nov 2021
 *      Author: GONZALO
 */

#ifndef MENU_MENSAJES_H_
#define MENU_MENSAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include "Utn_tomarDatos.h"
#include "Arcade.h"

int menu_ImprimirMenuPrincipal(int* pRespuesta);
int menu_ImprimirMenuGuardarListaArchivo(int opcion, int* pRespuesta);
int menu_ImprimirMenuAltas(int* pRespuesta);
int menu_ImprimirMenuModificacion(int opcion, int* pRespuesta);
int menu_ImprimirMenuListarArcades(int opcion, int* pRespuesta);
int menu_ImprimirMenuBajas(int opcion, int* pRespuesta);
int menu_ImprimirMenuActualizacionArchivo(int* pRespuesta);
int menu_ImprimirMenuSalir(int opcion, int* pRespuesta);
int menu_VerificarCargasDeArchivosParaSalir(int banderaCargaArchivoJuegos, int banderaCargaArchivoMultijugador);
int menu_imprimirMenuTomaDeId();
int menu_EsPosibleOperarMenu(int bandera);
int menu_actualizarFichas(int opcion);
void menu_imprimirCantidadCargasDesdeArchivo(int contador, int estadoOperacion);
int menu_cargarListaMultijugadorVacia();
int menu_cargarListaJuegosVacia();

#endif /* MENU_MENSAJES_H_ */
