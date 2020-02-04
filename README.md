# Platformio Examples STM32F4 Discovery


configure your board type to use TM libraries correctly.


src/defines.h

``
#define STM32F4XX = 1
#define STM32F4xx = 1
``



## 3 ADC

Fixed line 175 tm_stm32_adc.c 

Replace this:

``
//if (HAL_ADC_GetState(&AdcHandle) == HAL_ADC_STATE_EOC_REG) {
``

with:

``
	if (HAL_ADC_GetState(&AdcHandle) == 0x201) {
``

Use https://github.com/mpaland/printf if you have printf/sprintf problems


cAUTION



Sources

Replace http://stm32f4-discovery.com with https://stm32f4-discovery.net/
https://github.com/mpaland/printf