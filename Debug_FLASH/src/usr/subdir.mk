################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/usr/ecudb-fmon.c 

OBJS += \
./src/usr/ecudb-fmon.o 

C_DEPS += \
./src/usr/ecudb-fmon.d 


# Each subdirectory must supply rules for building sources it contributes
src/usr/%.o: ../src/usr/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/usr/ecudb-fmon.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


