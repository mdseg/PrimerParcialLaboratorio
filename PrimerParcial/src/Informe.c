/*
 * Informe.c
 *
 *  Created on: 11 oct. 2020
 *      Author: marcos
 */
#include "Cliente.h"
#include "Aviso.h"
#include "utn.h"
#include "Informe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int clienteAuxiliar_searchFreeIndex(ClienteAuxiliar* list,int* pIndex, int lenClientes);
static int clienteAuxiliar_init(ClienteAuxiliar* list, int lenClientes);
static int clienteAuxiliar_calculateNumAvisos(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos, ClienteAuxiliar* listAuxiliar);
static int clienteAuxiliar_sortByCantAvisos(ClienteAuxiliar* list, int lenClientes, int order);

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
	int index;
	Cliente clienteMayorAvisos;
	ClienteAuxiliar listaClientesAvisos[QTY_CLIENTES];
	int maxnumAvisos;
	if(listAvisos != NULL &&
	   lenAvisos > 0 &&
	   listClientes != NULL &&
	   lenClientes > 0)
	{
		clienteAuxiliar_init(listaClientesAvisos, lenClientes);
		clienteAuxiliar_calculateNumAvisos(listClientes, lenClientes, listAvisos, lenAvisos, listaClientesAvisos);
		clienteAuxiliar_sortByCantAvisos(listaClientesAvisos, lenClientes, UP);
		maxnumAvisos = listaClientesAvisos[0].cantidadAvisos;
		while(listaClientesAvisos[i].cantidadAvisos == maxnumAvisos)
		{
			index = cliente_findClienteById(listClientes, lenClientes, listaClientesAvisos[i].idCliente);
			clienteMayorAvisos = listClientes[index];
			printf(PRINT_ONE_CLIENTE_ADD_AVISO,clienteMayorAvisos.idCliente,clienteMayorAvisos.nombre,clienteMayorAvisos.apellido,clienteMayorAvisos.cuit,informe_calculateNumAvisosOneCliente(listAvisos, lenAvisos, clienteMayorAvisos.idCliente));
			i++;
		}

		retorno = 0;
	}
	return retorno;
}
int clienteAuxiliar_init(ClienteAuxiliar* list, int lenClientes)
{
	int retorno = -1;
	int i;
		if(list != NULL && lenClientes > 0)
		{
			for(i = 0;i<lenClientes;i++)
			{
			list[i].isEmpty = TRUE;
			list[i].cantidadAvisos = -1;

			}
			retorno = 0;
		}
		return retorno;
}
int clienteAuxiliar_calculateNumAvisos(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos, ClienteAuxiliar* listAuxiliar)
{
	int retorno = -1;
	int i;
	int index;
	int bufferCantAvisos;
	if(listAvisos != NULL &&
		   lenAvisos > 0 &&
		   listClientes != NULL &&
		   lenClientes > 0)
	{
		for (i = 0;i < lenClientes;i++)
		{
			if(listClientes[i].isEmpty == FALSE)
			{
				bufferCantAvisos = informe_calculateNumAvisosOneCliente(listAvisos, lenAvisos, listClientes[i].idCliente);
				clienteAuxiliar_searchFreeIndex(listAuxiliar, &index, lenClientes);
				listAuxiliar[index].idCliente = listClientes[i].idCliente;
				listAuxiliar[index].cantidadAvisos = bufferCantAvisos;
				listAuxiliar[index].isEmpty = FALSE;

			}
		}
	}
	return retorno;
}
/** \brief search the first free index on an array of avisos
*
* \param list Aviso*
* \param int pIndex* is a pointer that saves the first space available to save an aviso.
* \param lenAvisos int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (0) if Ok
*
*/
static int clienteAuxiliar_searchFreeIndex(ClienteAuxiliar* list,int* pIndex, int lenClientes)
{
	int retorno = -1;
		int i;
			if(list != NULL && lenClientes > 0)
			{
				for(i = 0;i<lenClientes;i++)
				{
					if(list[i].isEmpty == TRUE)
					{
						*pIndex = i;
						retorno = 0;
						break;
					}
				}
			}
		return retorno;
}
/** \brief search the first free index on an array of avisos
*
* \param list Aviso*
* \param int pIndex* is a pointer that saves the first space available to save an aviso.
* \param lenAvisos int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (0) if Ok
*
*/
static int clienteAuxiliar_sortByCantAvisos(ClienteAuxiliar* list, int lenClientes, int order)
{
	int retorno = -1;
		int flagSwap;
		int i;
		ClienteAuxiliar buffer;
		if(list != NULL && lenClientes >=0)
		{
			do
			{
				flagSwap=0;
				for(i=0; i<lenClientes-1;i++)
				{

					if(((order == DOWN && (list[i].cantidadAvisos > list[i+1].cantidadAvisos)))
							||
							(order == UP && (list[i].cantidadAvisos < list[i+1].cantidadAvisos)))
					{
						flagSwap=1;
						buffer = list[i];
						list[i] = list[i+1];
						list[i+1] = buffer;
					}

				}
			}
			while(flagSwap);
			retorno = 0;
		}

		return retorno;
}
int informe_calculateRubroMasAvisos(Aviso* avisos, int lenAvisos)
{
	int retorno = -1;
	int arrayRubros[30];
	int i;
	int j = 0;
	int cantidadAvisosRubro;
	int cantidadAvisosMayorRubro;
	int banderaPrimero = TRUE;
	int rubroMayorAvisos;
	utn_initIntArray(arrayRubros, 30, 100);

	if(avisos != NULL && lenAvisos > 0)
	{
		for (i = 0; i < lenAvisos;i++)
		{
			if(avisos[i].isEmpty == FALSE && utn_isInArrayInt(arrayRubros, 30, avisos[i].rubro) == 0)
			{
				arrayRubros[j] = avisos[i].rubro;
				j++;
			}
		}
		for (i = 0; i<j;i++)
		{
			cantidadAvisosRubro = informe_calculateNumAvisosOneRubro(avisos, lenAvisos, arrayRubros[i]);
			if(banderaPrimero == TRUE)
			{
				rubroMayorAvisos = arrayRubros[i];
				cantidadAvisosMayorRubro = cantidadAvisosRubro;
			}
			else
			{
				if(cantidadAvisosRubro > cantidadAvisosMayorRubro)
				{

				}
			}

		}
	}

	return retorno;
}
int informe_calculateNumAvisosOneRubro(Aviso* listAvisos, int lenAvisos, int rubro)
{
	int retorno = -1;
	int cantidadAvisos = 0;
	int i;
	if(listAvisos != NULL && lenAvisos > 0 && rubro >= RUBRO_MIN && rubro <= RUBRO_MAX)
	{
		for (i = 0; i < lenAvisos;i++)
			{
				if(listAvisos[i].isEmpty == FALSE && listAvisos[i].rubro == rubro)
				{
					cantidadAvisos++;
				}
			}
		retorno = cantidadAvisos;
	}
	return retorno;
}

