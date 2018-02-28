/**
 ******************************************************************************
 * @Author: ThanNT
 * @Date:   05/09/2016
 ******************************************************************************
**/
#ifndef __SYS_CFG_H__
#define __SYS_CFG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "stm32f10x.h"

#define SHELL_BUFFER_LENGHT				(32)

struct shell_t {
	uint8_t index;
	uint8_t data[SHELL_BUFFER_LENGHT];
} shell;

/* USART Communication boards Interface */
#define USARTx                           USART1
#define USARTx_CLK                       RCC_APB2Periph_USART1
#define USARTx_IRQn                      USART1_IRQn

#define USARTx_TX_PIN                    GPIO_Pin_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_GPIO_CLK               RCC_APB2Periph_GPIOA
#define USARTx_TX_SOURCE                 GPIO_PinSource9

#define USARTx_RX_PIN                    GPIO_Pin_10
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_GPIO_CLK               RCC_APB2Periph_GPIOA
#define USARTx_RX_SOURCE                 GPIO_PinSource10

extern void xputchar(uint8_t c);
extern uint8_t sys_ctrl_shell_get_char();
extern void sys_irq_shell();
extern void sys_cfg_console();
extern void task_shell(uint8_t *msg);

#ifdef __cplusplus
}
#endif

#endif //__SYS_CFG_H__
