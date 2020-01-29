################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CmdHandler.cpp \
../src/Gateway.cpp 

OBJS += \
./src/CmdHandler.o \
./src/Gateway.o 

CPP_DEPS += \
./src/CmdHandler.d \
./src/Gateway.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__LINUX__ -I"/home/ltzd/workspace/NetBlue/Common/src" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


