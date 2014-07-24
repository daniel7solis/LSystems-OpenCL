/*
 * Prod.cpp
 *
 *  Created on: 06/07/2014
 *      Author: dani
 */

#include "ObjChar.h"
#include <string>

ObjChar::ObjChar() {
	// TODO Auto-generated constructor stub
}

ObjChar::~ObjChar() {
	// TODO Auto-generated destructor stub
}

void ObjChar::create(std::string a){
	arreglo=a;
}
std::string ObjChar::get(){
	return arreglo;
}

