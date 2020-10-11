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

int main(void) {
	int op;
	Cliente clientes[QTY_CLIENTES];
	Aviso avisos[QTY_AVISOS];

	int idElegida;
	cliente_initClientes(clientes, QTY_CLIENTES);
	aviso_initAvisos(avisos, QTY_AVISOS);
	cliente_altaForzada(50, "Jorge", "Jesus", "20358638628", clientes, QTY_CLIENTES);
	cliente_altaForzada(51, "Maria", "Damonte", "27229381828", clientes, QTY_CLIENTES);
	cliente_altaForzada(52, "Fernando", "Fleitas", "20235838321", clientes, QTY_CLIENTES);


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
					aviso_changeStatus(avisos, QTY_AVISOS, idElegida, TRUE);

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
					aviso_changeStatus(avisos, QTY_AVISOS, idElegida, FALSE);

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
