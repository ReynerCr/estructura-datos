//main.h
/* 
 + MATERIA: Estructura de datos.
 + AUTORES:
 + Contreras Reyner; C.I: V 26934400;   seccion 2
 + Llanes John; C.I: V 30853320;   seccion 2
*/

#include <iostream>
#include <cstdlib>
#include <locale.h>
#include "Alumno.h"
#include "Carrera.h"
#include "Materia.h"
#include "Archivo.h"
#include "Inscrito.h"

using namespace std;

//FUNCIONES AUXLIARES
Alumno buscarAlumno(unsigned int ced) {
	Alumno al(ced, (char *)"", 0);
	Archivo<Alumno>obj((char * )"Alumnos.dat", transfAlumno);
	obj.AbrirT(ios::in|ios::binary);
	bool encontrado = false;
	
	if (!obj.Falla())
	{
		encontrado = obj.Buscar_Simple(al);
	}
	else
	{
		cout<<"Hubo un problema al abrir Alumnos.dat"<<endl;
	}
	
	if (obj.EstaAbierto())
	{
		obj.Cerrar();
	}
	
	if(!encontrado)
		al = Alumno(0, (char *)"", 0);
	
	return al;
}//bool buscarAlumno(unsigned int)

Carrera buscarCarrera(int codigo) {
	Carrera carr(codigo, (char *)"");
	
	Archivo<Carrera>obj((char * )"Carrera.dat", transfCarrera);
	obj.AbrirT(ios::in|ios::binary);
	bool encontrado = false;
	
	if (!obj.Falla())
	{
		encontrado = obj.Buscar_Simple(carr);
	}
	else
	{
		cout<<"Hubo un problema al abrir Carrera.dat"<<endl;
	}
	
	if (obj.EstaAbierto())
	{
		obj.Cerrar();
	}
	
	if (!encontrado)
		carr = Carrera(0, (char*)"");
	return carr;
}//bool buscarCarrera(int)

void gotoxy(int x,int y)
{
	HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hCon,dwPos);
}

Materia buscarMateria(int codigo) {
	bool encontrado = false;
	Materia mat(0, codigo, (char *)"", 0);
	Carrera car = buscarCarrera(codigo/100);
	
	if (car.getCodigo() != 0) {
		
		char pal[15]; itoa((codigo/100), pal, 10);
		strcat(pal, ".dat");
		Archivo<Materia>obj((char *)pal, transfMateria);
		obj.AbrirT(ios::in|ios::binary);
		
		if (!obj.Falla())
		{
			encontrado = obj.Buscar_Simple(mat);
		}
		else
		{
			cout<<"Hubo un problema al abrir "<<pal<<endl;
		}
		
		if (obj.EstaAbierto())
		{
			obj.Cerrar();
		}
	}//si buscarCarrera es verdadero
	
	if (!encontrado)
		mat = Materia(0, 0, (char*)"", 0);
	return mat;
}//bool buscarMateria(int)
//FIN FUNCIONES AUXILIARES
//-------------------------------------

//FUNCIONES DEL SWITCH EN EL MAIN
void agregarAlumno()
{
	Archivo<Alumno>obj1((char*)"Alumnos.dat", transfAlumno);
	obj1.AbrirT(ios::in|ios::out|ios::binary|ios::app);
	
	unsigned int ced;
	int cedd;
	cout<<"|--------------------<Nuevo alumno>----------------------|"<<endl;
	cout<<"Ingrese cedula: "; cin>>cedd;
	ced = cedd;
	if (!cin.fail() && cedd > 0 && ced < 40000000)
	{
		if (!obj1.Falla())
		{
			Alumno alumno;
			alumno.setCedula(ced);
		
			if(obj1.Buscar_Simple(alumno))
			{
				cout<<"Cedula ya existe en el registro, volvera al menu."<<endl;
			}
			else
			{
				alumno.cargarAlumno();
				Carrera carr = buscarCarrera(alumno.getCarrera());
				if (carr.getCodigo() != 0)
				{
					obj1.EscribirBi(alumno);
					cout<<"Alumno registrado satisfactoriamente."<<endl;
				}
				else
				{
					cout<<"No existe una carrera con ese codigo, volvera al menu principal."<<endl;
				}
			}//else de cedula no registrada
		}//if obj1 no fallo al abrir
		else {
			cout<<"Hubo un problema al abrir Alumnos.dat"<<endl;
			if (obj1.EstaAbierto())
					obj1.Cerrar();
			obj1.AbrirT(ios::out|ios::binary);
			obj1.Cerrar();
		}
	}//if ced ingresada es un numero mayor a 0 y menor a 40000000
	else
	{
		cin.clear();
		cout<<"No es una cedula valida. Cedula debe ser un numero entre 0 y 40000000."<<endl;
	}
	
	if (obj1.EstaAbierto())
		obj1.Cerrar();
	//ordenar alumnos	
	Archivo<Alumno>obj((char*)"Alumnos.dat", transfAlumno);
	obj.AbrirT(ios::in|ios::binary|ios::out);
	obj.Ordenar();
	obj.Cerrar();	
}//agregarAlumno()

void consultarAlumno(int cedd) {
	unsigned int ced = cedd;
	if (cedd < 0 || ced >= 40000000)
	{
		cout<<"No es una cedula valida. Cedula debe ser un numero entre 0 y 40000000."<<endl;
	}//if cedula no es valida
	else
	{
		Alumno alumno = buscarAlumno(ced);
	    if(alumno.getCedula() != 0)
		{
			cout<<alumno<<endl;
		}
	    else
		{
		  cout<<"La cedula no se encuentra en el registro."<<endl;	
		} 
	}//else cedula es valida
	
}//void consultarAlumno()

void consultarAsignatura(int codigo)
{
	Materia mat = buscarMateria(codigo);
	if(mat.getCodigo() != 0)
	{
  		cout<<mat<<endl;
	}
	else
	{
		cout<<"La materia no se encuentra en el registro."<<endl;
	}
}//void consultarAsignatura(int)

void mostrarDatosEstudiantes()
{
	Archivo<Alumno>obj((char*)"Alumnos.dat", transfAlumno);
	obj.AbrirT(ios::in|ios::binary|ios::out);
	obj.MostrarBi();
	obj.Cerrar();	
}

void pensumCarreraIncri(int codigo)
{
	Carrera carrAux = buscarCarrera(codigo);
	if (carrAux.getCodigo() != 0) {
		char palabra[15];
		itoa(codigo, palabra, 10);
		strcat(palabra, ".dat");
		Archivo<Materia>obj3((char *)palabra, transfMateria);
		int cont=0;Materia a;
		obj3.AbrirT(ios::binary|ios::in|ios::app);
		if (obj3.Falla())
		{
			cout<<"Hubo un problema al abrir"<<palabra<<endl;
		}
		else
		{
			cout<<"Pensum de "<<carrAux.getNombreC()<<":"<<endl;
			cout<<"|<Semestre>---<Codigo>---<UC>---<Nombre>---------------|"<<endl;
			for(int i=0;i<obj3.getTotalObj();)
			{
				obj3.LeerBi(i);
				a=obj3.Get_buf();
				cout<<"|----<"<<a.getSemestre()<<">------<"<<a.getCodigo()<<">---<"
				<<a.getUC()<<">---<"<<a.Get_nombreM()<<">"<<endl;
				i++;
			}
		}//si no fallo al abrir obj3
		
		if (obj3.EstaAbierto())
			obj3.Cerrar();
	}
	else
	{
		cout<<"Carrera no existe en los registros."<<endl;
	}//si no consiguio el codigo de carrera
}//void pensumCarrera(int);


void inscripcion()
{
	unsigned int ced;
	int auxI = ced,cont=0;
	cout<<"|------------------<Inscripcion alumno>----------------|"<<endl;
	cout<<"Ingrese la cedula: "; cin>>ced;
	if (cin.fail() || auxI < 0 || ced >= 40000000)
	{
		cout<<"No es una cedula valida. Cedula debe ser un numero entre 0 y 40000000."<<endl;
		cin.clear();
	}//si cedula no es valida
	else
	{
		Alumno alumn = buscarAlumno(ced);
		if (alumn.getCedula() != 0)
		{
			Carrera carr = buscarCarrera(alumn.getCarrera());
			if (carr.getCodigo() != 0)
			{
				cout<<endl<<"Estudiante de "<<carr.getNombreC()<<"."<<endl;
				Archivo<Inscrito>obj((char *)"Inscritos.dat", transfInscrito);
				Inscrito insc(ced, (char*)"", 0);
				obj.AbrirT(ios::in|ios::out|ios::app|ios::binary);
				if (!obj.Falla() && !obj.Buscar_Simple(insc))
				{
					char aux[10], aux2[4], materias[7][3];
					//de aqui en adelante auxI sera un contador para el numero de materias incritas
					//ced se utilizara como un auxiliar mas
					for (auxI = 0; auxI < 7; auxI++)
					{
						materias[auxI][2] = '\0';
					}
					itoa(carr.getCodigo(), aux, 10);
					strcat(aux, ".dat");
					Archivo<Materia>obj2((char*)aux, transfMateria);
					obj2.AbrirT(ios::in|ios::binary);
					if (!obj2.Falla())
					{
						Materia mat = Materia();
						pensumCarreraIncri(alumn.getCarrera());
						cout<<endl<<"Ingrese los ultimos dos digitos de los codigos de las asignaturas"<<endl;
					    cout<<"que vaya a registrar, pulsando enter entre cada materia."<<endl<<endl;
						cout<<"Recuerde que minimo debe inscribir 3 UC, y maximo 12 UC."<<endl
							<<"Maximo de asignaturas que puede inscribir es de 7."<<endl<<endl;
						
						int sumUC = 0;
						auxI = 0;
						do {
							cin.ignore(1000, '\n');cont++;
							cout<<cont<<". "; cin.getline(aux2, 4, '\n');
							if (cin.fail() || atoi(aux2) >= 100)
							{
								cout<<"Codigo no valido."<<endl<<endl;
								cin.clear();
								cin.ignore(1000, '\n');
							}//codigo no valido
							else
							{
								aux[0] = '\0';
								itoa(carr.getCodigo(), aux, 10);
								strcat(aux, aux2);
								mat.setCodigo(atoi(aux));
								if (obj2.Buscar_Simple(mat))
								{
									if (sumUC + mat.getUC() <= 12 && auxI < 7)
									{
										ced = 0;
										while(ced < auxI)
										{
											if (strcmp(aux2, materias[ced]) == 0)
											{
												break;
											}
											ced++;
										}//while para comprobar que no se repita mat inscrita
										if (ced == auxI)
										{
											sumUC += mat.getUC();
											strcpy(materias[auxI], aux2);
											cout<<"Inscrita."<<endl;
											auxI++;
										}//if materia no se repite en liste
										else
										{
											cout<<"Materia ya cargada en la lista para inscribir."<<endl;
										}//else materia se repitio en lista
									}//if sumatoria de uc < 12
									else if (auxI >= 7)
									{
										cout<<"Limite de materias a inscribir es de 7."<<endl;
										break;
									}//si sumUC > 12
									else
									{
										cout<<"No se pudo inscribir esa materia debido a que "
											<<"la sumatoria de UC seria mayor a 12."<<endl;
									}
								}//materia encontrada
								else
								{
									cout<<"No existe esa materia."<<endl;	
								}//no encontrada materia
							}//cuando codigo es valido (codigo<100)
							
							cout<<"UC inscritas hasta el momento: "<<sumUC<<endl;
							if (sumUC < 12)
							{
								cout<<"Desea continuar con la inscripcion? 0=no, 1=si    Respuesta: ";
								while(!(cin>>ced) || (ced != 0  && ced != 1))
								{
									cin.clear();
  									cin.ignore(1000, '\n');
  									cout<<"Respuesta no valida, reingrese: ";
								} //reutilizo ced como auxiliar
								cout<<endl<<endl;
							}
							else
							{
								ced = 0;
							}
						} while (sumUC < 12 && ced != 0);
						
						if (sumUC < 3 || sumUC > 12)
						{
							cout<<"No se pudo inscribir debido a que no cumplia con el min/max "
								<<"de UC inscritas."<<endl;
						}//if cuando no se pudo inscribir
						else
						{
							char matsJuntas[15];
							matsJuntas[0] = '\0';
							cout<<"Finalizada la inscripcion, estas son las materias que inscribio:"<<endl;
							for (ced = 0; ced < auxI; ced++) //reutilizo ced como iterador
							{
								strcat(matsJuntas, materias[ced]);
								itoa(carr.getCodigo(), aux, 10);
								strcat(aux, materias[ced]);
								mat.setCodigo(atoi(aux));
								obj2.Buscar_Simple(mat);
								cout<<mat<<endl;
							}
							
							//muestro los datos del alumn que se estaba inscribiendo
							//de modo que pueda verificar y decidir si esta bien el registro o no
							insc = Inscrito(alumn.getCedula(), matsJuntas, sumUC); //FALTA VALIDAR QUE NO REPITA ASIGNATURAS EN LA MISMA LISTA
							cout<<"Datos del alumno: "<<insc<<endl<<endl;
							cout<<"Esta seguro de que desea continuar con la inscripcion?"<<endl 
								<<"0=no   1=si    Respuesta:";
							while (!(cin>>ced) || (ced != 0 && ced != 1))
							{
								cin.clear();
  								cin.ignore(1000, '\n');
  								cout<<"Respuesta no valida, reingrese: ";	
							}
							if (ced == 1)
							{
								obj.EscribirBi(insc);
								cout<<"Alumno inscrito."<<endl;
								obj.Ordenar();
							}
							else
							{
								cout<<"Alumno no inscrito.";
							}
						}//else para cuando se pudo inscribir
					}//si archivo se pudo abrir correctamente
					else
					{
						cout<<"Hubo un problema al abrir archivo de materias."<<endl;
					}//if no se pudo abrir archivo
					
					if (obj2.EstaAbierto())
						obj2.Cerrar();
				}//if no encontrado en lista de inscritos
				else if (obj.Falla())
				{
					cout<<"Hubo un problema al abrir Inscritos.dat"<<endl;
					if (obj.EstaAbierto())
						obj.Cerrar();
					obj.AbrirT(ios::out|ios::binary);
				}//if fallo al abrir Inscritos.dat
				else
				{
					cout<<"No puede inscribirse dos veces en un mismo semestre."<<endl;
				}//if encontrado en lista de inscritos
				
				if (obj.EstaAbierto())
					obj.Cerrar();
			}//si al obtener codigo es diferente a 0 es que lo consiguio
			else
			{
				cout<<"Cedula registrada pero la carrera no existe. ERROR."<<endl;
			}//cuando la carrera no coincide pero nombre si, error de archivo
		}//cuando es diferente de 0 es que lo consiguio
		else
		{
			cout<<"Alumno no registrado, antes de inscribirse primero registrese."<<endl;
		}//alumno no registrado
	}//else cedula es valida

}//void inscripcion()

void mostrarDatosInscripcion()
{
	Archivo<Inscrito>obj((char*)"Inscritos.dat", transfInscrito);
	obj.AbrirT(ios::in|ios::binary|ios::out);
	obj.MostrarBi();
	obj.Cerrar();
}

void consultarInscripcion(int cedd)
{
	unsigned int ced = cedd;
	if (cedd > 0 && cedd < 40000000)
	{
		Inscrito insc(ced, (char*)"", 0);
		Archivo<Inscrito>obj((char*)"Inscritos.dat", transfInscrito);
		obj.AbrirT(ios::in|ios::binary);

		if (obj.Buscar_Simple(insc))
		{
			cout<<insc<<endl;
		}
		else
		{
			Alumno al = buscarAlumno(ced);
			if (al.getCedula() != 0){
				cout<<"Alumno no inscrito."<<endl;
			}
			else
			{
				cout<<"Alumno no registrado."<<endl;
			}
		}//else no consiguio alumno en Inscritos.dat

		if (obj.EstaAbierto())
			obj.Cerrar(); 
	}//if cedula es valida
	else
	{
		cout<<"No es una cedula valida. Cedula debe ser un numero entre 0 y 40000000."<<endl;
	}//else cedula no es valida
}//void consultarInscripcion(int cedd)

void consultInscAsig(int codigo) //FALTA ORDENAR POR CEDULA PERO ESO SE HACE EN LOS ARCHIVOS
{
	Materia mat = buscarMateria(codigo);
	if (mat.getCodigo() != 0)
	{
		Archivo<Inscrito>obj1((char*)"Inscritos.dat", transfInscrito);
		obj1.AbrirT(ios::in|ios::binary);
		cout<<"Alumnos inscritos para la asignatura "<<codigo<<":"<<endl<<endl;
		if (!obj1.Falla())
		{
			Inscrito insc;
			Alumno al;
			char codMaterias[15];
			int i, aux, contInsc = 0;
			while (!obj1.Es_Fin())
			{
				obj1.LeerB(insc);
				if (!obj1.Es_Fin()) {
					al = buscarAlumno(insc.getCedula());
					if (al.getCedula() != 0 && al.getCarrera() == codigo/100)
					{
						strcpy(codMaterias, insc.getCodMaterias());
						for (i = 0; i < 15 && codMaterias[i] != '\0'; i += 2)
						{
							aux = (int) (codMaterias[i] - '0');
							aux =  (aux * 10) + (int) (codMaterias[i+1] - '0');
							if (aux == codigo%100)
							{
								cout<<al<<endl;
								//utilizando al se pueden saber los datos del alumno para imprimir
								//utilizando mat se pueden saber los datos de la materia para imprimir
								contInsc++;
								break;
							}//if materia si inscrita
						}//for para comparar codigo con la materia inscrita
					}//alumno registrado, inscrito y de la misma carrera de la asignatura que se busca
				}//si no es fin de arhivo
			}//while no sea fin de archivo
			
			if (contInsc > 0)
			{
				cout<<endl<<"Total de alumnos inscritos para la asignatura: "<<contInsc<<endl;
			}
			else
			{
				cout<<"No hay ningun alumno inscrito para la asignatura"<<endl;
			}
		}//si Inscritos abrio
		else
		{
			cout<<"Hubo un problema al abrir Inscritos.dat"<<endl;
		}//si Inscritos no abrio
	}//if codigo de asignatura existe
	else
	{
	cout<<"Codigo de asignatura no registrado."<<endl;
	}//else codigo de asignatura no existe
}//void consultInscAsig(int)
//FIN FUNCIONES DEL SWITCH EN MAIN
//------------------------------------

//MAIN
int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
	int aux;
	char ban;
	do
	{
		system("cls");
		cout<<"|-------------<Unidad de Admision UNET>----------------|"<<endl;
		cout<<"|----------------------<Menú>--------------------------|"<<endl;
		cout<<"|-<Agregar alumno>--------------------------------<|a|>|"<<endl;
		cout<<"|-<Consultar alumno>------------------------------<|b|>|"<<endl;
		cout<<"|-<Matricula actual de alumnos>-------------------<|c|>|"<<endl;
		cout<<"|-<Consultar materia>-----------------------------<|d|>|"<<endl;
		cout<<"|-<Pensum de la carrera>--------------------------<|e|>|"<<endl;	
		cout<<"|-<Incripcion de alumno>--------------------------<|f|>|"<<endl;
		cout<<"|-<Reporte de inscripcion>------------------------<|g|>|"<<endl;
		cout<<"|-<Reporte actual de  inscripciones>--------------<|h|>|"<<endl;
		cout<<"|-<Lista de alumnos inscritos en una asignatura>--<|i|>|"<<endl;
		cout<<"|-<Salir>-----------------------------------------<|x|>|"<<endl;
		cout<<"|-------------<Que operación requiere?>----------------|"<<endl;	
		cout<<"Opcion: ";  ban = tolower(cin.get());
		
		cout<<endl;
		switch(ban)
		{
			case 'a': //Agregar alumno
				agregarAlumno();
			break;
			
			case 'b': //Consultar alumno
				cout<<"Ingrese cedula a buscar: ";
   				cin>>aux;
   				cout<<endl;
   				if (!cin.fail())
   				{
   					consultarAlumno(aux);
				}
			break;
			
			case 'c':
				cout<<"Matricula de estudiantes"<<endl;
                mostrarDatosEstudiantes();				
			break;	
			
			case 'd': //Consultar materia
				cout<<"Ingrese codigo de la asignatura que desea consultar: ";
				cin>>aux;
				cout<<endl;
				if (!cin.fail())
   				{
   					consultarAsignatura(aux);
				}
			break;
			
			case 'e':
				cout<<"Ingrese codigo de la carrera a consultar: ";
				cin>>aux;
				cout<<endl;
				if (!cin.fail())
   				{
   					pensumCarreraIncri(aux);
				}
			break;
			
			case 'f': //Inscripcion de nuevo alumno
				inscripcion();
			break;
			
			case 'g': //Reporte de inscripcion
				cout<<"Ingrese cedula del alumno del que desea consultar la inscripcion: ";
				cin>>aux;
				cout<<endl;
				if (!cin.fail())
   				{
   					consultarInscripcion(aux);
				}
			break;
			
			case 'h': //Reporte actual de inscripciones 
				cout<<"Estado actual de Incripciones "<<endl;
                mostrarDatosInscripcion();
			break;
			
			case 'i': //Lista de alumnos inscritos en una asignatura
				cout<<"Ingrese codigo de asignatura de la cual desea consultar los alumnos "
					<<"inscritos: "<<endl;
				cin>>aux;
				cout<<endl;
				if (!cin.fail())
   				{
   					consultInscAsig(aux);
				}
			break;
				
			case 'x': //Salir
				cout<<"|-----------<Que tenga un feliz dia :D>----------------|"<<endl;	
			break;
			
			default: //Opcion de menu no valida
				cout<<"|-<No es una opcion de menu valida, ingrese de nuevo.>-|"<<endl;
			break;
		}//switch(band)
		if (cin.fail())
		{
			cin.clear();
			cout<<"No es una entrada valida, reingrese."<<endl;
		}
		if (ban != 'x')
		{
			cout<<endl<<"Presione cualquier tecla para volver al menu.";
		}
		cin.ignore(1000, '\n');
		cin.get();
	}while(ban!='x');	
	return 0;
}//int main()
//FIN MAIN -------------------
