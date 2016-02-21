
#include "tListaJugadores.h"

bool listaJugadoresLlena(tListaJugadores lista)
{
	bool llena = false;

	if(lista.contador == NUMERO_JUGADORES)
	{
		llena = true;
	}

	return llena;
}

void redimensionarListaJugadores (tListaJugadores & listaJugadores) 
{
	tTablaJugadorPtr tablaJugadores_aux; 

	tablaJugadores_aux = listaJugadores.tablaJugadores;
	listaJugadores.capacidadJugadores = ( ( listaJugadores.capacidadJugadores * 3 ) / 2 ) + 1; 
	listaJugadores.tablaJugadores = new tJugador[listaJugadores.capacidadJugadores]; 

	for ( int i = 0; i < listaJugadores.contador; i++) 
	{
		listaJugadores.tablaJugadores[i] = tablaJugadores_aux[i]; 
	}

	delete []tablaJugadores_aux;
}

int buscarPosJugador(tListaJugadores lista, tCadena usuario)
{
	int posicion = -1, i = 0;
	bool encontrado = false;

	while((i < lista.contador) && (!encontrado))
	{
		if(strcmp(lista.tablaJugadores[i].usuario, usuario) == 0)
		{
			posicion = i;
			encontrado = true;
		}
		else i++;
	}
	
	return posicion;
}

void insertarJugador(tJugador jugador, tListaJugadores &lista)
{
	if (lista.contador == lista.capacidadJugadores) 
	{
		redimensionarListaJugadores(lista);
	}
	lista.tablaJugadores[lista.contador] = jugador;
	lista.contador++;
}

bool bajaJugador(tCadena usuario, tListaJugadores &listaJ, tListaEdificios &listaE)
{
	bool eliminado = false;
	int aux, posicion = buscarPosJugador(listaJ, usuario), ini = 0, fin = listaE.contador;

	if(posicion != -1)
	{	
		//ponemos sus edificios como disponibles
		for(int j = 0; j < listaJ.tablaJugadores[posicion].comprados.contador; j++)
		{
			 aux = buscarPosEdificio(listaE, listaJ.tablaJugadores[posicion].comprados.lista[j], ini, fin);
			 listaE.tablaEdificio[aux].estado = disponible;
		}
		//eliminamos el jugador de la lista
		for(int i = posicion; i < listaJ.contador; i++)
		{
			listaJ.tablaJugadores[i] = listaJ.tablaJugadores[i+1];
		}

		listaJ.contador--;
		eliminado = true;
	}

	return eliminado;
}