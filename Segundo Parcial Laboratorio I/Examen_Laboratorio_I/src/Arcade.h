/*
 * Arcade.h
 *
 *  Created on: 17 nov 2021
 *      Author: GONZALO
 */

#ifndef ARCADE_H_
#define ARCADE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ValidarDatos.h"
#include "Utn_tomarDatos.h"
#include "ComprobarErrores.h"
#include "LinkedList.h"
#include "Menu_mensajes.h"

#define LEN_NOMBRE_ALFANUMERICO 64
#define LEN_NOMBRE 51

typedef struct
{
    int idArcade;
    int tipoDeSonido;
    int cantidadJugadores;
    int capacidadMaximaDeFichas;
    char nacionalidadArcade[LEN_NOMBRE];
    char nombreJuego[LEN_NOMBRE_ALFANUMERICO];
    char nombreSalon[LEN_NOMBRE_ALFANUMERICO];
}eArcade;

void eArcade_delete(eArcade* pElemento);
eArcade* eArcade_newParametrosTexto(char* pIdArcade, char* pNombreJuego, char* pNacionalidad, char* pNombreSalon, char* pTipoDeSonido, char* pCantidadJugadores, char* pCapacidadMaximaDeFichas);
eArcade* eArcade_newParametrosDiferenciandoTiposDeDatos(int idArcade, char nombreJuego[], char nacionalidad[], char nombreSalon[], int tipoDeSonido, int cantidadDeJugadores, int capacidadMaximaDeFichas);
int eArcade_getDataToAddANewArcade(char nombreJuego[], char nacionalidad[], char nombreSalon[], int* pTipoDeSonido, int* pCantidadDeJugadores, int* pCapacidadMaximaDeFichas);
int eArcade_getDataFromUserToEditAFiel(eArcade* pElemento, int opcion);
int eArcade_getLastOrNextId(int opcion);
int eArcade_findeArcadeById(LinkedList* pArrayListeArcade, int id);
eArcade* eArcade_findPointerToeArcadeById(LinkedList* pArrayListeArcade, int id);
void eArcade_ImprimirEncabezadoDeDatos(int opcion);
void eArcade_ImprimirFilaVaciaDeDatos(int opcion);
int eArcade_ImprimirTodosLosDatos(void* pElemento);
int eArcade_ImprimirIdNombreYCantidadJugadores(void* pElemento);
int eArcade_imprimirUnSoloArcade(eArcade* this);
int eArcade_setId(eArcade* pElemento, int idArcade);
int eArcade_setIdTexto(eArcade* pElemento, char* pId);
int eArcade_getId(eArcade* pElemento, int* pIdArcade);
int eArcade_setTipoDeSonido(eArcade* pElemento, int tipoSonido);
int eArcade_setTipoDeSonidoTexto(eArcade* pElemento, char* pTipoDeSonido);
int eArcade_getTipoDeSonido(eArcade* pElemento, int* tipoDeSonido);
int eArcade_getTipoDeSonidoDeNumeroATexto(eArcade* pArcade, char* pTexto);
int eArcade_setCantidadDeJugadores(eArcade* pElemento, int cantidadDeJugadores);
int eArcade_setCantidadMaximaDeJugadoresTexto(eArcade* pElemento, char* pCantidadMaximaDeJugadores);
int eArcade_getCantidadDeJugadores(eArcade* pElemento, int* cantidadDeJugadores);
int eArcade_setCapacidadMaximaDeFichas(eArcade* pElemento, int capacidadMaximaDeFichas);
int eArcade_setCapacidadMaximaDeFichasTexto(eArcade* pElemento, char* pCapacidadMaximaDeFichas);
int eArcade_getCapacidadMaximaDeFichas(eArcade* pElemento, int* capacidadMaximaDeFichas);
int eArcade_setNombreDeJuego(eArcade* pElemento, char* pNombre);
int eArcade_getNombreDeJuego(eArcade* pElemento, char* pNombre);
int eArcade_setNombreDeSalon(eArcade* pElemento, char* pNombre);
int eArcade_getNombreDeSalon(eArcade* pElemento, char* pNombre);
int eArcade_setNacionalidad(eArcade* pElemento, char* pNacionalidad);
int eArcade_getNacionalidad(eArcade* pElemento, char* pNacionalidad);
int eArcade_gettersFromArcade(eArcade* pElemento, int* pIdArcade, char* pNombreJuego, char* pNacionalidad, char* pNombreSalon, char* pTipoDeSonido, int* pCantidadJugadores, int* pCapacidadMaximaDeFichas);
int eArcade_ordenarPorNombreDeJuego(void* pElementoUno, void* pElementoDos);
int eArcade_ordenarPorNombreDeSalon(void* pElementoUno, void* pElementoDos);
int eArcade_ordenarPorNacionalidad(void* pElementoUno, void* pElementoDos);
int eArcade_ordenarPorTipoDeSonido(void* pElementoUno, void* pElementoDos);
int eArcade_ordenarPorId(void* pElementoUno, void* pElementoDos);
int eArcade_ordenarPorCantidadDeJugadores(void* pElementoUno, void* pElementoDos);
int eArcade_ordenarPorCapacidadMaximaDeFichas(void* pElementoUno, void* pElementoDos);
int eArcade_liberarListaDeMemoria(LinkedList* pLinkedListArcades);
int eArcade_filtrarCantidadDeJugadores(void* pElemento);
int eArcade_incrementarCapacidadDeFichas(void* pElemento);

#endif /* ARCADE_H_ */
