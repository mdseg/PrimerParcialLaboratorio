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

static int auxiliar_searchFreeIndex(Auxiliar* list,int* pIndex, int lenClientes);
static int auxiliar_init(Auxiliar* list, int lenClientes);
static int auxiliar_calculateNumAvisos(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos, Auxiliar* listAuxiliar);
static int auxiliar_sortByCantAvisos(Auxiliar* list, int lenClientes, int order);
static int auxiliar_isInArray(Auxiliar* listAuxiliar, int lenAuxiliar, int inputInt);
static int auxiliar_uploadRubros(Auxiliar* listRubros, int lenRubros , Aviso* listAvisos, int lenAvisos);
static int auxiliar_calculateNumAvisosRubro(Aviso* listAvisos, int lenAvisos, Auxiliar* listAuxiliar, int lenAuxiliar);
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
	Auxiliar listaClientesAvisos[QTY_CLIENTES];
	int maxnumAvisos;
	if(listAvisos != NULL &&
	   lenAvisos > 0 &&
	   listClientes != NULL &&
	   lenClientes > 0)
	{
		auxiliar_init(listaClientesAvisos, lenClientes);
		auxiliar_calculateNumAvisos(listClientes, lenClientes, listAvisos, lenAvisos, listaClientesAvisos);
		auxiliar_sortByCantAvisos(listaClientesAvisos, lenClientes, UP);
		maxnumAvisos = listaClientesAvisos[0].cantidadAvisos;
		while(listaClientesAvisos[i].cantidadAvisos == maxnumAvisos)
		{
			index = cliente_findClienteById(listClientes, lenClientes, listaClientesAvisos[i].id);
			clienteMayorAvisos = listClientes[index];
			printf(PRINT_ONE_CLIENTE_ADD_AVISO,clienteMayorAvisos.idCliente,clienteMayorAvisos.nombre,clienteMayorAvisos.apellido,clienteMayorAvisos.cuit,informe_calculateNumAvisosOneCliente(listAvisos, lenAvisos, clienteMayorAvisos.idCliente));
			i++;
		}

		retorno = 0;
	}
	return retorno;
}
int auxiliar_init(Auxiliar* list, int lenClientes)
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
int auxiliar_calculateNumAvisos(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos, Auxiliar* listAuxiliar)
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
				auxiliar_searchFreeIndex(listAuxiliar, &index, lenClientes);
				listAuxiliar[index].id = listClientes[i].idCliente;
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
static int auxiliar_searchFreeIndex(Auxiliar* list,int* pIndex, int lenClientes)
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
static int auxiliar_sortByCantAvisos(Auxiliar* list, int lenClientes, int order)
{
	int retorno = -1;
		int flagSwap;
		int i;
		Auxiliar buffer;
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
int informe_findRubroMoreAvisos(Aviso* listAvisos, int lenAvisos)
{
	int retorno = -1;
	int i = 0;
	Auxiliar listaRubros[50];
	int maxnumAvisos;
	if(listAvisos != NULL &&
	   lenAvisos > 0
	   )
	{
		auxiliar_init(listaRubros, 50);
		//Cargar los rubros en la lista auxiliar verificando que no se repitan
		auxiliar_uploadRubros(listaRubros,50,listAvisos,lenAvisos);
		//Calcular la cantidad de avisos para cada rubro
		auxiliar_calculateNumAvisosRubro(listAvisos, lenAvisos, listaRubros, 50);
		//Ordernar de forma descendente
		auxiliar_sortByCantAvisos(listaRubros, 50, UP);
		//Imprimir los mayores
		maxnumAvisos = listaRubros[0].cantidadAvisos;
		printf("----------Listado de Rubros con mayores cantidad de avisos--------------\n");
				while(listaRubros[i].cantidadAvisos == maxnumAvisos)
				{
					printf(HIGH_AVISOS_RUBRO,listaRubros[i].id);
					i++;
				}
		retorno = 0;
	}
	return retorno;
}
static int auxiliar_uploadRubros(Auxiliar* listRubros, int lenRubros , Aviso* listAvisos, int lenAvisos)
{
	int retorno = -1;
	int i;
	int j = 0;
	if(listRubros != NULL &&
		lenRubros > 0 &&
	    listAvisos != NULL &&
		lenAvisos > 0)
	{
		for(i = 0;i < lenAvisos;i++)
		{
			if(listAvisos[i].isEmpty == 0 && auxiliar_isInArray(listRubros,lenRubros,listAvisos[i].rubro) == 0)
			{
				listRubros[j].id = listAvisos[i].rubro;
				listRubros[j].isEmpty = FALSE;
				j++;
			}
		}
	}
	return retorno;
}
static int auxiliar_isInArray(Auxiliar* listAuxiliar, int lenAuxiliar, int inputInt)
{
	int retorno = 0;
	int i;
	if (listAuxiliar != NULL &&
		lenAuxiliar > 0)
	{
		for(i = 0; i < lenAuxiliar; i++)
		{
			if(listAuxiliar[i].isEmpty == FALSE && listAuxiliar[i].id == inputInt)
			{
				retorno = 1;
				break;
			}
		}
	}
	return retorno;
}
static int auxiliar_calculateNumAvisosRubro(Aviso* listAvisos, int lenAvisos, Auxiliar* listAuxiliar, int lenAuxiliar)
{
	int retorno = -1;
	int i;
	int bufferCantAvisos;
	if(listAvisos != NULL &&
		   lenAvisos > 0
		)
	{
		for (i = 0;i < lenAuxiliar;i++)
		{
			if(listAuxiliar[i].isEmpty == FALSE)
			{
				bufferCantAvisos = informe_calculateNumAvisosOneRubro(listAvisos, lenAvisos, listAuxiliar[i].id);
				listAuxiliar[i].cantidadAvisos = bufferCantAvisos;

			}
		}
	}
	return retorno;
}
