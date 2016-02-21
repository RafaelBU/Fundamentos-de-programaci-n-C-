#include <iostream>

#include "tJugador.h"
#include <iostream>
#include "tListaJugadores.h"

using namespace std;

tJugador nuevoJugador()
{
	tJugador jugador; 

	cout << "Introduca los siguientes valores" << endl;
	cout << "Usuario :" << " " ; 
	cin.sync(); cin.getline(jugador.usuario,LONG_CADENA);
	cout << "Contrasenna :" << " " ; 
	cin.sync(); cin.getline(jugador.contrasenna,LONG_CADENA);
	cout << "Universidad :" << " "; 
	cin.sync(); cin.getline(jugador.universidad,LONG_CADENA);
	cout << endl;

	cout << "El dinero, prestigio y lista de edificios se iniciara por defecto" << endl;
	jugador.dinero = 3000; 
	jugador.prestigio = 0;
	jugador.comprados.contador = 0;

	return jugador;
	
}

void mostrarJugador(tJugador jugador, tListaEdificios lista)
{
	cout << "Usuario : " << " " << jugador.usuario << endl;
	cout << "Universidad : " << " " << jugador.universidad << endl;
	cout << "Dinero : " << " " << jugador.dinero << endl;
	cout << "Prestigio : " << " " << jugador.prestigio << endl;

	if(jugador.comprados.contador > 0)
	{
		misEdificios(lista, jugador);
	}
	
	else cout << " Actualmente no tiene ningun edificio." << endl;
}

bool listaCompradosLlena(tJugador jugador)
{
	bool llena = false;

	if(jugador.comprados.contador == LONGLISTA)
	{
		llena = true;
	}

	return llena;
}

bool comprarEdificio(tJugador &jugador, int codigo, tListaEdificios &lista)
{
	bool compra = false;
	int pos = 0;
	
	pos = buscarPosEdificio(lista, codigo);

	if(pos != -1)
	{
		if( (lista.edificios[pos].estado == disponible) && (lista.edificios[pos].precio <= jugador.dinero) )
		{
			compra = true;
			lista.edificios[pos].estado = comprado;
			jugador.dinero = jugador.dinero - lista.edificios[pos].precio;
			jugador.comprados.lista[jugador.comprados.contador] = lista.edificios[pos].codigo;
			jugador.comprados.contador++;
			
		}
	
		else if(lista.edificios[pos].estado == comprado)
		{
			cout << "Este edificio ya no se encuentra disponible para su venta" << endl;
		}

		else if(lista.edificios[pos].estado == borrado)
		{
			cout << "Este edificio ha sido eliminado, no se pueda llevar a cabo la compra" << endl;
		}

		else cout << "No dispone de suficiente dinero para la compra" << endl;
	}

	else cout << "No existe ningun edificio con ese codigo" << endl;
	
	return compra;
}

void misEdificios(tListaEdificios lista, tJugador jugador)
{
	int codigo = 0, a = 0;

	if(jugador.comprados.contador == 0)
	{
		cout << "Aun no has comprado ningun edificio!" << endl;
	}
	for(int i = 0; i < jugador.comprados.contador; i++)
	{
		codigo = jugador.comprados.lista[i]; 

		if (codigo != -1)
		{
			a = buscarPosEdificio(lista, codigo); 
			
			cout << "            " << "Nombre : " << " " << lista.edificios[a].nombre << endl;
			cout << "            " << "Dinero : " << " " << lista.edificios[a].dinero << endl;
			cout << "            " << "Prestigio : " << " " << lista.edificios[a].prestigio<< endl; 
			cout << "            " << "--------------" << endl;	
		}
	}
}
