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

int main(void) {
	int op;
	int opSecundario;
	Cliente clientes[QTY_CLIENTES];
	Aviso avisos[QTY_AVISOS];

	int idElegida;
	cliente_initClientes(clientes, QTY_CLIENTES);
	aviso_initAvisos(avisos, QTY_AVISOS);
	cliente_altaForzada(50, "Jorge", "Jesus", "20358638628", clientes, QTY_CLIENTES);
	cliente_altaForzada(51, "Maria", "Damonte", "27229381828", clientes, QTY_CLIENTES);
	cliente_altaForzada(52, "Fernando", "Fleitas", "20235838321", clientes, QTY_CLIENTES);

	aviso_altaForzada(50, 1, "Aviso de prueba", TRUE, 50, avisos, QTY_AVISOS);
	aviso_altaForzada(60, 2, "Se vende auto. 4 puertas con excelente vista a la calle", TRUE, 50, avisos, QTY_AVISOS);
	aviso_altaForzada(70, 3, "Pinto casas a domicilio", TRUE, 51, avisos, QTY_AVISOS);
	aviso_altaForzada(71, 3, "Plomero y gasista", TRUE, 51, avisos, QTY_AVISOS);
	aviso_altaForzada(71, 3, "Jardinero", TRUE, 51, avisos, QTY_AVISOS);

	do
	{
		utn_getInt(&op, MAIN_MENU, ERROR_GENERIC, 1, 9, ATTEMPTS);
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
					cliente_unsuscribeCliente(clientes, QTY_CLIENTES);
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 4:
				if(cliente_checkActiveClientes(clientes, QTY_CLIENTES) == 0)
				{
					printf(ENTERING_MODIFY_AVISO);
					aviso_createAviso(avisos, QTY_AVISOS, clientes, QTY_CLIENTES);
				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 5:
				if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0 &&
					utn_getInt(&idElegida, INPUT_IDAVISO, ERROR_GENERIC, ID_MIN, ID_MAX, ATTEMPTS) == 0)
				{
					printf(ENTERING_PAUSE_AVISO);
					aviso_changeStatus(avisos, QTY_AVISOS,clientes,QTY_CLIENTES, idElegida, TRUE);

				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
			case 6:
				if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0 &&
					utn_getInt(&idElegida, INPUT_IDAVISO, ERROR_GENERIC, ID_MIN, ID_MAX, ATTEMPTS) == 0)
				{
					printf(ENTERING_RESUME_AVISO);
					aviso_changeStatus(avisos, QTY_AVISOS,clientes,QTY_CLIENTES, idElegida, FALSE);
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
						if(utn_getInt(&opSecundario, MENU_REPORT, MENU_SELECT_ERROR, 1, 4, ATTEMPTS) == 0)
						{
							switch (opSecundario)
							{
								case 1:
									if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0)
									{
										informe_findClienteMoreAvisos(clientes, QTY_CLIENTES, avisos, QTY_AVISOS);
									}
									break;
								case 2:
									if(aviso_checkActiveAvisos(avisos, QTY_AVISOS) == 0)
									{
										informe_printCountAvisosPausados(avisos, QTY_AVISOS);
									}
									break;
								case 3:
									break;
							}
						}
					}
					while (op != 4);


				}
				else
				{
					printf(ERROR_NOT_AVAILABLE);
				}
				break;
				break;
			case 9:
				printf(EXIT_PROGRAM);
				break;
		}
	}
	while(op != 9);
	return EXIT_SUCCESS;
}
