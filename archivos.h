#ifndef archivos
#define archivos
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "estructura.h" // Se usa comillas dobles para incluir los archivos propios
#include "lista.h"     // Se usa comillas dobles para incluir los archivos propios
#include "fecha.h"     // Se usa comillas dobles para incluir los archivos propios


void aggArchivo(Nodo *p);  // Sirve para a la hora de crear un nodo pueda ser ingresado a lista y admemas al archivo.
void leerArchivo(Nodo **pp); // Sirve para para leer el archivo a traves de una lista encadenada
void editarArchivoPorProtocolo(Nodo *p, int num); // Toma un protocolo en especifico y se busca en la lista, y se le pide al usuario que ingrese el campo que quiera modificar, luego de ser modificado vuelve al archivo
void sobreescribirArchivo(Nodo *p); // Sirve para sobreescribir el archivo, cuando se elimina un nodo para poder obtener el archivo correspondiente ordenado y que no se pierdan protocolos
void cargarArchivo(Nodo **p); // Sirve para leer el archivo




void aggArchivo(Nodo *p) {
    FILE *f;
    f = fopen("cobros.dat", "ab");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    if (p != NULL) { // verifica si el puntero no es nulo antes de escribir en el archivo
        fwrite(&(p->info), sizeof(TData), 1, f);
    }
    fclose(f);
}

void sobreescribirArchivo(Nodo *p) {
    FILE *f;
    f = fopen("cobros.dat", "wb+");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    if (p == NULL) {
        printf("La lista esta vacia.\n");
        fclose(f);
        return;
    }
    while (p != NULL) {
        fwrite(&(p->info), sizeof(TData), 1, f); // Escribe lo almacenado lo que hay en el nodo->info y avanza al siguiente
        p = p->next;
    }
    fclose(f);
}



void leerArchivo(Nodo **pp) {
    FILE *f;
    f = fopen("cobros.dat", "rb");

    if (f == NULL) {
        printf("Error el archivo no existe\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long int tamanio = ftell(f);

    if (tamanio == 0) {
        printf("El archivo esta vacio.\n");
        fclose(f);
        return;
    }

    fseek(f, 0, SEEK_SET);

    // Crear la nueva lista con los nodos leídos del archivo
    Nodo *nuevaLista = NULL;
    TData buf;
    while (fread(&buf, sizeof(TData), 1, f) == 1) {
        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
        nuevo->info = buf;
        nuevo->next = NULL;  // El nuevo nodo siempre apunta a NULL
        if (nuevaLista == NULL) {
            // Si la nueva lista está vacía, este es el primer nodo
            nuevaLista = nuevo;
        } else {
            // Si la nueva lista no está vacía, agregar el nuevo nodo al final
            Nodo *aux = nuevaLista;
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = nuevo;
        }
    }

    fclose(f);

    // Liberar la lista anterior y asignar la nueva lista
    while (*pp != NULL) {  // Se utiliza ** para poder modificar el valor del puntero original pasado como argumento, en este caso para recorrer          
                            //y liberar todos los nodos de una lista y crear una nueva. 
        Nodo *aux = *pp;
        *pp = (*pp)->next;
        free(aux);
    }
    *pp = nuevaLista;

    // Imprimir los nodos creados
    Nodo *aux = nuevaLista;
    while (aux != NULL) {
        printf("\nProtocolo: %d\n", aux->info.protocolo);
        printf("Paciente: %s\n", aux->info.nombre);
        printf("Medico solicitado: %s\n", aux->info.medicosolicitado);
        printf("Fecha: %d/%d/%d\n", aux->info.fecha.dia, aux->info.fecha.mes, aux->info.fecha.anio);
        if (aux->info.tieneOS == 1) {
            printf("Nombre de la OS: %s\n", aux->info.nombreOS);
            printf("Monto de la OS: %d\n", aux->info.montoOS);
        }
        printf("Monto del paciente: %d\n\n", aux->info.montoPT);
        aux = aux->next;
    }
}
void cargarArchivo(Nodo **p){
    FILE *f;
    f = fopen("cobros.dat", "rb");

    fseek(f, 0, SEEK_END);
    long int tamanio = ftell(f); // Calcula el tamaño del archivo en bytes

    if (tamanio == 0) {
        printf("El archivo esta vacio.\n"); // Si no hay nada escrito
        fclose(f);
        return;
    }

    fseek(f, 0, SEEK_SET);

    // Crear la nueva lista con los nodos leídos del archivo
    Nodo *nuevaLista = NULL;
    TData dataPlanilla;
    while (fread(&dataPlanilla, sizeof(TData), 1, f) == 1) { // Lee un solo nodo
        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
        nuevo->info = dataPlanilla;
        nuevo->next = NULL;  // El nuevo nodo siempre apunta a NULL
        if (nuevaLista == NULL) {
            // Si la nueva lista está vacía, este es el primer nodo
            nuevaLista = nuevo;
        } else {
            // Si la nueva lista no está vacía, agregar el nuevo nodo al final
            Nodo *aux = nuevaLista;
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = nuevo;
        }
    }

    fclose(f);

    // Liberar la lista anterior y asignar la nueva lista a p
    while (*p != NULL) {
        Nodo *aux = *p;
        *p = (*p)->next;
        free(aux);
    }
    *p = nuevaLista;

}
void editarArchivoPorProtocolo(Nodo *p, int num) {
    if(p == NULL){
        printf("La lista esta vacia ingrese un informe antes");
        return;
    }
    int opc;

    printf("Que campo desea modificar?\n");
    printf("1: Paciente\n2: Medico Solicitado\n3: Nombre de la Obra Social\n4: Monto de la Obra Social\n5: Monto del paciente\n6: Cancelar\n");
    scanf("%d", &opc);
    
    switch(opc) {
        case 1:
            printf("Ingrese el nuevo nombre del paciente: \n");
            getchar();
            fgets(p->info.nombre, 50, stdin); // se lee una cadena de caracteres desde la entrada estándar del usuario y la guarda modificando la anterior en el nombre del paciente
            break;
        case 2:
            printf("Ingrese el nuevo nombre del medico solicitado: ");
            getchar();
            fgets(p->info.medicosolicitado, 50, stdin); // se lee una cadena de caracteres desde la entrada estándar del usuario y la guarda modificando la anterior en el nombre del medico solicitado
            break;
        case 3:
            if (p->info.tieneOS == 0) {
                printf("El paciente no tiene obra social\n"); 
                return;
            }
            printf("Ingrese el nuevo nombre de la obra social: ");
            getchar();
            fgets(p->info.nombreOS, 50, stdin); // se lee una cadena de caracteres desde la entrada estándar del usuario y la guarda modificando la anterior en el nombre de la Obra Social
            break;
        case 4:
            if (p->info.tieneOS == 0) {
                printf("El paciente no tiene obra social\n");
                return;
            }
            printf("Ingrese el nuevo monto de la obra social: ");
            scanf("%d", &p->info.montoOS); // se lee un entero desde la entrada estándar del usuario y la guarda modificando el anterior entero que estaba en el monto de la obra social
            break;
        case 5:
            printf("Ingrese el nuevo monto del paciente: ");
            scanf("%d", &p->info.montoPT); // se lee un entero desde la entrada estándar del usuario y la guarda modificando el anterior entero que estaba en el monto del paciente
            break;
        case 6:
            printf("Cancelando...\n");
            return;
        default:
            printf("Opcion invalida\n");
            return;
    }

    // Cerrar el archivo para poder abrirlo en modo de escritura
    fclose(fopen("cobros.dat", "rb"));

    // Actualizar el archivo
    FILE *f;
    f = fopen("cobros.dat", "rb+");
    if (f == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    TData registro;
    long int pos;  // se utiliza para un numeros enteros largos
    while (fread(&registro, sizeof(TData), 1, f) == 1) {
        if (registro.protocolo == num) {
            pos = ftell(f) - sizeof(TData); // Obtiene la posición actual y retroceder el tamaño del registro
            fseek(f, pos, SEEK_SET); // Regresa el cursor del archivo a la posición del registro

            // Actualizar solo el campo modificado
            switch(opc) {
                case 1:
                    strcpy(registro.nombre, p->info.nombre);
                    break;
                case 2:
                    strcpy(registro.medicosolicitado, p->info.medicosolicitado);
                    break;
                case 3:
                    strcpy(registro.nombreOS, p->info.nombreOS);
                    break;
                case 4:
                    registro.montoOS = p->info.montoOS;
                    break;
                case 5:
                    registro.montoPT = p->info.montoPT;
                    break;
                default:
                    break;
            }

            fwrite(&registro, sizeof(TData), 1, f); // actualizar registro con nuevo contenido

            printf("Registro actualizado\n");
            break;
        }
    }


fclose(f);

}





#endif