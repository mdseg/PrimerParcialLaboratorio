#include "Aviso.h"

#include "utn.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int generateNewId(void);
static int aviso_removeAviso(Aviso* list, int lenAvisos, int id);
int aviso_printAvisos(Aviso* list, int lenAvisosgth);
static int aviso_sortAvisos(Aviso* list, int lenAvisos, int order);
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
int aviso_modifyAviso(Aviso* listAviso, int lenAvisos, Cliente* listClientes, int lenClientes)
{
	int retorno = -1;
	int id;
	int op;
	int index;
	int flagCarga = FALSE;
	int bufferRubro;
	char bufferContenido[LONG_CONTENIDO];
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
						if(utn_getInt(&bufferIdCliente, INPUT_IDCLIENTE, ERROR_GENERIC, ID_MIN, ID_MAX, ATTEMPTS) == 0 && cliente_findClienteById(listClientes, lenClientes, bufferIdCliente))
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

int aviso_createAviso(Aviso* list, int lenAvisos)
{
	int retorno = -1;
	int id;
	char nombre[LONG_NAME];
	char apellido[LONG_NAME];
	char cuit[LONG_NAME];
	int index;
	if(aviso_searchFreeIndex(list, &index, lenAvisos) == 0 &&
		utn_getName(INPUT_NAME,ERROR_GENERIC,nombre, ATTEMPTS, LONG_NAME) == 0 &&
		utn_getName(INPUT_APELLIDO,ERROR_GENERIC,apellido, ATTEMPTS, LONG_NAME) == 0 &&
		utn_getCuit(INPUT_CUIT, ERROR_GENERIC, cuit, ATTEMPTS, LONG_NAME) == 0
		)
	{
		id = generateNewId();
		list[index].idAviso=id;

	    list[index].isEmpty = FALSE;
	    printf(CREATE_AVISO_SUCCESS,list[index].idAviso);
		retorno = 0;
	}
	return retorno;
}
/** \brief print the content of avisos array
 *
 * \param list Aviso*
 * \param lenAvisosgth int
 * \return retorno
 *
 */
int aviso_printAvisos(Aviso* list, int lenAvisosgth)
{
	int retorno = -1;
	int i;
	int flagResults = FALSE;
	if (list != NULL && lenAvisosgth > 0)
	{
		for(i = 0; i < lenAvisosgth; i++)
		{
			if(list[i].isEmpty == 0)
			{
				if(flagResults == FALSE)
				{
					flagResults = TRUE;
					retorno = 0;
				}
				//printf(PRINT_ONE_REGISTRY,list[i].idAviso,list[i].nombre,list[i].apellido,list[i].cuit);

			}
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
			list[i].idAviso = -1;
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
/** \brief Sort the elements in the array of avisos, the argument order
indicate UP or DOWN order
*
* \param list Aviso*
* \param lenAvisos int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid lenAvisosgth or NULL pointer] - (0) if Ok
*
*/
static int aviso_sortAvisos(Aviso* list, int lenAvisos, int order)
{
	int retorno = -1;
	int flagSwap;
	int i;
	//Aviso buffer;
	if(list != NULL && lenAvisos >=0)
	{
		do
		{
			flagSwap=0;
			for(i=0; i<lenAvisos-1;i++)
			{
				/*
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
				*/
			}
		}
		while(flagSwap);
		retorno = 0;
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
/** \brief call the statics functions to create an report of avisos
*
* \param list Aviso*
* \param lenAvisos int
* \param flagFirstAviso int it's a pointer that indicates if a new avisod has been created.
* * \return int Return (-1) if Error - (0) if Ok
*/
int aviso_createAvisoReport(Aviso* list, int lenAvisos)
{
	int retorno = -1;
	int op;
	int orden;
	if(aviso_checkActiveAvisos(list, lenAvisos) == 0)
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
							aviso_sortAvisos(list, QTY_AVISOS, UP);
						}
						else
						{
							aviso_sortAvisos(list, QTY_AVISOS, DOWN);
						}
						aviso_printAvisos(list, QTY_AVISOS);
						printf(REPORT_AVISO_SUCCESS_FINISH);
					}
					else
					{
						printf(REPORT_AVISO_ERROR);
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

