#include <iostream>
#include "funciones.h"

//Inicializar listas
void inicializarListaEdificios(tListaEdificios & listaEdificios) 
{
	listaEdificios.contador = 0; 
}

void inicializarListaJugadores(tListaJugadores & listaJugadores)
{
	listaJugadores.contador = 0; 
}

// Cargar listas

bool cargaEdificios(tListaEdificios &lista)
{
	bool cargado = false;
	tEdificio edificio;
	tEstado estado;
	int aux = 0;
	char ch;

	lista.contador = 0;

	ifstream archivo;
	archivo.open("edificios.txt");

	if( !archivo.is_open() )
	{
		cout << "Fallo al abrir el archivo de los edificios" << endl;
	}
	else
	{
		archivo >> edificio.codigo;
		
		while((edificio.codigo != -1) && (lista.contador < lista.capacidadEdificios))
		{
			archivo.get(ch);
			archivo.getline(edificio.nombre,LONG_CADENA);
			archivo >> edificio.precio;
			archivo >> edificio.dinero;
			archivo >> edificio.prestigio;
			archivo >> aux;
			estado = tEstado(aux);
			edificio.estado = estado;

			lista.tablaEdificio[lista.contador] = edificio;
			lista.contador++;

			archivo >> edificio.codigo;
		}

		cargado = true; 
		archivo.close();
	}
	return cargado;
}

bool cargaJugadores(tListaJugadores &lista)
{
	bool cargado = false;
	tJugador jugador;
	ifstream archivo;
	int i = 0;
	char ch;

	lista.contador = 0;
	jugador.comprados.contador = 0;

	archivo.open("jugadores.txt");

	if(!archivo.is_open())
	{
		cout << "Fallo al abrir el archivo de jugadores" << endl;
	}
	else
	{
		archivo >> jugador.usuario;

		while((strcmp(jugador.usuario, "X")!= 0) && (lista.contador < lista.capacidadJugadores))
		{
			archivo >> jugador.contrasenna;
			archivo.get(ch);
			archivo.getline(jugador.universidad, LONG_CADENA);
			archivo >> jugador.dinero;
			archivo >> jugador.prestigio;

			// Leeemos los edificios ..................
			archivo >> jugador.comprados.lista[i];

			while ( jugador.comprados.lista[i] != -1 )
			{
				i++; 
				archivo >> jugador.comprados.lista[i];
			}

			jugador.comprados.contador = i;

			// ......................................

			lista.tablaJugadores[lista.contador] = jugador;
			lista.contador++;
		
			archivo >> jugador.usuario;
		}
		cargado = true; 
		archivo.close();
	}
	
	return cargado; 
}

// Cargar listas como archivos binarios

bool cargarListaEdificios(tListaEdificios & listaEdificios)
{
	bool cargado = false;
	int pos, numEdificios;
	tEdificio edificio;

	fstream archivo;
	archivo.open("edificios.dat", ios::in | ios::binary );

	if ( archivo.is_open() )
	{ 
		archivo.seekg(0, ios::end);  
		pos = archivo.tellg();
		numEdificios = pos / SIZE_EDIFICIO; 

		listaEdificios.capacidadEdificios = ( ( numEdificios / 10) + 1) * 10;
		listaEdificios.tablaEdificio = new tEdificio[listaEdificios.capacidadEdificios]; 
		
		archivo.seekg(0, ios::beg); 

		for (int i = 0; i < numEdificios; i++) 
		{
			archivo.read( (char *) &edificio, SIZE_EDIFICIO);
			listaEdificios.tablaEdificio[listaEdificios.contador] = edificio; 
			listaEdificios.contador++; 
		}

		cargado = true; 
		archivo.close();
   }

	else
	{
		listaEdificios.capacidadEdificios = CAP_INICIAL;
		listaEdificios.tablaEdificio = new tEdificio[listaEdificios.capacidadEdificios];
		cout << " No se ha encontrado el archivo 'edificios.dat'. La lista se inicializara vacia" << endl << endl;
	}

	return cargado;
}

bool cargarListaJugadores(tListaJugadores & listaJugadores)
{
	bool cargado = false;
	int pos, numJugadores;	
	tJugador jugador; 

	fstream archivo;
	archivo.open("jugadores.dat", ios::in | ios::binary ); 
	
	if ( archivo.is_open() )
	{ 
		archivo.seekg(ios::beg, ios::end);  
		pos = archivo.tellg(); 
		numJugadores = pos / SIZE_JUGADOR; 

		listaJugadores.capacidadJugadores = (( numJugadores / 10) +1)*10;
		listaJugadores.tablaJugadores = new tJugador[listaJugadores.capacidadJugadores]; 

		listaJugadores.contador = 0; 
		archivo.seekg(0, ios::beg); 

		for (int i = 0; i < numJugadores; i++)
		{
			archivo.read( (char *) &jugador, SIZE_JUGADOR); 
			listaJugadores.tablaJugadores[listaJugadores.contador] = jugador; 
			listaJugadores.contador++; 
		}

		cargado = true; 
		archivo.close();
   }

	else
	{
		listaJugadores.capacidadJugadores = CAP_INICIAL;
		listaJugadores.tablaJugadores = new tJugador[listaJugadores.capacidadJugadores];
		cout << " No se ha encontrado el archivo 'jugadores.dat'. La lista se inicializara vacia" << endl << endl;	
	}

	return cargado;	
}

// Guardar listas Binarias
void guardarEdificios(tListaEdificios listaEdificios)
{
	fstream archivo;
	archivo.open("edificios.dat", ios::out | ios::binary | ios::trunc);

	if ( archivo.is_open() )
	{
		for ( int i = 0; i < listaEdificios.contador; i++) 
		{
			archivo.write( (char *) &listaEdificios.tablaEdificio[i], SIZE_EDIFICIO); 
		}

		archivo.close(); 
	}

	else cout << " No se han podido guardar los datos en el archivo 'edificios.txt'" << endl; 
}

void guardarJugadores(tListaJugadores listaJugadores)
{	
	fstream archivo;
	archivo.open("jugadores.dat", ios::out | ios::binary | ios::trunc);

	if ( archivo.is_open() )
	{
		for ( int i = 0; i < listaJugadores.contador; i++) 
		{	
			archivo.write( ( char *) &listaJugadores.tablaJugadores[i], SIZE_JUGADOR ); 
		}

		archivo.close(); 
	}

	else cout << " No se han podido guardar los datos en el archivo 'jugadores.txt'" << endl; 
}

// Otras funciones 

void bienvenida()
{
	cout << endl;
	cout << "Bienvenido a Campus Ville" << endl;
	cout << "-------------------------" << endl;
	cout << endl;
}

void pedirContrasenaAdmin(bool &correcta)
{
	tCadena password;

	for(int i = 3; (i > 0) && (!correcta); i--) 
	{
		cout << " Contrasena (" << i << " intentos): ";
		cin >> password;

		if( (strcmp (password, c_admin) == 0) )
		{
			correcta = true; 
		}
	}
}

void pedirContrasenaUsuario(bool &correcta, tListaJugadores lista, int posUsuario)
{
	tCadena password;

	for(int i = 3; (i > 0) && (!correcta); i--) 
	{
		cout << " Contrasena (" << i << " intentos): ";
		cin >> password;

		if ( (strcmp (lista.tablaJugadores[posUsuario].contrasenna, password) == 0) )
		{
			correcta = true;
		}
	}
}

bool validarUsuario(tListaJugadores lista, tCadena usuario, int &posUsuario)
{
	bool abandonar = false, correcta = false;
	
	bienvenida();

	do
	{
		cout << "Introduzca usuario :" << " " ; 
		cin.sync(); cin.getline (usuario, LONG_CADENA);		
		
		if(strcmp(usuario, n_admin) == 0)
		{
			pedirContrasenaAdmin(correcta); 
		}
		else if(strcmp(usuario, salir) == 0)
		{
			abandonar = true;
		}
		else
		{
			posUsuario = buscarPosJugador(lista, usuario);

			if (posUsuario != -1 )
			{
				pedirContrasenaUsuario(correcta, lista, posUsuario);
			}	
		}

	} while( (!abandonar) && (!correcta) );

	cout << endl;

	return abandonar;
}


// Menu administrador 

int menuAdmin()
{
	int opcion;

	do
	{
		cout << "Menu Administrador" << endl;
		cout << "------------------" << endl;
		cout << "1. Ver el listado de edificios" << endl;
		cout << "2. Nuevo edificio" << endl;
		cout << "3. Borrar un edificio" << endl;
		cout << "4. Ver el listado de jugadores" << endl;
		cout << "5. Nuevo jugador" << endl;
		cout << "6. Borrar un jugador" << endl;
		cout << "7. Ejecutar un turno" << endl;
		cout << "8. Ver la clasificacion" << endl;
		cout << "9. Importar archivos" << endl;
		cout << "0. Cerrar la sesion" << endl;
		cin >> opcion;
		cout << endl;

	}while(opcion < 0 || opcion > 9);

	return opcion;
}

void ejecutarMostrarListaEdificios(tListaEdificios lista)
{
	for(int i = 0; i < lista.contador; i++)
	{
		mostrarEdificio(lista.tablaEdificio[i]);
	}
}

void ejecutarMostrarListaJugadores(tListaJugadores lista1, tListaEdificios lista2)
{
	for(int i = 0; i < lista1.contador; i++)
	{
		mostrarJugador(lista1.tablaJugadores[i], lista2);
	}
}

void ejecutarNuevoEdificio(tListaEdificios & lista1) 
{
	tEdificio edificio; 

	if( !listaEdificiosLlena(lista1) )
	{
		edificio = nuevoEdificio();
		
		if ( !insertarEdificio(edificio, lista1) )
		{
			cout << "Fallo al insertar, codigo duplicado" << endl;
		}
		else cout << " Edificio insertado " << endl; 							
	}

	else cout << "Lista llena" << endl;

	cout << endl;
}

void ejecutarBorrarEdificio(tListaEdificios & lista1)
{
	int codigo; 

	cout << "Introduzca el codigo del edificio" << endl;
	cin >> codigo;
	cout << endl; 

	if (bajaEdificio(lista1, codigo) )
	{
		cout << "El edificio ha sido borrado" << endl; 
	}
	else cout << "Imposible borrar ese edificio" << endl;
}

void ejecutarNuevoJugador(tListaJugadores & lista2)
{
	tJugador jugador; 

	if( ! listaJugadoresLlena(lista2) )
	{
		jugador = nuevoJugador();

		if( (buscarPosJugador(lista2, jugador.usuario) == -1) && (strcmp(jugador.usuario, "salir") != 0) && (strcmp(jugador.usuario, "admin") != 0) )
		{
			insertarJugador(jugador, lista2);
			cout << " El jugador ha sido insertado " << endl;
		}
		else if((strcmp(jugador.usuario, "salir") == 0) || (strcmp(jugador.usuario, "admin") == 0))
		{
			cout << "Nombre de usuario no valido" << endl;
		}
		else cout << "Ya existe un jugador con ese nombre, no se incluira en la lista" << endl;
	}
				
	else cout << "Lista llena, no se pueden anadir nuevos juegadores" << endl;
	
	cout << endl;
}

void ejecutarBorrarJugador(tListaJugadores & lista2, tListaEdificios & lista1)
{
	tCadena nombre; 

	cout << "Introduzca el nombre del jugador : ";
	cin.sync();	cin.getline (nombre, LONG_CADENA); 
	cout << endl;
	
	if ( bajaJugador(nombre, lista2, lista1) )
	{
		cout << "El jugador y sus edificios han sido eliminados " << endl; 
	}

	else cout << "No existe ese jugador" << endl;
	
	cout << endl;
}

void ejecutarTurno(tListaJugadores &listaJ, tListaEdificios listaE)
{
	int h = 0;
	int ini = 0, fin = listaE.contador;
	for(int i = 0; i < listaJ.contador; i++)
	{ 
		cout << " Jugador : " << listaJ.tablaJugadores[i].universidad << endl; 
		
		for(int j = 0; j < listaJ.tablaJugadores[i].comprados.contador; j++)
		{ //Para cada edificio comprado por el jugador
			
			h = buscarPosEdificio(listaE, listaJ.tablaJugadores[i].comprados.lista[j], ini, fin);
			//actualizamos dinero
			listaJ.tablaJugadores[i].dinero = listaJ.tablaJugadores[i].dinero + listaE.tablaEdificio[h].dinero;
			//actualizamos prestigio
			listaJ.tablaJugadores[i].prestigio = listaJ.tablaJugadores[i].prestigio + listaE.tablaEdificio[h].prestigio;
			
			cout << "Edificio:" <<listaE.tablaEdificio[h].nombre;
			cout << "( Dinero: " << listaE.tablaEdificio[h].dinero;
			cout << ", Prestigio " << listaE.tablaEdificio[h].prestigio << " ) " << endl;
		}
			
		cout << " ::::::::::::::::::::::::::::::::::::::::::: " << endl; 
	}
}

// Menu usuario

void ejecutarEdificiosDisponibles(tListaEdificios lista)
{
	for(int i = 0; i < lista.contador; i++)
	{
		if(lista.tablaEdificio[i].estado == disponible)
		{
			mostrarEdificio(lista.tablaEdificio[i]);
		}
	}
}

int menuUsuario()
{
	int opcion;

	do
	{
		cout << "Menu Usuario" << endl;
		cout << "-------------" << endl;
		cout << "1. Ver mis edificios" << endl;
		cout << "2. Ver los edificios disponibles" << endl;
		cout << "3. Comprar un edificio" << endl;
		cout << "4. Ver la clasificacion(ordenada por dinero)" << endl;
		cout << "5. Ver la clasificacion(ordenada por prestigio)" << endl;
		cout << "0. Cerrar la sesion" << endl;
		cin >> opcion;
		cout << endl;
	}while(opcion < 0 || opcion > 5);

	return opcion;
}

void salirJuego()
{
	cout << "Cerrando sesion" << endl;
	cout << endl;
}

void ejecutarComprarEdificio( tJugador & jugador, tListaEdificios & lista1 ) 
{
	int codigo; 

	cout << "Introduzca el codigo del edificio" << endl;
	cin >> codigo;
	cout << endl;

	if (!listaCompradosLlena(jugador) )
	{
		if ( comprarEdificio(jugador, codigo, lista1) )
		{
			cout << "El edificio ha sido comprado" << endl; 
		}
		else cout << "No se ha podido comprar el edificio" << endl; 
	}
	else cout << "No se puede comprar el edificio, la lista esta llena." << endl; 
	
	cout << endl;
}

void importarArchivosTexto(tListaEdificios & listaEdificios, tListaJugadores & listaJugadores)
{
	inicializarListaEdificios(listaEdificios); 
	inicializarListaJugadores(listaJugadores);

	if (cargaEdificios(listaEdificios) && cargaJugadores(listaJugadores))
	{
		cout << " Las Listas han sido modificadas";
	}

	else cout << " ERROR: carga de ficheros incorrecta...";

	cout << endl << endl;
}

