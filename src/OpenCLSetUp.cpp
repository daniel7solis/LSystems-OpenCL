/*
 * OpenCLSetUp.cpp
 *
 *  Created on: 01/08/2014
 *      Author: dani
 */

#include "OpenCLSetUp.h"
#include "Productions.h"
/*Headers para OpenCl*/
#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#include <CL/cl.h>
/**/
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

OpenCLSetUp::OpenCLSetUp() {
	// TODO Auto-generated constructor stub
	platformIds=NULL;
	deviceIds=NULL;
	numDevices=-1;
	context=NULL;
	this->CreateContext();
//	this->CreateCommandQueue();
//	this->CreateProgram();
//	this->CreateKernel();
}

OpenCLSetUp::~OpenCLSetUp() {
	// TODO Auto-generated destructor stub
}

/*Función que se encarga de obtener las plataformas de OpenCl instaladas en el equipo,
 * y obtener la infoiamción*/
void OpenCLSetUp::Platforms(){
	cl_int errNum;
	cl_uint numPlatforms;

	/*Función que si se pasa como NULL el segundo parametro, retorna la cantidad
	 * de Plataformas disponibles; los argumentos son:
	 * clGetPlatformIDs(cl_uint num_entries,cl_platform_id * platforms,cl_uint * num_platforms)
	 * Una plataforma es un perfil que describe las caracteristicas
	 * y capacidades de la version particular dela version de OpenCl
	 * soportada*/
	// First, query the total number of platforms
	errNum = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (errNum != CL_SUCCESS || numPlatforms <= 0){
		std::cerr << "Failed to find any OpenCL platform." << std::endl;
		return;
	}

	/*Ahora creamos la locación en memoria de las plataformas
	 * que estan instaladas en el equipo*/
	// Next, allocate memory for the installed platforms, and query
	// to get the list.
	platformIds = (cl_platform_id *)malloc(sizeof(cl_platform_id) * numPlatforms);
	/*Obtenemos el Id de cada plataforma*/
	// First, query the total number of platforms
	errNum = clGetPlatformIDs(numPlatforms, platformIds, NULL);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
		return;
	}
	std::cout << "Numero de plataformas en tu equipo: \t" << numPlatforms << std::endl;

	/*Para cada plataforma en el equipo obtenemos su información*/
	// Iterate through the list of platforms displaying associated
	// information
	for (cl_uint i = 0; i < numPlatforms; i++) {
		// First we display information associated with the platform
		cout << "Información de la plataforma: " << i+1 << endl;
		DisplayPlatformInfo(platformIds[i], CL_PLATFORM_NAME, "CL_PLATFORM_NAME");
		DisplayPlatformInfo(platformIds[i], CL_PLATFORM_VENDOR, "CL_PLATFORM_VENDOR");
		DisplayPlatformInfo(platformIds[i], CL_PLATFORM_PROFILE, "CL_PLATFORM_PROFILE");
		DisplayPlatformInfo(platformIds[i], CL_PLATFORM_VERSION, "CL_PLATFORM_VERSION");
		DisplayPlatformInfo(platformIds[i],	CL_PLATFORM_EXTENSIONS,"CL_PLATFORM_EXTENSIONS");
		Devices(platformIds[i]);
	}
}

/*Función que se encaraga de mostrar la información que recibe de la plataforma*/
void OpenCLSetUp::DisplayPlatformInfo(cl_platform_id id,cl_platform_info name,std::string str){
	cl_int errNum;
	std::size_t paramValueSize;

	/*Obtiene el tamaño del parametro en la var paramValueSize*/
	errNum = clGetPlatformInfo(id,name,0,NULL,&paramValueSize);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to find OpenCL platform " << str << "." << std::endl;
		return;
	}
	/*Convierto a char lo que contiene la memoria que se obtubo en el paso anterior*/
	char * info = (char *)alloca(sizeof(char) * paramValueSize);
	/*Consulto el parametro buscado que se gurada en la misma locacion de mem*/
	errNum = clGetPlatformInfo(id,name,paramValueSize,info,NULL);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to find OpenCL platform " << str << "." << std::endl;
		return;
	}
	std::cout << "\t" << str << ":\t" << info << std::endl;
}

/*Función que obtine los devices de la plataforma*/
void OpenCLSetUp::Devices(cl_platform_id platform){
	cl_int errNum;

	errNum = clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,0,NULL,&numDevices);
	if (numDevices < 1)
	{
		std::cout << "No devices found for platform "<< platform << std::endl;
//		exit(1);
	}else{
		deviceIds = (cl_device_id *)malloc(sizeof(cl_device_id) * numDevices);
		errNum = clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,numDevices,deviceIds,NULL);
		if(errNum != CL_SUCCESS){
			cerr << "Error en dispositivos" << endl;
		}
	}
	std::cout << "\tNumero de dispositivos en la plataforma: " << numDevices << std::endl;

	/*Para cada plataforma en el equipo obtenemos su información POR EL MOMENTO NO FUNCIONA*/
	// Iterate through the list of platforms displaying associated
	// information
	cl_uint maxComputeUnits=0;
	size_t sizeParam;
	for (cl_uint i = 0; i < numDevices; i++) {
		cout << "	Dispositivo numero: " << i+1 << endl;
		// First we display information associated with the platform
		//DisplayDevicesInfo(deviceIds[i], CL_DEVICE_MAX_COMPUTE_UNITS, "CL_DEVICE_MAX_COMPUTE_UNITS");
		errNum = clGetDeviceInfo(deviceIds[i],CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_uint),&maxComputeUnits,&sizeParam);
		cout << "		El dispositivo tiene un maximo de unidaddes de computo: " << maxComputeUnits << endl;
	}
}

void OpenCLSetUp::CreateContext(){
	cl_int errNum;

	/*PRIMERO CONSULTO LA PLATAFORMA*/
	Platforms();

	cl_context_properties properties[] =
	{
			CL_CONTEXT_PLATFORM, (cl_context_properties)platformIds[0], 0
	};

//	context = clCreateContext(properties,numDevices,deviceIds,NULL,NULL,&errNum);
	context = clCreateContextFromType(properties,CL_DEVICE_TYPE_ALL,NULL,NULL,&errNum);

	if(errNum != CL_SUCCESS){
		cout << "Error context" <<  endl;
	}
}

cl_program OpenCLSetUp::CreateProgram(cl_device_id device){
	cl_int errNum;
	cl_program program;
	FilesPath+"kernel.cl";
	ifstream kernelFile(FilesPath.c_str(), ios::in);
	if (!kernelFile.is_open())
	{
		cerr << "Failed to open file for reading: " << FilesPath <<endl;
		return NULL;
	}
	ostringstream oss;
	oss << kernelFile.rdbuf();

	string srcStdStr = oss.str();
	const char *srcStr = srcStdStr.c_str();
	program = clCreateProgramWithSource(context, 1,(const char**)&srcStr,NULL, NULL);
	if (program == NULL)
	{
		cerr << "Failed to create CL program from source." << endl;
		return NULL;
	}

	errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (errNum != CL_SUCCESS)
	{
		// Determine the reason for the error
		char buildLog[16384];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,sizeof(buildLog), buildLog, NULL);
		cerr << "Error in kernel: " << endl;
		cerr << buildLog;
		clReleaseProgram(program);
		return NULL;
	}
	return program;
}


cl_command_queue OpenCLSetUp::CreateCommandQueue(cl_device_id *dev){
	cl_int errNum;
	cl_device_id *devices;
	cl_command_queue commandQueue = NULL;
	size_t deviceBufferSize = -1;

	// First get the size of the devices buffer
	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL,&deviceBufferSize);
	if (errNum != CL_SUCCESS)
	{
		cerr << "Failed call to clGetContextInfo(...,CL_CONTEXT_DEVICES,...)";
		return NULL;
	}

	if (deviceBufferSize <= 0)
	{
		cerr << "No devices available.";
		return NULL;
	}

	// Allocate memory for the devices buffer
	devices = new cl_device_id[deviceBufferSize /sizeof(cl_device_id)];

	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES,deviceBufferSize, devices, NULL);

	if (errNum != CL_SUCCESS)
	{
		cerr << "Failed to get device IDs";
		return NULL;
	}

	//you would likely use all available
//	devices or choose the highest performance device based on
//	OpenCL device queries.
	commandQueue = clCreateCommandQueue(context,devices[0], 0, NULL);

	if (commandQueue == NULL)
	{
		cerr << "Failed to create commandQueue for device 0";
		return NULL;
	}

	*dev = devices[0];
	delete [] devices;
	return commandQueue;
}

bool OpenCLSetUp::CreateMemObjects(cl_mem memObjects[4],char *sym, char *P,int cantP,int *result){
//	memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,sizeof(float) * ARRAY_SIZE, a,NULL);
//	memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY |CL_MEM_COPY_HOST_PTR,sizeof(float) * ARRAY_SIZE, b,NULL);
//	memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE,sizeof(float) * ARRAY_SIZE,NULL, NULL);
	cout<< "size of P: " << strlen(P)<< " Size of sym: "<< sizeof(int)*(strlen(sym)) <<endl;
	memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,sizeof(char)*(strlen(sym)),sym,NULL);//cadena del sistema
	memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY |CL_MEM_COPY_HOST_PTR,sizeof(char)*(strlen(P)),P,NULL);//arreglo de predecesores
	memObjects[2] = clCreateBuffer(context, CL_MEM_READ_ONLY |CL_MEM_COPY_HOST_PTR,sizeof(int),&cantP,NULL);//cantidad de predecesores
	memObjects[3] = clCreateBuffer(context, CL_MEM_READ_WRITE,sizeof(int)*(strlen(sym)),NULL, NULL);//memoria para el arreglo de result

	if (memObjects[0] == NULL || memObjects[1] == NULL || memObjects[2] == NULL || memObjects[3] == NULL)
	{
		cerr << "Error creating memory objects." << endl;
		return false;
	}
	return true;
}

cl_kernel OpenCLSetUp::CreateKernel(cl_program program){
	// Create OpenCL kernel
	cl_kernel kernel;
	kernel = clCreateKernel(program, "kernel1", NULL);
	if (kernel == NULL)
	{
		cerr << "Failed to create kernel" << endl;
//		Cleanup(context, commandQueue, program, kernel, memObjects);
		return NULL;
	}
	return kernel;
}

void OpenCLSetUp::SetKernelArg(cl_kernel kernel,cl_mem *memObjects){
	cl_int errNum;
	errNum = clSetKernelArg(kernel, 0,sizeof(cl_mem), &memObjects[0]);
	errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem),&memObjects[1]);
	errNum |= clSetKernelArg(kernel, 2, sizeof(cl_mem),&memObjects[2]);
	errNum |= clSetKernelArg(kernel, 3, sizeof(cl_mem),&memObjects[3]);

	if (errNum != CL_SUCCESS)
	{
		cerr << "Error setting kernel arguments." << endl;
		//			Cleanup(context, commandQueue, program, kernel, memObjects);
		//			return 1;
	}
}
