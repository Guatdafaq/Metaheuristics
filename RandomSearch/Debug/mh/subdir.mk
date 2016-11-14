################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../mh/CPH.cpp \
../mh/CWP.cpp \
../mh/MMDP.cpp \
../mh/TSP.cpp 

OBJS += \
./mh/CPH.o \
./mh/CWP.o \
./mh/MMDP.o \
./mh/TSP.o 

CPP_DEPS += \
./mh/CPH.d \
./mh/CWP.d \
./mh/MMDP.d \
./mh/TSP.d 


# Each subdirectory must supply rules for building sources it contributes
mh/%.o: ../mh/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


