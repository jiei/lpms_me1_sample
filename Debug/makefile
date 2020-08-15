################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F3xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
lpms_me1_sample.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
lpms_me1_sample.list \

OBJCOPY_BIN += \
lpms_me1_sample.bin \


# All Target
all: lpms_me1_sample.elf secondary-outputs

# Tool invocations
lpms_me1_sample.elf: $(OBJS) $(USER_OBJS) /home/jack/STM32CubeIDE/workspace_1.3.0/lpms_me1_sample/STM32F303K8TX_FLASH.ld
	arm-none-eabi-gcc -o "lpms_me1_sample.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/jack/STM32CubeIDE/workspace_1.3.0/lpms_me1_sample/STM32F303K8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="lpms_me1_sample.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

lpms_me1_sample.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "lpms_me1_sample.list"
	@echo 'Finished building: $@'
	@echo ' '

lpms_me1_sample.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "lpms_me1_sample.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
