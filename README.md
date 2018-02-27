STM32F103 Demo Application using FreeRTOSv8.0.0
=======================================================

# Description

This is a fork of https://github.com/torstenbitterlich/stm32f1-nucleo-freertos . I just modified the project to be able to run on my stm32f103 board.


# Usage

You will need the arm toolchain to build the project. I used this one: [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded).
Beside that, you need to add the FreeRTOS Source to the project. The current version 8.0.0 works.

If you setup a path to the locally installed toolchain, you will be able to build the project using "make". This will generate the binary, which can be loaded
to the target hardware using openocd/gdb.

