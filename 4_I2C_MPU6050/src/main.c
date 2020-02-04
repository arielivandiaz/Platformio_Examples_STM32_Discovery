
#include "main.h"

TM_MPU6050_t MPU6050;

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

  if (TM_MPU6050_Init(&MPU6050, TM_MPU6050_Device_0, TM_MPU6050_Accelerometer_8G, TM_MPU6050_Gyroscope_250s) == TM_MPU6050_Result_Ok) {

        TM_USART_Puts(USART3, "MPU6050 Detected\n");
	}

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

    TM_MPU6050_ReadAll(&MPU6050);

    result = TM_ADC_Read(ADC1, TM_ADC_Channel_11);
    
    	/* Raw data are available for use as needed */
		//MPU6050.Accelerometer_X;
		//MPU6050.Accelerometer_Y;
		//MPU6050.Accelerometer_Z;
		//MPU6050.Gyroscope_X;
		//MPU6050.Gyroscope_Y;
		//MPU6050.Gyroscope_Z;
		//MPU6050.Temperature;
    
    sprintf(buff, "%f\n\r", MPU6050.Temperature);
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
