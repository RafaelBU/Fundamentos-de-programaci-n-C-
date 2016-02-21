
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

void redimensionarListaEdificios(tListaEdificios & listaEdificios)
{
	tTablaEdificioPtr talbaEdificios_aux; 

	talbaEdificios_aux = listaEdificios.tablaEdificio;
	listaEdificios.capacidadEdificios = ( ( listaEdificios.capacidadEdificios * 3 ) / 2 ) + 1;
	listaEdificios.tablaEdificio = new tEdificio[listaEdificios.capacidadEdificios];

	for ( int i = 0; i < listaEdificios.contador; i++) 
	{
		listaEdificios.tablaEdificio[i] = talbaEdificios_aux[i]; 
	}

	delete[]talbaEdificios_aux; 
}

bool insertarEdificio(tEdificio edificio, tListaEdificios &lista)
{
	bool insertado = false;
	int pos = 0, existe = 0, ini = 0, fin = lista.contador;

	existe = buscarPosEdificio(lista, edificio.codigo, ini, fin);
	
	if (existe == -1) 
	{
		if (lista.contador == lista.capacidadEdificios) // Comprobamos si es necesario ajustar el tamaño de la lista
		{
			redimensionarListaEdificios(lista);
		}

		while ( (lista.tablaEdificio[pos].codigo <= edificio.codigo) && ( pos < lista.contador ) )
		{ 
			pos++; 
		}

		for (int j = lista.contador; j > pos ; j--) 
		{
			lista.tablaEdificio[j] = lista.tablaEdificio[j - 1]; 
		}

		lista.tablaEdificio[pos] = edificio; 
		lista.contador++; 
		insertado = true;
	}

	return insertado;

}

int buscarPosEdificio(const tListaEdificios lista, int codigo, int ini, int fin)
{
	int posicion = -1, mitad;  

	if ( ini <= fin ) 
	{
		mitad = (ini + fin) / 2; 

		if ( codigo == lista.tablaEdificio[mitad].codigo )
			posicion = mitad; 

		else 
			if ( codigo < lista.tablaEdificio[mitad].codigo ) 
				posicion = buscarPosEdificio(lista, codigo, ini, mitad -1); 
			else 
				posicion = buscarPosEdificio(lista, codigo, mitad + 1, fin); 
	}

	return posicion;
}

bool bajaEdificio(tListaEdificios &lista, int codigo)
{
	int posicion = 0, ini = 0, fin = lista.contador;
	bool eliminado = false; 

	posicion = buscarPosEdificio(lista, codigo, ini, fin);

	if(posicion !=1)
	{
		if(lista.tablaEdificio[posicion].estado == disponible)
		{
			lista.tablaEdificio[posicion].estado = borrado;
			eliminado = true;
		}
	}
	
	return eliminado;
}
