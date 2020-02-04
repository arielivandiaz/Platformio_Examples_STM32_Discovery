
#include "main.h"


void LED_Init(int pin);

int main(void)
{
  uint16_t result;

  HAL_Init();

  LED_Init(LED_PIN_1);
  LED_Init(LED_PIN_2);
  LED_Init(LED_PIN_3);
  LED_Init(LED_PIN_4);

  TM_USART_Init(USART3, TM_USART_PinsPack_1, 9600);

  TM_USART_Puts(USART3, "Hello world\n\r");
 

  TM_ADC_Init(ADC1, TM_ADC_Channel_11);

  while (1)
  {
    char buff[20];

    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_1);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_2);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_3);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_4);
    HAL_Delay(50);

    result = TM_ADC_Read(ADC1, TM_ADC_Channel_11);
    
    sprintf(buff, "%4d\n\r", result);
    TM_USART_Puts(USART3, buff);
  }
}

void LED_Init(int pin)
{
  LED_GPIO_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}
