/*
 * Informe.c
 *
 *  Created on: 11 oct. 2020
 *      Author: marcos
 */
#include "Cliente.h"
#include "Aviso.h"
#include "Informe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int informe_calculateNumAvisosOneCliente(Aviso* listAvisos, int lenAvisos, int idCliente)
{
	int retorno = -1;
	int cantidadAvisos = 0;
	int i;
	if(listAvisos != NULL && lenAvisos > 0 && idCliente > 0)
	{
		for (i = 0; i < lenAvisos;i++)
			{
				if(listAvisos[i].isEmpty == FALSE && listAvisos[i].idCliente == idCliente)
				{
					cantidadAvisos++;
				}
			}
		retorno = cantidadAvisos;
	}
	return retorno;
}
int informe_printAllClientes(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos)
{
	int retorno = -1;
	int i;
	int bufferCantidad;
	if(listAvisos != NULL &&
	   lenAvisos > 0 &&
	   listClientes != NULL &&
	   lenClientes > 0)
	{
		for (i = 0; i < lenClientes;i++)
		{
			if(listClientes[i].isEmpty == FALSE)
			{
				bufferCantidad = informe_calculateNumAvisosOneCliente(listAvisos, lenAvisos, listClientes[i].idCliente);
				if(bufferCantidad != -1)
				{
					printf(PRINT_ONE_CLIENTE_ADD_AVISO,listClientes[i].idCliente,listClientes[i].nombre,listClientes[i].apellido,listClientes[i].cuit,bufferCantidad);
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}
int informe_countAvisosPausados(Aviso* listAvisos, int lenAvisos)
{
	int retorno = -1;
	int cantidadAvisosPausados = 0;
	int i;
	if(listAvisos != NULL && lenAvisos > 0)
	{
		for (i = 0; i < lenAvisos;i++)
			{
				if(listAvisos[i].isActive == FALSE && listAvisos[i].isEmpty == FALSE)
				{
					cantidadAvisosPausados++;
				}
			}
		retorno = cantidadAvisosPausados;
	}
	return retorno;
}
int informe_printCountAvisosPausados(Aviso* listAvisos, int lenAvisos)
{
	int retorno = -1;
	int cantidadPausados;
	cantidadPausados = informe_countAvisosPausados(listAvisos, lenAvisos);
	if (cantidadPausados != -1)
	{
		printf(PRINT_COUNT_AVISOS_PAUSADOS, cantidadPausados);
	}

	return retorno;
}
int informe_findClienteMoreAvisos(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos)
{
	int retorno = -1;
	int i = 0;
	Cliente clienteMayorAvisos;
	int banderaPrimero = TRUE;
	int bufferNumeroAvisos;
	if(listAvisos != NULL &&
	   lenAvisos > 0 &&
	   listClientes != NULL &&
	   lenClientes > 0)
	{
		for (i = 0; i < lenClientes;i++)
		{
			if(listClientes[i].isEmpty == FALSE)
			{
				bufferNumeroAvisos = informe_calculateNumAvisosOneCliente(listAvisos, lenAvisos, listClientes[i].idCliente);
				if(banderaPrimero == TRUE)
				{
					clienteMayorAvisos = listClientes[i];
					banderaPrimero = FALSE;
				}
				else
				{
					if(bufferNumeroAvisos > informe_calculateNumAvisosOneCliente(listAvisos, lenAvisos, clienteMayorAvisos.idCliente))
					{
						clienteMayorAvisos = listClientes[i];
					}
				}
			}
		}
		printf(PRINT_ONE_CLIENTE_ADD_AVISO,clienteMayorAvisos.idCliente,clienteMayorAvisos.nombre,clienteMayorAvisos.apellido,clienteMayorAvisos.cuit,informe_calculateNumAvisosOneCliente(listAvisos, lenAvisos, clienteMayorAvisos.idCliente));
		retorno = 0;
	}
	return retorno;
}

