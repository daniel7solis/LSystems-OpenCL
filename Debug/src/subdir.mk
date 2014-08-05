################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Alphabet.cpp \
../src/Axiom.cpp \
../src/Lsystem1.cpp \
../src/ObjChar.cpp \
../src/OpenCLSetUp.cpp \
../src/Productions.cpp \
../src/managerXML.cpp 

OBJS += \
./src/Alphabet.o \
./src/Axiom.o \
./src/Lsystem1.o \
./src/ObjChar.o \
./src/OpenCLSetUp.o \
./src/Productions.o \
./src/managerXML.o 

CPP_DEPS += \
./src/Alphabet.d \
./src/Axiom.d \
./src/Lsystem1.d \
./src/ObjChar.d \
./src/OpenCLSetUp.d \
./src/Productions.d \
./src/managerXML.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/libxml++-2.6 -I/usr/local/lib/libxml++-2.6/include -I/usr/include/libxml2 -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/local/lib -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


