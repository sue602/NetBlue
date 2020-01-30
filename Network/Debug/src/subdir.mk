################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClientConnection.cpp \
../src/ClientRejectFilter.cpp \
../src/ClientsMgr.cpp \
../src/MessageQueue.cpp \
../src/ModuleHandler.cpp \
../src/Network.cpp \
../src/NetworkMgr.cpp 

OBJS += \
./src/ClientConnection.o \
./src/ClientRejectFilter.o \
./src/ClientsMgr.o \
./src/MessageQueue.o \
./src/ModuleHandler.o \
./src/Network.o \
./src/NetworkMgr.o 

CPP_DEPS += \
./src/ClientConnection.d \
./src/ClientRejectFilter.d \
./src/ClientsMgr.d \
./src/MessageQueue.d \
./src/ModuleHandler.d \
./src/Network.d \
./src/NetworkMgr.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__LINUX__ -I"/home/ltzd/workspace/NetBlue/Common/src" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


