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



/** \brief returns the sum of Avisos related an one Client
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \param int idCliente its the ID from the Client
* \return int Return (-1) if Error [Invalid length or NULL pointer] - The sum if Ok
*
*/
int informe_calculateNumAvisosOneCliente(Aviso* listAvisos, int lenAvisos, int idCliente)
{
	int retorno = -1;
	int cantidadAvisos = 0;
	int i;
	if(listAvisos != NULL && lenAvisos > 0 && idCliente > 0)
	{
		for (i = 0; i < lenAvisos;i++)
			{
				if(listAvisos[i].isEmpty == FALSE && listAvisos[i].isActive == TRUE && listAvisos[i].idCliente == idCliente)
				{
					cantidadAvisos++;
				}
			}
		retorno = cantidadAvisos;
	}
	return retorno;
}
/** \brief prints calculate the sum of Avisos related an one Client
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \param int idCliente its the ID from the Client
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
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
/** \brief prints calculate the sum of Avisos with isActive value setted "FALSE" in an Aviso list
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \return int Return (-1) if Error [Invalid length or NULL pointer] - The Sum if Ok
*
*/
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
/** \brief prints the sum of Avisos with isActive value setted "FALSE" in an Aviso list calling a static function
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int informe_printCountAvisosPausados(Aviso* listAvisos, int lenAvisos)
{
	int retorno = -1;
	int cantidadPausados;
	cantidadPausados = informe_countAvisosPausados(listAvisos, lenAvisos);
	if (cantidadPausados != -1)
	{
		printf(PRINT_COUNT_AVISOS_PAUSADOS, cantidadPausados);
		retorno = 0;
	}

	return retorno;
}
/** \brief prints the client's information with more Avisos related
* \param Aviso* listAvisos
* \param int lenAvisos
* \param Aviso* listAvisos
* \param int lenAvisos
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
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
		// Inicializar lista auxiliar
		auxiliar_init(listaClientesAvisos, lenClientes);
		// Calcular cantidad de avisos de cada cliente
		auxiliar_calculateNumAvisos(listClientes, lenClientes, listAvisos, lenAvisos, listaClientesAvisos);
		//Ordenar lista
		auxiliar_sortByCantAvisos(listaClientesAvisos, lenClientes, UP);
		printf(HIGH_CLIENTE_TOP);
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
/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array and set a non-range number in idCliente
 * \param list Auxiliar* Pointer to Auxiliar array
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
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
/** \brief recives an Client array and calculates the count of Avisos related to each Cliente
 * position of the array and set a non-range number in idCliente
 * \param Cliente* listClientes
 * \param int lenClientes
 * \param Aviso* listAvisos
 * \param int lenAvisos
 * \param Auxiliar* listAuxiliar this list is used to storage the sum of avisos related to an Client
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
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
/** \brief sort an Auxiliar list ordering by cantidadAvisos
*
* \param Auxiliar* list
* \param int lenClientes
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
/** \brief recibe an int an search it in a Aviso list
*
* \param Auxiliar* list
* \param int lenAvisos
* \param int rubro its the value to search in this function
* \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (the amount of Aviso related to rubro) if Ok
*
*/
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
/** \brief calculate the Rubro with the most aomunt of Avisos using statics functions
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (0) if Ok
*
*/
int informe_findRubroMoreAvisos(Aviso* listAvisos, int lenAvisos)
{
	int retorno = -1;
	int i = 0;
	Auxiliar listaRubros[RUBRO_LEN];
	int maxnumAvisos;
	if(listAvisos != NULL &&
	   lenAvisos > 0
	   )
	{
		auxiliar_init(listaRubros, RUBRO_LEN);
		//Cargar los rubros en la lista auxiliar verificando que no se repitan
		auxiliar_uploadRubros(listaRubros,RUBRO_LEN,listAvisos,lenAvisos);
		//Calcular la cantidad de avisos para cada rubro
		auxiliar_calculateNumAvisosRubro(listAvisos, lenAvisos, listaRubros, RUBRO_LEN);
		//Ordernar de forma descendente
		auxiliar_sortByCantAvisos(listaRubros, RUBRO_LEN, UP);
		//Imprimir los mayores
		maxnumAvisos = listaRubros[0].cantidadAvisos;
		printf(HIGH_AVISOS_TOP);
		while(listaRubros[i].cantidadAvisos == maxnumAvisos)
		{
			printf(HIGH_AVISOS_RUBRO,listaRubros[i].id);
			i++;
		}
		retorno = 0;
	}
	return retorno;
}
/** \brief select distinct the values of rubro present in a Aviso list and storages it in listRubros
* \param Auxiliar* listRubros
* \param int lenRubros
* \param Aviso* listAvisos
* \param int lenAvisos
* \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (0) if Ok
*
*/
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
/** \brief verify if an value is a valid Id in listAuxiliar
* \param Auxiliar* listRubros
* \param int lenRubros
* \param Aviso* listAvisos
* \param int lenAvisos
* \return int Return (0) if No results - (1) if it's present
*/
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
/** \brief returns the sum of Avisos related an one rubro in Auxiliar
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \param Auxiliar* listAuxiliar
* \param int lenAuxiliar
* \param int idCliente its the ID from the Client
* \return int Return (-1) if Error [Invalid length or NULL pointer] - The sum if Ok
*
*/
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

