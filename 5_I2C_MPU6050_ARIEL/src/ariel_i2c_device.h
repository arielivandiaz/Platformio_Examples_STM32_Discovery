/**
 * @author  Ariel Ivan Diaz
 * @email   ariel@laguna.com.ar
 * @website http://arielivandiaz.com 
 * @version v1.0
 * @ide     Platformio - Visual Studio Code
 *

***********************************************
*SCL         PB6           Clock line for I2C
*SDA         PB7           Data line for I2C
**********************************************
*/

#ifndef ARIEL_I2C_DEVICE_H
#define ARIEL_I2C_DEVICE_H 

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32fxxx_hal.h"
#include "tm_stm32_i2c.h"


/* Default I2C used */
#ifndef DEVICE_I2C
#define	DEVICE_I2C                    I2C1              /*!< Default I2C */
#define DEVICE_I2C_PINSPACK           TM_I2C_PinsPack_1 /*!< Default I2C pinspack. Check @ref TM_I2C for more information */
#endif

/* Default I2C clock */
#ifndef DEVICE_I2C_CLOCK
#define DEVICE_I2C_CLOCK              400000            /*!< Default I2C clock speed */
#endif



#define DEVICE_I2C_DataRate_8KHz       0   /*!< Sample rate set to 8 kHz */
#define DEVICE_I2C_DataRate_4KHz       1   /*!< Sample rate set to 4 kHz */
#define DEVICE_I2C_DataRate_2KHz       3   /*!< Sample rate set to 2 kHz */
#define DEVICE_I2C_DataRate_1KHz       7   /*!< Sample rate set to 1 kHz */
#define DEVICE_I2C_DataRate_500Hz      15  /*!< Sample rate set to 500 Hz */
#define DEVICE_I2C_DataRate_250Hz      31  /*!< Sample rate set to 250 Hz */
#define DEVICE_I2C_DataRate_125Hz      63  /*!< Sample rate set to 125 Hz */
#define DEVICE_I2C_DataRate_100Hz      79  /*!< Sample rate set to 100 Hz */

#define DEVICE_I2C_SMPLRT_DIV			0x19

#define I2C_ADDR 0xD0

/* Who I am register value */
#define I2C_ID_A 0x68

#define I2C_WHO_AM_I			0x75
#define I2C_PWR_MGMT_1			0x6B
#define I2C_PWR_MGMT_2			0x6C


typedef enum _I2C_ADDRESS_0 {
	I2C_ADDRESS_N_1 = 0x00, /*!< AD0 pin is set to low */
	I2C_ADDRESS_N_2 = 0x02  /*!< AD0 pin is set to high */
} I2C_ADDRESS_0;



typedef enum _DEVICE_I2C_Result_t {
	DEVICE_I2C_Result_Ok = 0x00,          /*!< Everything OK */
	DEVICE_I2C_Result_Error,              /*!< Unknown error */
	DEVICE_I2C_Result_DeviceNotConnected, /*!< There is no device with valid slave address */
	DEVICE_I2C_Result_DeviceInvalid       /*!< Connected device with address is not DEVICE_I2C */
} DEVICE_I2C_Result_t;


int I2C_Device_Init(uint8_t Device_Address, uint8_t Device_ID);

int I2C_Device_SetValue(uint8_t Device_Address, uint8_t AddressValue, uint8_t Value);

int16_t I2C_Device_ReadValue(uint8_t Device_Address, uint8_t AddressValue);


#ifdef __cplusplus
}
#endif

#endif