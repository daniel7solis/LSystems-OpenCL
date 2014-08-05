/*
 * Productions.cpp
 *
 *  Created on: 04/07/2014
 *      Author: dani
 */

#include "Productions.h"
#include "ObjChar.h"
#include "Alphabet.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <typeinfo>

using namespace std;

Productions::Productions() {
	// TODO Auto-generated constructor stub
	cont=0;/*Inicializo el contador a 0, este contador controla el indice en el que se van insertando
	las producciones al objeto de las Producciones*/
}

Productions::~Productions() {
	// TODO Auto-generated destructor stub
}

bool Productions::Prod(int filas){
	fil=new int(filas);
	col=new int(2);
	int i;
	/*Creo la matriz de objetos*/
	P=new string*[*fil];//Creo un puntero de un vector de punteros a objetos ObjChar
	for(i=0; i<*fil; i++){
		P[i]=new string[*col];//A cada puntero del vector hacer que apunte a un vector de objetos
	}

	/*imprimo la matriz*/
//	for(i=0; i<*fil; i++){
//		for(int j=0; j<*col; j++){
//			cout << i << " , " << j << endl;
//		}
//	}

//	/*C->produccion*/
////	char C[2]="C";//Se obtiene lado izq de la prod
////	char *pc=C;//obtengo el apuntador
//	obj.create("C");//con el obj apunto al array
//	P[0][0]=obj;//almaceno el la referencia al obj
////	char CP[4]="CDN";//Se obtiene lado derecho de la prod
////	char *pcp=CP;//obtengo el apuntador
//	obj.create("CDN");//con el obj apunto al array
//	P[0][1]=obj;//almaceno el la referencia al obj
//
//	/*A->Produccion*/
////	char A1[2]="A";
////	char *pa1=A1;
//	obj.create("A");
//	P[1][0]=obj;//almaceno el la referencia al obj
////	char A1P[3]="AE";//Se obtiene lado derecho de la prod
////	char *pa1p=A1P;//obtengo el apuntador
//	obj.create("AE");//con el obj apunto al array
//	P[1][1]=obj;//almaceno el la referencia al obj
//
//	/*D->Produccion*/
////	char D[2]="D";
////	char *pd=D;//obtengo el apuntador
//	obj.create("D");//con el obj apunto al array
//	P[2][0]=obj;//almaceno el la referencia al obj
////	char DP[4]="EEE";//Se obtiene lado derecho de la prod
////	char *pdp=DP;//obtengo el apuntador
//	obj.create("EEE");//con el obj apunto al array
//	P[2][1]=obj;//almaceno el la referencia al obj
//
//	/*E->Produccion*/
////	char E[2]="E";
////	char *pe=E;//obtengo el apuntador
//	obj.create("E");//con el obj apunto al array
//	P[3][0]=obj;//almaceno el la referencia al obj
////	char EP[4]="DDD";//Se obtiene lado derecho de la prod
////	char *pep=EP;//obtengo el apuntador
//	obj.create("DDD");//con el obj apunto al array
//	P[3][1]=obj;//almaceno el la referencia al obj
//
//	/*N->Produccion*/
////	char N[2]="N";
////	char *pn=N;//obtengo el apuntador
//	obj.create("N");//con el obj apunto al array
//	P[4][0]=obj;//almaceno el la referencia al obj
////	char NP[4]="AAA";//Se obtiene lado derecho de la prod
////	char *pnp=NP;//obtengo el apuntador
//	obj.create("AAA");//con el obj apunto al array
//	P[4][1]=obj;//almaceno el la referencia al obj
//
//	/*A->Produccion*/
////	char A2[2]="A";
////	char *pa2=A2;//obtengo el apuntador
//	obj.create("O");//con el obj apunto al array
//	P[5][0]=obj;//almaceno el la referencia al obj
////	char A2P[7]="NACENA";//Se obtiene lado derecho de la prod
////	char *pa2p=A2P;//obtengo el apuntador
////	obj.create(pa2p);//con el obj apunto al array
//	obj.create("NACENA");//con el obj apunto al array
//	P[5][1]=obj;//almaceno el la referencia al obj
	return true;
}

/*Función que inserta dentro de las producciones el PREDECESSOR=0,SUCCESSOR=1,CONDITION=3*/
void Productions::setProd(string text,int from){
//	char *p=&text[0];
	if(from==0){//si es cero, se debe insertar el predecessor a una posición izq de la matriz de prod
		cout << "Insertar el predecessor-> " << text << endl;
//		obj.create(&text[0]);//con el obj apunto al array
		P[cont][0]=text;//almaceno el la referencia al obj
		cout << ".P-> " << P[cont][0] << endl;
//		cout << ".P-> " << P[cont][0].get() << endl;
	}else if(from==1){//Si es 1, se debe insertar el successor a la posición derecha de la matriz de prod
		cout << "Insertar el successor-> " << text << endl;
//		obj.create(p);//con el obj apunto al array
		P[cont][1]=text;//almaceno el la referencia al obj
		cout << ".P-> " << P[cont][1] << endl;
//		cout << ".P-> " << P[cont][1].get() << endl;
		cont++;//Incremento el contador porque esta produccion termino
	}
}

void Productions::print(){
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			cout << "Z=" << P[i][j] << endl;
//			cout << "Z=" << P[i][j].get() << endl;
		}
	}
}

std::string Productions::getProd(char *f,Alphabet V){
	cout << "Recibo " << (f) << endl;
	string d=string(f);
	/*Antes de empezar a buscar el token dentro de las producciones, es conveniente
	 * buscar el token dentro del alfabeto existente, ya que si se ingresa un token
	 * que no existe en el alfabeto es una cadena centrante con error, por lo que no
	 * se tiene que procesar*/
	if(!V.verifiSymbol(f)){
		cout << "Simbolo invalido " << f << " no existe en el alfabeto. Vuelve a ingresar la cadena." << endl;
	}else{
		/*Recorro el arreglo de objetos ObjChar, en busqueda del token
		 * que se busca*/
		for(int i=0; i<*fil; i++){
			//		cout << i<<" "<< P[i][0].get() << f  << strcmp(P[i][0].get(),&f) <<endl;
//			cout << "Prod" << P[i][0].get() << &f << endl;
			if((P[i][0]).compare(d)==0){//Comparo el token con cada simbolo "a" de P es a -> X
				return P[i][1];//Si encontre el token dentro de las producciones, mando la producción que le corresponde
			}
//			if((P[i][0].get()).compare(d)==0){//Comparo el token con cada simbolo "a" de P es a -> X
//				return P[i][1].get();//Si encontre el token dentro de las producciones, mando la producción que le corresponde
//			}
		}
	}//strcmp(P[i][0].get(),&f)==0
	return "";//Si no lo encontre mando Null
}
