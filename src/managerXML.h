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
#include <glibmm/convert.h>
#include <string>

class managerXML {
private:

public:
	int x;//variable para saber la cantida de symbolos del alfabeto, y la cantidad de rules de las producciones
	Productions prod;
	Alphabet alpha;
	Alphabet *pAlpha;
	Axiom axiom;
	Glib::ustring filePath;
	std::string nameSystem;
	managerXML();
	virtual ~managerXML();
	bool beginParser(std::string filePath);
	bool Parser(xmlpp::Node* node);
	bool semantico(xmlpp::Node* node);
	bool getAxiom(xmlpp::Node* node);
	bool getAlphabet(xmlpp::Node* node);
	bool getProductions(xmlpp::Node* node);
	bool getRules(xmlpp::Node* nodePar);
	bool getRuleInside(xmlpp::Node* node,int from);
	void getSymFromXML(xmlpp::Node* node,int from);
};

#endif /* MANAGERXML_H_ */
