/*
 * Axiom.h
 *
 *  Created on: 17/07/2014
 *      Author: dani
 */

#ifndef AXIOM_H_
#define AXIOM_H_

#include "Alphabet.h"

class Axiom {
public:
	char A;
//	Alphabet alpha;
	char temp[2];
	Axiom();
	virtual ~Axiom();
	bool setAxiom(char sym,Alphabet pA);
};

#endif /* AXIOM_H_ */
