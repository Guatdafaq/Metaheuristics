################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../mh/MMDP.cpp \
../mh/TSP.cpp 

OBJS += \
./mh/MMDP.o \
./mh/TSP.o 

CPP_DEPS += \
./mh/MMDP.d \
./mh/TSP.d 


# Each subdirectory must supply rules for building sources it contributes
mh/%.o: ../mh/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


