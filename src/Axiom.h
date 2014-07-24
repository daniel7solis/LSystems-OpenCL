/*
 * Axiom.h
 *
 *  Created on: 17/07/2014
 *      Author: dani
 */

#ifndef AXIOM_H_
#define AXIOM_H_

#include "Alphabet.h"
#include <string>

class Axiom {
public:
	std::string A;
//	Alphabet alpha;
	char temp[2];
	Axiom();
	virtual ~Axiom();
	bool setAxiom(std::string sym,Alphabet pA);
	std::string getAxiom();
};

#endif /* AXIOM_H_ */
