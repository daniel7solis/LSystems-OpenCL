/*
 * Productions.h
 *
 *  Created on: 04/07/2014
 *      Author: dani
 */

#ifndef PRODUCTIONS_H_
#define PRODUCTIONS_H_

#include "ObjChar.h"
#include <string>
#include "Alphabet.h"

class Productions {
public:
	int *fil,*col,cont;
	std::string **P;
	ObjChar obj;//creo el objeto donde almacenaré el array de caracteres
//	ObjChar **P;
//	ObjChar obj;//creo el objeto donde almacenaré el array de caracteres
	Productions();
	virtual ~Productions();
	bool Prod(int filas);
	void setProd(std::string text,int from);
	std::string getProd(char *f, Alphabet V);
	void print();
};

#endif /* PRODUCTIONS_H_ */
