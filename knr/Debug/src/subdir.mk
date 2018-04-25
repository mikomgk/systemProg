################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/1-13.c \
../src/1-13v.c \
../src/1-14.c \
../src/1-14v.c \
../src/1-18.c \
../src/1-19.c \
../src/1-24.c \
../src/2-1.c 

OBJS += \
./src/1-13.o \
./src/1-13v.o \
./src/1-14.o \
./src/1-14v.o \
./src/1-18.o \
./src/1-19.o \
./src/1-24.o \
./src/2-1.o 

C_DEPS += \
./src/1-13.d \
./src/1-13v.d \
./src/1-14.d \
./src/1-14v.d \
./src/1-18.d \
./src/1-19.d \
./src/1-24.d \
./src/2-1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -Im -O0 -g -pedantic -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


