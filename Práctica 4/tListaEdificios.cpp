
#include "tListaEdificios.h"

bool listaEdificiosLlena(tListaEdificios lista)
{
	bool llena = false;

	if(lista.contador == NUMERO_EDIFICIOS)
	{
		llena = true;
	}

	return llena;
}

bool insertarEdificio(tEdificio edificio, tListaEdificios &lista)
{
	int pos = 0, existe = 0;
	bool insertado = false;

	existe = buscarPosEdificio(lista, edificio.codigo); 
	
	if (existe == -1) 
	{
		while ( (lista.edificios[pos].codigo <= edificio.codigo) && ( pos < lista.contador ) )
		{ 
			pos++; 
		}

		for (int j = lista.contador; j > pos ; j--) 
		{
			lista.edificios[j] = lista.edificios[j - 1]; 
		}

		lista.edificios[pos] = edificio; 
		lista.contador++; 
		insertado = true;
	}

	return insertado;

}

int buscarPosEdificio(tListaEdificios lista, int codigo)
{
	int ini = 0, fin = lista.contador, mitad, pos = -1;
	bool encontrado = false;

	while(((ini <= fin) && (!encontrado)))
	{
		mitad = (ini + fin)/2;
		if(codigo == lista.edificios[mitad].codigo)
		{
			encontrado = true;
			pos = mitad;
		}
		else if(codigo < lista.edificios[mitad].codigo)
		{
			fin = mitad - 1;
		}
		else
		{
			ini = mitad + 1;
		}
	}

	return pos;
}

bool bajaEdificio(tListaEdificios &lista, int codigo)
{
	int pos = 0;
	bool eliminado = false; 

	pos = buscarPosEdificio(lista, codigo);

	if(pos !=1)
	{
		if(lista.edificios[pos].estado == disponible)
		{
			lista.edificios[pos].estado = borrado;
			eliminado = true;
		}
	}
	
	return eliminado;
}
