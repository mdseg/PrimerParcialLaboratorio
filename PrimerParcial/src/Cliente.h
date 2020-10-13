/*
 * Cliente.h
 *
 *  Created on: 10 oct. 2020
 *      Author: marcos
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define TRUE 1
#define FALSE 0
#define ATTEMPTS 5
#define ID_MIN 0
#define ID_MAX 1000
#define LONG_NAME 50
#define QTY_CLIENTES 100
#define UP 1
#define DOWN 0


#define MENU_MODIFY "-------Menu de modificación de Clientes----------\nSeleccione el campo a modificar:\n1-Nombre\n2-Apellido\n3-CUIT\n4-Volver al menú principal\n"
#define MENU_SELECT_ERROR "Por favor, elija una opción valida.\n"


#define ERROR_GENERIC "Error\n"
#define INPUT_ID "Ingrese el Id:\n"
#define INPUT_NAME "Ingrese el nombre:\n"
#define INPUT_APELLIDO "Ingrese el apellido:\n"
#define INPUT_CUIT "Ingrese el Cuit del cliente sin guiones (ej: 20358638628):\n"
#define INPUT_DATOINT "Ingrese el datoInt.\n"

//Create
#define CREATE_CLIENTE_SUCCESS "Cliente creado con éxito con ID: %d"
#define CREATE_CLIENTE_CUIT_ERROR "Ya existe un cliente con ese CUIT"

//Modifiy
#define MODIFY_CLIENTE_SUCCESS "\nCliente modificado correctamente.\n"
#define MODIFY_CLIENTE_ERROR "\nError en la modificación del cliente.\n"
#define MODIFY_NAME_SUCCESS "Nombre modificado con éxito.\n"
#define MODIFY_NAME_ERROR "Error al intentar modificar el nombre.\n"
#define MODIFY_APELLIDO_SUCCESS "Apellido modificado con éxito.\n"
#define MODIFY_APELLIDO_ERROR "Error al intentar modificar el apellido.\n"
#define MODIFY_CUIT_SUCCESS "Cuit modificado con éxito.\n"
#define MODIFY_CUIT_ERROR "Error al intentar modificar el Cuit.\n"


//Informe
#define REPORT_CLIENTE_SUCCESS_FINISH "----Finalizado el informe----\n"
#define REPORT_CLIENTE_ERROR "\nError al realizar el informe.\n"
#define DELETE_CLIENTE_SUCCESS "\nCliente dado de baja correctamente.\n"
#define DELETE_CLIENTE_ERROR "No existe un cliente con ese ID.\n"
#define DELETE_CLIENTE_CONFIRM "¿Desea eliminar a este cliente? Ingrese 1 para confirmar o 2 para cancelar.\n"
#define DELETE_CLIENTE_CANCEL "\nSe ha cancelado la eliminación del cliente.\n"
//Acceso
#define ENTERING_CREATE_CLIENTE "Ingresando al sector de altas...\n"
#define ENTERING_MODIFY_CLIENTE "Ingresando al sector de modificaciones...\n"
#define ENTERING_REMOVE_CLIENTE "Ingresando al sector de bajas...\n"


#define ERROR_NOT_AVAILABLE "Debe ingresar al menos un registro para utilizar esta funcionalidad.\n"
#define PRINT_ONE_REGISTRY "ID: %d - Nombre: %s - Apellido: %s - CUIT: %s\n"
#define EXIT_PROGRAM "Saliendo de la aplicación...\n"

struct
{
 int idCliente;
 char nombre[LONG_NAME];
 char apellido[LONG_NAME];
 char cuit[LONG_NAME];
 int isEmpty;
}typedef Cliente;

int cliente_createCliente(Cliente* list, int len);
int cliente_createClienteReport(Cliente* list, int len);
int cliente_initClientes(Cliente* list, int len);
int cliente_checkActiveClientes(Cliente* list, int len);
int cliente_findClienteById(Cliente* list, int len,int id);
int cliente_modifyCliente(Cliente* list, int len);
int cliente_unsuscribeCliente(Cliente* list, int len, int idCliente);
int cliente_printClientes(Cliente* list, int length);
int cliente_altaForzada(char* nombre, char* apellido, char* cuit,Cliente* list, int len);
int cliente_printOneCliente(Cliente* list, int len, int idCliente);

#endif /* CLIENTE_H_ */

