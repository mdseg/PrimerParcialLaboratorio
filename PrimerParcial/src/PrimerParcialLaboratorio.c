/*
 ============================================================================
 Name        : TP2.c
 Author      : Marcos
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Cliente.h"
#include "Aviso.h"
#include <ctype.h>
#include "Informe.h"

#define MAIN_MENU "\n-------Sistema de Registro de Clientes y Avisos ----------\nElija una de estas opciones:\n1-Alta de Cliente\n2-Modificar datos de cliente\n3-Baja de Cliente\n4-Publicar\n5-Pausar aviso\n6-Renaudar aviso\n7-Imprimir Clientes\n8-Informar\n9-SALIR\n"
#define MENU_REPORT "-------Menu de reporte----------\nSeleccione el tipo de informe deseado:\n1-Cliente con más avisos\n2-Cantidad de avisos pausados\n3-Rubro con mas avisos\n4-Cliente con mayor cantidad de avisos activos.\n5-Cliente con mayor cantidad de avisos pausados.\n6-Volver al menú anterior\n"
#define ERROR_MENU "Por favor, elija una opción válida.\n"
#define EXIT_PROGRAM "Saliendo de la aplicación...\n"

#define ACTIVOS 0
#define PAUSADOS 1
#define TODOS 2

int crearListaInicial(Aviso* avisos, int lenAvisos, Cliente* clientes, int lenClientes);

int main(void) {
	int op;
	int opSecundario;
	int opcionConfirmar;
	Cliente clientes[QTY_CLIENTES];
	Aviso avisos[QTY_AVISOS];
	int idElegida;
	cliente_initClientes(clientes, QTY_CLIENTES);
	aviso_initAvisos(avisos, QTY_AVISOS);
	crearListaInicial(avisos, QTY_AVISOS, clientes, QTY_CLIENTES);
	do
	{
		utn_getInt(&op, MAIN_MENU, ERROR_MENU, 1, 9, ATTEMPTS);
		switch(op)
		{
			case 1:
				printf(ENTERING_CREATE_CLIENTE);
				cliente_createCliente(clientes, QTY_CLIENTES);
				break;
			case 2:
				if(cliente_checkActiveClientes(clientes, QTY_CLIENTES) == 0)
				{
					printf(ENTERING_MODIFY_CLIENTE);
					cliente_modifyCliente(clientes, QTY_CLIENTES);
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 3:
				if(cliente_checkActiveClientes(clientes, QTY_CLIENTES) == 0)
				{
					printf(ENTERING_REMOVE_CLIENTE);
					if(cliente_printClientes(clientes, QTY_CLIENTES) == 0 && utn_getInt(&opSecundario, INPUT_ID, ERROR_IDCLIENTE, ID_MIN, ID_MAX, ATTEMPTS) == 0 &&
						aviso_printAvisosByIdCliente(avisos, QTY_AVISOS, opSecundario) == 0)
					{
						if(utn_getInt(&opcionConfirmar,DELETE_CLIENTE_CONFIRM, ERROR_GENERIC, 1, 2, ATTEMPTS) == 0)
						{
							if(opcionConfirmar == 1)
							{
							aviso_deleteAllAvisosByIdCliente(avisos, QTY_AVISOS, opSecundario);
							cliente_unsuscribeCliente(clientes, QTY_CLIENTES,opSecundario);
							}
						}
						else
						{
							printf(DELETE_CLIENTE_CANCEL);
						}
					}
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 4:
				if(cliente_checkActiveClientes(clientes, QTY_CLIENTES) == 0)
				{
					printf(ENTERING_CREATE_AVISO);
					aviso_createAviso(avisos, QTY_AVISOS, clientes, QTY_CLIENTES);
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 5:
				if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0 && printf(ENTERING_PAUSE_AVISO) &&
						aviso_printAllAvisos(avisos, QTY_AVISOS) == 0)
				{
					if(utn_getInt(&idElegida, INPUT_IDAVISO, ERROR_IDAVISO, ID_MIN, ID_MAX, ATTEMPTS) == 0)
					{
						aviso_changeStatus(avisos, QTY_AVISOS,clientes,QTY_CLIENTES, idElegida, PAUSAR);
					}
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 6:
				if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0 && printf(ENTERING_RESUME_AVISO) &&
						aviso_printAllAvisos(avisos, QTY_AVISOS) == 0)
				{
					if(utn_getInt(&idElegida, INPUT_IDAVISO, ERROR_IDAVISO, ID_MIN, ID_MAX, ATTEMPTS) == 0)
					{
						aviso_changeStatus(avisos, QTY_AVISOS,clientes,QTY_CLIENTES, idElegida, RENAUDAR);
					}
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 7:
				if(cliente_checkActiveClientes(clientes, QTY_CLIENTES) == 0)
				{
					printf(ENTERING_CLIENTE_LIST);
					informe_printAllClientes(clientes, QTY_CLIENTES, avisos, QTY_AVISOS);
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 8:
				if(cliente_checkActiveClientes(clientes, QTY_CLIENTES) == 0)
				{
					do{
						if(utn_getInt(&opSecundario, MENU_REPORT, MENU_SELECT_ERROR, 1, 6, ATTEMPTS) == 0)
						{
							switch (opSecundario)
							{
								case 1:
									if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0)
									{
										informe_findClienteMoreAvisos(clientes, QTY_CLIENTES, avisos, QTY_AVISOS,TODOS);
									}
									break;
								case 2:
									if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0)
									{
										informe_printCountAvisosPausados(avisos, QTY_AVISOS);
									}
									break;
								case 3:
									if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0)
									{
										informe_findRubroMoreAvisos(avisos, QTY_AVISOS);
									}
									break;
								case 4:
									if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0)
									{
										informe_findClienteMoreAvisos(clientes, QTY_CLIENTES, avisos, QTY_AVISOS,ACTIVOS);
									}
									break;
								case 5:
									if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0)
									{
										informe_findClienteMoreAvisos(clientes, QTY_CLIENTES, avisos, QTY_AVISOS,PAUSADOS);
									}
									break;
							}
						}
					}
					while (opSecundario != 6);
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 9:
				printf(EXIT_PROGRAM);
				break;
		}
	}
	while(op != 9);
	return EXIT_SUCCESS;
}
/** \brief crea una lista de clientes y avisos relacionados para poder realizar pruebas mas facilmente
*
* \param Aviso* avisos
* \param int lenAvisos
* \param Cliente* clientes
* \param int lenClientes

* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int crearListaInicial(Aviso* avisos, int lenAvisos, Cliente* clientes, int lenClientes)
{
	int retorno =  -1;
	cliente_altaForzada("Jorge Ismael Dario", "Jesus", "20358638628", clientes, lenClientes);
	cliente_altaForzada("Maria", "Damonte", "27229381828", clientes, lenClientes);
	cliente_altaForzada("Fernando", "Fleitas", "20235838321", clientes, lenClientes);

	aviso_altaForzada(2, "Aviso de prueba", TRUE, 1, avisos, lenAvisos);
	aviso_altaForzada(2, "Se vende auto. 4 puertas con excelente vista a la calle", TRUE, 1, avisos, lenAvisos);
	aviso_altaForzada(2, "Pinto casas a domicilio", TRUE, 1, avisos, lenAvisos);
	aviso_altaForzada(3, "Plomero y gasista", TRUE, 2, avisos, lenAvisos);
	aviso_altaForzada(3, "Enfermero", TRUE, 2, avisos, lenAvisos);
	aviso_altaForzada(3, "Alquilo balcones", TRUE, 3, avisos, lenAvisos);
	aviso_altaForzada(4, "Se necesita empleado urgente", TRUE, 3, avisos, lenAvisos);
	retorno = 0;
	return retorno;
}
