/*
 * Informes.h
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#ifndef INFORMES_H_
#define INFORMES_H_

#include <stdio.h>
#include <stdlib.h>
#include "Arcade.h"
#include "Salon.h"
#include "Auxiliar.h"

int informes_eArcade_imprimirElementosConElIdEspecificado(eArcade lista[], int len, int id_eSalon, int mostrar);
int informes_eArcade_eliminarElementosConElIdEspecificado(eArcade lista[], int len, int id_eSalon);
int informes_imprimirArcadeConSuSalon(eArcade listaArcade[], int lenArcade, eSalon listaSalon[], int lenSalon);
int informes_imprimirListaDeJuegos(eArcade listaArcade[], int lenArcade);
int informe_generarListaDeJuegos(eAuxiliar listaJuegos[], int lenJuegos, eArcade listaArcade[], int lenArcade);
int informes_eArcade_contadorArcadePorSalon(eArcade listaArcade[], int len, int id_eSalon);
int informes_listarSalonesConMasDeCuatroArcades(eSalon listaSalones[], int lenSalones, eArcade listaArcades[], int lenArcade);
int informes_arcadesParaMasDeDosJugadores(eArcade listaArcade[], int lenArcade, eSalon listaSalon[], int lenSalon);
int informes_listarInfoDeSalonConCantidadDeArcades(eSalon listaSalon[], int indiceSalon, eArcade listaArcade[], int lenArcade, int idSalon);
int informes_listarSalonConListaDeSusArcades(eSalon salon, eArcade listaArcade[], int lenListaArcade, int idSalon);
int informes_CalcularSalonConMasArcades(eSalon listaSalones[], int lenSalones, eArcade listaArcades[], int lenArcades, int* mayorCantidadDeArcades);
int informes_imprimirSalonConMasArcades(eSalon listaSalones[], int lenSalones, eArcade listaArcades[], int lenArcades);
int informes_ContarFichasTotalesPorSalon(eArcade listaArcade[], int lenArcade, int idSalon);
int informes_CalcularTotalDeRecaudacionPosiblePorSalon(eArcade listaArcades[], int lenArcade, float precioPorFicha, int idSalon, float* recuadacionTotalPorSalon);
int informes_ImprimirMontoMaximoPorSalon(eSalon salon, float montoMaximo, int cantidadFichas, float precioPorFicha);
int informes_listarSalonesCompletos(eSalon listaSalon[], int lenSalon, eArcade listaArcades[], int lenArcades);
int informes_promedioArcadesPorSalon(eSalon listaSalones[], int lenSalon, eArcade listaArcades[], int lenArcades, float* pPromedioArcadesPorSalon);
int informes_imprimirListaSinRepetir(eArcade lista[], int len);
int informes_imprimirListaSinRepetirVolDos(eArcade lista[], int len);

#endif /* INFORMES_H_ */
