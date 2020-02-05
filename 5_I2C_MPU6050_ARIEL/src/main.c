
#include "main.h"

uint8_t MPU6050 = MPU6050_I2C_ADDR;

void LED_Init(int pin);

int main(void)
{

  HAL_Init();

  LED_Init(LED_PIN_1);
  LED_Init(LED_PIN_2);
  LED_Init(LED_PIN_3);
  LED_Init(LED_PIN_4);

  TM_USART_Init(USART3, TM_USART_PinsPack_1, 9600);



  TM_ADC_Init(ADC1, TM_ADC_Channel_11);

  if (I2C_Device_Init(MPU6050, 0x68) != 0)
    TM_USART_Puts(USART3, "Error I2C\n\r");
  else
    TM_USART_Puts(USART3, "Device I2C Conected\n\r");


  if (  MPU_Config(MPU6050) != 0)
    TM_USART_Puts(USART3, "Error Configuring I2C\n\r");
  else
    TM_USART_Puts(USART3, "Device I2C Configured\n\r");




  while (1)
  {
    float temperature;
    int16_t adc;
    char buff[20];

    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_1);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_2);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_3);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN_4);
    HAL_Delay(50);

    //HMC5883L_ReadAll(&HMC5883L);

    adc = TM_ADC_Read(ADC1, TM_ADC_Channel_11);

   temperature =(float)((int16_t)I2C_Device_ReadValue(MPU6050,MPU6050_TEMP_OUT_H) / (float)340.0 + (float)36.53);
  
    /* Raw data are available for use as needed */

    //sprintf(buff, "%f\n\r", HMC5883L.Compass_X);
    sprintf(buff, "%f\n\r", temperature);
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
