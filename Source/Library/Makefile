

GCC_PATH	= /home/fanning/workspace/tools/gcc-arm-none-eabi-5_4-2016q3
OPENOCD_PATH	= /home/fanning/workspace/tools/openocd-0.9.0

#CC		=	/home/fanning/workspace/tools/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-gcc
CC		=	$(GCC_PATH)/bin/arm-none-eabi-gcc
AR		=	$(GCC_PATH)/bin/arm-none-eabi-ar

###########################################

vpath %.c STM32F10x_StdPeriph_Driver/src

CFLAGS  = -g -O2 -Wall
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3
CFLAGS += -ffreestanding -nostdlib
CFLAGS += -DSTM32F10X_MD
CFLAGS += -includestm32f10x_conf.h -ICMSIS/Include -ICMSIS/Device/ST/STM32F10x/Include -ISTM32F10x_StdPeriph_Driver/inc

SRCS = stm32f10x_adc.c stm32f10x_cec.c stm32f10x_crc.c \
	stm32f10x_dac.c stm32f10x_dbgmcu.c stm32f10x_dma.c stm32f10x_exti.c \
	stm32f10x_flash.c stm32f10x_gpio.c stm32f10x_i2c.c stm32f10x_iwdg.c \
	misc.c stm32f10x_pwr.c stm32f10x_rcc.c stm32f10x_rtc.c \
	stm32f10x_spi.c stm32f10x_tim.c \
	stm32f10x_usart.c stm32f10x_wwdg.c

OBJS = $(SRCS:.c=.o)

.PHONY: libstm32f1.a

all: libstm32f1.a

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

libstm32f1.a: $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	rm -f $(OBJS) libstm32f1.a
