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
	//Ruta para el archivo XML que contiene el L-System
	//filePath=path+"ejemplo.xml";
}

managerXML::~managerXML() {
	// TODO Auto-generated destructor stub
}

bool managerXML::beginParser(string filePath){
	bool final=false;//variable para controlar los errores y en caso de existir se detiene el programa
	try{
		//Se crea un objeto tipo DomParser
		xmlpp::DomParser parser;
		/*Iniciamos el objeto pasando la ruta del archivo a leer*/
		parser.parse_file(filePath+"ejemplo.xml");//parsea un archivo xml
		/*Obtiene el nodo raiz del archivo*/
		xmlpp::Node* pNode = parser.get_document()->get_root_node();
		xmlpp::Node* NodeRet;
		cout << "Nodo raiz: " << (pNode->get_name()) << endl;
//		Parser(pNode);
		/*Obtenemos los nodos hijos del nodo raiz*/
		xmlpp::Node::NodeList hijos = pNode->get_children();
		/*Se comienza el analisis en cada nodo hijo, ya que a ese nivel se encuentran
		 * los sistemas de Lindenmayer*/
		for(xmlpp::Node::NodeList::iterator iter = hijos.begin(); iter != hijos.end(); ++iter){//
			/*El método Parser se encarga de comenza ra analizar cada nodo hijo del nodo raíz*/
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
	bool final=false;//variable para controlar los errores y en caso de existir se detiene el programa
	/*Se crean objetos de los 3 posibles tipos que puede ser el nodo, hay nodos con contenido (más nodos)
	 * nodos con contenido (texto dentro de el) y
	 * nodos de comentarios*/
	const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
	const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(node);
	const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);
	if(nodeText && (nodeText->is_white_space())){
		/*Como el Parser detecta espacios y lineas ignoramos los espacios en blanco, si es
		 * espacio en blanco no se debe desarrollar
		 * el proceso de analisis de esa parte del archivo xml; si no lo es entonces
		 * si se debe desarrollar el analisis*/
		final=true;
	}else{
		/*Este es el proceso de analisis del archivo XML, parte por parte*/
		/*Se verifica el tipo de nodo, ya que en cualquier nivel podemos
		 * encontrar nodos de contenido o nodos de comentario*/
		if(!nodeText && !nodeComment){//SI NO SON TEXT ó COMMENT
			cout << "1 -> " << (node->get_name()) << endl;//AQUI PODEMOS LLAMAR A SEMANTICO
			/*Si el nombre del nodo correponde a l-system, por lo tanto encontramos
			 * un sistema de lindenmayer definido*/
			if((node->get_name()).compare("l-system")==0){
				/*Mando llamar al método semantico que se encarga de
				 * revisar que el sistema de Lindenmayer que se encontro,
				 * cuente con la estructura basica, la estructura basica
				 * debe contar con un conjunto de simbolos llamado
				 * alfabeto, un simbolo inicial que debe estar dentro
				 * del alfabeto y un conjunto de reglas de producción*/
				final=semantico(node);
			}
		}
		/*Fin de busqueda de nodos l-system*/

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
				nameSystem=at->get_value();
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
			/*Como el Parser detecta espacios y lineas ignoramos los espacios en blanco, si es
			 * espacio en blanco no se debe desarrollar
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
	bool final=true;
	xmlpp::Node::NodeList hijos = nodePar->get_children();
	x=0;//variable para contar las rules que son parte de las producciones llamadas "endomorphisms" dentro del xml
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
//	cout << "Cantidad de rules -> " << x << endl;
	/*Creo el alfabeto de acuerdo al cantidad de simbolos dentro del xml*/
	prod.Prod(x);
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
				if((node->get_name()).compare("rule")==0){//LLAMAMOS  A LA FUNCIÓN QUE INSERTA EL SYM AL ALFABETO
					getRules(node);
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
//	prod.print();
	return true;
}

bool managerXML::getRules(xmlpp::Node* nodePar){
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
				cout << "			4 -> " << (node->get_name()) << endl;
				if((node->get_name()).compare("predecessor")==0){//LLAMAMOS  A LA FUNCIÓN QUE INSERTA EL SYM AL ALFABETO
					getRuleInside(node,0);//0 es la referencia que significa que es el predecesor
				}else if((node->get_name()).compare("successor")==0){
					getRuleInside(node,1);//1 es la referencia que significa que es el succesor
				}else if((node->get_name()).compare("condition")==0){
//					getRuleInside(node,2);//2 es la referencia que significa que es la condition
				}
			}

			/*Ahora verifiquemos el contenido de los diferentes tipos de nodos*/
			if(nodeText){
				cout  << "			4 -> " << "Tiene texto--> " << nodeText->get_content() << endl;//LUGAR DONDE SE TIENE QUE GUARDAR EN EL L-SYSTEM
			}else if(nodeComment){
				cout  << "			4 -> " << "El comentario--> " << nodeComment->get_content() << endl;//SE PUDE ALMACENAR LOS COMENTARIOS PARA UNA REFENCIA AL USUARIO
			}else if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(node)){
				//Ahora se tiene un node de Elemento

				/*Solo a los nodos tipo elemento, se le pueden tomas sus atributos*/
				const xmlpp::Element::AttributeList& atributos=nodeElement->get_attributes();
				for(xmlpp::Element::AttributeList::const_iterator att=atributos.begin(); att!=atributos.end(); att++){
					xmlpp::Attribute* at=*att;
					cout   << "			4 -> " << "Atributo: " << at->get_name() << " = " << at->get_value() << endl;
				}
			}
		}
	}
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
				char w=z[0];
//				cout << z << endl;
				if(from==0){//viene de getAlphabet, por lo tanto es agregar simbolo al alfabeto
					/*Almaceno el symbolo dentro del alfabeto*/
					alpha.setSym(z[0]);
				}else if(from==1){//viene de getAxiom, por lo tanto es agregar simbolo al axioma
					/*Almaceno el symbolo dentro del alfabeto*/
//					pAlpha=alpha;
					axiom.setAxiom(z,alpha);
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

/*Método para obtener el predecessor, successor, y la condition de las reglas de producción.
 * Para esto recibe el nodo y un numero (0,1,2) respectivamente para el predecessor, successor y condition*/
bool managerXML::getRuleInside(xmlpp::Node* nodePar, int from){
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
				cout << "				5 -> " << "Tiene texto--> " << nodeText->get_content() << endl;//LUGAR DONDE SE TIENE QUE GUARDAR EN EL L-SYSTEM
				string z=nodeText->get_content();
				//				cout << z << endl;
				if(from==0){
					prod.setProd(z,0);
				}else if(from==1){
					prod.setProd(z,1);
				}else if(from==2){
					prod.setProd(z,2);
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

