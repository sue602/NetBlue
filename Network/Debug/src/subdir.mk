################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Network.cpp \
../src/ServerConnection.cpp \
../src/ServerRejectFilter.cpp 

OBJS += \
./src/Network.o \
./src/ServerConnection.o \
./src/ServerRejectFilter.o 

CPP_DEPS += \
./src/Network.d \
./src/ServerConnection.d \
./src/ServerRejectFilter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__LINUX__ -I"/home/ltzd/workspace/NetBlue/Common/src" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


