/*
 * Alphabet.cpp
 *
 *  Created on: 04/07/2014
 *      Author: dani
 */

#include "Alphabet.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <typeinfo>

using namespace std;

Alphabet::Alphabet() {
	// TODO Auto-generated constructor stub
//	V[7]="CADENO";
}

Alphabet::~Alphabet() {
	// TODO Auto-generated destructor stub
}

bool Alphabet::verifiSymbol(char *s){
	for(int i=0; i<sizeof(V)/sizeof(char)-1; i++){
		temp[0]=V[i];
		temp[1]='\0';
//		cout << sizeof(q) << endl;
//		cout <<"Valor de V[i] "<< &V[i] << " Sym " << s << " " << q <<endl;
//		cout << temp << s << strcmp(temp,s) << endl;
		if(strcmp(temp,s)==0){
			return true;
		}
	}
	return false;
}
