// ESTE CODIGO FUE CREADO EN EL SISTEMA OPERATIVO WINDOWS 11
// UTILIZANDO EL COMPILADOR GCC, DE MSMSYS2.
// SE DEBE EJECUTAR proyecto.c 
// Y DEBE CONTENER EN UNA CARPETA TODO JUNTO archivos.h, estructura.h lista.h, fecha.h y proyecto.c


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
 

#include "lista.h"
#include "archivos.h"
#include "fecha.h"
#include "estructura.h"


int opcion; // se utiliza para obtener que es lo que quiere hacer el usuario en el programa


int main(){
    // CARGA DE LA FECHA QUE SE UTILIZA EN LA PLANTILLA.
    cargarFecha(&fecha);
    cargarArchivo(&lista);
do{
        printf("\n\t\t\t==> MENU DE OPCIONES <==\n");
        printf("\n\t\t1: Cargar un informe \n\t\t2: Modificar un informe \n\t\t3: Eliminar un informe \n\t\t4: Buscar un protocolo \n\t\t5: Listar informes \n\t\t6: Listar montos pagados por las obras sociales en un mes dado \n\t\t7: Guardar y Salir \n\t\t");
        printf("\nIngrese su opcion: [ ]\b\b");
        scanf("%d", &opcion);
        // CARGA DE INFORMES
        if(opcion == 1){
           nodoCreado = crearNodo(lista, &fecha);
           lista = agregarNodo(lista, nodoCreado);
           aggArchivo(lista);

        }
        // MODIFICACION DE INFORMES
        if(opcion == 2){
            int protocoloModificado; // entero que sirve para modificar protocolo
            printf("Porfavor ingrese el protocolo del cual quieras modificar: \n");
            scanf("%i", &protocoloModificado);
            editarArchivoPorProtocolo(lista, protocoloModificado);

        }
        // ELIMINAR INFORMES
        if (opcion == 3) {
            int protocoloEliminar; // entero que sirve para elminar protocolo
            printf("Ingrese el protocolo que quiera borrar: \n");
            scanf("%i", &protocoloEliminar);
            lista = eliminarNodo(lista, protocoloEliminar);
            sobreescribirArchivo(lista);
        }
        // BUSCAR POR PROTOCOLO
        if (opcion == 4) {
            int protocoloBuscar; // entero que sirve para buscar el protocolo
            printf("Ingrese protocolo para buscar: \n");
            scanf("%i", &protocoloBuscar);
            buscarPorProtocoloDicotomica(lista, protocoloBuscar);
            
        }
        // LISTAR INFORMES
        if(opcion == 5){
            leerArchivo(&lista);
            }
        // LISTAR MONTOS PAGADOS POR LAS OS EN UN MES DADO
        if(opcion == 6){
            int mes;
            printf("Ingrese el mes a buscar (en formato numerico de un digito): ");
            scanf("%i", &mes);
            if(mes > 12 || mes < 1){
                printf("Ingrese un numero correcto");
                continue;
            }
            mostrarListadoPorMes(lista, mes);
        }
        // GUARDAR Y SALIR
        }while(opcion != 7);
            sobreescribirArchivo(lista);
            printf("Guardado con exito!");
    return(0);
}
