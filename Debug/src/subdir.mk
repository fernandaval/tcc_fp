################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TCC\ FP.cpp 

OBJS += \
./src/TCC\ FP.o 

CPP_DEPS += \
./src/TCC\ FP.d 


# Each subdirectory must supply rules for building sources it contributes
src/TCC\ FP.o: ../src/TCC\ FP.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/TCC FP.d" -MT"src/TCC\ FP.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


