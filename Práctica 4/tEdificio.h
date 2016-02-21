#ifndef TEDIFICIO_H
#define TEDIFICIO_H
#include <string>
#include "constantes.h"

using namespace std;

// TIPOS //

typedef enum {disponible, comprado, borrado}tEstado;

typedef struct {
	int codigo;
	tCadena nombre;
	int precio;
	int dinero;
	int prestigio;
	tEstado estado;
}tEdificio;

// PROTOTIPOS //

//No recibe ningún valor de entrada. Pide al usuario los datos de un edificio y devuelve como salida una estructura tEdificio
//debidamente inicializada
tEdificio nuevoEdificio();

//Dado un tEdificio muestra todos sus datos en la consola, debidamente formateados.
void mostrarEdificio(tEdificio edificio);

#endif