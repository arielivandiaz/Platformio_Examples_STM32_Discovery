/**	
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
#include "ariel_stm32_hmc5883l.h"

/* Default I2C address */
#define HMC5883L_I2C_ADDR 0x1E

/* Who I am register value */
#define HMC5883L_I_AM 0x0A

/* HMC5883L registers */

#define HMC5883L_RA_CONFIG_A 0x00
#define HMC5883L_RA_CONFIG_B 0x01
#define HMC5883L_RA_MODE 0x02
#define HMC5883L_RA_DATAX_H 0x03
#define HMC5883L_RA_DATAX_L 0x04
#define HMC5883L_RA_DATAZ_H 0x05
#define HMC5883L_RA_DATAZ_L 0x06
#define HMC5883L_RA_DATAY_H 0x07
#define HMC5883L_RA_DATAY_L 0x08
#define HMC5883L_RA_STATUS 0x09
#define HMC5883L_RA_ID_A 0x0A
#define HMC5883L_RA_ID_B 0x0B
#define HMC5883L_RA_ID_C 0x0C

#define HMC5883L_CRA_AVERAGE_BIT 6
#define HMC5883L_CRA_AVERAGE_LENGTH 2
#define HMC5883L_CRA_RATE_BIT 4
#define HMC5883L_CRA_RATE_LENGTH 3
#define HMC5883L_CRA_BIAS_BIT 1
#define HMC5883L_CRA_BIAS_LENGTH 2

#define HMC5883L_AVERAGING_1 0x00
#define HMC5883L_AVERAGING_2 0x01
#define HMC5883L_AVERAGING_4 0x02
#define HMC5883L_AVERAGING_8 0x03

#define HMC5883L_RATE_0P75 0x00
#define HMC5883L_RATE_1P5 0x01
#define HMC5883L_RATE_3 0x02
#define HMC5883L_RATE_7P5 0x03
#define HMC5883L_RATE_15 0x04
#define HMC5883L_RATE_30 0x05
#define HMC5883L_RATE_75 0x06

#define HMC5883L_BIAS_NORMAL 0x00
#define HMC5883L_BIAS_POSITIVE 0x01
#define HMC5883L_BIAS_NEGATIVE 0x02

#define HMC5883L_CRB_GAIN_BIT 7
#define HMC5883L_CRB_GAIN_LENGTH 3
#define HMC5883L_PWR_MGMT_1 0x6B
#define HMC5883L_PWR_MGMT_2 0x6C

#define HMC5883L_GAIN_1370 0x00
#define HMC5883L_GAIN_1090 0x01
#define HMC5883L_GAIN_820 0x02
#define HMC5883L_GAIN_660 0x03
#define HMC5883L_GAIN_440 0x04
#define HMC5883L_GAIN_390 0x05
#define HMC5883L_GAIN_330 0x06
#define HMC5883L_GAIN_220 0x07
/** Get magnetic field gain value.
 * The table below shows nominal gain settings. Use the "Gain" column to convert
 * counts to Gauss. Choose a lower gain value (higher GN#) when total field
 * strength causes overflow in one of the data output registers (saturation).
 * The data output range for all settings is 0xF800-0x07FF (-2048 - 2047).
 *
 * Value | Field Range | Gain (LSB/Gauss)
 * ------+-------------+-----------------
 * 0     | +/- 0.88 Ga | 1370
 * 1     | +/- 1.3 Ga  | 1090 (Default)
 * 2     | +/- 1.9 Ga  | 820
 * 3     | +/- 2.5 Ga  | 660
 * 4     | +/- 4.0 Ga  | 440
 * 5     | +/- 4.7 Ga  | 390
 * 6     | +/- 5.6 Ga  | 330
 * 7     | +/- 8.1 Ga  | 230
 *
 * @return Current magnetic field gain value
 * @see HMC5883L_GAIN_1090
 * @see HMC5883L_RA_CONFIG_B
 * @see HMC5883L_CRB_GAIN_BIT
 * @see HMC5883L_CRB_GAIN_LENGTH
 */

#define HMC5883L_MODEREG_BIT 1
#define HMC5883L_MODEREG_LENGTH 2

#define HMC5883L_MODE_CONTINUOUS 0x00
#define HMC5883L_MODE_SINGLE 0x01
#define HMC5883L_MODE_IDLE 0x02

#define HMC5883L_STATUS_LOCK_BIT 1
#define HMC5883L_STATUS_READY_BIT 0

int HMC5883L_Init(HMC5883L_t *DataStruct, HMC5883L_Device_t DeviceNumber)
{
	uint8_t temp;

	/* Format I2C address */
	DataStruct->Address = HMC5883L_I2C_ADDR; // | (uint8_t)DeviceNumber;

	/* Initialize I2C */
	TM_I2C_Init(HMC5883L_I2C, HMC5883L_I2C_PINSPACK, HMC5883L_I2C_CLOCK);

	/* Check if device is connected */
	/*
	if (TM_I2C_IsDeviceConnected(HMC5883L_I2C, DataStruct->Address) != TM_I2C_Result_Ok)
	{
		// Return error 
		return HMC5883L_Result_DeviceNotConnected;
	}
	*/
	/* Check who am I */
	TM_I2C_Read(HMC5883L_I2C, DataStruct->Address, HMC5883L_RA_ID_B, &temp);	
	if (temp != 0x00)
	{
		/* Return error */
		return temp;
	}

	// write CONFIG_A register
	TM_I2C_Write(HMC5883L_I2C, DataStruct->Address, HMC5883L_RA_CONFIG_A,
				 (HMC5883L_AVERAGING_8 << (HMC5883L_CRA_AVERAGE_BIT - HMC5883L_CRA_AVERAGE_LENGTH + 1)) |
					 (HMC5883L_RATE_15 << (HMC5883L_CRA_RATE_BIT - HMC5883L_CRA_RATE_LENGTH + 1)) |
					 (HMC5883L_BIAS_NORMAL << (HMC5883L_CRA_BIAS_BIT - HMC5883L_CRA_BIAS_LENGTH + 1)));
	// Write CONFIG_B register
	uint8_t gain = HMC5883L_GAIN_1090;
	TM_I2C_Write(HMC5883L_I2C, DataStruct->Address, HMC5883L_RA_CONFIG_B, gain << (HMC5883L_CRB_GAIN_BIT - HMC5883L_CRB_GAIN_LENGTH + 1));

	// Write MODE register
	uint8_t newMode = HMC5883L_MODE_SINGLE;
	TM_I2C_Write(HMC5883L_I2C, DataStruct->Address, HMC5883L_RA_MODE, newMode << (HMC5883L_MODEREG_BIT - HMC5883L_MODEREG_LENGTH + 1));
	// track to tell if we have to clear bit 7 after a read

	/* Set sample rate to 1kHz */
	//HMC5883L_SetDataRate(DataStruct, HMC5883L_DataRate_1KHz);

	/* Return OK */
	return HMC5883L_Result_Ok;
}

HMC5883L_Result_t HMC5883L_ReadAll(HMC5883L_t* DataStruct) {
	uint8_t data[6];
	int16_t temp;
	
	// Read full raw data, 7bytes 
	TM_I2C_ReadMulti(HMC5883L_I2C, DataStruct->Address, HMC5883L_RA_DATAX_H  , data, 6);
	
	// Format accelerometer data 
	DataStruct->Compass_X = (int16_t)(data[0] << 8 | data[1]);	
	DataStruct->Compass_Y = (int16_t)(data[2] << 8 | data[3]);
	DataStruct->Compass_Z = (int16_t)(data[4] << 8 | data[5]);



	return HMC5883L_Result_Ok;
}
