################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/ecudb.c 

OBJS += \
./src/lib/ecudb.o 

C_DEPS += \
./src/lib/ecudb.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/%.o: ../src/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/lib/ecudb.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


