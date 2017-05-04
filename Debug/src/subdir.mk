################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Application.cpp \
../src/Bus.cpp \
../src/Company.cpp \
../src/Driver.cpp \
../src/Line.cpp \
../src/PROG_Project2.cpp \
../src/Shift.cpp 

OBJS += \
./src/Application.o \
./src/Bus.o \
./src/Company.o \
./src/Driver.o \
./src/Line.o \
./src/PROG_Project2.o \
./src/Shift.o 

CPP_DEPS += \
./src/Application.d \
./src/Bus.d \
./src/Company.d \
./src/Driver.d \
./src/Line.d \
./src/PROG_Project2.d \
./src/Shift.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


