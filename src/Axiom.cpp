/*
 * Axiom.cpp
 *
 *  Created on: 17/07/2014
 *      Author: dani
 */

#include "Axiom.h"
#include "Alphabet.h"
#include <iostream>
#include <stdio.h>

using namespace std;

Axiom::Axiom() {
	// TODO Auto-generated constructor stub

}

Axiom::~Axiom() {
	// TODO Auto-generated destructor stub
}

bool Axiom::setAxiom(char sym,Alphabet pA){
	temp[0]=sym;
	temp[1]='\0';
//	cout << pA.verifiSymbol(temp) << endl;
	if(pA.verifiSymbol(temp)){
		A=sym;
		cout << "setAxiom" << A << endl;
	}
}

