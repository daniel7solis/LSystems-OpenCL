/*
 * Productions.h
 *
 *  Created on: 04/07/2014
 *      Author: dani
 */

#ifndef PRODUCTIONS_H_
#define PRODUCTIONS_H_

#include "ObjChar.h"

class Productions {
public:
	int *fil,*col;
	ObjChar **P;
	ObjChar obj;//creo el objeto donde almacenaré el array de caracteres
	Productions();
	virtual ~Productions();
	void Prod();
	char* getProd(char f);
};

#endif /* PRODUCTIONS_H_ */
