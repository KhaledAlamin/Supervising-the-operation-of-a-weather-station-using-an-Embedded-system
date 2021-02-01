################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/KSDK/platform/hal/sim/MK64F12/fsl_sim_hal_K64F12.c 

OBJS += \
./KSDK/platform/hal/sim/MK64F12/fsl_sim_hal_K64F12.o 

C_DEPS += \
./KSDK/platform/hal/sim/MK64F12/fsl_sim_hal_K64F12.d 


# Each subdirectory must supply rules for building sources it contributes
KSDK/platform/hal/sim/MK64F12/fsl_sim_hal_K64F12.o: C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/KSDK/platform/hal/sim/MK64F12/fsl_sim_hal_K64F12.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DDEBUG -DCPU_MK64FN1M0VMD12 -DKDS -DFSL_RTOS_UCOSIII -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/.." -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../BSP" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../BSP/KSDK" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M4/Generic/GNU" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/rtos/uCOSIII/src/uCOS-III/Source" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M4/GNU" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/rtos/uCOSIII/src/uC-CPU" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/rtos/uCOSIII/src/uC-LIB" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/utilities" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/osa" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/CMSIS/Include" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/CMSIS/Include/device" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/startup/MK64F12" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/adc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/can" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/dac" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/dmamux" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/dspi" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/edma" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/enet" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/flextimer" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/gpio" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/i2c" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/lptmr" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/mcg" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/osc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/pdb" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/pit" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/pmc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/port" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/rtc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/sai" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/sdhc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/sim" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/smc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/uart" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/hal/wdog" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/adc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/adc/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/can" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/can/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/edma" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/edma/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/dac" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/dac/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/dspi/dspi_master" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/dspi/dspi_slave" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/dspi/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/enet" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/enet/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/enet/src" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/flash" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/flextimer" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/flextimer/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/gpio" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/gpio/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/i2c/i2c_master" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/i2c/i2c_slave" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/i2c/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/lptmr" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/lptmr/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/mmcau" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/pdb" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/pdb/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/pit" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/pit/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/rtc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/rtc/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/sai" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/sai/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/sdhc" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/sdhc/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/sdcard" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/soundcard" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/uart" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/uart/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/wdog" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/drivers/wdog/common" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/system/clock" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/system/hwtimer" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/system/interrupt" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/platform/system/power" -I"C:/Users/TOSHIBA/Desktop/assi/Micrium/Examples/Freescale/FRDM-K64F/OS3-KSDK/KDS/../../../KSDK/boards/frdmk64f120m" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


