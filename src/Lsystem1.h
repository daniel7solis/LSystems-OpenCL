#ifndef LSYSTEM1_H_
#define LSYSTEM1_H_

#include <string.h>
#include "managerXML.h"

class Lsystem1 {
private:

public:
	managerXML manXML;
	Lsystem1();
	virtual ~Lsystem1();
	void leerCadena();
	void control();
	bool getXML();
};
#endif /*LSYSTEM1_H_*/
