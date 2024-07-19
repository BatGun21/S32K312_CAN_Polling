################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/butl/evcc_ecudb-binutil.c \
../src/butl/vector__xxx_ecudb-binutil.c 

OBJS += \
./src/butl/evcc_ecudb-binutil.o \
./src/butl/vector__xxx_ecudb-binutil.o 

C_DEPS += \
./src/butl/evcc_ecudb-binutil.d \
./src/butl/vector__xxx_ecudb-binutil.d 


# Each subdirectory must supply rules for building sources it contributes
src/butl/%.o: ../src/butl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/butl/evcc_ecudb-binutil.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


