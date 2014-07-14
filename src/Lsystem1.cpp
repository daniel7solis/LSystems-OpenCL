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
#include <iostream>
#include <stdio.h>

using namespace std;

string input,temp;
int iteraciones;

Lsystem1::Lsystem1(){
	iteraciones=0;
}
Lsystem1::~Lsystem1() {
	// TODO Auto-generated destructor stub
}

void leerCadena(){
	printf("Escribe la cadena del L-System: ");
	cin >> input;
	printf("Ingresa la cantidad de iteraciones:");
	cin >> iteraciones;
}
void control(){
	Productions P;
	P.Prod();
	for(int j=0; j<iteraciones; j++){
		cout << "Pasada numero: " << j+1;
		for(int i=0; i<input.length(); i++){
			cout << "-------------------------------------" << endl;
			cout << "Iteración: " << i << " para el simbolo -> " << input[i] << endl;
			char a=input[i];
			char *X=P.getProd(a);
			if(X!=NULL){
				cout << "Producción de " << input[i] << ":" << X << endl;
				temp+=X;
			}else{
				cout << "Error" << endl;
			}
		}
		cout << "Final de la cadena de la pasada " << j+1 << ": " << temp << endl;
		input=temp;
		temp="";
	}

}

int main() {
	leerCadena();
	control();
	return 0;
}
