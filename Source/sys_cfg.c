#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "main.h"

#include "stm32f10x.h"
#include "sys_cfg.h"


#include "common/xprintf.h"
#include "common/cmd_line.h"

extern cmd_line_t lgn_cmd_table[];

void sys_cfg_console() {
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(USARTx_TX_GPIO_CLK | USARTx_RX_GPIO_CLK, ENABLE);

	/* Enable USART clock */
	RCC_APB2PeriphClockCmd(USARTx_CLK, ENABLE);

	/* Configure USART Tx and Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
	GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

	/* USARTx configuration */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTx, &USART_InitStructure);

	/* NVIC configuration */
	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearITPendingBit(USARTx,USART_IT_RXNE);
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

	/* Enable USART */
	USART_Cmd(USARTx, ENABLE);

	xfunc_out = xputchar;
}

void xputchar(uint8_t c) {
	USART_SendData(USART1, (uint8_t)c);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

uint8_t sys_ctrl_shell_get_char() {
	uint8_t c = 0;
	if(USART_GetITStatus(USARTx, USART_IT_RXNE) == SET) {
		c = (uint8_t)USART_ReceiveData(USARTx);
	}
	return c;
}

void sys_irq_shell() {
	uint8_t c = 0;
	c = sys_ctrl_shell_get_char();
	if (shell.index < SHELL_BUFFER_LENGHT - 1) {
		if (c == '\r' || c == '\n') {
			shell.data[shell.index] = c;
			shell.data[shell.index + 1] = 0;
			shell.index = 0;

			cmd_flag = 1;
		}
		else if (c == 8) {
			if (shell.index) {
				shell.index--;
			}
		}
		else {
			shell.data[shell.index++] = c;
		}
	}
	else {
		shell.index = 0;
	}
}

void task_shell(uint8_t *msg) {

	uint8_t fist_char = *msg;

	switch (cmd_line_parser(lgn_cmd_table, msg)) {
	case CMD_SUCCESS:
		break;

	case CMD_NOT_FOUND:
		if (fist_char != '\r' &&
				fist_char != '\n') {
			xprintf("cmd unknown\n");
		}
		break;

	case CMD_TOO_LONG:
		xprintf("cmd too long\n");
		break;

	case CMD_TBL_NOT_FOUND:
		xprintf("cmd table not found\n");
		break;

	default:
		xprintf("cmd error\n");
		break;
	}

	xprintf("#");
}
