#ifndef MAIN_H
#define MAIN_H 


#include "tm_stm32_usart.h"
#include "tm_stm32_adc.h"
#include "stm32f4xx_hal.h"
#include "mpu6050.h"



#include "printf.h"



#define LED_PIN_1                              GPIO_PIN_12
#define LED_PIN_2                              GPIO_PIN_13
#define LED_PIN_3                              GPIO_PIN_14
#define LED_PIN_4                              GPIO_PIN_15
#define LED_GPIO_PORT                          GPIOD
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOD_CLK_ENABLE()


#endif