#ifndef TLISTAEDIFICIOS_H
#define TLISTAEDIFICIOS_H

#include "tEdificio.h"

// *** TIPOS *** //

//typedef tEdificio tArrayEdificios[NUMERO_EDIFICIOS];
typedef tEdificio *tTablaEdificioPtr;

typedef struct{
	tTablaEdificioPtr tablaEdificio;
	//tArrayEdificios edificios;
	int contador;
	int capacidadEdificios;
}tListaEdificios;

//Prototipos//

//Función que recibe como parámetro una lista de edificios y devuelve un booleano indicando si esa lista está llena o no.
bool listaEdificiosLlena(tListaEdificios lista);

//Recibe una lista de edificios y un código. Indica si se ha encontrado o no un edificio con ese código y, en caso afirmativo, 
//la posición en la que se encuentra.
int buscarPosEdificio(const tListaEdificios lista, int codigo, int ini, int fin);

//Recibe un tEdificio y una lista de edificios. Inserta el edificio en la lista en la posición que le corresponda por código 
//y devuelve la lista actualizada
bool insertarEdificio(tEdificio edificio, tListaEdificios &lista);

//Recibe la lista edificios y un código de edificio. Si el edificio existe y está disponible, lo marca como borrado en la lista
bool bajaEdificio(tListaEdificios &lista, int codigo);

//Funciones de Redimensionar 
void redimensionarListaEdificios(tListaEdificios & listaEdificios);
#endif