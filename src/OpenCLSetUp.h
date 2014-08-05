/*
 * OpenCLSetUp.h
 *
 *  Created on: 01/08/2014
 *      Author: dani
 */

#ifndef OPENCLSETUP_H_
#define OPENCLSETUP_H_

#include "Productions.h"
/*Headers para OpenCl*/
#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#include <CL/cl.h>
/**/
#include <string>

using namespace std;

class OpenCLSetUp {
public:
	string FilesPath;
	cl_platform_id * platformIds;
	cl_device_id * deviceIds;
	cl_uint numDevices;
	cl_context context;
//	cl_program program;
//	cl_kernel kernel;
	OpenCLSetUp();
	virtual ~OpenCLSetUp();
	void Platforms();
	void DisplayPlatformInfo(cl_platform_id id,cl_platform_info name,std::string str);
	void Devices(cl_platform_id platform);
	void CreateContext();
	cl_program CreateProgram(cl_device_id device);
//	cl_command_queue CreateCommandQueue(cl_context context,cl_device_id *device);
	bool CreateMemObjects(cl_mem memObjects[3],char *sym, char *P, int cantP, int *result);
	cl_kernel CreateKernel(cl_program program);
	cl_command_queue CreateCommandQueue(cl_device_id *dev);
	void SetKernelArg(cl_kernel kernel,cl_mem *memObjects);
};

#endif /* OPENCLSETUP_H_ */
