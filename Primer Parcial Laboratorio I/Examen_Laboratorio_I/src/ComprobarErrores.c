/*
 * ComprobarErrores.c
 *
 *  Created on: 18 oct 2021
 *      Author: GONZALO
 */

#include "ComprobarErrores.h"
#define EXITO 1
#define ERROR 0
#define LEN_MENSAJE 200

static void imprimirErrores(int codigoError);

/*
* \brief Evalua el exito de una operacion. Si hay exito, no realiza acciones.
*        Ante una falla (estado menor que 0), se apoya en otra funcion imprimirErrores (int codigoError),
*        enviandole el estado recibido de la operacion (que almacena el codigo de error).
* \param int estadoOperacion - Valor que identifica el estado (exito o falla) de una operacion.
* \return retorna un INT. 1 si la operacion recibida fue exitosa.
* 		  retorna 0 si la operacion recibida no fue exitosa.
*/
int utn_comprobarEstadoDeOperacion(int estadoOperacion)
{
	int retorno = EXITO;

	if(estadoOperacion < 0)
	{
		imprimirErrores(estadoOperacion);
		retorno = ERROR;
	}
	return retorno;
}

/*
* \brief Evalua el codigo de error recibido, e imprime el error asociado (si corresponde).
* \param int codigoError - Codigo de identificacion del error
* \return void.
*/
static void imprimirErrores(int codigoError)
{
	char mensaje[LEN_MENSAJE];

	switch(codigoError)
	{
		case -1:
			strncpy(mensaje,"\n\t\t--ERROR. Direccion de memoria de parametros es NULL. No se puede operar.--\n", LEN_MENSAJE);
			break;
		case -2:
			strncpy(mensaje, "\n\t\t--ERROR. Longitud de ARRAY es invalida o supera el limite del buffer. No se puede operar.--\n", LEN_MENSAJE);
			break;
		case -3:
			strncpy(mensaje, "\n\t\t--ERROR. Funcion fgets() No se pudo asignar el dato ingresado. No se puede operar--\n", LEN_MENSAJE);
			break;
		case -4:
			strncpy(mensaje, "\n\t\t--ERROR. Se acabaron los reintentos para operar.--\n", LEN_MENSAJE);
			break;
		case -5:
			strncpy(mensaje, "\n\t\t--ERROR. Cantidad de reintentos no puede ser negativa. No se puede operar--\n", LEN_MENSAJE);
			break;
		case -6:
			strncpy(mensaje,"\n\t\t--ERROR. Error con los maximos y minimos. El minimo no puede ser mayor que el maximo.--\n" , LEN_MENSAJE);
			break;
		case -7:
			strncpy(mensaje, "\n\t\t--ERROR. La funcion mygets() devolvio un error.--\n", LEN_MENSAJE);
			break;
		case -8:
			strncpy(mensaje, "\n\t\t--ERROR. La funcion esNumeroEntero() devolvio un error.--\n", LEN_MENSAJE);
			break;
		case -9:
			strncpy(mensaje, "\n\t\t--ERROR. La funcion esNombreOApellido() devolvio un error.--\n", LEN_MENSAJE);
			break;
		case -10:
			strncpy(mensaje, "\n\t\t--ERROR. La funcion esNumeroFloat() devolvio un error.--\n", LEN_MENSAJE);
			break;
		case -11:
			strncpy(mensaje,"\n\t\t--ERROR. ID invalido.--\n" , LEN_MENSAJE);
			break;
		case -12:
			strncpy(mensaje, "\n\t\t--ERROR. El Salon que estaba asociado a ese Id ha sido dado de baja.--\n", LEN_MENSAJE);
			break;
		case -13:
			strncpy(mensaje, "\n\t\t--ERROR. El parametro 'i' y el parametro 'j' no pueden ser el mismo numero.--\n", LEN_MENSAJE);
			break;
		case -14:
			strncpy(mensaje, "\n\t\t--ERROR. No se pudieron tomar los datos correctamente.\n\t\t  No se aplicaron cambios en el sistema.--\n", LEN_MENSAJE);
			break;
		case -15:
			strncpy(mensaje, "\n\t\t--ERROR. No se aplicaron modificaciones sobre el elemento.--\n", LEN_MENSAJE);
			break;
		case -16:
			strncpy(mensaje, "\n\t\t--ERROR. No hay elementos cargados en la lista del sistema.--\n", LEN_MENSAJE);
			break;
		case -17:
			strncpy(mensaje, "\n\t\t--ERROR. Indice fuera de rango.--\n", LEN_MENSAJE);
			break;
		case -18:
			strncpy(mensaje, "\n\t\t--ERROR. El Arcade que estaba asociado a ese Id ha sido dado de baja.--\n", LEN_MENSAJE);
			break;
		case -19:
			strncpy(mensaje, "\n\t\t--No se aplicaron bajas en el sistema.--\n", LEN_MENSAJE);
			break;
		case -20:
			strncpy(mensaje,"\n\t\t--No se encontraron datos asociados al ID indicado.--\n" , LEN_MENSAJE);
			break;
		case -21:
			strncpy(mensaje, "\n\t\t--ERROR. El listado esta lleno. No se pueden cargar mas elementos.--\n", LEN_MENSAJE);
			break;
		case -22:
			strncpy(mensaje, "\n\t\t--ERROR. No se pudo obtener una respuesta valida.--\n", LEN_MENSAJE);
			break;
		case -23:
			strncpy(mensaje, "\n\t\t--ERROR. El parametro i o j estan fuera de rango.--\n", LEN_MENSAJE);
			break;
		case -24:
			strncpy(mensaje, "\n\t\t--ERROR. Error al intentar borrar espacios en blanco.--\n", LEN_MENSAJE);
			break;
		case -25:
			strncpy(mensaje, "\n\t\t--ERROR. No se pudo llevar a cabo ningun alta.--\n", LEN_MENSAJE);
			break;
		case -26:
			strncpy(mensaje, "\n\t\t--ERROR. El elemento recibido esta vacio.--\n", LEN_MENSAJE);
			break;
		default :
			strncpy(mensaje, "\n\t\t--ERROR.--\n", LEN_MENSAJE);
			break;
	}
	printf("%s", mensaje);
}
