################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Lsystem_ProcesoParalelo

# Tool invocations
Lsystem_ProcesoParalelo: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/usr/local/include/libxml++-2.6 -L/opt/AMDAPP/lib/x86_64 -L/usr/local/lib/libxml++-2.6/include -L/usr/include/libxml2 -L/usr/include/glibmm-2.4 -L/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -L/usr/include/sigc++-2.0 -L/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -L/usr/include/glib-2.0 -L/usr/lib/x86_64-linux-gnu/glib-2.0/include -L/usr/local/lib -o "Lsystem_ProcesoParalelo" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) Lsystem_ProcesoParalelo
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
