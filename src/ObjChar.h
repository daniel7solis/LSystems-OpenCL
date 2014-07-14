/*
 * ObjChar.h
 *
 *  Created on: 06/07/2014
 *      Author: dani
 */

#ifndef OBJCHAR_H_
#define OBJCHAR_H_

class ObjChar {
public:
	char *arreglo;
	ObjChar();
	virtual ~ObjChar();
	void create(char a[]);
	char* get();
};

#endif /* PROD_H_ */
