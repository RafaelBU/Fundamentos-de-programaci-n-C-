#ifndef TLISTAEDIFICIOS_H
#define TLISTAEDIFICIOS_H

#include "tEdificio.h"

// *** TIPOS *** //

typedef tEdificio tArrayEdificios[NUMERO_EDIFICIOS];

typedef struct{
	tArrayEdificios edificios;
	int contador;
}tListaEdificios;

//Prototipos//

//Funci�n que recibe como par�metro una lista de edificios y devuelve un booleano indicando si esa lista est� llena o no.
bool listaEdificiosLlena(tListaEdificios lista);

//Recibe una lista de edificios y un c�digo. Indica si se ha encontrado o no un edificio con ese c�digo y, en caso afirmativo,
//la posici�n en la que se encuentra. Debe estar implementado como una b�squeda binaria
int buscarPosEdificio(tListaEdificios lista, int codigo);

//Recibe un tEdificio y una lista de edificios. Inserta el edificio en la lista en la posici�n que le corresponda por c�digo y devuelve la
//lista actualizada.
bool insertarEdificio(tEdificio edificio, tListaEdificios &lista);

//Recibe la lista edificios y un c�digo de edificio. Si el edificio existe y est� disponible, lo marca como borrado en la lista
bool bajaEdificio(tListaEdificios &lista, int codigo);

#endif