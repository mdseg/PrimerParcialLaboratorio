#include "Aviso.h"

#include "utn.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int generateNewId(void);
static int aviso_removeAviso(Aviso* list, int lenAvisos, int id);
static int aviso_searchFreeIndex(Aviso* list,int* pIndex, int lenAvisos);

/** \brief call the statics functions to remove an aviso
* \param list Aviso*
* \param lenAvisos int
* \param flagFirstAviso int it's a pointer that indicates if a new avisod has been created.
* \return int Return (-1) if Error - (0) if Ok
*/
int aviso_unsuscribeAviso(Aviso* list, int lenAvisos)
{
	int retorno = -1;
	int scanId;
	printf(ENTERING_REMOVE_AVISO);
	if(aviso_checkActiveAvisos(list, lenAvisos) == 0)
	{
		if(utn_getInt(&scanId, INPUT_IDAVISO, ERROR_GENERIC, ID_MIN, ID_MAX, ATTEMPTS) == 0 &&
				aviso_removeAviso(list, QTY_AVISOS, scanId) == 0)
		{
			printf(DELETE_AVISO_SUCCESS);
			retorno = 0;
		}
		else
		{
			printf(DELETE_AVISO_ERROR);
		}
	}
	else
	{
		printf(ERROR_NOT_AVAILABLE);
	}

	return retorno;
}
/** \brief show a menu to change Aviso rubro, contenido or idCliente
* \param listAviso Aviso* list of Aviso
* \param len int len of the Aviso* list
* \return int Return (-1) if Error - (0) if Ok
*/
int aviso_modifyAviso(Aviso* listAviso, int lenAvisos, Cliente* listClientes, int lenClientes)
{
	int retorno = -1;
	int id;
	int op;
	int index;
	int flagCarga = FALSE;
	int bufferRubro;
	char bufferContenido[LONG_AVISO];
	int bufferIdCliente;
	Aviso bufferAviso;


	if(utn_getInt(&id, INPUT_IDAVISO, ERROR_GENERIC, ID_MIN, ID_MAX, 2) == 0)
	{
		index = aviso_findAvisoById(listAviso, QTY_AVISOS, id);

		if(index != -1)
		{
			bufferAviso = listAviso[index];
			do
			{
				utn_getInt(&op, MENU_MODIFY_AVISO, MENU_SELECT_ERROR, 1, 5, ATTEMPTS);
				switch (op)
				{
					case 1:
						if(utn_getInt(&bufferRubro, INPUT_IDAVISO, ERROR_GENERIC, ID_MIN, ID_MAX, ATTEMPTS) == 0)
						{
							bufferAviso.rubro = bufferRubro;
							flagCarga = TRUE;
							printf(MODIFY_RUBRO_SUCCESS);
						}
						else
						{
							printf(MODIFY_RUBRO_ERROR);
						}
						break;
					case 2:
						if(utn_getString(INPUT_CONTENIDO,ERROR_GENERIC,bufferContenido, ATTEMPTS, LONG_NAME) == 0)
						{
							strcpy(bufferAviso.contenido,bufferContenido);
							flagCarga = TRUE;
							printf(MODIFY_CONTENIDO_SUCCESS);
						}
						else
						{
							printf(MODIFY_CONTENIDO_ERROR);
						}
						break;
					case 3:
						if(utn_getInt(&bufferIdCliente, INPUT_IDCLIENTE, ERROR_GENERIC, ID_MIN, ID_MAX, ATTEMPTS) == 0 && cliente_findClienteById(listClientes, lenClientes, bufferIdCliente) != 1)
						{
							bufferAviso.idCliente = bufferIdCliente;
							flagCarga = TRUE;
							printf(MODIFY_IDAVISO_SUCCESS);
						}
						else
						{
							printf(MODIFY_IDAVISO_ERROR);
						}
						break;
				}
			}
			while(op != 4);
			if(flagCarga == TRUE)
			{
				listAviso[index] = bufferAviso;
				retorno = 0;
			}
		}
	}

	return retorno;
}
/** \brief creates a new registry of Aviso type
* \param list Aviso*
* \param lenAvisos int len of the Aviso* list
* \return int Return (-1) if Error - (0) if Ok
*/
int aviso_createAviso(Aviso* listAvisos, int lenAvisos, Cliente* listClientes, int lenClientes)
{
	int retorno = -1;
	int id;
	int rubro;
	char contenido[LONG_AVISO];
	int idCliente;
	int index;
	if(aviso_searchFreeIndex(listAvisos, &index, lenAvisos) == 0 &&
		cliente_printClientes(listClientes, lenClientes) == 0 &&
		utn_getInt(&idCliente, INPUT_IDCLIENTE, ERROR_GENERIC, ID_MIN, ID_MAX, ATTEMPTS) == 0 &&
		cliente_findClienteById(listClientes, lenClientes, idCliente) != -1
		)
	{
		if(utn_getInt(&rubro, INPUT_RUBRO, ERROR_GENERIC, RUBRO_MIN, RUBRO_MAX, ATTEMPTS) == 0 &&
			utn_getString(INPUT_CONTENIDO, ERROR_GENERIC, contenido, ATTEMPTS, LONG_NAME) == 0 )
		{
			id = generateNewId();
			listAvisos[index].idAviso=id;
			listAvisos[index].isEmpty = FALSE;
			listAvisos[index].isActive = TRUE;
			listAvisos[index].rubro = rubro;
			listAvisos[index].idCliente = idCliente;
			strcpy(listAvisos[index].contenido,contenido);
			printf(CREATE_AVISO_SUCCESS,listAvisos[index].idAviso);
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Aviso* Pointer to array of avisos
 * \param lenAvisos int Array lenAvisosgth
 * \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (0) if Ok
 *
 */
int aviso_initAvisos(Aviso* list, int lenAvisos)
{
	int retorno = -1;
	int i;
		if(list != NULL && lenAvisos > 0)
		{
			for(i = 0;i<lenAvisos;i++)
			{
			list[i].isActive = FALSE;
			list[i].isEmpty = TRUE;
			}
			retorno = 0;
		}
		return retorno;
}
/** \brief verify if is almost one active aviso in a array of avisos. This function is used
 *  to check if there are records to modify, delete, or make an aviso report
* \param list Aviso*
* \param lenAvisos int
* \return int Return (-1) if Error - (0) if Ok
*/
int aviso_checkActiveAvisos(Aviso* list, int lenAvisos)
{
	int retorno = -1;
	int i;
	if(list != NULL && lenAvisos > 0)
	{
		for(i = 0;i<lenAvisos;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/** \brief find an Aviso by Id en returns the index position in array.
 *
 * \param list Aviso*
 * \param lenAvisos int
 * \param id int
 * \return Return aviso index position or (-1) if [Invalid lenAvisosgth or NULL
pointer received or aviso not found]
 *
 */
int aviso_findAvisoById(Aviso* list, int lenAvisos,int id)
{
	int i = 0;
	int retorno = -1;
		if(list != NULL && lenAvisos > 0 && id > 0)
		{
			for ( i = 0; i < lenAvisos; i++)
			{
				if(list[i].idAviso == id)
				{
					retorno = i;
				}
			}
		}
	return retorno;
}
/** \brief Remove a Aviso by Id (put isEmpty Flag in 1)
 *
 * \param list Aviso*
 * \param lenAvisos int
 * \param id int
 * \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer or if can't
find a aviso] - (0) if Ok
 *
 */
static int aviso_removeAviso(Aviso* list, int lenAvisos, int id)
{
	int retorno = -1;
	int bufferIndex = aviso_findAvisoById(list, lenAvisos, id);
	if( list != NULL && lenAvisos > 0 &&
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
/** \brief search the first free index on an array of avisos
*
* \param list Aviso*
* \param int pIndex* is a pointer that saves the first space available to save an aviso.
* \param lenAvisos int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (0) if Ok
*
*/
static int aviso_searchFreeIndex(Aviso* list,int* pIndex, int lenAvisos)
{
	int retorno = -1;
		int i;
			if(list != NULL && lenAvisos > 0)
			{
				for(i = 0;i<lenAvisos;i++)
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
//Order TRUE activar FALSE desactivar
/** \brief change the status of Aviso element
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \param Cliente* listClientes
* \param int lenClientes
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (0) if Ok
*
*/
int aviso_changeStatus(Aviso* listAvisos, int lenAvisos, Cliente* listClientes, int lenClientes, int id, int order)
{
	int retorno = -1;
	int bufferIndex = aviso_findAvisoById(listAvisos, lenAvisos, id);
	int idCliente;
	int op;
	if( listAvisos != NULL && lenAvisos > 0 &&
		id > 0 && bufferIndex != -1
		&& listAvisos[bufferIndex].isEmpty == FALSE)
	{
		if(order == PAUSAR && listAvisos[bufferIndex].isActive == FALSE)
		{
			printf(CHANGE_AVISO_ALREADY_PAUSED);
		}
		else if(order == RENAUDAR && listAvisos[bufferIndex].isActive == TRUE)
		{
			printf(CHANGE_AVISO_ALREADY_ACTIVED);
		}
		else
		{
			idCliente = listAvisos[bufferIndex].idCliente;
			printf(CHANGE_AVISO_CLIENTE);
			cliente_printOneCliente(listClientes, lenClientes, idCliente);

			if(utn_getInt(&op, CONFIRM_CHANGE_STATUS, ERROR_GENERIC, 1, 2, ATTEMPTS) == 0)
			{
				if(op == 1)
				{
					if(order == PAUSAR)
					{
						listAvisos[bufferIndex].isActive = FALSE;
						retorno = 0;
						printf(PAUSE_AVISO_SUCCESS,listAvisos[bufferIndex].idAviso);
					}
					else
					{
						listAvisos[bufferIndex].isActive = TRUE;
						retorno = 0;
						printf(RESUME_AVISO_SUCCESS,listAvisos[bufferIndex].idAviso);
					}
				}
				else
				{
					printf(CHANGE_USER_ABORT);
				}
			}
		}
	}
	else
	{
		printf(CHANGE_AVISO_ERROR);
	}

	return retorno;
}
/** \brief create a Aviso registry directly
*
* \param int idAviso
* \param int rubro
* \param char* contenido
* \param int isActive
* \param Aviso* list
* \param int lenAviso
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int aviso_altaForzada(int rubro, char* contenido, int isActive, int idCliente, Aviso* list, int lenAviso)
{
	int retorno = -1;
	int index;
	if(rubro >= RUBRO_MIN && rubro <= RUBRO_MAX && contenido != NULL &&
			(isActive == (TRUE || FALSE)) && idCliente > 0 && list != NULL && lenAviso > 0)
	{
		if(aviso_searchFreeIndex(list, &index, lenAviso) == 0)
		{
			Aviso aviso;
			aviso.idAviso= generateNewId();
			aviso.rubro = rubro;
			strcpy(aviso.contenido,contenido);
			aviso.isActive = isActive;
			aviso.idCliente = idCliente;
			aviso.isEmpty = FALSE;
			list[index] = aviso;
			retorno = 0;
		}
	}

	return retorno;
}
/** \brief prints All avisos related with an idCliente
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \param int idCliente its the ID from the Client
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int aviso_printAvisosByIdCliente(Aviso* listAvisos, int lenAvisos, int idCliente)
{
	int retorno = -1;
	int i;
	int cantidadAvisosImpresos = 0;
	char bufferEstado[LONG_NAME];
	if(listAvisos != NULL && lenAvisos > 0)
	{
		printf(PRINT_REGISTRY_BY_ID_TOP,idCliente);
		for (i = 0; i < lenAvisos;i++)
			{
				if(listAvisos[i].isEmpty == FALSE && listAvisos[i].idCliente == idCliente)
				{
					if(listAvisos[i].isActive == TRUE)
					{
						strcpy(bufferEstado,"Activa");
					}
					else
					{
						strcpy(bufferEstado,"Pausada");
					}
					printf(PRINT_ONE_REGISTRY_BY_ID,listAvisos[i].idAviso, listAvisos[i].contenido,bufferEstado);
					cantidadAvisosImpresos++;
				}
			}
		if (cantidadAvisosImpresos == 0)
		{
			printf(PRINT_REGISTRY_NO_RESULTS);
		}
		retorno = 0;
	}

	return retorno;
}
/** \brief delete All avisos related with an idCliente
*
* \param Aviso* listAvisos
* \param int lenAvisos
* \param int idCliente its the ID from the Client
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int aviso_deleteAllAvisosByIdCliente(Aviso* listAvisos, int lenAvisos, int idCliente)
{
	int retorno = -1;
	int i;
	int cantidadAvisosBorrados = 0;
	if(listAvisos != NULL && lenAvisos > 0 && idCliente > 0)
		{
			for (i = 0; i < lenAvisos;i++)
				{
					if(listAvisos[i].isEmpty == FALSE && listAvisos[i].idCliente == idCliente)
					{
						listAvisos[i].isEmpty = TRUE;
						cantidadAvisosBorrados++;
					}
				}
			if (cantidadAvisosBorrados == 0)
			{
				printf(DELETE_REGISTRY_NO_RESULTS);
			}
			else
			{
				printf(DELETE_REGISTRY_RESULTS,cantidadAvisosBorrados);
			}
			retorno = 0;
		}
	return retorno;
}

