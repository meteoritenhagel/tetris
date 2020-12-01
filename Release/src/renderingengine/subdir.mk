################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/renderingengine/renderingengine.cpp 

OBJS += \
./src/renderingengine/renderingengine.o 

CPP_DEPS += \
./src/renderingengine/renderingengine.d 


# Each subdirectory must supply rules for building sources it contributes
src/renderingengine/%.o: ../src/renderingengine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -I/media/tristan/TRISTAN/Intel/compilers_and_libraries_2020.0.166/linux/ipp/include -I/media/tristan/TRISTAN/Intel/compilers_and_libraries_2020.0.166/linux/mkl/include -I/media/tristan/TRISTAN/Intel/compilers_and_libraries_2020.0.166/linux/pstl/include -I/media/tristan/TRISTAN/Intel/compilers_and_libraries_2020.0.166/linux/pstl/stdlib -I/media/tristan/TRISTAN/Intel/compilers_and_libraries_2020.0.166/linux/tbb/include -I/media/tristan/TRISTAN/Intel/compilers_and_libraries_2020.0.166/linux/daal/include -I/usr/include/SDL2 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


