#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_hal.h"

#define LED_PIN                                GPIO_PIN_13
#define LED_GPIO_PORT                          GPIOD
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()

#endif // MAIN_H