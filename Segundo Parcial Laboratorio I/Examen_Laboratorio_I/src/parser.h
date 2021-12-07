/*
 * parser.h
 *
 *  Created on: 5 nov 2021
 *      Author: GONZALO
 */
#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Arcade.h"
#include "EntidadAuxiliar.h"

int parser_ArcadeFromText(FILE* pFile, LinkedList* pArrayListArcades);
int parser_ArcadeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee);
int parser_AuxiliarFromText(FILE* pFile, LinkedList* pArrayListAuxiliar);
int parser_TextFromArcade(FILE* pFile, void* pElemento);
int parser_TextFromAuxiliar(FILE* pFile, void* pElemento);
int parser_BinaryFromArcade(FILE* pFile, void* pElemento);

#endif /* PARSER_H_ */
