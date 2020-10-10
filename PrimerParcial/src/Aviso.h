/*
 * aviso.h
 *
 *  Created on: 30 sep. 2020
 *      Author: marcos
 */

#ifndef AVISO_H_
#define AVISO_H_

#include "Cliente.h"

#define TRUE 1
#define FALSE 0
#define ATTEMPTS 5
#define ID_MIN 0
#define ID_MAX 1000
#define RUBRO_MIN 1
#define RUBRO_MAX 30
#define UP 1
#define DOWN 0
#define LONG_NAME 50
#define LONG_CONTENIDO 51
#define QTY_AVISOS 100
#define DATOINT_MIN 0
#define DATOINT_MAX 1000
#define FLOTANTE_MIN 0
#define FLOTANTE_MAX 100000

//#define MAIN_MENU "\n-------Sistema de Registro de Avisos y Avisos ----------\nElija una de estas opciones:\n1-Alta de Aviso\n2-Modificar datos de aviso\n3-Baja de Aviso\n4-Publicar\n5-Pausar publicación\n6-Renaudar publicación\n7-Imprimir Avisos\n8-Informar\n9-SALIR\n"
#define MENU_MODIFY_AVISO "-------Menu de modificación de Avisos----------\nSeleccione el campo a modificar:\n1-Nombre\n2-Apellido\n3-CUIT\n4-Volver al menú principal\n"
//#define MENU_REPORT "-------Menu de reporte----------\nSeleccione el tipo de informe deseado:\n1-Listado de los empleados ordenados alfabéticamente por Name y datoInt.\n2- Función Personalizada\n3-Volver al menú principal\n"
//#define MENU_ORDER "Seleccione el orden alfabético del informe:\n1-Ascendente\n2-Descendente\n"
#define MENU_SELECT_ERROR "Por favor, elija una opción valida.\n"



#define INPUT_IDAVISO "Ingrese el Id del aviso:\n"
#define INPUT_RUBRO "Ingrese el rubro:\n"
#define INPUT_CONTENIDO "Ingrese el contenido del aviso:\n"
#define INPUT_CUIT_AVISO "Ingrese el Cuit del aviso:\n"
#define INPUT_IDCLIENTE "Ingrese el ID del cliente.\n"

//Create
#define CREATE_AVISO_SUCCESS "Aviso creado con éxito con ID: %d"

//Modifiy
#define MODIFY_AVISO_SUCCESS "\nAviso modificado correctamente.\n"
#define MODIFY_AVISO_ERROR "\nError en la modificación del aviso.\n"
#define MODIFY_IDAVISO_SUCCESS "Id del aviso modificado.\n"
#define MODIFY_IDAVISO_ERROR "Error al modificar el Id del aviso.\n"
#define MODIFY_RUBRO_SUCCESS "Rubro del aviso modificado.\n"
#define MODIFY_RUBRO_ERROR "Error al modificar el rubro del aviso.\n"
#define MODIFY_CONTENIDO_SUCCESS "Contenido del aviso modificado.\n"
#define MODIFY_CONTENIDO_ERROR "Error al modificar el contenido del aviso.\n"


//Informe
#define REPORT_AVISO_SUCCESS_FINISH "----Finalizado el informe----\n"
#define REPORT_AVISO_ERROR "\nError al realizar el informe.\n"
#define DELETE_AVISO_SUCCESS "\nAviso dado de baja correctamente.\n"
#define DELETE_AVISO_ERROR "No existe un aviso con ese ID.\n"

//Acceso
#define ENTERING_CREATE_AVISO "Ingresando al sector de altas...\n"
#define ENTERING_MODIFY_AVISO "Ingresando al sector de modificaciones...\n"
#define ENTERING_REMOVE_AVISO "Ingresando al sector de bajas...\n"


#define ERROR_NOT_AVAILABLE "Debe ingresar al menos un registro para utilizar esta funcionalidad.\n"
#define PRINT_ONE_REGISTRY "ID: %d - Nombre: %s - Apellido: %s - CUIT: %s\n"
#define EXIT_PROGRAM "Saliendo de la aplicación...\n"

struct
{
 int idAviso;
 int rubro;
 char contenido[LONG_NAME];
 int isActive;
 int idCliente;
 int isEmpty;
}typedef Aviso;

int aviso_createAviso(Aviso* listAvisos, int lenAvisos, Cliente* listClientes, int lenClientes);
int aviso_createAvisoReport(Aviso* list, int len);
int aviso_initAvisos(Aviso* list, int len);
int aviso_checkActiveAvisos(Aviso* list, int len);
int aviso_findAvisoById(Aviso* list, int len,int id);
int aviso_modifyAviso(Aviso* listAviso, int lenAvisos, Cliente* listClientes, int lenClientes);
int aviso_unsuscribeAviso(Aviso* list, int len);
int aviso_printAvisos(Aviso* list, int length);

#endif /* AVISO_H_ */
