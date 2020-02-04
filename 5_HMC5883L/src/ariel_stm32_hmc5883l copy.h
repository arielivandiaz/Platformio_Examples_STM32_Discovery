/**
 * @author  Ariel Ivan Diaz
 * @email   ariel@laguna.com.ar
 * @website http://arielivandiaz.com 
 * @version v1.0
 * @ide     Platformio - Visual Studio Code
 * @license MIT 
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (c) 2020 Ariel Ivan Diaz 

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge,
    publish, distribute, sublicense, and/or sell copies of the Software, 
    and to permit persons to whom the Software is furnished to do so, 
    subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
    AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
   ----------------------------------------------------------------------
@endverbatim
 */

#ifndef ARIEL_STM32_HMC5883L_H
#define ARIEL_STM32_HMC5883L_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/*
@verbatim
HMC5883L     STM32Fxxx     Descrption
 
SCL         PB6           Clock line for I2C
SDA         PB7           Data line for I2C
IRQ         -             User selectable pin if needed. Interrupts for STM must be manually enabled by user.
VCC         3.3V
GND         GND
AD0         -             If pin is low, I2C address is 0xD0, if pin is high, the address is 0xD2
@endverbatim
 */

#include "stm32fxxx_hal.h"
#include "defines.h"
#include "tm_stm32_i2c.h"


/* Default I2C used */
#ifndef HMC5883L_I2C
#define	HMC5883L_I2C                    I2C1              /*!< Default I2C */
#define HMC5883L_I2C_PINSPACK           TM_I2C_PinsPack_1 /*!< Default I2C pinspack. Check @ref TM_I2C for more information */
#endif

/* Default I2C clock */
#ifndef HMC5883L_I2C_CLOCK
#define HMC5883L_I2C_CLOCK              400000            /*!< Default I2C clock speed */
#endif

/**
 * @brief  Data rates predefined constants
 * @{
 */
#define HMC5883L_DataRate_8KHz       0   /*!< Sample rate set to 8 kHz */
#define HMC5883L_DataRate_4KHz       1   /*!< Sample rate set to 4 kHz */
#define HMC5883L_DataRate_2KHz       3   /*!< Sample rate set to 2 kHz */
#define HMC5883L_DataRate_1KHz       7   /*!< Sample rate set to 1 kHz */
#define HMC5883L_DataRate_500Hz      15  /*!< Sample rate set to 500 Hz */
#define HMC5883L_DataRate_250Hz      31  /*!< Sample rate set to 250 Hz */
#define HMC5883L_DataRate_125Hz      63  /*!< Sample rate set to 125 Hz */
#define HMC5883L_DataRate_100Hz      79  /*!< Sample rate set to 100 Hz */



typedef enum _HMC5883L_Device_t {
	HMC5883L_Device_0 = 0x00, /*!< AD0 pin is set to low */
	HMC5883L_Device_1 = 0x02  /*!< AD0 pin is set to high */
} HMC5883L_Device_t;

/**
 * @brief  HMC5883L result enumeration	
 */
typedef enum _HMC5883L_Result_t {
	HMC5883L_Result_Ok = 0x00,          /*!< Everything OK */
	HMC5883L_Result_Error,              /*!< Unknown error */
	HMC5883L_Result_DeviceNotConnected, /*!< There is no device with valid slave address */
	HMC5883L_Result_DeviceInvalid       /*!< Connected device with address is not HMC5883L */
} HMC5883L_Result_t;



typedef enum HMC5883L_Samples_t {
    HMC5883L_SAMPLES_8     = 0b11,
    HMC5883L_SAMPLES_4     = 0b10,
    HMC5883L_SAMPLES_2     = 0b01,
    HMC5883L_SAMPLES_1     = 0b00
} HMC5883L_Samples_t;

typedef enum HMC5883L_DataRate_t {
    HMC5883L_DATARATE_75HZ       = 0b110,
    HMC5883L_DATARATE_30HZ       = 0b101,
    HMC5883L_DATARATE_15HZ       = 0b100,
    HMC5883L_DATARATE_7_5HZ      = 0b011,
    HMC5883L_DATARATE_3HZ        = 0b010,
    HMC5883L_DATARATE_1_5HZ      = 0b001,
    HMC5883L_DATARATE_0_75_HZ    = 0b000
} HMC5883L_DataRate_t;

typedef enum HMC5883L_Range_t {
    HMC5883L_RANGE_8_1GA     = 0b111,
    HMC5883L_RANGE_5_6GA     = 0b110,
    HMC5883L_RANGE_4_7GA     = 0b101,
    HMC5883L_RANGE_4GA       = 0b100,
    HMC5883L_RANGE_2_5GA     = 0b011,
    HMC5883L_RANGE_1_9GA     = 0b010,
    HMC5883L_RANGE_1_3GA     = 0b001,
    HMC5883L_RANGE_0_88GA    = 0b000
} HMC5883L_Range_t;

typedef enum HMC5883L_Mode_t {
    HMC5883L_IDLE          = 0b10,
    HMC5883L_SINGLE        = 0b01,
    HMC5883L_CONTINOUS     = 0b00
} HMC5883L_Mode_t;

/**
 * @brief  Main HMC5883L structure
 */
typedef struct _HMC5883L_t {
	/* Private */
	uint8_t Address;         /*!< I2C address of device. Only for private use */
	/* Public */
	float Compass_X;
    float Compass_Y;
    float Compass_Z;
	int xOffset;
	int  yOffset;
} HMC5883L_t;

/**
 * @brief  Interrupts union and structure
 */
typedef union _HMC5883L_Interrupt_t {
	struct {
		uint8_t DataReady:1;       /*!< Data ready interrupt */
		uint8_t reserved2:2;       /*!< Reserved bits */
		uint8_t Master:1;          /*!< Master interrupt. Not enabled with library */
		uint8_t FifoOverflow:1;    /*!< FIFO overflow interrupt. Not enabled with library */
		uint8_t reserved1:1;       /*!< Reserved bit */
		uint8_t MotionDetection:1; /*!< Motion detected interrupt */
		uint8_t reserved0:1;       /*!< Reserved bit */
	} F;
	uint8_t Status;
} HMC5883L_Interrupt_t;

/**
 * @}
 */


HMC5883L_Result_t HMC5883L_Init(HMC5883L_t* DataStruct, HMC5883L_Device_t DeviceNumber, HMC5883L_Accelerometer_t AccelerometerSensitivity, HMC5883L_Gyroscope_t GyroscopeSensitivity);

/**
 * @brief  Sets gyroscope sensitivity
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure indicating HMC5883L device
 * @param  GyroscopeSensitivity: Gyro sensitivity value. This parameter can be a value of @ref HMC5883L_Gyroscope_t enumeration
 * @retval Member of @ref HMC5883L_Result_t enumeration
 */
HMC5883L_Result_t HMC5883L_SetGyroscope(HMC5883L_t* DataStruct, HMC5883L_Gyroscope_t GyroscopeSensitivity);

/**
 * @brief  Sets accelerometer sensitivity
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure indicating HMC5883L device
 * @param  AccelerometerSensitivity: Gyro sensitivity value. This parameter can be a value of @ref HMC5883L_Accelerometer_t enumeration
 * @retval Member of @ref HMC5883L_Result_t enumeration
 */
HMC5883L_Result_t HMC5883L_SetAccelerometer(HMC5883L_t* DataStruct, HMC5883L_Accelerometer_t AccelerometerSensitivity);

/**
 * @brief  Sets output data rate
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure indicating HMC5883L device
 * @param  rate: Data rate value. An 8-bit value for prescaler value
 * @retval Member of @ref HMC5883L_Result_t enumeration
 */
HMC5883L_Result_t HMC5883L_SetDataRate(HMC5883L_t* DataStruct, uint8_t rate);

/**
 * @brief  Enables interrupts
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure indicating HMC5883L device
 * @retval Member of @ref HMC5883L_Result_t enumeration
 */
HMC5883L_Result_t HMC5883L_EnableInterrupts(HMC5883L_t* DataStruct);

/**
 * @brief  Disables interrupts
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure indicating HMC5883L device
 * @retval Member of @ref HMC5883L_Result_t enumeration
 */
HMC5883L_Result_t HMC5883L_DisableInterrupts(HMC5883L_t* DataStruct);

/**
 * @brief  Reads and clears interrupts
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure indicating HMC5883L device
 * @param  *InterruptsStruct: Pointer to @ref HMC5883L_Interrupt_t structure to store status in
 * @retval Member of @ref HMC5883L_Result_t enumeration
 */
HMC5883L_Result_t HMC5883L_ReadInterrupts(HMC5883L_t* DataStruct, HMC5883L_Interrupt_t* InterruptsStruct);

/**
 * @brief  Reads accelerometer data from sensor
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure to store data to
 * @retval Member of @ref HMC5883L_Result_t:
 *            - HMC5883L_Result_Ok: everything is OK
 *            - Other: in other cases
 */
HMC5883L_Result_t HMC5883L_ReadAccelerometer(HMC5883L_t* DataStruct);

/**
 * @brief  Reads gyroscope data from sensor
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure to store data to
 * @retval Member of @ref HMC5883L_Result_t:
 *            - HMC5883L_Result_Ok: everything is OK
 *            - Other: in other cases
 */
HMC5883L_Result_t HMC5883L_ReadGyroscope(HMC5883L_t* DataStruct);

/**
 * @brief  Reads temperature data from sensor
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure to store data to
 * @retval Member of @ref HMC5883L_Result_t:
 *            - HMC5883L_Result_Ok: everything is OK
 *            - Other: in other cases
 */
HMC5883L_Result_t HMC5883L_ReadTemperature(HMC5883L_t* DataStruct);

/**
 * @brief  Reads accelerometer, gyroscope and temperature data from sensor
 * @param  *DataStruct: Pointer to @ref HMC5883L_t structure to store data to
 * @retval Member of @ref HMC5883L_Result_t:
 *            - HMC5883L_Result_Ok: everything is OK
 *            - Other: in other cases
 */
HMC5883L_Result_t HMC5883L_ReadAll(HMC5883L_t* DataStruct);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
