//============================================================================
// Name        : Lsystem1.cpp
// Author      : 
// Version     :
// Copyright   :
// Description :
//============================================================================

#include "Lsystem1.h"
#include "Alphabet.h"
#include "Productions.h"
#include "managerXML.h"
#include "Axiom.h"
#include <iostream>
#include <stdio.h>
#include <string>
/*Libreria para las funciones del tiempo*/
#include <time.h>
/*Libreria para el buffer de string, usado para convertir de numero a cadena*/
#include <sstream>

using namespace std;

managerXML manXML;
string input,temp;
int iteraciones;
/*Variables para las funciones del tiempo*/
clock_t start,end;
time_t start_t,end_t;
struct tm *timeStartPtr, *tiemEndPtr;
/*Variables para escribir en el archivo*/
std::string cadena;
std::ostringstream convert;
/*archivo*/
FILE *file;

Lsystem1::Lsystem1(){
	iteraciones=0;
}
Lsystem1::~Lsystem1() {
	// TODO Auto-generated destructor stub
}

bool getXML(){
	return manXML.beginParser();
}

void leerCadena(){
//	printf("Escribe la cadena del L-System: ");
//	cin >> input;
	printf("Ingresa la cantidad de iteraciones:");
	cin >> iteraciones;
}
void control(){
	file=fopen("/home/dani/workspace/Lsystem1/bitacora.txt", "a");
	if(!file) {
		printf("El fichero no existe o no puede ser abierto.\n");
	}
	if(getXML()){
//		Productions P;
//		P.Prod();
//		for(int j=0; j<iteraciones; j++){
//			cout << "Pasada numero: " << j+1;
//			for(int i=0; i<input.length(); i++){
//				cout << "-------------------------------------" << endl;
//				cout << "Iteración: " << i << " para el simbolo -> " << input[i] << endl;
//				char a=input[i];
//				char *X=P.getProd(a);
//				if(X!=NULL){
//					cout << "Producción de " << input[i] << ":" << X << endl;
//					temp+=X;
//				}else{
//					cout << "Error" << endl;
//				}
//			}
//			cout << "Final de la cadena de la pasada " << j+1 << ": " << temp << endl;
//			input=temp;
//			temp="";
//		}
		cout << "=========================================================" << endl;
		cout << "=======================L-System==========================" << endl;
		input=manXML.axiom.getAxiom();
		cout << "Axioma -----> " << input << endl;
		cout << "Alfabeto ---> " << manXML.alpha.V << endl;
		char z[2];
		z[0]=input[0];
		z[1]='\0';
		cout << "Produccion para el Axioma " << input << "---> " << manXML.prod.getProd(z,manXML.alpha) << endl;
		/*Funciones que comienzan a contabilizar el tiempo*/
		start = clock();//Para los segundos de procesamiento
		start_t=time(NULL);//Para el tiempo de ejecución
		for(int j=0; j<iteraciones; j++){
			cout << "Pasada numero: " << j+1;
			for(unsigned int i=0; i<input.length(); i++){
				cout << "-------------------------------------" << endl;
				char a[2];
				a[0]=input[i];
				a[1]='\0';
				cout << "Iteración: " << i << " para el simbolo -> " << a << endl;
//				cout << "Produccion para el Axioma " << input << "---> " << manXML.prod.getProd(input[0],manXML.alpha) << endl;
				std::string X=manXML.prod.getProd(a,manXML.alpha);
				if((X).compare("")!=0){
					cout << "Producción de " << input[i] << "-> " << X << endl;
					temp+=X;
				}else{
					cout << "Error" << endl;
				}
			}
			cout << "Final de la cadena de la pasada " << j+1 << ": " << temp << endl;
			input=temp;
			temp="";
		}
		/*Funciones que capturan el tiempo al finalizar el ciclo*/
		end=clock();
		end_t=time(NULL);
		timeStartPtr = localtime( &start_t );
//		timeEndPtr = localtime( &end_t );/se supone que se contaba el tiempo pero no funciona, toma el mismo tiempo que de inicio

		/*Ponemos mensajes en consola*/
		/*Tiempo del sistema*/
		printf( "\nBitacora: %s", asctime((timeStartPtr)));
		//	printf( "Final: %s\n", asctime(tiempoFinalPtr) );//se supone que se contaba el tiempo pero no funciona
		/*Tiempo de procesamiento*/
		printf("\nTiempo de procesamiento en segundos -> Inicio: %f Fin: %f",start/(double)CLOCKS_PER_SEC,end/(double)CLOCKS_PER_SEC);
		printf( "\nTotal de segundos de procesamiento: %f s\n", (end-start)/(double)CLOCKS_PER_SEC );
		/*Tiempo de ejecución*/
		printf( "Tiempo de ejecución en segundos -> Inicio: %ld Fin: %ld\n",start_t,end_t );
		printf( "Total de segundos transcurridos desde el comienzo del ciclo: %f s\n", difftime(end_t, start_t) );

		/*Almacenamos en el archivo*/
		cadena="\n-----------------------------------------------------------------------------";
		fputs(cadena.c_str(),file);
		cadena="\nBitacora -> "+string(asctime(timeStartPtr));
		fputs(cadena.c_str(),file);

		convert << (iteraciones);
		cadena="Iteraciones -> "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		convert << (start/(double)CLOCKS_PER_SEC);
		cadena="\nTiempo de procesamiento en segundos -> Inicio: "+convert.str();
		convert.str("");
		convert << (end/(double)CLOCKS_PER_SEC);
		cadena=cadena+" Fin: "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		convert << ((end-start)/(double)CLOCKS_PER_SEC);
		cadena="\nTotal de segundos de procesamiento: "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		convert << start_t;
		cadena="\nTiempo de ejecución en segundos -> Inicio: "+convert.str();
		convert.str("");
		convert << end_t;
		cadena=cadena+" Fin: "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		convert << difftime(end_t, start_t);
		cadena="\nTotal de segundos transcurridos desde el comienzo del ciclo: "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		fclose(file);
		/*Fin del uso de archivo*/
	}else{//fallo el managerXML

	}
}

int main() {
	leerCadena();
	control();
	return 0;
}
