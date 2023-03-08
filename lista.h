#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estructura.h"
#include "fecha.h"
#include "archivos.h"

int contarNodos(Nodo *p); // Itera la lista con un entero i y despues devuelve la cantidad de nodos que contiene la misma
void buscarPorProtocoloDicotomica(Nodo *p, int protocolo); // Busca un protocolo atraves de una busqueda dicotomica, muestra todos los campos.
TData* cargarArreglo(Nodo *p); // Pasa la lista a un arreglo
Nodo* crearNodo(Nodo *p, struct TFecha *fecha); // Sirve para crear un nodo con las especificaciones de la plantilla
Nodo* eliminarNodo(Nodo *p, int protocolo); // Sirve para eliminar un nodo a traves del protocolo.
Nodo* agregarNodo(Nodo *p, Nodo *nuevoNodo) ; // Sirve para agregar un nodo al comienzo se utiliza en conjunto con la funcion agregarNdoo
int obtenerUltimoProtocolo(Nodo *p); // Se utiliza para obtener el protocolo del ultimo nodo, para que al agregar siga ordenado.
int calcularMontoPorOS(Nodo *p, int mes, char* nombreOS); //Utiliza una llamada recursiva para recorrer la lista enlazada hasta el final, y luego acumula los montos de las obras sociales que coinciden con los criterios de mes y nombre de la obra social
void mostrarListadoPorMes(Nodo *p, int mes); // Imprime el nombre de la OS y el monto calculado por calcularMontoPorOS para cada informe que corresponda al mes y tenga una OS con el nombre indicado. Ademas acumula el monto total y lo imprime al final de la función.



int num_protocolo = 0;

Nodo* crearNodo(Nodo *p, struct TFecha *fecha){
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria dinamica.\n");
        exit(1);
    }

    int ultimoProtocolo = obtenerUltimoProtocolo(p);

    nuevoNodo->info.protocolo = ultimoProtocolo + 1;



    printf("Ingrese el nombre del paciente:\n");
    getchar(); // Absorbe el carácter de salto de línea del buffer
    fgets(planilla.nombre, sizeof(planilla.nombre), stdin);
    strcpy(nuevoNodo->info.nombre, planilla.nombre); //Copia lo que manda el usuario, al puntero de la lista

    printf("Ingrese el nombre del medico:\n");
    fgets(planilla.medicosolicitado, sizeof(planilla.medicosolicitado), stdin);
    strcpy(nuevoNodo->info.medicosolicitado, planilla.medicosolicitado); //Copia lo que manda el usuario, al puntero de la lista

    printf("Ingrese 1 si tiene OS o 0 si no:\n");
    scanf("%i", &nuevoNodo->info.tieneOS);
    getchar(); // Absorbe el carácter de salto de línea del buffer
    if(nuevoNodo->info.tieneOS < 0 || nuevoNodo->info.tieneOS > 1){ // Se comprueba el OS atraves de un logico
        printf("Ingrese un numero correcto.\n");
        exit(1);
    }

    if(nuevoNodo->info.tieneOS == 1){ // Verdadero
        printf("Ingrese el nombre de la OS:\n");
        fgets(planilla.nombreOS, sizeof(planilla.nombreOS), stdin);
        strcpy(nuevoNodo->info.nombreOS, planilla.nombreOS); //Copia lo que manda el usuario, al puntero de la lista

        printf("Ingrese el monto de la OS:\n");
        scanf("%i", &nuevoNodo->info.montoOS);
        if(nuevoNodo->info.montoOS < 0){
            printf("Ingrese un número correcto.\n");
            exit(1);
        }
    }
    // Si no tiene OS salta directamente a esta linea
    printf("Ingrese el monto del paciente:\n");
    scanf("%i", &nuevoNodo->info.montoPT); //Copia lo que manda el usuario, al puntero de la lista
    if(nuevoNodo->info.montoPT < 0){
        printf("Ingrese un numero correcto.\n");
        exit(1);
    }

    memcpy(&nuevoNodo->info.fecha, fecha, sizeof(struct TFecha)); // Copia la fecha que el usuario ingreso al principio y la inserta en el nodo.
    nuevoNodo->next = NULL;

    return nuevoNodo;
}


int obtenerUltimoProtocolo(Nodo *p) {
    int maxProtocolo = 0;
    Nodo *aux = p;
    while (aux != NULL) {
        if (aux->info.protocolo > maxProtocolo) {
            maxProtocolo = aux->info.protocolo; // Guarda el puntero que esta en la ultima posicion de la lista
        }
        aux = aux->next;
    }
    return maxProtocolo;
}



Nodo* agregarNodo(Nodo *p, Nodo *nuevoNodo) { // Inserta el nodo a la cabeza
    if(p == NULL) {
        p = nuevoNodo;
    } else {
        nuevoNodo->next = p;
        p = nuevoNodo;
    }
    return p;
}

Nodo *eliminarNodo(Nodo *lista, int protocolo_eliminar){
    Nodo *aux = lista;
    Nodo *aux2;

    if (aux != NULL && aux->info.protocolo == protocolo_eliminar) { // Se busca el mismo protocolo para poder eliminar el nodo correcto
        lista = aux->next;
        free(aux);
        printf("\nNodo con protocolo %d eliminado correctamente.\n", protocolo_eliminar);
        return lista;
    }

    while (aux != NULL && aux->info.protocolo != protocolo_eliminar) { // Mientras que no lo encuentre, sigue avazando
        aux2 = aux;
        aux = aux->next;
    }

    if (aux == NULL) { // Si llega alfinal de la lista y no lo encuentra
        printf("\nNo se encontro el protocolo %d\n", protocolo_eliminar);
        return lista;
    }

    aux2->next = aux->next;
    free(aux); // Elimina el nodo free = Liberar 
    printf("\nNodo con protocolo %d eliminado correctamente.\n", protocolo_eliminar);
    return lista;
}


int contarNodos(Nodo *p) { // Cuenta la cantidad de nodos que hay en la lista
    int i = 0;
    while (p != NULL) {
        i++;
        p = p->next;
    }
    return i;
}


TData* cargarArreglo(Nodo *p){
    int cantidad = 0;
    Nodo *aux = p;

    // Contar la cantidad de elementos en la lista
    cantidad = contarNodos(p); // Carga el numero de la cantidad de nodos que hay en la lista

    TData* informacion = (TData*)malloc(cantidad * sizeof(TData)); // cantidad se utiliza para determinar la longitud del arreglo
    aux = p;
    int i = 0;

    // Copiar la información de la lista al arreglo
    while(aux != NULL){
        informacion[i] = aux->info;
        i++;
        aux = aux->next; 
    }

    return informacion;
}

void buscarPorProtocoloDicotomica(Nodo *p, int protocolo) {
    TData* informacion;
    informacion = cargarArreglo(p);
    int inicio = 0;
    int n = contarNodos(p);
    int fin = n-1;
    int encontrado = -1;



    // Búsqueda dicotómica
    while (inicio <= fin && encontrado == -1) {
        int medio = (inicio + fin) / 2;

        // Si el elemento está en el medio, se devuelve su posición
        if (informacion[medio].protocolo == protocolo) {
            encontrado = medio;
        }
        // Si el elemento es menor que el valor medio, se busca en la mitad inferior
        else if (informacion[medio].protocolo > protocolo) {
            fin = medio - 1;
        }
        // Si el elemento es mayor que el valor medio, se busca en la mitad superior
        else {
            inicio = medio + 1;
        }
    }

    // Si se encontró el elemento, se muestra su información
    if (encontrado != -1) {
        printf("Protocolo encontrado!! \n\n");
        printf("Numero de protocolo: %i\n", informacion[encontrado].protocolo);
        printf("Nombre del paciente: %s\n", informacion[encontrado].nombre);
        printf("Nombre del medico: %s\n", informacion[encontrado].medicosolicitado);
        printf("Fecha: %i/%i/%i\n", informacion[encontrado].fecha.dia, informacion[encontrado].fecha.mes, informacion[encontrado].fecha.anio);
        if(informacion[encontrado].tieneOS == 1){
            printf("Nombre Obra Social: %s\n", informacion[encontrado].nombreOS);
            printf("Monto Obra Social: %i\n", informacion[encontrado].montoOS);
        }
        printf("Monto del paciente: %i\n", informacion[encontrado].montoPT);
    } else {
        printf("Protocolo no encontrado!\n");
    }

    free(informacion);
}


int calcularMontoPorOS(Nodo *p, int mes, char* nombreOS){
    if(p == NULL){
        return 0;
    }
    int acumulado = calcularMontoPorOS(p->next, mes, nombreOS); // Parte Recursiva
    if (p->info.fecha.mes == mes && p->info.tieneOS == 1 && strcmp(p->info.nombreOS, nombreOS) == 0) { // Compara el mes del nodo, con el mes que entra y si tiene OS, ademas compara 
        acumulado += p->info.montoOS;                                                                  //el nombre de la OS con el nombre que entra si son iguales deberia devolver 0
    }
    return acumulado;
}


void mostrarListadoPorMes(Nodo *p, int mes){
    int acumuladoTotal = 0;
    Nodo *aux;
    aux = p;
    while(aux != NULL){
        if(aux->info.fecha.mes == mes && aux->info.tieneOS == 1){ // Si el info del aux es igual al del mes y tiene OS, entra y llama a la funcion recursiva
            int montoOS = calcularMontoPorOS(aux, mes, aux->info.nombreOS);
            printf("%s: $%i\n", aux->info.nombreOS, montoOS); // Devuelve el nombre de la OS y la cantidadd $
            acumuladoTotal += montoOS;
        }
        aux = aux->next;
    }
    printf("Total acumulado: $%i\n", acumuladoTotal);
}


#endif

