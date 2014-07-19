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
	bool final=false;
	try{
		xmlpp::DomParser parser;
		parser.parse_file(filePath);//parsea un archivo xml
		xmlpp::Node* pNode = parser.get_document()->get_root_node();
		xmlpp::Node* NodeRet;
		cout << "Nodo raiz: " << (pNode->get_name()) << endl;
//		Parser(pNode);
		xmlpp::Node::NodeList hijos = pNode->get_children();
		for(xmlpp::Node::NodeList::iterator iter = hijos.begin(); iter != hijos.end(); ++iter){//
			final=Parser(*iter);
//			cout << "1 -> " << NodeRet->get_name() << endl;
		}
		return final;
	}catch(const std::exception& ex){
		std::cerr << "Se capturo una excepción: " << ex.what() << endl;
		return false;
	}
}

bool managerXML::Parser(xmlpp::Node* node){
	bool final=false;
	const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
	const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(node);
	const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);
	if(nodeText && (nodeText->is_white_space())){
		/*ignoramos los espacios en blanco, si es espacio en blanco no se debe desarrollar
		 * el proceso de analisis de esa parte del archivo xml; si no lo es entonces
		 * si se debe desarrollar el analisis*/
		final=true;
	}else{
		/*Este es el proceso de analisis del archivo XML, parte por parte*/
		if(!nodeText && !nodeComment){//No se quiere que se imprima los nodos que son TEXT ó COMMENT
//			return node;
			cout << "1 -> " << (node->get_name()) << endl;//AQUI PODEMOS LLAMAR A SEMANTICO
			if((node->get_name()).compare("l-system")==0){
				final=semantico(node);
			}
//			if(nodeContent){
//				cout << "Tiene contenido" << nodeContent->get_content() << endl;
//			}
//			if(nodeComment){
//				cout << "El comentario" << nodeComment->get_content() << endl;
//			}
//			if(!nodeContent){
//				xmlpp::Node::NodeList hijos = node->get_children();
//				for(xmlpp::Node::NodeList::iterator iter = hijos.begin(); iter != hijos.end(); ++iter){//
//					Parser(*iter);
//				}
//			}
		}

		/*Ahora verifiquemos el contenido de los diferentes tipos de nodos*/
		if(nodeText){
			cout << "1 -> " << "Tiene texto--> " << nodeText->get_content() << endl;//LUGAR DONDE SE TIENE QUE GUARDAR EN EL L-SYSTEM
		}else if(nodeComment){
			cout << "1 -> " << "El comentario--> " << nodeComment->get_content() << endl;//SE PUDE ALMACENAR LOS COMENTARIOS PARA UNA REFENCIA AL USUARIO
		}else if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(node)){
			//Ahora se tiene un node de Elemento

			/*Solo a los nodos tipo elemento, se le pueden tomas sus atributos*/
			const xmlpp::Element::AttributeList& atributos=nodeElement->get_attributes();
			for(xmlpp::Element::AttributeList::const_iterator att=atributos.begin(); att!=atributos.end(); att++){
				xmlpp::Attribute* at=*att;
				cout << "1 -> " << "Atributo: " << at->get_name() << " = " << at->get_value() << endl;
			}
		}
	}
	return final;
}

bool managerXML::semantico(xmlpp::Node* nodePar){
	bool final=true;
	xmlpp::Node::NodeList hijos = nodePar->get_children();
	for(xmlpp::Node::NodeList::iterator iter = hijos.begin(); iter != hijos.end(); ++iter){//
		xmlpp::Node* node=*iter;
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
				cout << "	2 -> " << (node->get_name()) << endl;
				if((node->get_name()).compare("alphabet")==0){//LLAMAMOS AL METODO QUE DEFINE EL ALFABETO
					final=final & getAlphabet(node);
				}else if((node->get_name()).compare("axiom")==0){//LLAMAMOS AL METODO QUE DEFINE EL AXIOMA
					final=final & getAxiom(node);
				}else if((node->get_name()).compare("endomorphisms")==0){//LLAMAMOS AL METODO QUE DEFINE LAS PRODUCCIONES
					final=final & getProductions(node);
				}
			}

			/*Ahora verifiquemos el contenido de los diferentes tipos de nodos*/
			if(nodeText){
				cout << "	2 -> " << "Tiene texto--> " << nodeText->get_content() << endl;//LUGAR DONDE SE TIENE QUE GUARDAR EN EL L-SYSTEM
			}else if(nodeComment){
				cout << "	2 -> " << "El comentario--> " << nodeComment->get_content() << endl;//SE PUDE ALMACENAR LOS COMENTARIOS PARA UNA REFENCIA AL USUARIO
			}else if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(node)){
				//Ahora se tiene un node de Elemento

				/*Solo a los nodos tipo elemento, se le pueden tomas sus atributos*/
				const xmlpp::Element::AttributeList& atributos=nodeElement->get_attributes();
				for(xmlpp::Element::AttributeList::const_iterator att=atributos.begin(); att!=atributos.end(); att++){
					xmlpp::Attribute* at=*att;
					cout << "	2 -> " << "Atributo: " << at->get_name() << " = " << at->get_value() << endl;
				}
			}
		}
	}
	cout << "semantico -> " << final << endl;
	return final;
}

bool managerXML::getAlphabet(xmlpp::Node* nodePar){
	bool final=true;
	xmlpp::Node::NodeList hijos = nodePar->get_children();
	xmlpp::Node::NodeList hijos2 = nodePar->get_children();
	x=0;//variable para contar los symbolos que son parte del alfabeto dentro del xml
	for(xmlpp::Node::NodeList::iterator iter = hijos.begin(); iter != hijos.end(); ++iter){
		xmlpp::Node* node=*iter;
		const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
		const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(node);
		const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);
		if(!nodeText && !nodeComment){
			/*Incrementamos la variable de contador de symbolos para crear el alfabeto*/
			x++;
		}
	}
	/*Creo el alfabeto de acuerdo al cantidad de simbolos dentro del xml*/
	alpha.Alpha(x);
	for(xmlpp::Node::NodeList::iterator iter = hijos.begin(); iter != hijos.end(); ++iter){//
		xmlpp::Node* node=*iter;
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
				cout << "		3 -> " << (node->get_name()) << endl;
				if((node->get_name()).compare("symbol")==0){//LLAMAMOS  A LA FUNCIÓN QUE INSERTA EL SYM AL ALFABETO
					getSymFromXML(node,0);
				}
			}

			/*Ahora verifiquemos el contenido de los diferentes tipos de nodos*/
			if(nodeText){
				cout  << "		3 -> " << "Tiene texto--> " << nodeText->get_content() << endl;//LUGAR DONDE SE TIENE QUE GUARDAR EN EL L-SYSTEM
			}else if(nodeComment){
				cout  << "		3 -> " << "El comentario--> " << nodeComment->get_content() << endl;//SE PUDE ALMACENAR LOS COMENTARIOS PARA UNA REFENCIA AL USUARIO
			}else if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(node)){
				//Ahora se tiene un node de Elemento

				/*Solo a los nodos tipo elemento, se le pueden tomas sus atributos*/
				const xmlpp::Element::AttributeList& atributos=nodeElement->get_attributes();
				for(xmlpp::Element::AttributeList::const_iterator att=atributos.begin(); att!=atributos.end(); att++){
					xmlpp::Attribute* at=*att;
					cout   << "		3 -> " << "Atributo: " << at->get_name() << " = " << at->get_value() << endl;
				}
			}
		}
	}
	return true;
}

bool managerXML::getAxiom(xmlpp::Node* nodePar){
	getSymFromXML(nodePar,1);
	return true;
}

bool managerXML::getProductions(xmlpp::Node* nodePar){
//	prod.Prod();
//	prod.setProd();
	return true;
}

void managerXML::getSymFromXML(xmlpp::Node* nodePar, int from){
	xmlpp::Node::NodeList hijos = nodePar->get_children();
	for(xmlpp::Node::NodeList::iterator iter = hijos.begin(); iter != hijos.end(); ++iter){//
		xmlpp::Node* node=*iter;
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
				cout << "			4 -> " << (node->get_name()) << endl;
			}

			/*Ahora verifiquemos el contenido de los diferentes tipos de nodos*/
			if(nodeText){
				cout << "			4 -> " << "Tiene texto--> " << nodeText->get_content() << endl;//LUGAR DONDE SE TIENE QUE GUARDAR EN EL L-SYSTEM
				string z=nodeText->get_content();
//				cout << z << endl;
				if(from==0){//viene de getAlphabet, por lo tanto es agregar simbolo al alfabeto
					/*Almaceno el symbolo dentro del alfabeto*/
					alpha.setSym(z[0]);
				}else if(from==1){//viene de getAxiom, por lo tanto es agregar simbolo al axioma
					/*Almaceno el symbolo dentro del alfabeto*/
//					pAlpha=alpha;
					axiom.setAxiom(z[0],alpha);
				}
			}else if(nodeComment){
				cout << "			4 -> " << "El comentario--> " << nodeComment->get_content() << endl;//SE PUDE ALMACENAR LOS COMENTARIOS PARA UNA REFENCIA AL USUARIO
			}else if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(node)){
				//Ahora se tiene un node de Elemento

				/*Solo a los nodos tipo elemento, se le pueden tomas sus atributos*/
				const xmlpp::Element::AttributeList& atributos=nodeElement->get_attributes();
				for(xmlpp::Element::AttributeList::const_iterator att=atributos.begin(); att!=atributos.end(); att++){
					xmlpp::Attribute* at=*att;
					cout << "			4 -> " << "Atributo: " << at->get_name() << " = " << at->get_value() << endl;
				}
			}
		}
	}
}

