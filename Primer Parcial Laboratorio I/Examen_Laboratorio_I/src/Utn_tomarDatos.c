/*
 * Utn_tomarDatos.c
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#include "Utn_tomarDatos.h"

#define TRUE 1
#define FALSE 0
#define LEN_BUFFER_CARACTER 5
#define LEN_BUFFER_STRING 63
#define BUFFER_LEN_CUIT 20
#define LEN_CUIT 13
#define LEN_BUFFER_INT 16
#define LEN_BUFFER_FLOAT 51
#define REINTENTOS 2
#define DATO_VALIDO 1
#define DATO_INVALIDO 0
#define OPERACION_EXITOSA 0
#define ERROR -1
#define SIN_MAS_REINTENTOS -4

static int esSigno(char caracter);
static int esNumero(char caracter);
static int esLetra(char caracter);
static int esNumeroEntero(char cadena[], int largo);
static int esNumeroFloat(char cadena[], int largo);
static int esNombreOApellido(char cadena[], int largo);
static int swapCaracteres(char plistaCaracteres[], int i, int j);
static int darFormatoMayusculaMinuscula(char pNombre[], int len);
static int borrarEspacios(char pCadena[], int len);
static int cambiarTabsPorEspacios(char pCadena[], int len);
static int borrarEspaciosIzquierda(char pCadena[], int len, int indiceInicial);
static int borrarEspaciosExtrasIntermedios(char pCadena[], int len);
static int borrarEspaciosFinales(char pCadena[], int len);
static int myGets(char pCadena[], int largo, char* mensaje);
static int esDireccion(char pCadena[], int len);
static int esCaracterValidoParaDireccion(char caracter);
static int esCaracterAlfanumerico(char caracter);
static int esCuit(char pCadena[], int len);
static int esAlfanumerico(char pCadena[], int len);
static int convertirUnCaracterEnMayuscula(char* pCaracter);
static int esNombreAlfanumerico(char pCadena[], int len);

/**
* \brief Evalua si el caracter recibido por parametro corresponde a un numero o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a un numero.
*         retorna 0 (para falso) si el caracter NO corresponde a un numero.
*/
static int esNumero (char caracter)
{
	int retorno = TRUE;

	if(caracter < 48 || caracter > 57) //48 ASCII para el caracter '0' y 57 para '9'
	{
		retorno = FALSE;
	}
	return retorno;
}

/**
* \brief Evalua si el caracter recibido por parametro corresponde a un signo ('+' o '-') o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a un signo ('+' o '-').
*         retorna 0 (para falso) si el caracter NO corresponde a un signo.
*/
static int esSigno (char caracter)
{
	int retorno = TRUE;

	if(caracter != 43 && caracter != 45) //43 ASCII para el caracter '+' y 45 para '-'
	{
		retorno = FALSE;
	}
	return retorno;
}

/**
* \brief Evalua si el caracter recibido por parametro corresponde a una letra o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a una letra.
*         retorna 0 (para falso) si el caracter NO corresponde a una letra.
*/
static int esLetra (char caracter)
{
	int retorno = TRUE; //Asumo que es letra. 1 para verdadero

	if((caracter > 122 || caracter < 97) && (caracter > 90 || caracter < 65))
	{
		retorno = FALSE; //0 para Falso. No es una letra
	}
	return retorno;
}

/**
* \brief Verifica si un caracter es un caracter alfanumerico.
* \param char caracter - caracter que se evaluara
* \return retorna INT. 1 si el caracter es valido
*         retorna  0 es si el caracter no es valido
*/
static int esCaracterAlfanumerico(char caracter)
{
	int retorno = TRUE;

	if(esLetra(caracter) == FALSE && esNumero(caracter) == FALSE)
	{
		return FALSE;
	}
	return retorno;
}

/**
* \brief Verifica si un caracter es un caracter valido para una direccion.
* \param char caracter - caracter que se evaluara
* \return retorna INT. 1 si el caracter es valido
*         retorna  0 es si el caracter no es valido
*/
static int esCaracterValidoParaDireccion(char caracter)
{
	int retorno = TRUE;

	if(caracter != '.' && caracter != ',' && caracter != ' ')
	{
		return FALSE;
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa una direccion VALIDA (numeros, letras y algunos caracteres permitidos).
* \param char pCadena [] - Cadena que se evaluara, para determinar si es una direccion valida.
* \param int largo - Largo del array de caracteres.
* \return retorna INT. 1 si el dato es valido
*         retorna  0 es si el dato no es valido
* 		  retorna -1 si ERROR
*/
static int esDireccion(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = ERROR;

	if(pCadena != NULL && len >0)
	{
		largo = strnlen(pCadena, len);

		if(largo > 0)
		{
			retorno = TRUE;
			for(i = 0; i < largo ; i++)
			{
				if(esLetra(pCadena[i]) == FALSE && esCaracterValidoParaDireccion(pCadena[i]) == FALSE && esNumero(pCadena[i]) == FALSE)
				{
					retorno = FALSE;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Evalua si el caracter recibido por parametro corresponde a una letra o un numero.
* \param char pCadena [] - Cadena que se evaluara para determinar si es alfanumerico.
* \param int largo - Largo del array recibido por parametro.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a una letra o numero.
*         retorna 0 (para falso) si el caracter NO corresponde a una letra ni un numero.
*         retorna -1 si ERROR
*/
static int esAlfanumerico(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = ERROR;

	if(pCadena != NULL)
	{
		largo = strnlen(pCadena, len);
		if(largo >0)
		{
			retorno = TRUE;
			for(i = 0; i < largo; i++)
			{
				if(esCaracterAlfanumerico(pCadena[i])==FALSE)
				{
					retorno = FALSE;
					break;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Evalua si la cadena de texto recibida representa un CUIT
* \param char pCadena[] - Direccion de memoria de la variable que almacena el CUIT.
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 1 si es CUIL
* 		  retorna 0 si NO es CUIL
*         retorna -1 si ERROR
*/
static int esCuit(char pCadena[], int len)
{
	int i;
	int retorno = ERROR;
	if(pCadena != NULL && len == LEN_CUIT)
	{
		retorno = TRUE;

		for(i = 0; i < len; i ++)
		{
			//En posicion 2 y 11 va un guion medio '-'
			if((i != 2 && i != 11 && esNumero(pCadena[i])==FALSE) || ((i == 2 || i == 11) && pCadena[i] != 45))
			{
				retorno = FALSE;
				break;
			}
		}
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa un numero ENTERO VALIDO.
* \param char pCadena [] - Cadena que se evaluara, para determinar si contiene un ENTERO valido.
* \param int largo - Largo del array recibido por parametro.
* \return retorna INT. 1 si el dato es Entero
*         retorna  0 es si el dato es invalido
* 		  retorna -1 si ERROR
*/
static int esNumeroEntero (char pCadena [], int largo)
{
	int longitudActual;
	int i=0;
	int retorno = ERROR;

	if(pCadena != NULL && largo > 0)
	{
		retorno = FALSE; //Dato invalido (no tiene caracteres).

		longitudActual = strnlen(pCadena, largo); //No cuenta el \0

		//mygets() borra el ENTER, por lo que si el ENTER fue la unica
		//tecla apretada, entonces la cadena tiene un largo actual de 0 (seria un error).
		if(longitudActual > 0)
		{
			retorno = TRUE;

			//Si el indice 0 es un signo, entonces la cadena debe tener mas de 1 elemento.
			//La cadena no puede tener un unico elemento, y ese unico elemento ser un signo.
			if(esSigno(pCadena[0]) == TRUE && longitudActual > 1)
			{
				i++;
			}

			for(	; i < longitudActual; i++)
			{
				if(esNumero(pCadena[i]) == FALSE)
				{
					retorno = FALSE;//Dato invalido, no es numero.
					break;
				}
			}
		}

	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa un numero FLOAT VALIDO.
* \param char pCadena [] - Cadena que se evaluara, para determinar si contiene un FLOAT valido.
* \param int largo - Largo del array recibido por parametro.
* \return retorna INT. 1 si el dato es FLOAT
*         retorna  0 es si el dato es invalido
* 		  retorna -1 si ERROR
*/
static int esNumeroFloat (char pCadena [], int largo)
{
	int longitudActual;
	int i=0;
	int contadorPuntos = 0;
	int retorno = ERROR;

	if(pCadena != NULL && largo > 0)
	{

		retorno = FALSE; //Dato invalido (no tiene caracteres).

		longitudActual = strnlen(pCadena, largo);
		//mygets() borra el ENTER, por lo que si el ENTER fue la unica
		//tecla apretada, entonces la cadena tiene un largo actual de 0 (seria un error).
		if(longitudActual > 0)
		{
			retorno = TRUE; //todo OK.

			//Para validar un signo '-' o '+', la longitud debe ser necesariamente mayor a 1.
			//Esto es porque el signo ocupa 1 caracter, por lo que la cadena NO PUEDE TENER
			//ESE UNICO CARACTER, debe tener por lo menos 2 (1 ocupado por el signo, y el otro por un digito).
			if(esSigno(pCadena[0]) == 1 && longitudActual > 1 )
			{
				i++;
			}

			for(	;i < longitudActual; i++)
			{
				if(esNumero(pCadena[i]) == FALSE)
				{
					if(pCadena[i] == 46 && contadorPuntos == 0)//46 para '.'
					{
						contadorPuntos++;
					}
					else
					{
						retorno = FALSE; //Dato invalido.
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Obtiene una cadena y verifica si es un nombre o un apellido valido.
* \param char pCadena[] - array de tipo CHAR a evaluar.
* \param int largo - Largo del array de caracteres recibido.
* \return retorna INT. 1 si el dato es valido.
*         retorna  0 si el dato es invalido
*         retorna -1 si ERROR
*/
static int esNombreOApellido (char pCadena[], int largo)
{
	int i;
	int longitudActual;
	int retorno = ERROR;

	if(pCadena != NULL && largo > 0)
	{
		longitudActual = strnlen(pCadena, largo);

		//mygets() borra el ENTER, por lo que si el ENTER fue la unica
		//tecla apretada, entonces la cadena tiene un largo actual de 0 (seria un error).
		if(longitudActual > 0)
		{
			retorno = TRUE;//Asumo que esta todo OK.

			for(i = 0; i < longitudActual; i++)
			{
				//Si no es letra, ni un espacio en blanco (validado) es un caracter INVALIDO.
				if(esLetra(pCadena[i]) == FALSE && pCadena[i] != 32)
				{
					retorno = FALSE;
					break;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa un nombre Alfanumerico VALIDO (numeros, letras y espacios).
* \param char pCadena [] - Cadena que se evaluara, para determinar si es una cadena alfanumerica valida.
* \param int largo - Largo del array de caracteres.
* \return retorna INT. 1 si el dato es valido
*         retorna  0 es si el dato no es valido
* 		  retorna -1 si ERROR
*/
static int esNombreAlfanumerico(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = ERROR;

	if(pCadena != NULL && len >0)
	{
		largo = strnlen(pCadena, len);

		if(largo > 0)
		{
			retorno = TRUE;
			for(i = 0; i < largo ; i++)
			{
				if(esLetra(pCadena[i]) == FALSE && pCadena[i] != 32 && esNumero(pCadena[i]) == FALSE)
				{
					retorno = FALSE;
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Recibe un caracter ya validado como letra, y lo convierte en mayuscula
* \param char* pCaracter - puntero al caracter
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si ERROR
*/
static int convertirUnCaracterEnMayuscula(char* pCaracter)
{
	int retorno = ERROR;
	if(pCaracter != NULL)
	{
		retorno = OPERACION_EXITOSA;
		if(*pCaracter >= 97 && *pCaracter <=122)
		{
			*pCaracter = *pCaracter - 32;
		}
	}
	return retorno;
}

/**
* \brief Recibe una cadena de caracteres y coloca una mayuscula en la primer letra de cada palabra (si corresponde)
*        Convierte la primer letra de cada palabra en Mayuscula y el resto en minusculas.
* \param char pNombre[] - Array de caracteres
* \param int len - largo del Array
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si ERROR
*/
static int darFormatoMayusculaMinuscula(char pNombre[], int len)
{
	int largo;
	int i = 0;
	int retorno = ERROR;

	if(pNombre != NULL && len >0)
	{
		largo = strnlen(pNombre, len);
		retorno = OPERACION_EXITOSA;

		if(pNombre[i] <= 122 && pNombre[i] >= 97)
		{
			pNombre[i] = pNombre[i] - 32;
		}

		for(i = 1; i < largo; i++)
		{
			if(pNombre[i] != 32)
			{
				if(pNombre[i] >= 65 && pNombre[i]<= 90)
				{
					pNombre[i] = pNombre[i] + 32;
				}
			}
			else
			{
				if(pNombre[i+1] <= 122 && pNombre[i+1] >= 97)
				{
					pNombre[i+1] = pNombre[i+1] - 32;
				}
				i++;
			}
		}
	}
	return retorno;
}

/*
* \brief Reemplaza los tabs que se encuentre por espacios en blanco.
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* * \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si ERROR
*/
static int cambiarTabsPorEspacios(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = ERROR;

	if(pCadena != NULL && len > 0 && len <= LEN_BUFFER_STRING)
	{
		largo = strnlen(pCadena, len);

		retorno = OPERACION_EXITOSA;

		for(i=0;i < largo; i++)
		{
			 if(pCadena[i] == '\t')
			 {
				 pCadena[i] = 32; //32 para ' ' (espacio en blanco)
			 }
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco (al inicio de la cadena, al final y los extras en el medio)
* 		 Se apoya en 4 funciones para operar correctamente.
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si ERROR
*/
static int borrarEspacios(char pCadena[], int len)
{
	int i = 0;
	int retorno = ERROR;
	if(pCadena != NULL && len > 0 && len <= LEN_BUFFER_STRING)
	{
		if(cambiarTabsPorEspacios(pCadena, len) == OPERACION_EXITOSA)
		{
			if(borrarEspaciosIzquierda(pCadena, len,i) == OPERACION_EXITOSA)
			{
				if(borrarEspaciosExtrasIntermedios(pCadena, len) == OPERACION_EXITOSA)
				{
					if(borrarEspaciosFinales(pCadena, len) == OPERACION_EXITOSA)
					{
						retorno = OPERACION_EXITOSA;
					}
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco a partir de la posicion especificada, hasta que detecta una letra
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \param int indiceInicial - Indice a partir del cual empieza a borrar espacios.
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si ERROR
*/
static int borrarEspaciosIzquierda(char pCadena[], int len, int indiceInicial)
{
	int largo;
	int i = indiceInicial;
	int j = indiceInicial;
	int banderaHayLetras = FALSE;
	int retorno = ERROR;

	if(pCadena != NULL&& len > 0 && len <= LEN_BUFFER_STRING)
	{
		largo = strnlen(pCadena, len);

		retorno = OPERACION_EXITOSA;

		for(	;i < largo; i++)
		{

			 if(pCadena[i] != 32)
			 {
				 banderaHayLetras = TRUE; //En cuanto encuentre una letra, activo la bandera
				 swapCaracteres(pCadena, i, j);//Cambio de lugar el espacio con la letra.
				 j++;
			 }
			 else
			 {
			  //Si la posicion [i] es igual al caracter 32 (espacio), y ademas ya detecte una letra previamente,
			  //ROMPO EL BUCLE, porque ya habria acomodado todas las letras a la izquierda.
			  //Ese espacio "intermedio" se deja, porque se interpreta que se coloco para
			  //separar palabras o nombres.
				 if(banderaHayLetras == TRUE)
				 {
					 break;
				 }
			 }
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco EXTRAS (mas de 1) que esten en medio de la cadena, hasta que detecta una letra
* \param char pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si ERROR
*/
static int borrarEspaciosExtrasIntermedios(char pCadena[], int len)
{
	int largo;
	int i=0;
	int j=1;
	int retorno = ERROR;

	if(pCadena != NULL && len > 0 && len <= LEN_BUFFER_STRING)
	{
		retorno = OPERACION_EXITOSA;
		largo =	strnlen(pCadena, len)-1;
		//i debe llegar a la Anteultima posicion, mientras que j sera quien llegara a la ultima posicion.

		while(i < largo)
		{
			if(pCadena[i] == 32 && pCadena[j] == 32)//Si ambos son espacios en blanco, borro el segundo.
			{
				borrarEspaciosIzquierda(pCadena, len, j);//Paso el indice j, para que sea borrado, y salvar el espacio en i.
			}
			i++;
			j++;
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco que esten al final de la cadena, hasta que detecta una letra
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si ERROR
*/
static int borrarEspaciosFinales(char pCadena[], int len)
{
	int i;
	int retorno = ERROR;

	if(pCadena != NULL && len > 0 && len <= LEN_BUFFER_STRING)
	{
		i = strnlen(pCadena, len)-1;
		retorno = OPERACION_EXITOSA;

		while (i >= 0)
		{
			if(pCadena[i] == 32) //32 es para el espacio en blanco ' '
			{
				pCadena[i] = '\0';
			}
			else
			{
				break;
			}
			i--;
		}
	}
	return retorno;
}

/*
* \brief intercambia 2 caracteres de posicion en un array de caracteres especificado.
* \param char pCadena[] - Array de caracteres que contiene la cadena.
* \param int i - Indice uno que se intercambiara con el Indice dos
* \param int j - Indice dos que se intercambiara con el indice uno
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si ERROR
*/
static int swapCaracteres(char plistaCaracteres[], int i, int j)
{
	char auxiliar;
	int retorno = ERROR;

	if(plistaCaracteres != NULL && (i >= 0 && i < LEN_BUFFER_STRING) &&
			(j >= 0 && j < LEN_BUFFER_STRING) && i != j )
	{
		auxiliar = plistaCaracteres[i];
		plistaCaracteres[i] = plistaCaracteres[j];
		plistaCaracteres[j] = auxiliar;
		retorno = OPERACION_EXITOSA;
	}
	return retorno;
}

/**
* \brief Recibe un array de caracteres en donde almacenara el texto ingresado por el usuario
*        de forma segura. Elimina el ENTER de la cadena, en caso de haber uno.
* \param char pCadena[] - Cadena de caracteres donde almacenara el texto ingresado por el usuario
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 0 si pudo operar correctamente,
*  		  retorna -1 si ERROR
*/
static int myGets(char pCadena[], int largo, char* pMensaje)
{
    int indiceFinalDeCadena;
    int retorno= ERROR;
    char bufferString[LEN_BUFFER_STRING];

    if(pCadena != NULL && pMensaje != NULL && largo > 0 && largo <= LEN_BUFFER_STRING)
    {
		printf("%s->", pMensaje);
		fflush(stdin);

		if(fgets(bufferString,largo,stdin) != NULL)
		{
			indiceFinalDeCadena = strnlen(bufferString, largo) -1;

			if(bufferString[indiceFinalDeCadena] == '\n')
			{
				bufferString[indiceFinalDeCadena] = '\0';
			}

			strncpy(pCadena, bufferString, largo);
			retorno = OPERACION_EXITOSA;
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
*         retorna -1 si ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_getLetra(char* pLetra, char* pMensaje, char* pMensajeError,char minimo, char maximo, int reintentos)
{
    int i;
    int retorno = ERROR;
    char caracterAuxiliar[LEN_BUFFER_CARACTER];

    if(pLetra != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = SIN_MAS_REINTENTOS;
    	if(reintentos >= 0)
    	{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(caracterAuxiliar,LEN_BUFFER_CARACTER, pMensaje)==0)
				{
					if(strnlen(caracterAuxiliar, LEN_BUFFER_CARACTER) == 1)
					{
						if(esLetra(caracterAuxiliar[0]) && convertirUnCaracterEnMayuscula(&caracterAuxiliar[0])==OPERACION_EXITOSA)
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
*         retorna -1 ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_getInt(int* pNumero, char* pMensaje, char* pMensajeError, int minimo, int maximo, int reintentos)
{
    int i;
    int bufferInt;
    int retorno = ERROR;
    char bufferCadenaAuxiliar[LEN_BUFFER_INT];

    if(pNumero != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
		if(reintentos >= 0 && minimo <= maximo)
		{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(bufferCadenaAuxiliar,LEN_BUFFER_INT, pMensaje) == OPERACION_EXITOSA)
				{
					retorno = SIN_MAS_REINTENTOS;
					if(esNumeroEntero(bufferCadenaAuxiliar, LEN_BUFFER_INT) == TRUE)
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
*         retorna -1 si ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_getFloat(float* pNumero, char* pMensaje, char* pMensajeError, int minimo, int maximo, int reintentos)
{
    int i;
    float bufferFloat;
    int retorno = ERROR;
    char bufferCadenaAuxiliar[LEN_BUFFER_FLOAT];

    if(pNumero != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
		if(reintentos >= 0 && minimo <= maximo)
		{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(bufferCadenaAuxiliar,LEN_BUFFER_FLOAT, pMensaje) == OPERACION_EXITOSA)
				{
					retorno = SIN_MAS_REINTENTOS;
					if(esNumeroFloat(bufferCadenaAuxiliar, LEN_BUFFER_FLOAT)== TRUE)
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
*         retorna -1 si ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_getNombreOApellido(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR;
    char bufferCadenaAuxiliar[LEN_BUFFER_STRING];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	if(largo > 0 && largo <= LEN_BUFFER_STRING && reintentos >= 0)
    	{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(bufferCadenaAuxiliar,LEN_BUFFER_STRING, pMensaje)==OPERACION_EXITOSA)
				{
					retorno = SIN_MAS_REINTENTOS;
					//Si entro al IF, el usuario ingreso correctamente texto.
					//Borro los espacios invalidos
					borrarEspacios(bufferCadenaAuxiliar, LEN_BUFFER_STRING);

					if(esNombreOApellido(bufferCadenaAuxiliar, LEN_BUFFER_STRING)== TRUE)
					{
						if(darFormatoMayusculaMinuscula(bufferCadenaAuxiliar, LEN_BUFFER_STRING) == OPERACION_EXITOSA)
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
    return retorno;
}

/*
* \brief Toma el Id del empleado con el que se quiere operar.
* \param int idMaximo - Maximo id registrado hasta el momento
* \return Retorna INT. Retorna un numero positivo que es el ID ingresado por el usuario,
*         retorno -4 si se quedo sin reintentos
*/
int utn_tomarID(int iDMaximo)
{
	int retorno = SIN_MAS_REINTENTOS;
	int id;

	if(utn_getInt(&id, "\nIngrese Id. O pulse '0' para <<Volver al menu.", "Error, dato invalido", 0, iDMaximo, REINTENTOS)==OPERACION_EXITOSA)
	{
		retorno = id;
	}
	return retorno;
}

/*
* \brief Solicita el ingreso de una opcion al usuario. Requiere maximo y minimo.
* \param int* opcion - retorna a traves de este parametro la opcion seleccionada
* \param int minimo - minimo valor de la opcion
* \param int maximo - maximo valor de la opcion
* \return retorna INT. Retorna un numero positivo que representa la opcion seleccionada.
* 		  retorna   0 si esta OK.
* 		  retorn   -1 si ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_ingreseUnaOpcion(int* opcion, int minimo, int maximo)
{
	int retorno = ERROR;
	if(opcion != NULL && minimo <= maximo)
	{
		retorno = SIN_MAS_REINTENTOS;
		 if(utn_getInt(opcion, "\nIngrese una opcion", "Error. Dato invalido", minimo, maximo, REINTENTOS)==OPERACION_EXITOSA)
		 {
			 retorno = OPERACION_EXITOSA;
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
*         retorna -1 si ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_getTexto(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int largoFinalCadenaAuxiliar;
    int retorno = ERROR;
    char bufferCadenaAuxiliar[LEN_BUFFER_STRING];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	if(largo > 0 && largo <= LEN_BUFFER_STRING && reintentos >= 0)
    	{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(bufferCadenaAuxiliar,LEN_BUFFER_STRING, pMensaje)==OPERACION_EXITOSA)
				{
					retorno = SIN_MAS_REINTENTOS;
					//Si entro al IF, el usuario ingreso correctamente texto.
					//Borro los espacios invalidos
					if(borrarEspacios(bufferCadenaAuxiliar, LEN_BUFFER_STRING)== OPERACION_EXITOSA)
					{
						largoFinalCadenaAuxiliar = strnlen(bufferCadenaAuxiliar, LEN_BUFFER_STRING);

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
*         retorna -1 si ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_getAlfanumerico(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR;
    char bufferCadenaAuxiliar[LEN_BUFFER_STRING];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	if(largo > 0 && largo <= LEN_BUFFER_STRING && reintentos >= 0)
    	{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(bufferCadenaAuxiliar,LEN_BUFFER_STRING, pMensaje)== OPERACION_EXITOSA)
				{
					retorno = SIN_MAS_REINTENTOS;
					//Si entro al IF, el usuario ingreso correctamente texto.
					//Borro los espacios invalidos
					if(esAlfanumerico(bufferCadenaAuxiliar, LEN_BUFFER_STRING)== TRUE)
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
*         retorna -1 si ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_getCuit(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR;
    char bufferCadenaAuxiliar[BUFFER_LEN_CUIT];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	if(largo <= BUFFER_LEN_CUIT && reintentos >= 0) //El largo debe ser exacto. 13 para el CUIL y 1 para el '\0'
    	{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(bufferCadenaAuxiliar,BUFFER_LEN_CUIT, pMensaje)==OPERACION_EXITOSA)
				{
					retorno = SIN_MAS_REINTENTOS;
					//Si entro al IF, el usuario ingreso correctamente texto.
					//Borro los espacios invalidos
					if(esCuit(bufferCadenaAuxiliar, strnlen(bufferCadenaAuxiliar,largo)) == TRUE)
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
*         retorna -1 si ERROR
*         retorno -4 si se quedo sin reintentos
*/
int utn_getDireccion(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR;
    char bufferCadenaAuxiliar[LEN_BUFFER_STRING];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	if(largo > 0 && largo <= LEN_BUFFER_STRING && reintentos >= 0)
    	{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(bufferCadenaAuxiliar,LEN_BUFFER_STRING, pMensaje)==OPERACION_EXITOSA)
				{
					retorno = SIN_MAS_REINTENTOS;
					borrarEspacios(bufferCadenaAuxiliar, LEN_BUFFER_STRING);
			 		if(esDireccion(bufferCadenaAuxiliar, LEN_BUFFER_STRING) == TRUE)
					{
			 			if(darFormatoMayusculaMinuscula(bufferCadenaAuxiliar, LEN_BUFFER_STRING)==OPERACION_EXITOSA)
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
*         retorna -1 si ERROR
*/
int utn_getNombreAlfanumerico(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int retorno = ERROR;
    char bufferCadenaAuxiliar[LEN_BUFFER_STRING];

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	if(largo > 0 && largo <= LEN_BUFFER_STRING && reintentos >= 0)
    	{
			for(i = 0; i <= reintentos; i++)
			{
				if(myGets(bufferCadenaAuxiliar,LEN_BUFFER_STRING, pMensaje)== OPERACION_EXITOSA)
				{
					borrarEspacios(bufferCadenaAuxiliar, LEN_BUFFER_STRING);
					if(esNombreAlfanumerico(bufferCadenaAuxiliar, LEN_BUFFER_STRING) == TRUE)
					{
						if(darFormatoMayusculaMinuscula(bufferCadenaAuxiliar, largo) == OPERACION_EXITOSA)
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
    return retorno;
}
