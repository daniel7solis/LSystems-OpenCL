################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Alphabet.cpp \
../src/Lsystem1.cpp \
../src/ObjChar.cpp \
../src/Productions.cpp 

OBJS += \
./src/Alphabet.o \
./src/Lsystem1.o \
./src/ObjChar.o \
./src/Productions.o 

CPP_DEPS += \
./src/Alphabet.d \
./src/Lsystem1.d \
./src/ObjChar.d \
./src/Productions.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


