################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Untitled\ Folder/123.c 

OBJS += \
./src/Untitled\ Folder/123.o 

C_DEPS += \
./src/Untitled\ Folder/123.d 


# Each subdirectory must supply rules for building sources it contributes
src/Untitled\ Folder/123.o: ../src/Untitled\ Folder/123.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -Im -O0 -g -pedantic -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"src/Untitled Folder/123.d" -MT"src/Untitled\ Folder/123.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


