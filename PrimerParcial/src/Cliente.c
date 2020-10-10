/*
 * Cliente.c
 *
 *  Created on: 10 oct. 2020
 *      Author: marcos
 */

#include "Cliente.h"

#include "utn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int generateNewId(void);
static int cliente_removeCliente(Cliente* list, int len, int id);
int cliente_printClientes(Cliente* list, int length);
static int cliente_sortClientes(Cliente* list, int len, int order);
static int cliente_searchFreeIndex(Cliente* list,int* pIndex, int len);
/** \brief call the statics functions to remove an cliente
* \param list Cliente*
* \param len int
* \param flagFirstCliente int it's a pointer that indicates if a new cliented has been created.
* \return int Return (-1) if Error - (0) if Ok
*/
int cliente_unsuscribeCliente(Cliente* list, int len)
{
	int retorno = -1;
	int scanId;
	printf(ENTERING_REMOVE_CLIENTE);
	if(cliente_checkActiveClientes(list, len) == 0)
	{
		if(utn_getInt(&scanId, INPUT_ID, ERROR_GENERIC, ID_MIN, ID_MAX, ATTEMPTS) == 0 &&
				cliente_removeCliente(list, QTY_CLIENTES, scanId) == 0)
		{
			printf(DELETE_CLIENTE_SUCCESS);
			retorno = 0;
		}
		else
		{
			printf(DELETE_CLIENTE_ERROR);
		}
	}
	else
	{
		printf(ERROR_NOT_AVAILABLE);
	}

	return retorno;
}
int cliente_modifyCliente(Cliente* list, int len)
{
	int retorno = -1;
	int id;
	int op;
	int index;
	int flagCarga = FALSE;
	char bufferNombre[LONG_NAME];
	char bufferApellido[LONG_NAME];
	char bufferCuit[LONG_NAME];

	Cliente bufferCliente;


	if(utn_getInt(&id, INPUT_ID, ERROR_GENERIC, ID_MIN, ID_MAX, 2) == 0)
	{
		index = cliente_findClienteById(list, QTY_CLIENTES, id);

		if(index != -1)
		{
			bufferCliente = list[index];
			do
			{
				utn_getInt(&op, MENU_MODIFY, MENU_SELECT_ERROR, 1, 5, ATTEMPTS);
				switch (op)
				{
					case 1:
						if(utn_getName(INPUT_NAME,ERROR_GENERIC,bufferNombre, ATTEMPTS, LONG_NAME) == 0)
						{
							utn_upperFirstCharArray(bufferNombre);
							strcpy(bufferCliente.nombre,bufferNombre);
							flagCarga = TRUE;
							printf(MODIFY_NAME_SUCCESS);
						}
						else
						{
							printf(MODIFY_NAME_ERROR);
						}
						break;
					case 2:
						if(utn_getName(INPUT_APELLIDO,ERROR_GENERIC,bufferApellido, ATTEMPTS, LONG_NAME) == 0)
						{
							utn_upperFirstCharArray(bufferApellido);
							strcpy(bufferCliente.nombre,bufferApellido);
							flagCarga = TRUE;
							printf(MODIFY_NAME_SUCCESS);
						}
						else
						{
							printf(MODIFY_NAME_ERROR);
						}
						break;
					case 3:
						if(utn_getCuit(INPUT_CUIT, ERROR_GENERIC, bufferCuit, ATTEMPTS, LONG_NAME) == 0)
						{
							strcpy(bufferCliente.cuit,bufferCuit);
							flagCarga = TRUE;
							printf(MODIFY_CUIT_SUCCESS);
						}
						else
						{
							printf(MODIFY_CUIT_ERROR);
						}
						break;
				}
			}
			while(op != 4);
			if(flagCarga == TRUE)
			{
				list[index] = bufferCliente;
				retorno = 0;
			}
		}
	}

	return retorno;
}

int cliente_createCliente(Cliente* list, int len)
{
	int retorno = -1;
	int id;
	char nombre[LONG_NAME];
	char apellido[LONG_NAME];
	char cuit[LONG_NAME];
	int index;
	if(cliente_searchFreeIndex(list, &index, len) == 0 &&
		utn_getName(INPUT_NAME,ERROR_GENERIC,nombre, ATTEMPTS, LONG_NAME) == 0 &&
		utn_getName(INPUT_APELLIDO,ERROR_GENERIC,apellido, ATTEMPTS, LONG_NAME) == 0 &&
		utn_getCuit(INPUT_CUIT, ERROR_GENERIC, cuit, ATTEMPTS, LONG_NAME) == 0
		)
	{
		id = generateNewId();
		list[index].idCliente=id;
		utn_upperFirstCharArray(nombre);
		utn_upperFirstCharArray(apellido);
		strcpy(list[index].nombre,nombre);
		strcpy(list[index].apellido,apellido);
		strcpy(list[index].cuit,cuit);
	    list[index].isEmpty = FALSE;
	    printf(CREATE_CLIENTE_SUCCESS,list[index].idCliente);
		retorno = 0;
	}
	return retorno;
}
/** \brief print the content of clientes array
 *
 * \param list Cliente*
 * \param length int
 * \return retorno
 *
 */
int cliente_printClientes(Cliente* list, int length)
{
	int retorno = -1;
	int i;
	int flagResults = FALSE;
	if (list != NULL && length > 0)
	{
		for(i = 0; i < length; i++)
		{
			if(list[i].isEmpty == 0)
			{
				if(flagResults == FALSE)
				{
					flagResults = TRUE;
					retorno = 0;
				}
				printf(PRINT_ONE_REGISTRY,list[i].idCliente,list[i].nombre,list[i].apellido,list[i].cuit);

			}
		}
	}
 return retorno;
}
/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Cliente* Pointer to array of clientes
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int cliente_initClientes(Cliente* list, int len)
{
	int retorno = -1;
	int i;
		if(list != NULL && len > 0)
		{
			for(i = 0;i<len;i++)
			{
			list[i].idCliente = -1;
			list[i].isEmpty = TRUE;
			}
			retorno = 0;
		}
		return retorno;
}
/** \brief verify if is almost one active cliente in a array of clientes. This function is used
 *  to check if there are records to modify, delete, or make an cliente report
* \param list Cliente*
* \param len int
* \return int Return (-1) if Error - (0) if Ok
*/
int cliente_checkActiveClientes(Cliente listaClientes[], int len)
{
	int retorno = -1;
	int i;
	if(listaClientes != NULL && len > 0)
	{
		for(i = 0;i<len;i++)
		{
			if(listaClientes[i].isEmpty == FALSE)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/** \brief find an Cliente by Id en returns the index position in array.
 *
 * \param list Cliente*
 * \param len int
 * \param id int
 * \return Return cliente index position or (-1) if [Invalid length or NULL
pointer received or cliente not found]
 *
 */
int cliente_findClienteById(Cliente* list, int len,int id)
{
	int i = 0;
	int retorno = -1;
		if(list != NULL && len > 0 && id > 0)
		{
			for ( i = 0; i < len; i++)
			{
				if(list[i].idCliente == id)
				{
					retorno = i;
				}
			}
		}
	return retorno;
}
/** \brief Remove a Cliente by Id (put isEmpty Flag in 1)
 *
 * \param list Cliente*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a cliente] - (0) if Ok
 *
 */
static int cliente_removeCliente(Cliente* list, int len, int id)
{
	int retorno = -1;
	int bufferIndex = cliente_findClienteById(list, len, id);
	if( list != NULL && len > 0 &&
		id > 0 && bufferIndex != -1
		&& list[bufferIndex].isEmpty == FALSE)
	{
		list[bufferIndex].isEmpty = TRUE;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief generates a new id for a new user
 * \return id int the current id after it is generated by the function
 */
static int generateNewId(void)
{
	static int id= ID_MIN;
	id = id+1;
	return id;
}
/** \brief Sort the elements in the array of clientes, the argument order
indicate UP or DOWN order
*
* \param list Cliente*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
static int cliente_sortClientes(Cliente* list, int len, int order)
{
	int retorno = -1;
	int flagSwap;
	int i;
	Cliente buffer;
	if(list != NULL && len >=0)
	{
		do
		{
			flagSwap=0;
			for(i=0; i<len-1;i++)
			{
				if((order == UP && (( strncmp(list[i].nombre, list[i+1].nombre,LONG_NAME) > 0) ||
						(strncmp(list[i].nombre, list[i+1].nombre,LONG_NAME) == 0 && list[i].cuit > list[i+1].cuit)))
						||
						(order == DOWN && (( strncmp(list[i].nombre, list[i+1].nombre,LONG_NAME) < 0) ||
						(strncmp(list[i].nombre, list[i+1].nombre,LONG_NAME) == 0 && list[i].cuit < list[i+1].cuit))))
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
/** \brief search the first free index on an array of clientes
*
* \param list Cliente*
* \param int pIndex* is a pointer that saves the first space available to save an cliente.
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
static int cliente_searchFreeIndex(Cliente* list,int* pIndex, int len)
{
	int retorno = -1;
		int i;
			if(list != NULL && len > 0)
			{
				for(i = 0;i<len;i++)
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
/** \brief call the statics functions to create an report of clientes
*
* \param list Cliente*
* \param len int
* \param flagFirstCliente int it's a pointer that indicates if a new cliented has been created.
* * \return int Return (-1) if Error - (0) if Ok
*/
int cliente_createClienteReport(Cliente* list, int len)
{
	int retorno = -1;
	int op;
	int orden;
	if(cliente_checkActiveClientes(list, len) == 0)
	{
		do
		{
			utn_getInt(&op, MENU_REPORT, MENU_SELECT_ERROR, 1, 3, ATTEMPTS);
			switch (op)
			{
				case 1:
					if(utn_getInt(&orden, MENU_ORDER, MENU_SELECT_ERROR, 1, 2, ATTEMPTS) == 0)
					{
						if(orden == 1)
						{
							cliente_sortClientes(list, QTY_CLIENTES, UP);
						}
						else
						{
							cliente_sortClientes(list, QTY_CLIENTES, DOWN);
						}
						cliente_printClientes(list, QTY_CLIENTES);
						printf(REPORT_CLIENTE_SUCCESS_FINISH);
					}
					else
					{
						printf(REPORT_CLIENTE_ERROR);
					}
					break;
				case 2:
					break;
			}
		}
		while(op!= 3);
	}
	else
	{
		printf(ERROR_NOT_AVAILABLE);
	}

	return retorno;
}
int cliente_altaForzada(int idCliente, char* nombre, char* apellido, char* cuit,Cliente* list, int len)
{
	int retorno = -1;
	int index;
if(cliente_searchFreeIndex(list, &index, len) == 0)
{
	Cliente cliente;
	cliente.idCliente = idCliente;
	strcpy(cliente.nombre,nombre);
	strcpy(cliente.apellido,apellido);
	strcpy(cliente.cuit,cuit);
	list[index] = cliente;

}
	return retorno;
}

