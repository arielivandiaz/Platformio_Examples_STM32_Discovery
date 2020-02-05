

#include "ariel_i2c_device.h"

int I2C_Device_Init( uint8_t Device_Address, uint8_t Device_ID)
{
    uint8_t temp;

  
    /* Initialize I2C */
    TM_I2C_Init(DEVICE_I2C, DEVICE_I2C_PINSPACK, DEVICE_I2C_CLOCK);

    if (TM_I2C_IsDeviceConnected(DEVICE_I2C, Device_Address) != TM_I2C_Result_Ok)
    {
        /* Return error */
        return DEVICE_I2C_Result_DeviceNotConnected;
    }

    /* Check who am I */
    TM_I2C_Read(DEVICE_I2C, Device_Address, I2C_WHO_AM_I, &temp);
    if (temp != Device_ID)
    {
        /* Return error */
        return DEVICE_I2C_Result_DeviceInvalid;
    }

    /* Wakeup Device */
    TM_I2C_Write(DEVICE_I2C, Device_Address, I2C_PWR_MGMT_1, 0x00);

    return DEVICE_I2C_Result_Ok;
};

int I2C_Device_SetValue(uint8_t Device_Address, uint8_t AddressValue, uint8_t Value)
{
    if (TM_I2C_Write(DEVICE_I2C,Device_Address, AddressValue, Value) != TM_I2C_Result_Ok)
    {

        /* Return error */
        return DEVICE_I2C_Result_Error;
    }
    return DEVICE_I2C_Result_Ok;
};

int16_t I2C_Device_ReadValue(uint8_t Device_Address, uint8_t AddressValue)
{
	uint8_t data[2];

	TM_I2C_ReadMulti(DEVICE_I2C, Device_Address, AddressValue, data, 2);
		
	return (data[0] << 8 | data[1]);
	

};


