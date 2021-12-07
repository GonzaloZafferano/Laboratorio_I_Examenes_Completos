/*
 * Utn_tomarDatos.c
 *
 *  Created on: 26 oct 2021
 *      Author: GONZALO
 */

#include "Utn_tomarDatos.h"

#define TRUE 1
#define LEN_BUFFER_CARACTER 3
#define LEN_MYGETS 250
#define LEN_TEXTO 200
#define LEN_NOMBRE 51
#define LEN_NOMBRE_ALFANUMERICO 64
#define LEN_ALFANUMERICO 51
#define LEN_DIRECCION 51
#define LEN_TEXTO_CUIT 15
#define LEN_BUFFER_INT 10
#define LEN_BUFFER_FLOAT 10
#define REINTENTOS 2
#define OPERACION_EXITOSA 0
#define ERROR_PUNTERO_NULL -1
#define ERROR_LEN_INVALIDO -2
#define ERROR_CANTIDAD_REINTENTOS_NEGATIVA -3
#define ERROR_MINIMO_ES_MAYOR_QUE_MAXIMO -4
#define ERROR_FUNCION_INTERNA_FALLO -20
#define ERROR_SIN_MAS_REINTENTOS -21

static int myGets(char pCadena[], int len, char* pMensaje);

/**
* \brief Recibe un array de caracteres en donde almacenara el texto ingresado por el usuario
*        de forma segura. Elimina el ENTER de la cadena, en caso de haber uno.
* \param char pCadena[] - Cadena de caracteres donde almacenara el texto ingresado por el usuario
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -20 si fallo alguna funcion interna
*/
static int myGets(char pCadena[], int len, char* pMensaje)
{
    int indiceFinalDeCadena;
    int retorno= ERROR_PUNTERO_NULL;
    char bufferString[LEN_MYGETS];

    if(pCadena != NULL && pMensaje != NULL)
    {
    	retorno = ERROR_LEN_INVALIDO;
    	if(len > 0 && len <= LEN_MYGETS)
    	{
    		retorno = ERROR_FUNCION_INTERNA_FALLO;
			printf("%s->", pMensaje);
			fflush(stdin);

			if(fgets(bufferString,len,stdin) != NULL)
			{
				indiceFinalDeCadena = strnlen(bufferString, len) -1;

				if(bufferString[indiceFinalDeCadena] == '\n')
				{
					bufferString[indiceFinalDeCadena] = '\0';
				}

				strncpy(pCadena, bufferString, len);
				retorno = OPERACION_EXITOSA;
			}
    	}
    }
    return retorno;
}

/**
* \brief Obtiene una sola letra del usuario. Evalua si es valida.
* \param char* letra - Direccion de memoria de la variable CHAR donde almacenara la letra ingresada.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param char minimo - Caracter minimo que se puede recibir
* \param char maximo - caracter maximo que se puede recibir
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -4 si el minimo es mayor que el maximo
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getLetra(char* pLetra, char* pMensaje, char* pMensajeError,char minimo, char maximo, int reintentos)
{
    int i;
    int retorno = ERROR_PUNTERO_NULL;
    char caracterAuxiliar[LEN_BUFFER_CARACTER];

    if(pLetra != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
    	if(reintentos >= 0)
    	{
    		retorno = ERROR_MINIMO_ES_MAYOR_QUE_MAXIMO;
    		if(minimo <= maximo)
    		{
				retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(caracterAuxiliar,sizeof(caracterAuxiliar), pMensaje)==0)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;
						if(strnlen(caracterAuxiliar, sizeof(caracterAuxiliar)) == 1)
						{
							if(validar_letra(&caracterAuxiliar[0]) == TRUE)
							{
								if(caracterAuxiliar[0] >= minimo && caracterAuxiliar[0] <= maximo)
								{
									*pLetra = caracterAuxiliar[0];
									retorno = OPERACION_EXITOSA;
									break;
								}
							}
						}
						printf("%s\n", pMensajeError);
					}
				}
    		}
		}
	}
    return retorno;
}

/**
* \brief Obtiene un numero INT del usuario, verificando que sea valido.
* \param int pNumero - Direccion de memoria de la variable INT donde almacenara el numero ingresado por el usuario, una vez validado.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -4 si el minimo es mayor que el maximo
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getInt(int* pNumero, char* pMensaje, char* pMensajeError, int minimo, int maximo, int reintentos)
{
    int i;
    int bufferInt;
    int retorno = ERROR_PUNTERO_NULL;
    char bufferCadenaAuxiliar[LEN_BUFFER_INT];

    if(pNumero != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
		if(reintentos >= 0)
		{
			retorno = ERROR_MINIMO_ES_MAYOR_QUE_MAXIMO;
			if(minimo <= maximo)
			{
				retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(bufferCadenaAuxiliar,sizeof(bufferCadenaAuxiliar), pMensaje) == OPERACION_EXITOSA)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;
						if(validar_numeroEntero(bufferCadenaAuxiliar, sizeof(bufferCadenaAuxiliar)) == TRUE)
						{
							//Si es numero entero, convierto la cadena a INT
							bufferInt = atoi(bufferCadenaAuxiliar);

							//Ahora que tengo el numero, verificado y ENTERO, evaluo si esta en el rango.
							if(bufferInt >= minimo && bufferInt <= maximo)
							{
								*pNumero = bufferInt;
								retorno = OPERACION_EXITOSA;
								break;
							}
						}
						printf("%s\nSolo se aceptan numeros enteros entre %d y %d\n", pMensajeError, minimo, maximo);
					}
				}
			}
		}
	}
    return retorno;
}

/**
* \brief Obtiene un numero FLOAT del usuario, verificando que sea valido.
* \param float pNumero - Direccion de memoria de la variable FLOAT donde almacenara el numero ingresado por el usuario, una vez validado.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -4 si el minimo es mayor que el maximo
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getFloat(float* pNumero, char* pMensaje, char* pMensajeError, int minimo, int maximo, int reintentos)
{
    int i;
    float bufferFloat;
    int retorno = ERROR_PUNTERO_NULL;
    char bufferCadenaAuxiliar[LEN_BUFFER_FLOAT];

    if(pNumero != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
		if(reintentos >= 0)
		{
			retorno = ERROR_MINIMO_ES_MAYOR_QUE_MAXIMO;
			if(minimo <= maximo)
			{
				retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(bufferCadenaAuxiliar,sizeof(bufferCadenaAuxiliar), pMensaje) == OPERACION_EXITOSA)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;
						if(validar_numeroFloat(bufferCadenaAuxiliar, sizeof(bufferCadenaAuxiliar))== TRUE)
						{
							//Si es numero float, convierto la cadena a FLOAT
							bufferFloat = atof(bufferCadenaAuxiliar);

							//Ahora que tengo el numero, verificado y FLOAT, evaluo si esta en el rango.
							if(bufferFloat >= minimo && bufferFloat <= maximo)
							{
								*pNumero = bufferFloat;
								retorno = OPERACION_EXITOSA;
								break;
							}
						}
						printf("%s\n", pMensajeError);
					}
				}
			}
		}
	}
    return retorno;
}

/**
* \brief Obtiene un nombre o apellido del usuario. Evalua si es valido.
* \param char pCadena[] - Direccion de memoria de la variable CHAR donde almacenara el dato ingresado por el usuario, una vez validado.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getNombreOApellido(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR_PUNTERO_NULL;
    char bufferCadenaAuxiliar[LEN_NOMBRE];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_LEN_INVALIDO;
    	if(largo > 0 && largo <= LEN_NOMBRE)
    	{
    		retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
    		if(reintentos >= 0)
    		{
    			retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(bufferCadenaAuxiliar,largo, pMensaje)==OPERACION_EXITOSA)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;
						if(validar_nombre(bufferCadenaAuxiliar, largo) == TRUE)
						{
							strncpy(pCadena, bufferCadenaAuxiliar, largo);
							retorno = OPERACION_EXITOSA;
							break;
						}
						printf("%s\n", pMensajeError);
					}
				}
    		}
		}
	}
    return retorno;
}

/**
* \brief Obtiene una cadena de texto. Admite cualquier caracter.
* \param char pCadena[] - Direccion de memoria de la variable CHAR donde almacenara la cadena de texto ingresada por el usuario.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getTexto(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int largoFinalCadenaAuxiliar;
    int retorno = ERROR_PUNTERO_NULL;
    char bufferCadenaAuxiliar[LEN_TEXTO];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_LEN_INVALIDO;
    	if(largo > 0 && largo <= LEN_TEXTO)
    	{
    		retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
    		if(reintentos >= 0)
    		{
    			retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(bufferCadenaAuxiliar,largo, pMensaje)==OPERACION_EXITOSA)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;

						if(validar_texto(bufferCadenaAuxiliar, largo) == TRUE)
						{
							largoFinalCadenaAuxiliar = strnlen(bufferCadenaAuxiliar, largo);

							if(largoFinalCadenaAuxiliar > 0)
							{
								strncpy(pCadena, bufferCadenaAuxiliar, largo);
								retorno = OPERACION_EXITOSA;
								break;
							}
						}
						printf("%s\n", pMensajeError);
					}
				}
    		}
		}
	}
    return retorno;
}

/**
* \brief Obtiene una cadena de texto alfanumerica (solo letras y numeros, sin espacios)
* \param char pCadena[] - Direccion de memoria de la variable CHAR donde almacenara la cadena de texto ingresada por el usuario.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getAlfanumerico(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR_PUNTERO_NULL;
    char bufferCadenaAuxiliar[LEN_ALFANUMERICO];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_LEN_INVALIDO;
    	if(largo > 0 && largo <= LEN_ALFANUMERICO)
    	{
    		retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
    		if(reintentos >= 0)
    		{
    			retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(bufferCadenaAuxiliar,largo, pMensaje)== OPERACION_EXITOSA)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;

						if(validar_alfanumerico(bufferCadenaAuxiliar, largo)== TRUE)
						{
							strncpy(pCadena, bufferCadenaAuxiliar, largo);
							retorno = OPERACION_EXITOSA;
							break;
						}
						printf("%s\n", pMensajeError);
					}

    		}
			}
		}
	}
    return retorno;
}

/**
* \brief Obtiene una cadena de texto que representa un CUIT en el formato 00-00000000-0.
* \param char pCadena[] - Direccion de memoria de la variable CHAR donde almacenara la cadena de texto ingresada por el usuario.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getCuit(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR_PUNTERO_NULL;
    char bufferCadenaAuxiliar[LEN_TEXTO_CUIT];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_LEN_INVALIDO;
    	if(largo >= LEN_TEXTO_CUIT)
    	{
    		retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
    		if(reintentos >= 0)
    		{
    			retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(bufferCadenaAuxiliar,sizeof(bufferCadenaAuxiliar), pMensaje)==OPERACION_EXITOSA)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;
						if(validar_cuit(bufferCadenaAuxiliar, sizeof(bufferCadenaAuxiliar)) == TRUE)
						{
							strncpy(pCadena, bufferCadenaAuxiliar, largo);
							retorno = OPERACION_EXITOSA;
							break;
						}
						printf("%s\n", pMensajeError);
					}
				}
    		}
		}
	}
    return retorno;
}

/**
* \brief Obtiene una cadena de texto para una direccion (letras, numeros y espacios)
* \param char pCadena[] - Direccion de memoria de la variable CHAR donde almacenara la cadena de texto ingresada por el usuario.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getDireccion(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR_PUNTERO_NULL;
    char bufferCadenaAuxiliar[LEN_DIRECCION];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_LEN_INVALIDO;
    	if(largo > 0 && largo <= LEN_DIRECCION)
    	{
    		retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
    		if(reintentos >= 0)
    		{
    			retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(bufferCadenaAuxiliar,largo, pMensaje) == OPERACION_EXITOSA)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;
						if(validar_direccion(bufferCadenaAuxiliar, largo) == TRUE)
						{
							strncpy(pCadena, bufferCadenaAuxiliar, largo);
							retorno = OPERACION_EXITOSA;
							break;
						}
						printf("%s\n", pMensajeError);
					}
				}
    		}
		}
	}
    return retorno;
}

/**
* \brief Obtiene una cadena de texto para un nombre AlfaNumerico (letras, numeros y espacios)
* \param char pCadena[] - Direccion de memoria de la variable CHAR donde almacenara la cadena de texto ingresada por el usuario.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero apunta a NULL
*         retorna -2 si el len es invalido
*         retorna -3 si la cantidad de reintentos es negativa
*         retorna -20 si fallo alguna funcion interna
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_getNombreAlfanumerico(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR_PUNTERO_NULL;
    char bufferCadenaAuxiliar[LEN_NOMBRE_ALFANUMERICO];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = ERROR_LEN_INVALIDO;
    	if(largo > 0 && largo <= LEN_NOMBRE_ALFANUMERICO)
    	{
    		retorno = ERROR_CANTIDAD_REINTENTOS_NEGATIVA;
    		if(reintentos >= 0)
    		{
    			retorno = ERROR_FUNCION_INTERNA_FALLO;
				for(i = 0; i <= reintentos; i++)
				{
					if(myGets(bufferCadenaAuxiliar,largo, pMensaje)== OPERACION_EXITOSA)
					{
						retorno = ERROR_SIN_MAS_REINTENTOS;
						if(validar_nombreAlfanumerico(bufferCadenaAuxiliar, largo) == TRUE)
						{
							strncpy(pCadena, bufferCadenaAuxiliar, largo);
							retorno = OPERACION_EXITOSA;
							break;
						}
						printf("%s\n", pMensajeError);
					}
				}
    		}
		}
	}
    return retorno;
}

/*
* \brief Solicita el ingreso de una opcion al usuario. Requiere maximo y minimo.
* \param int* opcion - retorna a traves de este parametro la opcion seleccionada
* \param int minimo - minimo valor de la opcion
* \param int maximo - maximo valor de la opcion
* \return retorna INT. Retorna 0 si OK.
*         retorna -1 si el puntero apunta a NULL
*         retorna -4 si el minimo es mayor que el maximo
*         retorna -21 si se quedo sin mas reintentos
*/
int utn_ingreseUnaOpcion(int* opcion, int minimo, int maximo)
{
	int retorno = ERROR_PUNTERO_NULL;
	if(opcion != NULL)
	{
		retorno = ERROR_MINIMO_ES_MAYOR_QUE_MAXIMO;
		if(minimo <= maximo)
		{
			retorno = ERROR_SIN_MAS_REINTENTOS;
			if(utn_getInt(opcion, "\nIngrese una opcion", "Error. Dato invalido", minimo, maximo, REINTENTOS)==OPERACION_EXITOSA)
		    {
			    retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}
