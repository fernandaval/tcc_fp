################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TCC\ FP.cpp \
../src/VInterfaceDTO.cpp \
../src/matching.cpp \
../src/minutia.cpp \
../src/minutiaeExtraction.cpp \
../src/preProcessing.cpp \
../src/window.cpp 

OBJS += \
./src/TCC\ FP.o \
./src/VInterfaceDTO.o \
./src/matching.o \
./src/minutia.o \
./src/minutiaeExtraction.o \
./src/preProcessing.o \
./src/window.o 

CPP_DEPS += \
./src/TCC\ FP.d \
./src/VInterfaceDTO.d \
./src/matching.d \
./src/minutia.d \
./src/minutiaeExtraction.d \
./src/preProcessing.d \
./src/window.d 


# Each subdirectory must supply rules for building sources it contributes
src/TCC\ FP.o: ../src/TCC\ FP.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fpic -std=c++11 -MMD -MP -MF"src/TCC FP.d" -MT"src/TCC\ FP.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fpic -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


