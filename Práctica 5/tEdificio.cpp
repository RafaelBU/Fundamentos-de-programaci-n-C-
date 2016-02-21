#include <iostream>
#include <cstring>
#include "tListaEdificios.h"

using namespace std;

tEdificio nuevoEdificio()
{
	tEdificio edificio;
	
	cout << "Introduca los siguientes valores" << endl;
	cout << "Codigo"<< " "; 
	cin >> edificio.codigo;
	cout << "Nombre"<< " "; 
	cin.sync(); cin.getline(edificio.nombre,LONG_CADENA);
	cout << "Precio"<< " "; 
	cin >> edificio.precio;
	cout << "Dinero"<< " ";
	cin >> edificio.dinero;
	cout << "Prestigio"<< " "; 
	cin >> edificio.prestigio;
	
	edificio.estado = disponible;

	return edificio;
}

void mostrarEdificio(tEdificio edificio)
{
	cout << "-------------------------------------" <<endl;
	cout << "Codigo :" <<edificio.codigo << endl;
	cout << "Nombre :" <<edificio.nombre << endl;
	cout << "Precio :" <<edificio.precio << endl;
	cout << "Dinero :" <<edificio.dinero << endl;
	cout << "Prestigio :" <<edificio.prestigio << endl;
	cout << "Estado : ";

	if ( edificio.estado  ==  disponible ) 
	{
		cout << "DISPONIBLE"; 
	}
	else if ( edificio.estado  ==  comprado ) 
	{
		cout << "COMPRADO"; 
	}
	else 
	{
		cout << "BORRADO"; 
	}

	cout << endl;
	

}
