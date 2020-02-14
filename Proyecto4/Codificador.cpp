//Codificador.cpp
#include "Codificador.h"
#include <string>

Codificador::Codificador()
{
	auxF = new CircDobList<Frase>(0);
	if (!cargarArchivo((char*)"char.in"))
		return;
	
	codificado = false; //se carga decodificado
	procesar((char*)"char.in", (char*)"incode.out");

	
}//Codificador()

void Codificador::procesar(char nomArch[30], char nom2[30])
{
	cout << "IMPRESION DE MAPAS DE CODIFICACION: " << endl << endl;
	imprimirCP();
	cout << "----------------------------------------------" << endl << endl;

	cout << "IMPRESION DE FRASES CARGADAS EN " << nomArch << ":" << endl << endl;

	imprimirFrases();

	codificar();

	cout << "----------------------------------------------" << endl << endl;
	cout << "IMPRESION DE LO CODIFICADO: " << endl << endl;
	imprimirFrases();
	cout << endl;

	bool guardado;
	guardado = escribirArchivo((char*)nom2);
	if (guardado)
		cout << "GUARDADO CORRECTAMENTE EN " << nom2 << endl;
	else
		cout << "PROBLEMA AL GUARDAR EN " << nom2 << endl;
}//procesar(char nomArch[30])

bool Codificador::cargarArchivo(char nombre[30])
{
	bool valido = true, privez; //privez = primera vez
	privez = (auxF->getQuantity() == 0 ? true : false);

	//abro el archivo
	if (arch.EstaAbierto())
		arch.Cerrar();
	arch.CambiarNom(nombre);
	
	valido = arch.AbrirT(ios::in); //true = cargado correctamente, false = error.
	if (!valido)
		return false;

	if (!privez)
	{
		delete auxF;
		auxF = new CircDobList<Frase>(0);
	}
	if (privez) //carga archivo con casos de prueba
		valido = cargarCP();
	else //cargar archivo que va a codificar
		valido = cargarFrasCodif();

	arch.Cerrar();

	if (!valido)
		delete auxF;

	return valido;
}//cargarArchivo(char nombre[30])

bool Codificador::cargarCP()
{
	//verifico si la primera linea del archivo es un numero
	bool valido = true;
	char leido[180];
	arch.Leer(leido);
	if (isdigit(leido[0]) && (leido[1] == '\0' || (isdigit(leido[1] && leido[2] == '\0'))))
	{
		tCasoPrue = atoi(leido);
		if (tCasoPrue <= 0 || tCasoPrue > 10)
			valido = false;
	}//if numero de casos de prueba
	if (!valido)
	{
		cout << "Numero de casos de prueba no es valido." << endl;
		return valido;
	}//else si no es un numero, o si no esta entre 1<=N<=10

	//cargo los mapas de los casos de prueba, y las primeras frases a codificar
	cp = new List<MapaCod>;
	if (cp == NULL)
	{
		cout << "Error al cargar memoria para casos de prueba." << endl;
		return false;
	}

	char leidoaux[180];
	for (int i = 1; i <= tCasoPrue; i++)
	{
		MapaCod var(i, true);
		arch.Leer(leido);
		arch.Leer(leidoaux);
		if (strlen(leido) != strlen(leidoaux))
		{
			valido = false;
			cout << "C.P. " << i << ": Longitud de las cadenas S y T no es igual." << endl;
			break;
		}
		int j = 0;
		while (j < 180 && leido[j] != '\0')
		{
			carCod car;
			car.carNor = leido[j];
			if (var.caracteres->seek(car) == 1)
			{
				valido = false;
				cout << "C.P. " << i << ": caracter de la cadena \"S\" repetido." << endl;
				break;
			}//if
			car.carCodi = leidoaux[j];
			var.caracteres->add(car);
			j++;
		}//while

		valido = cp->add(var);
		if (!valido)
		{
			cout << "Posiblemente error de memoria al guardar." << endl;
			break;
		}

		arch.Leer(leido);

		Frase frase(i, leido);
		auxF->add(frase);
		frase.frase = 0;
		var.caracteres = 0;
	}//for 

	if (!valido)
	{
		delete cp;
		delete auxF;
		cp = NULL;
	}
	return valido;
}//cargarCP()

void Codificador::codificar()
{
	if (!codificado)
		codificarUno();
	else
		codificarDos();
	
	codificado = true;
}//void codificar()

void Codificador::codificarUno()
{
	auxF->reset();
	int nFrases = auxF->getQuantity();
	carCod carC;
	MapaCod mapita;
	Frase fras;
	for (int i = 0; i < nFrases; i++)
	{
		mapita.casoPrueba = i + 1;
		fras = auxF->getCurrent();
		if (cp->seek(mapita) == 1)
		{
			int j = 0, nCaracteres = fras.frase->getQuantity();
			string str = fras.getString();
			while (j < nCaracteres)
			{
				carC.carNor = str[j];
				if (mapita.caracteres->seek(carC) == 1)
				{
					str[j] = carC.carCodi;
				}//if
				j++;
			}//while
			fras.setString(str);
			auxF->setCurrent(fras);
		}//if
		auxF->move(1);
	}//for
	fras.frase = NULL;
	mapita.caracteres = NULL;
}//codificarUno()

void Codificador::codificarDos()
{
	auxF->reset();
	int totalCP = cp->getQuantity();
	int nFrases = auxF->getQuantity();
	carCod carC;
	MapaCod mapita;
	Frase fras;
	for (int i = 0; i < nFrases; i++)
	{
		fras = auxF->getCurrent();
		int j = 0, nCaracteres = fras.frase->getQuantity();
		string str = fras.getString();
		while (j < nCaracteres)
		{
			mapita.casoPrueba = ((int)(str[j] % totalCP)) + 1; //no estoy seguro de la suma
			if (cp->seek(mapita) == 1)
			{
				carC.carNor = str[j];
				if (mapita.caracteres->seek(carC) == 1)
				{
					str[j] = carC.carCodi;
				}//if
			}//if encontrado
			j++;
		}//while
		fras.setString(str);
		auxF->setCurrent(fras);
		auxF->move(1);
	}//for
	fras.frase = NULL;
	mapita.caracteres = NULL;
}//codificarDos()

bool Codificador::escribirArchivo(char nombre[30])
{
	Archivo<char*>archG(nombre);
	if (!archG.AbrirT(ios::out))
		return false;

	int cantFrases = auxF->getQuantity() + 1;
	auxF->reset();

	Frase fras;
	int i = 1, a;
	do
	{
		fras.numFrase = i;
		a = auxF->seek(fras);

		if (a == 1) //encontrado
		{
			archG.EscribirTXT(fras.getString());
			archG.TXT_NL();
		}
		i++;
	} while (a == 1);
	
	fras.frase = NULL;
	archG.Cerrar();
	return true;
}//escribirArchivo(char nombre[30])

bool Codificador::cargarFrasCodif()
{
	char leido[180];
	int i = 1;
	while (true)
	{
		arch.Leer(leido);
		if (arch.Es_Fin())
			break;
		Frase frase(i, leido);
		if (auxF->add(frase) == 0)
			return false;
		frase.frase = 0;
		i++;
	}//while para carga de nuevas frases
	return true;
}//cargarFrasCodif()

void Codificador::imprimirCP() {
	MapaCod mapa;
	int i = 1, a;
	do
	{
		mapa.casoPrueba = i;
		a = cp->seek(mapa);
		
		if (a == 1) //encontrado
		{
			cout << i << ": ";
			mapa.caracteres->print();
			cout << endl;
		}
		i++;
	} while (a == 1);
	cout << endl;
	mapa.caracteres = NULL;
}//imprimirCP()

void Codificador::imprimirFrases()
{
	Frase fras;
	int i = 1, a;
	do
	{
		fras.numFrase = i;
		a = auxF->seek(fras);

		if (a == 1) //encontrado
		{
			cout << i << ": ";
			fras.frase->print();
			cout << endl;
		}
		i++;
	} while (a == 1);
	cout << endl;
	fras.frase = NULL;
}//imprimirFrases()
