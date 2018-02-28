/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "FreeRTOS.h"
#include "task.h"

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#include "sys_cfg.h"
#include "../common/xprintf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static __IO uint32_t TimingDelay;

uint8_t cmd_flag = 0;

void prvSetupHardware(void) {
	sys_cfg_console();
	led_life_init();
}

void task_life(void *dummy) {
	(void)dummy;

	while (1) {
		led_life_on();
		vTaskDelay(600);
		led_life_off();
		vTaskDelay(600);
	}
}

void systemConsole(void *dummy) {
	(void)dummy;

	while (1) {
		if (cmd_flag) {
			task_shell(shell.data);
			cmd_flag = 0;
		}
		vTaskDelay(10);
	}
}

void vTaskInit(void) {
	xTaskCreate(task_life,
				(const signed char *)"task_life",
				configMINIMAL_STACK_SIZE,
				NULL,                 /* pvParameters */
				tskIDLE_PRIORITY + 1, /* uxPriority */
				NULL                  /* pvCreatedTask */);

	xTaskCreate(systemConsole,
				(const signed char *)"systemConsole",
				configMINIMAL_STACK_SIZE,
				NULL,                 /* pvParameters */
				tskIDLE_PRIORITY + 2, /* uxPriority */
				NULL                  /* pvCreatedTask */);
}

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int main(void) {
	/*!< At this stage the microcontroller clock setting is already configured,
	 * this is done through SystemInit() function which is called from startup
	 * file (startup_stm32f2xx_xx.s) before to branch to application main.
	 * To reconfigure the default setting of SystemInit() function, refer to
	 * system_stm32f2xx.c file */

	prvSetupHardware();

	vTaskInit();

	vTaskStartScheduler();

	return (0);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line) {
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	(void)file;
	(void)line;

	/* Infinite loop */
	while (1) {
	}
}

#endif /* ifdef  USE_FULL_ASSERT */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
