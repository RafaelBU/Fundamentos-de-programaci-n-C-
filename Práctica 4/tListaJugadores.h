#ifndef TLISTAJUGADORES_H
#define TLISTAJUGADORES_H

#include "tJugador.h"

// TIPOS //
typedef tJugador tArrayJugadores[NUMERO_JUGADORES];

typedef struct{
	tArrayJugadores jugadores;
	int contador;
}tListaJugadores;

//Prototipos

//Función que recibe como parámetro una lista de jugadores y devuelve un booleano indicando si la lista está llena o no
bool listaJugadoresLlena(tListaJugadores lista);

//Recibe como entrada una lista de jugadores y un nombre de usuario. Devuelve un booleano indicando si se ha encontrado el jugador o
//no y, en caso afirmativo, la posición en la que se encuentra el jugador
int buscarPosJugador(tListaJugadores lista, tCadena usuario);

//Recibe una variable de tipo tJugador y una lista de jugadores. Inserta el jugador al final de la lista de jugadores
void insertarJugador(tJugador jugador, tListaJugadores &lista);

//Recibe un nombre de usuario, la lista de jugadores y la lista de edificios. Busca al jugador en la lista y lo elimina completamente
bool bajaJugador(tCadena usuario,tListaJugadores &listaJ, tListaEdificios &listaE);

#endif