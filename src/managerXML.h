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
private:
	int x;//variable para saber la cantida de symbolos del alfabeto
public:
	Productions prod;
	Alphabet alpha;
	Alphabet *pAlpha;
	Axiom axiom;
	Glib::ustring filePath;
	managerXML();
	virtual ~managerXML();
	bool beginParser();
	bool Parser(xmlpp::Node* node);
	bool semantico(xmlpp::Node* node);
	bool getAxiom(xmlpp::Node* node);
	bool getAlphabet(xmlpp::Node* node);
	bool getProductions(xmlpp::Node* node);
	void getSymFromXML(xmlpp::Node* node,int from);
};

#endif /* MANAGERXML_H_ */
