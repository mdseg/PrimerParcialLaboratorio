/*
 * Informe.h
 *
 *  Created on: 11 oct. 2020
 *      Author: marcos
 */

#ifndef INFORME_H_
#define INFORME_H_

#define UP 1
#define DOWN 0

#define PRINT_ONE_CLIENTE_ADD_AVISO "ID: %d - Nombre: %s - Apellido: %s - CUIT: %s - Cantidad de avisos contratados: %d\n"
#define ENTERING_CLIENTE_LIST "Ingresando al listado de todos los clientes.\n"
#define PRINT_COUNT_AVISOS_PAUSADOS "La cantidad de avisos pausados es de: %d\n"
#define HIGH_AVISOS_RUBRO "Rubro: %d\n"
#define HIGH_AVISOS_TOP "----------Listado de Rubros con la mayor cantidad de avisos--------------\n"
#define HIGH_CLIENTE_TOP "----------Listado de Clientes con la mayor cantidad de avisos--------------\n"

int informe_calculateNumAvisosOneCliente(Aviso* listAvisos, int lenAvisos, int idCliente);
int informe_calculateNumAvisosOneRubro(Aviso* listAvisos, int lenAvisos, int rubro);
int informe_printAllClientes(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos);
int informe_countAvisosPausados(Aviso* listAvisos, int lenAvisos);
int informe_printCountAvisosPausados(Aviso* listAvisos, int lenAvisos);
int informe_findClienteMoreAvisos(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos);
int informe_calculateRubroMasAvisos(Aviso* avisos, int lenAvisos);
int informe_findRubroMoreAvisos(Aviso* listAvisos, int lenAvisos);
typedef struct
{
	int id;
	int cantidadAvisos;
	int isEmpty;
} Auxiliar;


#endif /* INFORME_H_ */
