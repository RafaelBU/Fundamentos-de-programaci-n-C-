//Practica 4 Campus Ville
//Rafael Buzón Urbano y Alberto Casas Ortiz
//1º B
#include <iostream>
#include <fstream>
#include "funciones.h"

using namespace std;

//Prototipos//

void clasificacionPorDinero(tListaJugadores lista);
void clasificacionPorPrestigio(tListaJugadores lista);

//Main
int main()
{
	int opcion = 0, posUsuario = 0;
	bool salir = false, abandonar = false; 
	tCadena usuario;

	tListaEdificios lista1;
	tListaJugadores lista2;

	cargaEdificios(lista1);
	cargaJugadores(lista2);

	abandonar = validarUsuario(lista2, usuario, posUsuario);
	
	while ( !abandonar)
	{
		if(strcmp(usuario, n_admin) == 0)
		{
			salir = false;

			do 
			{
				opcion = menuAdmin();

				switch(opcion)
				{
					case 0: //Salir menu administrador
							salir = true;
							salirJuego();
							break;
					case 1: //Lista de edificios
							ejecutarMostrarListaEdificios(lista1); 
							break;
					case 2: //Nuevo edificio
							ejecutarNuevoEdificio(lista1); 
							break;		
					case 3: //Borrar edificio
							ejecutarBorrarEdificio(lista1);
							break;
					case 4: //Mostrar jugadores
							ejecutarMostrarListaJugadores(lista2, lista1);
							break;
					case 5: //Nuevo jugador
							ejecutarNuevoJugador(lista2);
							break;
					case 6: //Borrar jugador
							ejecutarBorrarJugador(lista2,lista1);
							break;
					case 7: //Ejecutar turno
							ejecutarTurno(lista2, lista1);
							break;
					case 8: //Ver clasificacion(por dinero)
							clasificacionPorDinero(lista2);
							break;
				}
			} while (!salir);
		}

		else
		{
			salir = false;

			do 
			{
				opcion = menuUsuario();

				switch(opcion)
				{
					case 0: //Salir menu usuario
							salir = true;
							salirJuego();
							break;
					case 1: //Ver mis edificios
							misEdificios(lista1, lista2.jugadores[posUsuario]);
							break;
					case 2: //Ver edificios disponibles
							ejecutarEdificiosDisponibles(lista1);
							break;
					case 3: //Comprar edificio
							ejecutarComprarEdificio(lista2.jugadores[posUsuario], lista1);
							break;
					case 4: //Ver clasificacion(por dinero)
							clasificacionPorDinero(lista2);
							break;
					case 5: //Ver clasificacion(por prestigio)
							clasificacionPorPrestigio(lista2);
							break;
				}
			} while(!salir);
		}

		abandonar = validarUsuario(lista2, usuario, posUsuario);
	}

	guardarJugadores(lista2);
	guardarEdificios(lista1);

	return 0;		
}


void clasificacionPorDinero(tListaJugadores lista)
{
	typedef tJugador tAux[NUMERO_JUGADORES];
	tAux listaAux;
	for(int b = 0; b < lista.contador; b++)
	{
		listaAux[b] = lista.jugadores[b];
	}
	bool inter = true;
	int i = 0, aux;
	while ((i < lista.contador - 1) && inter)
	{
		inter = false;
		for (int j = lista.contador - 1; j > i; j--)
		{
			if (listaAux[j].dinero < listaAux[j-1].dinero) 
			{
				tJugador tmp;
				tmp = listaAux[j];
				listaAux[j] = listaAux[j-1];
				listaAux[j-1] = tmp;
				inter = true;
			}
		}
		if (inter) 
		{
			i++;
		}
	}

	aux = lista.contador;
	cout << "Clasificacion" <<"        "<< "Dinero" <<"          "<< "Universidad" << endl;
	cout << "-------------" <<"        "<< "------" <<"          "<<"------------" << endl;
	for(int a = 0; a < lista.contador; a++)
	{
		cout <<"   "<< a+1 <<"                 "<< listaAux[aux-1].dinero<<"             "<< listaAux[aux-1].universidad;
		cout << endl;
		aux--;
	}
	 
}

void clasificacionPorPrestigio(tListaJugadores lista)
{
	typedef tJugador tAux[NUMERO_JUGADORES];
	tAux listaAux;
	for(int b = 0; b < lista.contador; b++)
	{
		listaAux[b] = lista.jugadores[b];
	}
	bool inter = true;
	int i = 0, aux;
	while ((i < lista.contador - 1) && inter)
	{
		inter = false;
		for (int j = lista.contador - 1; j > i; j--)
		{
			if (listaAux[j].prestigio < listaAux[j-1].prestigio) 
			{
				tJugador tmp;
				tmp = listaAux[j];
				listaAux[j] = listaAux[j-1];
				listaAux[j-1] = tmp;
				inter = true;
			}
		}
		if (inter) 
		{
			i++;
		}
	}

	aux = lista.contador;
	cout << "Clasificacion" <<"        "<< "Prestigio" <<"          "<< "Universidad" << endl;
	cout << "-------------" <<"        "<< "---------" <<"          "<<"------------" << endl;
	for(int a = 0; a < lista.contador; a++)
	{
		cout <<"   "<< a+1 <<"                 "<< listaAux[aux-1].prestigio<<"             "<< listaAux[aux-1].universidad;
		cout << endl;
		aux--;
	}
}
