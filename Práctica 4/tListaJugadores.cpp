
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

int buscarPosJugador(tListaJugadores lista, tCadena usuario)
{
	int posicion = -1, i = 0;
	bool encontrado = false;

	while((i < lista.contador) && (!encontrado))
	{
		if(strcmp(lista.jugadores[i].usuario, usuario) == 0)
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
		lista.jugadores[lista.contador] = jugador;
		lista.contador++;
}

bool bajaJugador(tCadena usuario, tListaJugadores &listaJ, tListaEdificios &listaE)
{
	bool eliminado = false;
	int aux, posicion = buscarPosJugador(listaJ, usuario);

	if(posicion != -1)
	{	
		//ponemos sus edificios como disponibles
		for(int j = 0; j < listaJ.jugadores[posicion].comprados.contador; j++)
		{
			 aux = buscarPosEdificio(listaE, listaJ.jugadores[posicion].comprados.lista[j]);
			 listaE.edificios[aux].estado = disponible;
		}
		//eliminamos el jugador de la lista
		for(int i = posicion; i < listaJ.contador; i++)
		{
			listaJ.jugadores[i] = listaJ.jugadores[i+1];
		}

		listaJ.contador--;
		eliminado = true;
	}

	return eliminado;
}