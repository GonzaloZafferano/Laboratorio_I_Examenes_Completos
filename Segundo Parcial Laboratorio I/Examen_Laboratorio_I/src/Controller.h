/*
 * Controller.h
 *
 *  Created on: 5 nov 2021
 *      Author: GONZALO
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "ComprobarErrores.h"
#include "Utn_tomarDatos.h"
#include "parser.h"
#include "Menu_mensajes.h"
#include "Arcade.h"
#include "EntidadAuxiliar.h"

int controller_loadFromText(char* pathArchivo, LinkedList* pLinkedListArcades);
int controller_loadFromBinary(char* pathArchivo, LinkedList* pLinkedListArcades);
int controller_loadJuegosFromTxt(LinkedList* pLinkedListJuegos, char* pathArchivo);
int controller_addArcade(LinkedList* pLinkedListArcades, char* pathArchivo);
int controller_editArcade(LinkedList* pLinkedListArcades, char* pathArchivo);
int controller_removeArcade(LinkedList* pLinkedListArcades, char* pathArchivo);
int controller_listarArcadesOrdenados(LinkedList* pLinkedListArcades);
LinkedList* generarListaDeJuegosSinRepetir(LinkedList* pLinkedListArcades);
int controller_saveAsText(char* pathArchivo , LinkedList* pLinkedListArcades);
int controller_saveAsBinary(char* pathArchivo, LinkedList* pLinkedListArcades);
int controller_generarArchivoDeJuegos(LinkedList* pLinkedListArcades, char* pathArchivoJuegos);
int controller_generarArchivoConArcadesMultijugador(LinkedList* pListaArcades, char* pathArchivo);
int controller_actualizarCantidadDeFichas(LinkedList* pLinkedListArcade, char* pathArchivo);
int controller_existeArchivo(char* pathArchivo);
int controller_exitApp(LinkedList* pLinkedListArcades, char* pathArchivoJuegos, char* pathArchivoMultijugador, int banderaArchivoJuegos, int banderaArchivoMultijugador);
//int controller_cargarArchivoConListaJuegosSinRepetir(LinkedList* pLinkedListElementos, char* pathArchivo);
//int controller_imprimirListaJuegosSinRepetir(LinkedList* pLinkedListElementos);


#endif /* CONTROLLER_H_ */
