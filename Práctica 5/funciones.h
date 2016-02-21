#ifndef FUNCIONES_H
#define funciones_H

#include <iostream>
#include <fstream>
#include <string>
#include "tListaEdificios.h"
#include "tListaJugadores.h"
#include "constantes.h"


const int SIZE_EDIFICIO = sizeof(tEdificio);
const int SIZE_JUGADOR = sizeof(tJugador);

// PROTOTIPOS // 

// Cargar listas
bool cargaJugadores(tListaJugadores &lista);
bool cargaEdificios(tListaEdificios &lista);

//Cargas listas binarias
bool cargarListaJugadores(tListaJugadores &lista); 
bool cargarListaEdificios(tListaEdificios &lista);

// Guardar Listas binarias
void guardarJugadores(tListaJugadores listaJ);
void guardarEdificios(tListaEdificios listaE);

// Otras funciones

void bienvenida();
void pedirContrasenaAdmin(bool &correcta);
void pedirContrasenaUsuario(bool &correcta, tListaJugadores lista, int posUsuario);
bool validarUsuario(tListaJugadores lista, tCadena usuario, int &posUsuario);
void importarArchivosTexto(tListaEdificios & listaEdificios, tListaJugadores & listaJugadores);
void inicializarListaEdificios(tListaEdificios & listaEdificios);
void inicializarListaJugadores(tListaJugadores & listaJugadores);


// Funciones del Administrador
int menuAdmin();
void ejecutarMostrarListaEdificios(tListaEdificios lista);
void ejecutarNuevoEdificio(tListaEdificios & lista); 
void ejecutarBorrarEdificio(tListaEdificios & lista);
void ejecutarMostrarListaJugadores(tListaJugadores lista1, tListaEdificios lista2);
void ejecutarNuevoJugador(tListaJugadores & lista2); 
void ejecutarBorrarJugador(tListaJugadores & lista2, tListaEdificios & lista1);
void ejecutarTurno(tListaJugadores &listaJ, tListaEdificios listaE);

// Funciones del Usuario
int menuUsuario();
void ejecutarEdificiosDisponibles(tListaEdificios lista);
void ejecutarComprarEdificio( tJugador & jugador, tListaEdificios & lista1);
void salirJuego();

#endif

