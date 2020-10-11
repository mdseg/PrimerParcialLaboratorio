/*
 * Informe.h
 *
 *  Created on: 11 oct. 2020
 *      Author: marcos
 */

#ifndef INFORME_H_
#define INFORME_H_

#define PRINT_ONE_CLIENTE_ADD_AVISO "ID: %d - Nombre: %s - Apellido: %s - CUIT: %s - Cantidad de avisos contratados: %d\n"
#define ENTERING_CLIENTE_LIST "Ingresando al listado de todos los clientes.\n"
#define PRINT_COUNT_AVISOS_PAUSADOS "La cantidad de avisos pausados es de: %d\n"
int informe_calculateNumAvisosOneCliente(Aviso* listAvisos, int lenAvisos, int idCliente);
int informe_printAllClientes(Cliente* listClientes, int lenClientes, Aviso* listAvisos, int lenAvisos);
int informe_countAvisosPausados(Aviso* listAvisos, int lenAvisos);
int informe_printCountAvisosPausados(Aviso* listAvisos, int lenAvisos);

#endif /* INFORME_H_ */
