//Practica2
//Rafael Buzon Urbano y Alberto Casas Ortiz
//1º B

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


//Tipos definidos
typedef enum {N,S,E,O} tDireccion;
typedef enum {piedra, papel, tijera, lagarto, spock} tJugada; //Tipos de jugada definidos como enum

//Prototipos Piedra Papel Tijera
int menuJuego1();
void mostrarReglasJuego1();
int menuJugadasJuego1();
void jugadasJuego1(int &ganadas, int &empatadas, int &perdidas);
tJugada jugadaMaquina();
void juego1(int &ganadas, int &empatadas, int &perdidas);
void mostrarEstadisticasJuego1(int &ganadas, int &empatadas, int &perdidas);

//Prototipos Voltear el Dado
void juego2(int &ganadas, int &perdidas);
void mostrarReglasDado();
void dibujoDado(int &superior, int &frontal, int &lateral, int &contador);
void eleccionJugador(int &opcion, int &superior, int &frontal, int &lateral, int &contador, bool &turno);
void bucleJuego(int &opcion, int &superior, int &frontal, int &lateral,int &contador, bool &turno);
void tiradaInicial(int &opcion, int &superior, int &frontal, int &lateral, int &contador, int &quienEmpieza, bool &turno);
void eleccionMaquina(int &superior, int &frontal, int &lateral, int &contador, bool &turno);
void mostrarEstadisticasJuego2(int &ganadas, int &perdidas);
int menuUsuario();

//Prototipos Portal de Juegos
int menuPortalJuegos();
bool usuarioRegistrado(string &usuario, string &contrasenaAux, bool &cargaOk);
bool contrasenaOk(string &contrasenaAux);
bool registrarUsuario(string &usuario, bool &cargaOk);
bool login();

//Main//
int main()
{
	int opcion, ganadasJuego1, ganadasJuego2, empatadas, perdidasJuego1, perdidasJuego2;
	ganadasJuego1 = 0, ganadasJuego2 = 0;
	empatadas = 0;
	perdidasJuego1 = 0, perdidasJuego2 = 0;
	if(login())
	{
		cout <<"           " << "------------------------------------------------" << endl;
		cout <<"           " << "|        BIENVENIDO AL PORTAL DE JUEGOS        |" << endl;
		cout <<"           " << "------------------------------------------------" << endl;
		cout << endl;
		opcion = menuPortalJuegos();
		do{
			switch(opcion)
			{
				case 1 : mostrarReglasJuego1();
						 cout << endl;
						 opcion = menuPortalJuegos();
						 break;
				case 2 : juego1(ganadasJuego1, empatadas, perdidasJuego1);
						 cout << endl;
						 opcion = menuPortalJuegos();
						 break;
				case 3 : mostrarReglasDado();
						 cout << endl;
						 opcion = menuPortalJuegos();
						 break;
				case 4 : juego2(ganadasJuego2, perdidasJuego2);
						 cout << endl;
						 opcion = menuPortalJuegos();
						 break;
				case 0 :
						 break;
			}
		}while(opcion!=0);

		mostrarEstadisticasJuego1(ganadasJuego1, empatadas, perdidasJuego1);
		cout << endl;
		mostrarEstadisticasJuego2(ganadasJuego2, perdidasJuego2);
		cout << endl;
		cout << "Hasta Pronto!" << endl;
	}
	else{
		mostrarEstadisticasJuego1(ganadasJuego1, empatadas, perdidasJuego1);
		cout << endl;
		mostrarEstadisticasJuego2(ganadasJuego2, perdidasJuego2);
		cout << endl;
		cout << "Hasta Pronto!" << endl;
		cout << "Saliendo del portal de juegos" << endl;
	}
	
	system("pause");
	return 0;
}

//Comprobacion de usuario//
bool usuarioRegistrado(string &usuario, string &contrasenaAux, bool &cargaOk)
{
	ifstream registro;
	string usuarioAux;
	bool usuarioExistente = false;

	//Introducimos usuario y comprobamos si existe
	registro.open("registro.txt");
	if(!registro.is_open())
	{
		cout << "Fallo en el sistema de ficheros" << endl;
		cargaOk = false;
	}
	else{
		cargaOk = true;
		cout << "Usuario: ";
		cin >> usuario;

		registro >> usuarioAux;
		registro >> contrasenaAux;
		while (usuarioAux != "XXX" && usuarioExistente == false) 
		{
			if (usuario == usuarioAux && usuario != "XXX")
			{
				usuarioExistente = true;
			}
			else{
				registro >> usuarioAux;
				registro >> contrasenaAux;
			}
		}
		registro.close();
	}

	return usuarioExistente;
}

//Comprobacion de contraseña//
bool contrasenaOk(string &contrasenaAux)
{
	string contrasena;
	int intentos = 1;
	bool correcto = true;
	cout << "Contrasena: ";
	cin >> contrasena;
	while (contrasena != contrasenaAux && intentos < 3) 
	{
		cout << "Contrasena: ";
		cin >> contrasena;
		if(contrasena != contrasenaAux)
		{
			intentos++;
		}
	}
	if (intentos == 3)
	{
		correcto = false;
		cout <<"Has fallado tres veces la contrasena, no tienes acceso al portal" << endl;
	}

	return correcto;
	
}

//Registrar nuevo usuario//
bool registrarUsuario(string &usuario, bool &cargaOk)
{
	bool comprobacion = true;
	if(cargaOk)
	{
		ifstream copiarRegistro, leerRegistro;
		ofstream actualizaRegistro, registroAux;
		string usuarioAux, contrasenaAux, contrasena;

		cout <<"Alta de nuevo usuario, cree una contrasena" << endl;
		cout << "Contrasena: ";
		cin >> contrasena;
		while(contrasena == "XXX")
		{
			cout << "Esta contrasena no es aceptada por el sistema, invente otra" << endl;
			cout << "Contrasena: ";
			cin >> contrasena;
		}
		leerRegistro.open("registro.txt");
		registroAux.open("auxiliar.txt");
		leerRegistro >> usuarioAux;
		leerRegistro >> contrasenaAux;
		while (usuarioAux != "XXX") 
		{
			if (usuarioAux != "XXX") 
			{
				registroAux << usuarioAux << endl;
				registroAux << contrasenaAux << endl;
			}
			leerRegistro >> usuarioAux;
			leerRegistro >> contrasenaAux;
		}
		registroAux << usuario << endl;
		registroAux << contrasena << endl;
		registroAux << "XXX" << endl;

		//Y metemos ahora los datos del registro auxiliar en el original
		actualizaRegistro.open("registro.txt");
		copiarRegistro.open("auxiliar.txt");
		copiarRegistro >> usuarioAux;
		copiarRegistro >> contrasenaAux;
		while (usuarioAux != "XXX") 
		{
			if (usuarioAux != "XXX") 
			{
				actualizaRegistro << usuarioAux << endl;
				actualizaRegistro << contrasenaAux << endl;
			}
			copiarRegistro >> usuarioAux;
			copiarRegistro >> contrasenaAux;
		}
		actualizaRegistro << "XXX" << endl;
		actualizaRegistro.close();
		copiarRegistro.close();

	}
	else{
		comprobacion = false;
	}

	return comprobacion;
}

//Login de usuario//
bool login()
{
	bool loginOk = true;
	bool cargaOk;
	string usuario, contrasenaAux;
	if(usuarioRegistrado(usuario, contrasenaAux,cargaOk))
	{
		if(!contrasenaOk(contrasenaAux))
		{
			loginOk = false;
		}
	}
	else{
		if(!registrarUsuario(usuario,cargaOk))
		{
			loginOk = false;
		}
	}
	
	return loginOk;
}

//Menu Portal de Juegos//
int menuPortalJuegos()
{
	int opcion;
	do{
		cout << "1. Ver instrucciones Piedra - Papel - Tijera - Lagarto - Spock" << endl;
		cout << "2. Jugar a Piedra - Papel - Tijera - Lagarto - Spock" << endl;
		cout << "3. Ver instrucciones Voltear el Dado" << endl;
		cout << "4. Jugar a Voltear el Dado" << endl;
		cout << "0. Salir del Portal de Juegos" << endl;
		cin >> opcion;
	}while((opcion < 0) || (opcion > 4));

	return opcion;
}

////////////////////////////////////////////
//Subprogramas juego Piedra Papel Tijera///
///////////////////////////////////////////


//Menu juego piedra papel tijera//
int menuJuego1()
{
	int opcion;

	do{
		cout << "Seleccione una opcion" << endl;
		cout << " 2 - Instrucciones " << endl;
		cout << " 1 - Jugar Partida" << endl;
		cout << " 0 - Salir del juego" << endl;
		cin >> opcion;
		cout << "Opcion : " << opcion << endl;
	}while((opcion < 0) || (opcion > 2));
	
	return opcion;
}

//Reglas del Piedra papel tijera//
void mostrarReglasJuego1()
{
	ifstream reglas;
	string texto;
	cout << "Instrucciones" << endl;
	reglas.open("reglasSpock.txt");
	if(!reglas.is_open())
	{
		cout << "No se ha podido abrir el fichero con las reglas!" << endl;
	}
	else{
		while(texto != "XXX")
		{
			getline(reglas, texto);
			if(texto != "XXX")
				cout << texto << endl;
		}
	}
	texto = "cadena vacia";
	reglas.close();

}

//Para elegir jugadas en el Piedra papel tijera//
int menuJugadasJuego1()
{
	int contador;
	do{
		cout << "Elige opcion" << endl;
		cout << "0 : piedra" << endl;
		cout << "1 : papel " << endl;
		cout << "2 : tijera " << endl;
		cout << "3 : lagarto" << endl;
		cout << "4 : spock" << endl;
		cout << "Introduzca un valor entre 0 y 4" << endl;
		cin >> contador;
	}while((contador < 0) || (contador > 4));
	
    return contador;
}

//Jugadas del piedra papel tijera del humano//
void jugadasJuego1(int &ganadas, int &empatadas, int &perdidas)
{
	tJugada jugadaH, jugadaM;
	jugadaM = jugadaMaquina();
	int contador = menuJugadasJuego1();
	jugadaH = tJugada(contador);

	switch(jugadaH)
	{
		
		case piedra :  cout << "Tu eleccion : piedra" << endl;
					   if(jugadaM == tijera)
					   {
						cout << "Mi eleccion : tijera" << endl;
						cout << ".............." << endl;
						cout << "Ganas tu" << endl; 
						ganadas++;
					   }
					   else if(jugadaM == lagarto)
					   {
						cout << "Mi eleccion : lagarto" << endl;
						cout << ".............." << endl;
						cout << "Ganas tu" << endl; 
						ganadas++;
					   }
					   else if(jugadaM == jugadaH)
					   {
						cout << "Mi eleccion : piedra" << endl;
						cout << ".............." << endl;
						cout << "Empate" << endl;
						empatadas++;
					   }
					   else if(jugadaM == spock)
					   {
						cout << "Mi eleccion : spock " << endl;
						cout << ".............." << endl;
						cout << "Gano yo" << endl;
						perdidas++;
					   }
					   else{
						cout << "Mi eleccion : papel " << endl;
						cout << ".............." << endl;
						cout << "Gano yo" << endl;
						perdidas++;
					   }
					   break;

		case papel :  cout << "Tu eleccion : papel" << endl;
					   if(jugadaM == piedra)
					   {
						cout << "Mi eleccion : piedra" << endl;
						cout << ".............." << endl;
						cout << "Ganas tu" << endl; 
						ganadas++;
					   }
					   else if(jugadaM == spock)
					   {
						cout << "Mi eleccion : spcok" << endl;
						cout << ".............." << endl;
						cout << "Ganas tu" << endl; 
						ganadas++;
					   }
					   else if(jugadaM == jugadaH)
					   {
						cout << "Mi eleccion : papel" << endl;
						cout << ".............." << endl;
						cout << "Empate" << endl;
						empatadas++;
					   }
					   else if(jugadaM == tijera)
					   {
						cout << "Mi eleccion : tijera " << endl;
						cout << ".............." << endl;
						cout << "Gano yo" << endl;
						perdidas++;
					   }
					   else{
						cout << "Mi eleccion : lagarto " << endl;
						cout << ".............." << endl;
						cout << "Gano yo" << endl;
						perdidas++;
					   }
					   break;

		case tijera :  cout << "Tu eleccion : tijera" << endl;
					   if(jugadaM == papel)
					   {
						cout << "Mi eleccion : papel" << endl;
						cout << ".............." << endl;
						cout << "Ganas tu" << endl; 
						ganadas++;
					   }
					   else if(jugadaM == lagarto)
					   {
						cout << "Mi eleccion : lagarto" << endl;
						cout << ".............." << endl;
						cout << "Ganas tu" << endl; 
						ganadas++;
					   }
					   else if(jugadaM == jugadaH)
					   {
						cout << "Mi eleccion : tijera" << endl;
						cout << ".............." << endl;
						cout << "Empate" << endl;
						empatadas++;
					   }
					   else if(jugadaM == spock)
					   {
						cout << "Mi eleccion : spock " << endl;
						cout << ".............." << endl;
						cout << "Gano yo" << endl;
						perdidas++;
					   }
					   else{
						cout << "Mi eleccion : piedra " << endl;
						cout << ".............." << endl;
						cout << "Gano yo" << endl;
						perdidas++;
					   }
					   break;

		case lagarto :  cout << "Tu eleccion : lagarto" << endl;
					    if(jugadaM == spock)
					    {
						 cout << "Mi eleccion : spock" << endl;
						 cout << ".............." << endl;
						 cout << "Ganas tu" << endl; 
						 ganadas++;
					    }
					    else if(jugadaM == papel)
					    {
						 cout << "Mi eleccion : papel" << endl;
						 cout << ".............." << endl;
						 cout << "Ganas tu" << endl; 
						 ganadas++;
					    }
					    else if(jugadaM == jugadaH)
					    {
						 cout << "Mi eleccion : lagarto" << endl;
						 cout << ".............." << endl;
						 cout << "Empate" << endl;
						 empatadas++;
					    }
					    else if(jugadaM == tijera)
					    {
						 cout << "Mi eleccion : tijera " << endl;
						 cout << ".............." << endl;
						 cout << "Gano yo" << endl;
						 perdidas++;
					    }
					    else{
						 cout << "Mi eleccion : piedra " << endl;
						 cout << ".............." << endl;
						 cout << "Gano yo" << endl;
						 perdidas++;
					    }
					    break;

		case spock :  cout << "Tu eleccion : spock" << endl;
					   if(jugadaM == tijera)
					   {
						cout << "Mi eleccion : tijera" << endl;
						cout << ".............." << endl;
						cout << "Ganas tu" << endl; 
						ganadas++;
					   }
					   else if(jugadaM == piedra)
					   {
						cout << "Mi eleccion : piedra" << endl;
						cout << ".............." << endl;
						cout << "Ganas tu" << endl; 
						ganadas++;
					   }
					   else if(jugadaM == jugadaH)
					   {
						cout << "Mi eleccion : spock" << endl;
						cout << ".............." << endl;
						cout << "Empate" << endl;
						empatadas++;
					   }
					   else if(jugadaM == lagarto)
					   {
						cout << "Mi eleccion : lagarto " << endl;
						cout << ".............." << endl;
						cout << "Gano yo" << endl;
						perdidas++;
					   }
					   else{
						cout << "Mi eleccion : papel " << endl;
						cout << ".............." << endl;
						cout << "Gano yo" << endl;
						perdidas++;
					   }
					   break;

		default :      cout << "Jugada no valida";
	}
}

//Jugadas de la maquina del piedra papel tijera
tJugada jugadaMaquina()
{
	tJugada maquina;
	int i = rand()%5;
	maquina = tJugada(i);

	return maquina;
}

//Juego piedra papel tijera//
void juego1(int &ganadas, int &empatadas, int &perdidas)
{
	cout <<"           " << "---------------------------------------------------" << endl;
	cout <<"           " << "|        PIEDRA PAPEL TIJERA LAGARTO SPOCK        |" << endl;
	cout <<"           " << "---------------------------------------------------" << endl;
	cout << endl;
	int opcion;
	bool jugar = true;
	do{
		opcion = menuJuego1();
		switch(opcion)
		{
			case 2 : mostrarReglasJuego1();
					 cout << endl;
					 break;

			case 1 : jugadasJuego1(ganadas, empatadas, perdidas);
					 jugar = false;
					 break;

			case 0 : cout << "Saliendo del juego" << endl;
					 break;
		}
	}while((opcion != 0) &&(jugar));
	
}

//Muestra estadisticas del piedra papel tijera
void mostrarEstadisticasJuego1(int &ganadas, int &empatadas, int &perdidas)
{
	int partidasTotales = ganadas + empatadas + perdidas;
	cout << "Partidas Piedra - Papel - Tijera - Lagarto - Spock : " << partidasTotales << endl;
	cout << "Partidas ganadas : " << ganadas << endl;
	cout << "Partidas empatadas : " << empatadas << endl;
	cout << "Partidas perdidas : " << perdidas << endl;
}


//////////////////////////////////////////
//Subprogramas juego Voltear el Dado//////
//////////////////////////////////////////

//Mostrar Reglas volterar el dado//
void mostrarReglasDado()
{
	 ifstream reglasDados;
	 string textoDados;

	 cout << "Instrucciones" << endl;
	 reglasDados.open("reglasDados.txt");
	 if(!reglasDados.is_open())
	 {
		cout << "No se ha podido abrir el fichero con las reglas!" << endl;
	 }
	 else{
		while(textoDados != "XXX")
		{
			getline(reglasDados, textoDados);
			if(textoDados != "XXX")
				cout << textoDados << endl;
		}
	 }
	textoDados = "cadena vacia";
    reglasDados.close();
}

///////////////////////
////dibujo del dado////
///////////////////////
void dibujoDado(int &superior, int &frontal, int &lateral, int &contador) 
{
		cout << "   -----" << endl;
		cout << " / " << superior << "   /| "<< endl;
		cout << " ---- /" << lateral<< "/" << endl;
		cout << "| " << frontal <<"  | /     " << "Contador = " << contador << endl;
		cout << " ---- /" << endl;
}


//////////////////////////
////Menu de usuario///////
//////////////////////////
int menuUsuario()
{
	int opcion;
	do{
		cout << "Tu turno" << endl;
		cout << "Selecciona opcion" << endl;
		cout << "0. Norte" << endl;
		cout << "1. Sur" << endl;
		cout << "2. Este" << endl;
		cout << "3. Oeste" << endl;
		cout << "4. Ver instrucciones" << endl;
		cout << "5. Salir del juego" << endl;
		cin >> opcion;
	}while((opcion < 0) || (opcion > 5));
	
	return opcion;
}

//////////////////////////
////Elección del jugador//
//////////////////////////
void eleccionJugador(int &perdidas, int &opcion, int &superior, int &frontal, int &lateral, int &contador, bool &turno) 
{
	tDireccion dir;
	int aux;
	bool salir = false;
	opcion = menuUsuario();
	while((opcion >= 4) && (!salir))
	{
		switch(opcion)
		{
			case 4:	mostrarReglasDado(); 
					cout << endl;
					break;

			case 5:  cout << "Saliendo del juego" << endl;
					 salir = true;
					 break;
		}
		if(opcion != 5)
		{
			opcion = menuUsuario();
		}	
	}

	dir = tDireccion(opcion);
	switch(dir) 
	{
		case N:
			aux = superior; superior = frontal; frontal = 7 - aux;
			cout << "Tu eleccion es Norte" << endl;
			break;
		case S:
			aux = frontal; frontal = superior; superior = 7 - aux;
			cout << "Tu eleccion es Sur" << endl;
			break;
		case E:
			aux = lateral; lateral = superior; superior = 7 - aux;
			cout << "Tu eleccion es Este" << endl;
			break;
		case O:
			aux = superior; superior = lateral; lateral = 7 - aux;
			cout << "Tu eleccion es Oeste" << endl;
			break;
	}

	if(opcion != 5)
	{
		contador = contador + superior;
		dibujoDado(superior, frontal, lateral, contador);
	}
	
	if (contador < 50) 
	{
			turno = false;
	}
	else {
		cout << "Has perdido!" << endl;
		perdidas++;
	}
}


//////////////////////////////
////Elección de la máquina////
//////////////////////////////
void eleccionMaquina(int &ganadas, int &superior, int &frontal, int &lateral, int &contador, bool &turno) 
{
	int aux;
	cout << "Turno maquina" << endl;
	if (frontal == 1) 
	{
		cout << "Maquina ha elegido Norte" << endl;
		aux = superior; superior = frontal; frontal = 7 - aux;
	}
	else if ((7 - frontal) == 1) 
	{
		cout << "Maquina ha elegido Sur" << endl;
		aux = frontal; frontal = superior; superior = 7 - aux;
	}
	else if ((7 - lateral) == 1) 
	{
		cout << "Maquina ha elegido Este" << endl;
		aux = lateral; lateral = superior; superior = 7 - aux;
	}
	else if (lateral == 1) 
	{
		cout << "Maquina ha elegido Oeste" << endl;
		aux = superior; superior = lateral; lateral = 7 - aux;
	}
	else if (frontal == 2) 
	{
		cout << "Maquina ha elegido Norte" << endl;
		aux = superior; superior = frontal; frontal = 7 - aux;
	}
	else if ((7 - frontal) == 2) 
	{
		cout << "Maquina ha elegido Sur" << endl;
		aux = frontal; frontal = superior; superior = 7 - aux;
	}
	else if ((7 - lateral) == 2) 
	{
		cout << "Maquina ha elegido Este" << endl;
		aux = lateral; lateral = superior; superior = 7 - aux;
	}
	else if (lateral == 2) 
	{
		cout << "Maquina ha elegido Oeste" << endl;
		aux = superior; superior = lateral; lateral = 7 - aux;
	}
	contador = contador + superior;
	dibujoDado(superior, frontal, lateral, contador);
	if (contador < 50) 
	{
		turno = true;
	}
	else {
		cout << "Has ganado!" << endl;
		ganadas++;
	}
}

///////////////////////
////Bucle del juego////
///////////////////////
void bucleJuego(int &ganadas, int &perdidas, int &opcion, int &superior, int &frontal, int &lateral,int &contador, bool &turno) 
{
	while((contador < 50) && (opcion != 5))
	{
		if (turno == true) 
		{
			eleccionJugador(perdidas, opcion, superior, frontal, lateral, contador, turno);
		}
		else {
			eleccionMaquina(ganadas, superior, frontal, lateral, contador, turno);
		}			
	}
}

//////////////////////
////Tirada inicial////
//////////////////////
void tiradaInicial(int &ganadas, int &perdidas, int &opcion, int &superior, int &frontal, int &lateral, int &contador, int &quienEmpieza, bool &turno) 
{
	int tiradaMaquina = rand()%5;
	switch (tiradaMaquina) 
	{
		case 0: 
			superior = 1; frontal = 2; lateral = 3; 			
			break;
		case 1:
			superior = 2; frontal = 6; lateral = 3;
			break;
		case 2:
			superior = 3; frontal = 2; lateral = 6;
			break;
		case 3: 
			superior = 4; frontal = 6; lateral = 2;
			break;
		case 4: 
			superior = 5; frontal = 3; lateral = 6;
			break;
		case 5: 
			superior = 6; frontal = 3; lateral = 2;
			break;
	}
	contador = superior;
	dibujoDado(superior, frontal, lateral, contador);
	
	if(quienEmpieza == 1)
	{
		turno = true;
	}
	else{
		turno = false;
	}
	bucleJuego(ganadas, perdidas, opcion, superior, frontal, lateral, contador, turno);

}

//Juego de voltear el dado//
void juego2(int &ganadas, int &perdidas)
{
	srand(time(NULL));
	int tiradaMaquina = rand()%5;
	int contador = 0;
	int superior, frontal, lateral;
	int opcion;
	bool turno;
	int eleccionQuienEmpieza = rand()%2;
	cout <<"           " << "--------------------------------" << endl;
	cout <<"           " << "|        VOLTEAR EL DADO       |" << endl;
	cout <<"           " << "--------------------------------" << endl;
	cout << endl;
	//Tirada de humano
	if (eleccionQuienEmpieza == 1) 
	{
		turno = true;
		tiradaInicial(ganadas, perdidas, opcion, superior, frontal, lateral, contador, eleccionQuienEmpieza, turno);

	}
			
	//Tirada maquina
	else {     
		turno = false;
		tiradaInicial(ganadas, perdidas, opcion, superior, frontal, lateral, contador, eleccionQuienEmpieza, turno);
	}
}

//Estadisticas Voltear el Dado//
void mostrarEstadisticasJuego2(int &ganadas, int &perdidas)
{
	int partidasTotales = ganadas + perdidas;
	cout << "Partidas totales Voltear el Dado : " << partidasTotales << endl;
	cout << "Partidas ganadas : " << ganadas << endl;
	cout << "Partidas perdidas : " << perdidas << endl;
}
