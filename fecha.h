#ifndef FECHA_H
#define FECHA_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "estructura.h"
#include "lista.h"


void cargarFecha(struct TFecha *fecha); // Sirve para cargar la fecha en la plantilla, ademas se utiliza al comienzo del programa



void cargarFecha(struct TFecha *fecha){
    printf("\n\t\t\t==> INSERTAR FECHA <==\n");
    printf("\nIngrese el anio: ");
    scanf("%i", &fecha->anio);
    if(fecha->anio <= 0){
        printf("Ingrese una fecha correcta");
        exit(1);
    }
    printf("\nIngrese el mes: ");
    scanf("%i", &fecha->mes);
    if(fecha->mes > 12 || fecha->mes <= 0){
        printf("Ingrese una fecha correcta");
        exit(1);
    }
    printf("\nIngrese el dia: ");
    scanf("%i", &fecha->dia);
    if(fecha->dia <= 0 || fecha->dia > 31){
        printf("Ingrese una fecha correcta");
        exit(1);
    }
    if(((fecha->dia == 29) && (fecha->mes == 2)) && !((fecha->anio%4 == 0) && (!(fecha->anio%100 == 0) || (fecha->anio%400 == 0)))){
        printf("El valor ingresado no es correcto\n");
        exit(1);
    }else{
        if((fecha->dia > 29) && (fecha->mes == 2)){
            printf("El valor ingresado no es correcto\n");
            exit(1);
        }else{
            if((fecha->dia > 30) && ((fecha->mes == 1) || (fecha->mes == 6) || (fecha->mes == 9) || (fecha->mes == 11))){
                printf("El valor ingresado no es correcto\n");
                exit(1);
            }else{
                if(fecha->dia > 31){
                    printf("El valor ingresado no es correcto\n");
                    exit(1);
                }
            }
        }
    }
}


#endif