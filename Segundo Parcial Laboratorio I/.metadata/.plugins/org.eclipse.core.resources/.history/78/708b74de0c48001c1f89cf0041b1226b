#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ComprobarErrores.h"
#include "Utn_tomarDatos.h"
#include "LinkedList.h"
#include "ValidarDatos.h"
#include "Menu_mensajes.h"

typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    float sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* pIdStr,char* pNombreStr,char* pHorasTrabajadasStr, char* pSalarioStr);
Employee* employee_newParametrosDiferenciandoTiposDeDatos(int id, char pNombre[],  float salario, int horasTrabajadas);
void employee_delete(Employee* pEmpleado);
int employee_getDataFromUserToEditAFiel(Employee* pEmpleado, int opcion);
void employee_ImprimirEncabezadoDeDatos(int opcion);
void employee_ImprimirFilaVaciaDeDatos(int opcion);
int employee_ImprimirFilaDeDatos(Employee* this, int opcion);
int employee_imprimirUnSoloEmpleado(Employee* this);
int employee_setSueldo(Employee* this, float sueldo);
int employee_getSueldo(Employee* this, float* pSueldo);
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this, int* pHorasTrabajadas);
int employee_setId(Employee* this, int id);
int employee_getId(Employee* this, int* pId);
int employee_setNombre(Employee* this, char* pNombre);
int employee_getNombre(Employee* this, char* pNombre);
int employee_setIdTexto(Employee* pElemento, char* pId);
int employee_setHorasTrabajadasTexto(Employee* pElemento, char* pHorasTrabajadas);
int employee_setSueldoTexto(Employee* pElemento, char* pSalario);
int employee_orderByName(void* pElementoUno, void* pElementoDos);
int employee_orderById(void* pElementoUno, void* pElementoDos);
int employee_orderBySalary(void* pElementoUno, void* pElementoDos);
int employee_orderByHoursWorked(void* pElementoUno, void* pElementoDos);
int employee_findEmployeeById(LinkedList* pArrayListEmployee, int id);
Employee* employee_findPointerToEmployeeById(LinkedList* pArrayListEmployee, int id);
int employee_getDataToAddANewEmployee(char nombre[], int lenNombre, int* pHorasTrabajadas, float* pSalario);
int employee_gettersFromEmployee(Employee* pEmpleado, int* pId, int* pHorasTrabajadas, char* nombre, float *pSalario);
int employee_getLastOrNextId(int opcion);

#endif // employee_H_INCLUDED
