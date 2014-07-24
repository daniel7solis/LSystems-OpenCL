/*
 * ObjChar.h
 *
 *  Created on: 06/07/2014
 *      Author: dani
 */

#ifndef OBJCHAR_H_
#define OBJCHAR_H_

#include <string>

class ObjChar {
public:
	std::string arreglo;
	ObjChar();
	virtual ~ObjChar();
	void create(std::string a);
	std::string get();
};

#endif /* PROD_H_ */
