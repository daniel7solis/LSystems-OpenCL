/*
 * managerXML.cpp
 *
 *  Created on: 17/07/2014
 *      Author: dani
 */

#include "managerXML.h"

#include <stdlib.h>
#include <iostream>
/*Incluyo la libreria de libXML++ Parse, libreria utilizada para obtenr los datos del archivo xml*/
#include <libxml++/libxml++.h>
#include <glibmm/convert.h> //For Glib::ConvertError
#include <libxml++/parsers/domparser.h>
#include <libxml/parser.h>
#include <typeinfo>
#include <string.h>

using namespace std;

managerXML::managerXML() {
	// TODO Auto-generated constructor stub
	// Set the global C++ locale to the user-configured locale,
	// so we can use std::cout with UTF-8, via Glib::ustring, without exceptions.
	std::locale::global(std::locale(""));
	filePath="/home/dani/workspace/XMLParser/src/ejemplo.xml";
}

managerXML::~managerXML() {
	// TODO Auto-generated destructor stub
}

bool managerXML::beginParser(){
	try{
		xmlpp::DomParser parser;
		parser.parse_file(filePath);//parsea un archivo xml
		xmlpp::Node* pNode = parser.get_document()->get_root_node();
		cout << "Nodo raiz: " << (pNode->get_name()) << endl;
		return Parser(pNode);
	}catch(const std::exception& ex){
		std::cerr << "Se capturo una excepción: " << ex.what() << endl;
		return false;
	}
}

bool managerXML::Parser(xmlpp::Node* node){
	const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
	const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(node);
	const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);
	if(nodeText && (nodeText->is_white_space())){
		/*ignoramos los espacios en blanco, si es espacio en blanco no se debe desarrollar
		 * el proceso de analisis de esa parte del archivo xml; si no lo es entonces
		 * si se debe desarrollar el analisis*/
	}else{
		/*Este es el proceso de analisis del archivo XML, parte por parte*/
		if(!nodeText && !nodeComment){//No se quiere que se imprima los nodos que son TEXT ó COMMENT
			cout << (node->get_name()) << endl;//AQUI PODEMOS LLAMAR A SEMANTICO
			if((node->get_name()).compare("l-system")==0){
				cout << "encontrada" << endl;
			}
			if(nodeContent){
				cout << "		Tiene contenido" << nodeContent->get_content() << endl;
			}
			if(nodeComment){
				cout << "		El comentario" << nodeComment->get_content() << endl;
			}
			if(!nodeContent){
				xmlpp::Node::NodeList hijos = node->get_children();
				for(xmlpp::Node::NodeList::iterator iter = hijos.begin(); iter != hijos.end(); ++iter){//
					Parser(*iter);
				}
			}
		}

		/*Ahora verifiquemos el contenido de los diferentes tipos de nodos*/
		if(nodeText){
			cout << "		Tiene texto--> " << nodeText->get_content() << endl;//LUGAR DONDE SE TIENE QUE GUARDAR EN EL L-SYSTEM
		}else if(nodeComment){
			cout << "		El comentario--> " << nodeComment->get_content() << endl;//SE PUDE ALMACENAR LOS COMENTARIOS PARA UNA REFENCIA AL USUARIO
		}else if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(node)){
			//Ahora se tiene un node de Elemento

			/*Solo a los nodos tipo elemento, se le pueden tomas sus atributos*/
			const xmlpp::Element::AttributeList& atributos=nodeElement->get_attributes();
			for(xmlpp::Element::AttributeList::const_iterator att=atributos.begin(); att!=atributos.end(); att++){
				xmlpp::Attribute* at=*att;
				cout << "Atributo: " << at->get_name() << " = " << at->get_value() << endl;
			}
		}
	}
	return true;
}

bool managerXML::semantico(){

}

