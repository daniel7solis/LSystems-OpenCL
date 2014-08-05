#ifndef LSYSTEM1_H_
#define LSYSTEM1_H_

#include <string.h>
#include "managerXML.h"

/*Headers para OpenCl*/
#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#include <CL/cl.h>
/**/

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
