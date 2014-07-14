/*
 * Prod.cpp
 *
 *  Created on: 06/07/2014
 *      Author: dani
 */

#include "ObjChar.h"

ObjChar::ObjChar() {
	// TODO Auto-generated constructor stub
}

ObjChar::~ObjChar() {
	// TODO Auto-generated destructor stub
}

void ObjChar::create(char *arr){
	arreglo=arr;
}
char* ObjChar::get(){
	return arreglo;
}

