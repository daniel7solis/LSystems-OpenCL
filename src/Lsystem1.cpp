//============================================================================
// Name        : Lsystem1.cpp
// Author      : 
// Version     :
// Copyright   :
// Description :
//============================================================================

#include "Lsystem1.h"
#include "Alphabet.h"
#include "Productions.h"
#include "managerXML.h"
#include "Axiom.h"
#include "OpenCLSetUp.h"
#include <iostream>
#include <stdio.h>
#include <string>
/*Libreria para las funciones del tiempo*/
#include <time.h>
/*Libreria para el buffer de string, usado para convertir de numero a cadena*/
#include <sstream>
#include <typeinfo>
#include <cstring>

/*Headers para OpenCl*/
#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#include <CL/cl.h>
/**/

using namespace std;

/*Files Path, for XML, Bitacora and Kernel*/
string FilesPath="/home/dani/workspace/Lsystem_ProcesoParalelo/src/";

managerXML manXML;
string input,temp;
int iteraciones;
/*Variables para las funciones del tiempo*/
clock_t start,end;
time_t start_t,end_t;
struct tm *timeStartPtr, *tiemEndPtr;
/*Variables para escribir en el archivo*/
std::string cadena;
std::ostringstream convert;
/*archivo*/
FILE *file;
/*OpenCl*/
OpenCLSetUp openCl;
cl_mem memObjects[4] = { 0, 0, 0, 0};
cl_int errNum;

cl_platform_id * platformIds;
cl_device_id * deviceIds;
cl_uint numDevices;
cl_context context;

/*Arreglo de caracteres que almacenaran el predecesor de las producciones para poder
 * manejarlas desde un kernel de OpenCL, ya que no soporta punteros de punteros ni
 * paso de clases*/
char *predecesores;
int *result;
int cantProd;

Lsystem1::Lsystem1(){
	iteraciones=0;
}
Lsystem1::~Lsystem1() {
	// TODO Auto-generated destructor stub
}

bool getXML(){
	//Ruta para el archivo XML que contiene el L-System
	return manXML.beginParser(FilesPath);
}

void leerCadena(){
//	printf("Escribe la cadena del L-System: ");
//	cin >> input;
	printf("Ingresa la cantidad de iteraciones:");
	cin >> iteraciones;
}

void control(){
	openCl.FilesPath=FilesPath;
	file=fopen((FilesPath+"bitacoraParalelo.txt").c_str(), "a");
	if(!file) {
		printf("El fichero no existe o no puede ser abierto.\n");
	}
	if(getXML()){
		cout << "=========================================================" << endl;
		cout << "=======================L-System==========================" << endl;
		/*Cargamos los predecesores desde las Producciones en el arreglo
		 * llamdo predecesores*/
		cout << manXML.x << endl;
		cantProd=manXML.x;//en la variable X se tiene la cantidad de producciones
		predecesores = new char[cantProd];//en la variable X se tiene la cantidad de producciones
		for(int q=0; q<cantProd; q++){
			predecesores[q]=(manXML.prod.P[q][0])[0];
			cout << "array de prede:" << predecesores[q] << endl;
		}
		cout << "cantidad de pre: " << cantProd << endl;

		input=manXML.axiom.getAxiom();
		cout << "Axioma -----> " << input << endl;
		cout << "Alfabeto ---> " << manXML.alpha.V << endl;
		char z[2];
		z[0]=input[0];
		z[1]='\0';
		cout << "Produccion para el Axioma " << input << "---> " << manXML.prod.getProd(z,manXML.alpha) << endl;
		/*Funciones que comienzan a contabilizar el tiempo*/

//		cout << typeid(manXML.prod.P).name() << endl;

		start = clock();//Para los segundos de procesamiento
		start_t=time(NULL);//Para el tiempo de ejecución
		for(int j=0; j<iteraciones; j++){
			cout << "-------------------------------------" << endl;
			/*En el arreglo result se almacenara el indice de donde
			 * se encontro la posición del precedesor, esto se debe a que
			 * al kernel que se encarga de buscar la producción esta limitado
			 * y no puede recibir como parametro pointers to pointers ni
			 * clases (solo funciona con lenguaje c plano con restricciones
			 * y limitaciones), el diseño del sistema controla las reglas de
			 * Producción mediante una clase. Posteriomente se crea un arreglo
			 * que solo almacene las predecesores, el kernel recibe el
			 * simbolo a buscar y el arreglo de predecesores (char);
			 * los sucesores no pueden ser pasados como paramentros por que
			 * son almacenados como arreglo de cadenas y por las limitantes
			 * del lenguaje OpenCL C; no es posible pasar un arreglo de apuntadores
			 * a arreglos de caracteres, ya que se formaria la forma
			 * pointers to pointers; y como ya se menciono no es
			 * soportado por OpenCL C*/
			cout << "Creo el arreglo de result de tamaño: " << input.length() << endl;
			result=new int[input.length()];
			cout << "Pasada numero: " << j+1;
			/*Procesamiento en Paralelo*/
			cl_device_id device;
			cl_command_queue commandQueue=openCl.CreateCommandQueue(&device);
			cl_program program=openCl.CreateProgram(device);
			//En input tenemos la cadena que se tiene que procesar cada simbolo
			//en la primera vez solo corresponde al axioma
			char *cadenaSystema=(char*) input.c_str();
//			cout << "cadena del sistema de Lindenmyer: " << cadenaSystema << endl;
			if (!openCl.CreateMemObjects(memObjects, cadenaSystema, predecesores,cantProd,result))
			{
				cerr << "Error al crear la memoria de los argumentos" << endl;
//				Cleanup(context, commandQueue, program, kernel, memObjects);
//				return 1;
			}
			/*Creamos el kernel*/
			cl_kernel kernel=openCl.CreateKernel(program);

			// Set the kernel arguments (result, a, b)
			openCl.SetKernelArg(kernel,memObjects);

			/*Variables que controlan el indice local de cada kernel
			 * y la cantidad total de kernels*/
			size_t globalWorkSize[1] = { input.size() };
			size_t localWorkSize[1] = { 1 };

			// Queue the kernel up for execution across the input string
			errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,globalWorkSize, localWorkSize,0, NULL, NULL);

			if (errNum != CL_SUCCESS)
			{
				cerr << "Error queuing kernel for execution." << endl;
//				Cleanup(context, commandQueue, program, kernel, memObjects);
//				return 1;
			}
			// Read the output buffer back to the Host
			//	errNum = clEnqueueReadBuffer(commandQueue, memObjects[2],CL_TRUE, 0, ARRAY_SIZE * sizeof(float),result, 0, NULL, NULL);
			errNum = clEnqueueReadBuffer(commandQueue, memObjects[3],CL_TRUE, 0,sizeof(int)*(input.length()),result, 0, NULL, NULL);
			//en temp almacenaremos la cadena resultante

//			cout << "size: "<< input.length() << endl;
			for(int i=0; i<input.length(); i++){
//				cout << "\nresult " << result[i] << " i: "<< i << endl;
				if(result[i]!=(-1)){
					temp+=manXML.prod.P[result[i]][1];
				}else{
					cout << "\nError simbolo no encontrado en las reglas de Producción: " << input[i] << endl;
				}
			}
//			cout << "La cadena termina: " << temp << endl;
			input=temp;
			temp="";
			delete[] result;
		}
		/*Funciones que capturan el tiempo al finalizar el ciclo*/
		end=clock();
		end_t=time(NULL);
		timeStartPtr = localtime( &start_t );
//		timeEndPtr = localtime( &end_t );/se supone que se contaba el tiempo pero no funciona, toma el mismo tiempo que de inicio

		/*Ponemos mensajes en consola*/
		/*Tiempo del sistema*/
		printf( "\nBitacora: %s", asctime((timeStartPtr)));
		//	printf( "Final: %s\n", asctime(tiempoFinalPtr) );//se supone que se contaba el tiempo pero no funciona
		/*Tiempo de procesamiento*/
		printf("\nTiempo de procesamiento en segundos -> Inicio: %f Fin: %f",start/(double)CLOCKS_PER_SEC,end/(double)CLOCKS_PER_SEC);
		printf( "\nTotal de segundos de procesamiento: %f s\n", (end-start)/(double)CLOCKS_PER_SEC );
		/*Tiempo de ejecución*/
		printf( "Tiempo de ejecución en segundos -> Inicio: %ld Fin: %ld\n",start_t,end_t );
		printf( "Total de segundos transcurridos desde el comienzo del ciclo: %f s\n", difftime(end_t, start_t) );

		/*Almacenamos en el archivo*/
		cadena="\n-----------------------------------------------------------------------------";
		fputs(cadena.c_str(),file);
		cadena="\nBitacora -> "+string(asctime(timeStartPtr));
		fputs(cadena.c_str(),file);

		cadena="L-System -> "+manXML.nameSystem;
		fputs(cadena.c_str(),file);

		convert << (iteraciones);
		cadena="\nIteraciones -> "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		convert << (start/(double)CLOCKS_PER_SEC);
		cadena="\nTiempo de procesamiento en segundos -> Inicio: "+convert.str();
		convert.str("");
		convert << (end/(double)CLOCKS_PER_SEC);
		cadena=cadena+" Fin: "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		convert << ((end-start)/(double)CLOCKS_PER_SEC);
		cadena="\nTotal de segundos de procesamiento: "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		convert << start_t;
		cadena="\nTiempo de ejecución en segundos -> Inicio: "+convert.str();
		convert.str("");
		convert << end_t;
		cadena=cadena+" Fin: "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		convert << difftime(end_t, start_t);
		cadena="\nTotal de segundos transcurridos desde el comienzo del ciclo: "+convert.str();
		convert.str("");
		fputs(cadena.c_str(),file);

		fclose(file);
		/*Fin del uso de archivo*/
	}else{//fallo el managerXML

	}
}

int main() {
	int *s=new int[282607402];//marca error de bad_alloc
	clCreateBuffer(context, CL_MEM_READ_WRITE,1130429608,NULL, NULL);
//	leerCadena();
//	control();
	return 0;
}
