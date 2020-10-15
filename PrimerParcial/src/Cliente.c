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
static int cliente_searchFreeIndex(Cliente* list,int* pIndex, int len);
static int cliente_isRepeatCuit(Cliente* list, int len, char* cuit);

/** \brief call the statics functions to remove an cliente
* \param list Cliente*
* \param len int
* \param idCliente id from the client to be erased
* \return int Return (-1) if Error - (0) if Ok
*/
int cliente_unsuscribeCliente(Cliente* list, int len, int idCliente)
{
	int retorno = -1;
	if(cliente_checkActiveClientes(list, len) == 0)
	{
		cliente_removeCliente(list, QTY_CLIENTES, idCliente);
		printf(DELETE_CLIENTE_SUCCESS);
		retorno = 0;
	}
	else
	{
		printf(DELETE_CLIENTE_ERROR);
	}
	return retorno;
}

/** \brief show a menu to change Cliente nombre, apellido or CUIT
* \param list Cliente*
* \param len int lenght of the Cliente* list
* \return int Return (-1) if Error - (0) if Ok
*/
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
	cliente_printClientes(list, len);

	if(utn_getInt(&id, INPUT_ID, ERROR_GENERIC, 1, 1000, 2) == 0)
	{
		index = cliente_findClienteById(list, len, id);

		if(index != -1)
		{
			bufferCliente = list[index];
			do
			{
				utn_getInt(&op, MENU_MODIFY, MENU_SELECT_ERROR, 1, 5, ATTEMPTS);
				switch (op)
				{
					case 1:
						if(utn_getName(INPUT_NAME,ERROR_NAME,bufferNombre, ATTEMPTS, LONG_NAME) == 0)
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
						if(utn_getName(INPUT_APELLIDO,ERROR_APELLIDO,bufferApellido, ATTEMPTS, LONG_NAME) == 0)
						{
							utn_upperFirstCharArray(bufferApellido);
							strcpy(bufferCliente.apellido,bufferApellido);
							flagCarga = TRUE;
							printf(MODIFY_APELLIDO_SUCCESS);
						}
						else
						{
							printf(MODIFY_NAME_ERROR);
						}
						break;
					case 3:
						if(utn_getCuit(INPUT_CUIT, ERROR_CUIT, bufferCuit, ATTEMPTS, LONG_NAME) == 0)
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
				printf(MODIFY_CLIENTE_SUCCESS);
				retorno = 0;
			}
		}
	}

	return retorno;
}
/** \brief creates a new registry of Cliente type
* \param list Cliente*
* \param len int len of the Cliente* list
* \return int Return (-1) if Error - (0) if Ok
*/
int cliente_createCliente(Cliente* list, int len)
{
	int retorno = -1;
	int id;
	char nombre[LONG_NAME];
	char apellido[LONG_NAME];
	char cuit[LONG_NAME];
	int index;
	if(cliente_searchFreeIndex(list, &index, len) == 0 &&
		utn_getName(INPUT_NAME,ERROR_NAME,nombre, ATTEMPTS, LONG_NAME) == 0 &&
		utn_getName(INPUT_APELLIDO,ERROR_APELLIDO,apellido, ATTEMPTS, LONG_NAME) == 0 &&
		utn_getCuit(INPUT_CUIT, ERROR_CUIT, cuit, ATTEMPTS, LONG_NAME) == 0

		)
	{
		if(cliente_isRepeatCuit(list, len, cuit) == 0)
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
		else
		{
			printf(CREATE_CLIENTE_CUIT_ERROR);
		}

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
		printf(PRINT_ONE_REGISTRY_TOP);
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
		printf(PRINT_ONE_REGISTRY_BOTTOM);
	}
 return retorno;
}
/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array and set a non-range number in idCliente
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
					break;
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
	static int id= 0;
	id = id+1;
	return id;
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
/** \brief create a Client registry directly
*
* \param idCLiente int
* \param nombre char*
* \param apellido char*
* \param cuit char*
* \param list Cliente*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int cliente_altaForzada(char* nombre, char* apellido, char* cuit,Cliente* list, int len)
{
	int retorno = -1;
	int index;
	if(nombre != NULL && apellido != NULL && cuit != NULL &&
		list != NULL && len > 0)
	{
		if(cliente_searchFreeIndex(list, &index, len) == 0)
		{
			if(cliente_isRepeatCuit(list, len, cuit) == 0)
			{
				Cliente cliente;
				cliente.idCliente = generateNewId();
				strcpy(cliente.nombre,nombre);
				strcpy(cliente.apellido,apellido);
				strcpy(cliente.cuit,cuit);
				list[index] = cliente;
			}
			else
			{
				printf(CREATE_CLIENTE_CUIT_ERROR);
			}

		}
	}

	return retorno;
}
/** \brief search the first free index on an array of clientes
*
* \param list Cliente*
* \param len int
* \param id int id from client
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int cliente_printOneCliente(Cliente* list, int len, int id)
{
	int retorno = -1;
	Cliente clienteEncontrado;
	int indexCliente;
	indexCliente = cliente_findClienteById(list, len, id);
	if(indexCliente != -1)
	{
		clienteEncontrado = list[indexCliente];
		printf(PRINT_ONE_REGISTRY,clienteEncontrado.idCliente,clienteEncontrado.nombre,clienteEncontrado.apellido,clienteEncontrado.cuit);
	}
	return retorno;
}
/** \brief veirfy if a char array is present in a list
*
* \param list Cliente*
* \param len int
* \param cuit char input cuit
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if no Results (1) if is present
*
*/
static int cliente_isRepeatCuit(Cliente* list, int len, char* cuit)
{
	int retorno = -1;
	int i;
	if( list != NULL && len >0 && cuit != NULL)
	{
		retorno = 0;
		for (i = 0; i < len;i++)
			{
				if(strcmp(list[i].cuit, cuit) == 0)
				{
				retorno = 1;
				break;
				}
			}
	}

	return retorno;
}


