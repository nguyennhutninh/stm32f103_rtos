/**
  ******************************************************************************
  * @file    stm32f1xx_nucleo.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-February-2014
  * @brief   This file contains all the functions prototypes for the
  *          stm32f1xx_nucleo.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IO_CFG_H
#define __IO_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "../common/cmd_line.h"

/*****************************************************************************
  *Pin map led life
 ******************************************************************************/
#define LED_LIFE_IO_PIN								(GPIO_Pin_7)
#define LED_LIFE_IO_PORT							(GPIOE)
#define LED_LIFE_IO_CLOCK							(RCC_APB2Periph_GPIOE)

extern void led_life_init();
extern void led_life_on();
extern void led_life_off();

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __IO_CFG_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
