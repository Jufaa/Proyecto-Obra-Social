#ifndef estructura
#define estructura

struct TFecha{
    int dia;
    int mes;
    int anio;
}; // Registro para manejar fechas

// Arreglo
typedef struct {
    int protocolo;
    char nombre[50];
    char medicosolicitado[50];
    struct TFecha fecha;
    char nombreOS[50];
    int tieneOS;
    int montoOS;
    int montoPT;
}TData; // Registro para manejar las plantillas

typedef struct TNodo{
    TData info;
    struct TNodo *next;
}Nodo; // Nodo para manejar las listas


// Variables utilizadas en el programa
struct TFecha fecha;
Nodo *lista = NULL;
Nodo *nodoCreado = NULL;
TData planilla;
TData informacion;






#endif