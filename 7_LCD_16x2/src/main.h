#ifndef MAIN_H
#define MAIN_H 


#include "tm_stm32_usart.h"
#include "tm_stm32_adc.h"
#include "stm32f4xx_hal.h"
#include "STM_MY_LCD16X2.h"




#include "printf.h"

/* Private defines -----------------------------------------------------------*/
#define D0_Pin GPIO_PIN_12
#define D0_GPIO_Port GPIOB
#define D1_Pin GPIO_PIN_13
#define D1_GPIO_Port GPIOB
#define D2_Pin GPIO_PIN_14
#define D2_GPIO_Port GPIOB
#define D3_Pin GPIO_PIN_15
#define D3_GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_8
#define D4_GPIO_Port GPIOD
#define D5_Pin GPIO_PIN_9
#define D5_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_10
#define D6_GPIO_Port GPIOD
#define D7_Pin GPIO_PIN_11
#define D7_GPIO_Port GPIOD
#define RS_Pin GPIO_PIN_0
#define RS_GPIO_Port GPIOE
#define E_Pin GPIO_PIN_1
#define E_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */


#define LED_PIN_1                              GPIO_PIN_12
#define LED_PIN_2                              GPIO_PIN_13
#define LED_PIN_3                              GPIO_PIN_14
#define LED_PIN_4                              GPIO_PIN_15
#define LED_GPIO_PORT                          GPIOD
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOD_CLK_ENABLE()


#endif