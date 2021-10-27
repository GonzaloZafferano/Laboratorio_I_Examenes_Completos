/*
 * Menu.h
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>

void menu_ImprimirMenuPrincipal(void);
void menu_ImprimirMenuInformes(void);
int menu_EsPosibleOperarMenu(int bandera);
int menu_OperarMenuInformes(eSalon lista_eSalon[], int lenSalon, eArcade lista_eArcade[], int lenArcade, int idMaximo_eSalon);
int menu_OperarMenuAltaDeSalon(eSalon lista_eSalon[], int lenSalon, int* idMaximo_eSalon, int* bandera_eSalon_hayElementos, int* bandera_eArcade_hayElementos);
int menu_OperarMenuEliminacionDeSalon(eSalon lista_eSalon[], int lenSalon, eArcade lista_eArcade[], int lenArcade, int* bandera_eArcade_hayElementos, int* bandera_eSalon_hayElementos, int idMaximo_eSalon);
int menu_OperarMenuAltaDeArcade(eArcade lista_eArcade[], int lenArcade, eSalon lista_eSalon[], int lenSalon, int idMaximo_eSalon, int* bandera_eArcade_hayElementos, int* idMaximo_eArcade);
int menu_OperarMenuModificacionDeArcade(eArcade lista_eArcade[], int lenArcade, int idMaximo_eArcade);
int menu_OperarMenuEliminacionDeArcade(eArcade lista_eArcade[], int lenArcade, eSalon lista_eSalon[], int lenSalon, int idMaximo_eArcade, int* bandera_eArcade_hayElementos);

#endif /* MENU_H_ */
