/*
 * managerXML.h
 *
 *  Created on: 17/07/2014
 *      Author: dani
 */

#ifndef MANAGERXML_H_
#define MANAGERXML_H_

#include "Productions.h";
#include "Alphabet.h";
#include "Axiom.h";
#include <libxml++/libxml++.h>
#include <glibmm/convert.h> //For Glib::ConvertError

class managerXML {
public:
	Productions prod;
	Alphabet alpha;
	Axiom axiom;
	Glib::ustring filePath;
	managerXML();
	virtual ~managerXML();
	bool beginParser();
	bool Parser(xmlpp::Node* node);
	bool semantico();
	void getAxiom();
	void getAlphabet();
	void getProductions();
};

#endif /* MANAGERXML_H_ */
