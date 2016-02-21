#ifndef TJUGADOR_H
#define TJUGADOR_H

#include "tListaEdificios.h"

// TIPOS  //

typedef int tInfoLista[LONGLISTA];

typedef struct{
	tInfoLista lista;
	int contador;
}tListaComprados;

typedef struct {
	tCadena usuario;
	tCadena contrasenna;
	tCadena universidad;
	int dinero; 
	int prestigio; 
	tListaComprados comprados;
}tJugador;

// PROTOTIPOS //

//Lee los datos de un jugador, inicializa su lista de edificios comprados como vacía, el dinero a 3.000 créditos y 
//los puntos de prestigio a 0.Devuelve la estructura tJugador debidamente inicializada.
tJugador nuevoJugador();

//Dado un tJugador y la lista de edificios, muestra en la consola los datos del jugador y los datos básicos de todos sus edificios
//(nombre, dinero y prestigio por turno)
void mostrarJugador(tJugador jugador, tListaEdificios lista);

//Recibe como entrada un tJugador y devuelve un booleano indicando si su lista de edificios comprados está llena.
bool listaCompradosLlena(tJugador jugador);

//Recibe como entrada un tJugador, un código de edificio y la lista completa de edificios. Si se puede hacer la compra (el edificio
//existe, está disponible y hay dinero suficiente) realiza la compra y añade el código de edificio a la lista de edificios del jugador.
bool comprarEdificio(tJugador &jugador, int codigo, tListaEdificios &lista);

// AUXILIARES //

void misEdificios(tListaEdificios lista, tJugador jugador);

#endif