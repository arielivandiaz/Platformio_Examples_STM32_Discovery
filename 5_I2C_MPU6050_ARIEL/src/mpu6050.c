#include "mpu6050.h"

int MPU_Config(uint8_t Device_Address)
{

    /* Set data sample rate */
    if (TM_I2C_Write(DEVICE_I2C, Device_Address, MPU6050_SMPLRT_DIV, MPU6050_DataRate_1KHz) != TM_I2C_Result_Ok)
    {
        return DEVICE_I2C_Result_Error;
    }

    /* Config accelerometer */
    uint8_t temp;

    /* Config accelerometer */
    TM_I2C_Read(DEVICE_I2C, Device_Address, MPU6050_ACCEL_CONFIG, &temp);
    temp = (temp & 0xE7) | (uint8_t)MPU6050_Accelerometer_8G << 3;
    TM_I2C_Write(DEVICE_I2C, Device_Address, MPU6050_ACCEL_CONFIG, temp);

    // Set sensitivities for multiplying accelerometer data
    switch (AccelerometerSensitivity)
    {
    case MPU6050_Accelerometer_2G:
        MPU_Acce_Mult = (float)1 / MPU6050_ACCE_SENS_2;
        break;
    case MPU6050_Accelerometer_4G:
        MPU_Acce_Mult = (float)1 / MPU6050_ACCE_SENS_4;
        break;
    case MPU6050_Accelerometer_8G:
        MPU_Acce_Mult = (float)1 / MPU6050_ACCE_SENS_8;
        break;
    case MPU6050_Accelerometer_16G:
        MPU_Acce_Mult = (float)1 / MPU6050_ACCE_SENS_16;
    default:
        break;
    }

    temp = 0;
    TM_I2C_Read(DEVICE_I2C, Device_Address, MPU6050_GYRO_CONFIG, &temp);
    temp = (temp & 0xE7) | (uint8_t)GyroscopeSensitivity << 3;
    TM_I2C_Write(DEVICE_I2C, Device_Address, MPU6050_GYRO_CONFIG, temp);

    // Set sensitivities for multiplying gyro data
    switch (GyroscopeSensitivity)
    {
    case MPU6050_Gyroscope_250s:
        MPU_Gyro_Mult = (float)1 / MPU6050_GYRO_SENS_250;
        break;
    case MPU6050_Gyroscope_500s:
        MPU_Gyro_Mult = (float)1 / MPU6050_GYRO_SENS_500;
        break;
    case MPU6050_Gyroscope_1000s:
        MPU_Gyro_Mult = (float)1 / MPU6050_GYRO_SENS_1000;
        break;
    case MPU6050_Gyroscope_2000s:
        MPU_Gyro_Mult = (float)1 / MPU6050_GYRO_SENS_2000;
    default:
        break;
    }

    /* Return OK */
    return DEVICE_I2C_Result_Ok;
}