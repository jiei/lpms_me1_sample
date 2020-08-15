/***********************************************************************
**
**
** Copyright (C) 2013 LP-Research
** All rights reserved.
** Contact: LP-Research (info@lp-research.com)
***********************************************************************/


#include "lpme1.h"
//#include "usart.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Follow 4 functions are low level drivers depend on platforms
  * must be complement by user in file "lpme1_driver.c"
  * {
  */
extern lpme1_status_t lpme1_read_reg(uint8_t regaddr,uint8_t *buf);
extern lpme1_status_t lpme1_write_reg(uint8_t regaddr,uint8_t *buf);
extern lpme1_status_t lpme1_read_buffer(uint8_t regaddr,uint8_t *buf,uint8_t len);
extern lpme1_status_t lpme1_write_buffer(uint8_t regaddr,uint8_t *buf,uint8_t len);
/* }
 */

/**
  *@brief: Get system time stamp
  *@para: Pointer to float variable use to save read value
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_timestamp(float *time)
{
    uint8_t buffer[4];
    if(lpme1_read_buffer(TIMESTAMP_0, buffer, 4) == LPME1_OK)
    {
        *time = uint8_to_float(buffer);
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Get accelerometer data
  *@para: Pointer to float array that have 3 elements at least
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_acc(float *acc)
{
    DataDecoder data[3];
    if(lpme1_read_buffer(ACC_X_0, (uint8_t *)data[0].u8vals, 12) == LPME1_OK)
    {
        for(uint8_t i = 0; i<3; i++)
        {
            *(acc+i) = data[i].fval;
        }
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;

}

/**
  *@brief: Get gyroscope data
  *@para: Pointer to float array that have 3 elements at least
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_gyr(float *gyr)
{
    DataDecoder data[3];
    if(lpme1_read_buffer(GYR_X_0, (uint8_t *)data[0].u8vals, 12) == LPME1_OK)
    {
        for(uint8_t i = 0; i<3; i++)
        {
            *(gyr+i) = data[i].fval;
        }
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Get magnetometer data
  *@para: Pointer to float array that have 3 elements at least
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_mag(float *mag)
{
    DataDecoder data[3];
    if(lpme1_read_buffer(MAG_X_0, (uint8_t *)data[0].u8vals, 12) == LPME1_OK)
    {
        for(uint8_t i = 0; i<3; i++)
        {
            *(mag+i) = data[i].fval;
        }
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Get euler angle
  *@para: Pointer to float array that have 3 elements at least
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_euler(float *euler)
{
    DataDecoder data[3];
    if(lpme1_read_buffer(EULER_X_0, (uint8_t *)data[0].u8vals, 12) == LPME1_OK)
    {
        for(uint8_t i = 0; i<3; i++)
        {
            *(euler+i) = data[i].fval;
        }
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Get quateration
  *@para: Pointer to float array that have 4 elements at least
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_quat(float *quat)
{
    DataDecoder data[4];
    if(lpme1_read_buffer(QUAT_W_0, (uint8_t *)data[0].u8vals, 16) == LPME1_OK)
    {
        for(uint8_t i = 0; i<4; i++)
        {
            *(quat+i) = data[i].fval;
        }
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Get liner  acceleration
  *@para: Pointer to float array that have 3 elements at least
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_linacc(float *linacc)
{
    DataDecoder data[3];
    if(lpme1_read_buffer(LIN_ACC_X_0, (uint8_t *)data[0].u8vals, 12) == LPME1_OK)
    {
        for(uint8_t i = 0; i<3; i++)
        {
            *(linacc+i) = data[i].fval;
        }
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Get hardware system temperature
  *@para: Pointer to float array that have 3 elements at least
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_temp(float *temp)
{
    uint8_t buffer[4];
    if(lpme1_read_buffer(TEMP_0, buffer, 4) == LPME1_OK)
    {
        *temp = uint8_to_float(buffer);
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Get all data of lpms-me1
  *@para: Pointer to Lpme1_Data structure
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_get_all(Lpme1_Data *alldata)
{
    uint8_t buffer[LPME1_DATA_SIZE];
    Lpme1_Data *pall;
    if(lpme1_read_buffer(DATA_BASE, buffer, LPME1_DATA_SIZE) == LPME1_OK)
    {
        pall = (Lpme1_Data *)&buffer[0];

        *alldata = *pall;

        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**************************************************************************************/

/**
  *@brief: Config registers write enable
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_config_enable(void)
{
    uint8_t data = 0x80;
    if(lpme1_write_reg(FUN_CONFIG, &data) == LPME1_OK)
    {
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Config registers write disable
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_config_disable(void)
{
    uint8_t data = 0x00;
    if(lpme1_write_reg(FUN_CONFIG, &data) == LPME1_OK)
    {
        return LPME1_OK;
    }
    else
        return LPME1_ERROR;
}

/**
  *@brief: Reset all registers
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_sys_reset(void)
{
    uint8_t data;

    if(lpme1_read_reg(SYS_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    data |= LPMS_SYS_RESET;

    if(lpme1_write_reg(SYS_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Reboot the Sensor
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_sys_reboot(void)
{
    uint8_t data;

    if(lpme1_read_reg(SYS_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    data |= LPMS_SYS_REBOOT;

    if(lpme1_write_reg(SYS_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Configure the led
  *@para: New status for the led. Must be LED_ENABLE or LED_DISABLE
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_led(lpme1_Led_Status status)
{
    uint8_t data;

    if(lpme1_read_reg(SYS_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    if(status == LED_ENABLE)
        data |= LPMS_LED_EN;
    else
        data &= ~LPMS_LED_EN;

    if(lpme1_write_reg(SYS_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Reset the timestamp
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_reset_time(void)
{
    uint8_t data;

    if(lpme1_read_reg(DATA_CTRL, &data) != LPME1_OK)
        return LPME1_ERROR;

    data |= LPMS_RESET_TIME;

    if(lpme1_write_reg(DATA_CTRL, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Set output data format
  *@para: Format for the the output data. Must be LPMS_DATA_FORMAT_32BIT_FLOAT or LPMS_DATA_FORMAT_16BIT_UINT
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_DataFormat(uint8_t format)
{
    uint8_t data;

    if(lpme1_read_reg(DATA_CTRL, &data) != LPME1_OK)
        return LPME1_ERROR;

    if(format == LPMS_DATA_FORMAT_32BIT_FLOAT)
        data &= ~LPMS_DATA_FORMAT;
    else
        data |= LPMS_DATA_FORMAT;

    if(lpme1_write_reg(DATA_CTRL, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Set output data frequency
  *@para: frequency for the the output data.
    This parameter can be one of the following values:
        LPMS_DATA_FREQ_5HZ
        LPMS_DATA_FREQ_10HZ
        LPMS_DATA_FREQ_50HZ
        LPMS_DATA_FREQ_100HZ
        LPMS_DATA_FREQ_200HZ
        LPMS_DATA_FREQ_400HZ
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_Freq(uint8_t freq)
{
    uint8_t data;

    if(lpme1_read_reg(DATA_CTRL, &data) != LPME1_OK)
        return LPME1_ERROR;

    data &= ~LPMS_DATA_FREQ_MASK;

    if(freq == LPMS_DATA_FREQ_5HZ)          data |= LPMS_DATA_FREQ_5HZ;
    else if(freq == LPMS_DATA_FREQ_10HZ)    data |= LPMS_DATA_FREQ_10HZ;
    else if(freq == LPMS_DATA_FREQ_50HZ)    data |= LPMS_DATA_FREQ_50HZ;
    else if(freq == LPMS_DATA_FREQ_100HZ)   data |= LPMS_DATA_FREQ_100HZ;
    else if(freq == LPMS_DATA_FREQ_200HZ)   data |= LPMS_DATA_FREQ_200HZ;
    else if(freq == LPMS_DATA_FREQ_400HZ)   data |= LPMS_DATA_FREQ_400HZ;

    if(lpme1_write_reg(DATA_CTRL, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Set output data enable
  *@para: Select which data output enable
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_DataOutput(uint8_t data)
{
    if(lpme1_write_reg(DATA_ENABLE, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Set ACC range
  *@para: Range for the acc
    This parameter can be one of the following values:
        LPMS_ACC_FS_2G
        LPMS_ACC_FS_4G
        LPMS_ACC_FS_8G
        LPMS_ACC_FS_16G
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_AccRange(uint8_t range)
{
    uint8_t data;

    if(lpme1_read_reg(CTRL_0_A, &data) != LPME1_OK)
        return LPME1_ERROR;

    data &= ~LPMS_ACC_FS_MASK;

    if(range == LPMS_ACC_FS_2G)         data |= LPMS_ACC_FS_2G;
    else if(range == LPMS_ACC_FS_4G)    data |= LPMS_ACC_FS_4G;
    else if(range == LPMS_ACC_FS_8G)    data |= LPMS_ACC_FS_8G;
    else if(range == LPMS_ACC_FS_16G)   data |= LPMS_ACC_FS_16G;

    if(lpme1_write_reg(CTRL_0_A, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Set GYR range
  *@para: Range for the gyr
    This parameter can be one of the following values:
        LPMS_GYR_FS_125DPS
        LPMS_GYR_FS_245DPS
        LPMS_GYR_FS_500DPS
        LPMS_GYR_FS_1000DPS
        LPMS_GYR_FS_2000DPS
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_GyrRange(uint8_t range)
{
    uint8_t data;

    if(lpme1_read_reg(CTRL_1_G, &data) != LPME1_OK)
        return LPME1_ERROR;

    data &= ~LPMS_GYR_FS_MASK;

    if(range == LPMS_GYR_FS_125DPS)         data |= LPMS_GYR_FS_125DPS;
    else if(range == LPMS_GYR_FS_245DPS)    data |= LPMS_GYR_FS_245DPS;
    else if(range == LPMS_GYR_FS_500DPS)    data |= LPMS_GYR_FS_500DPS;
    else if(range == LPMS_GYR_FS_1000DPS)   data |= LPMS_GYR_FS_1000DPS;
    else if(range == LPMS_GYR_FS_2000DPS)   data |= LPMS_GYR_FS_2000DPS;

    if(lpme1_write_reg(CTRL_1_G, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Set MAG range
  *@para: Range for the mag
    This parameter can be one of the following values:
        LPMS_MAG_FS_4GAUSS
        LPMS_MAG_FS_8GAUSS
        LPMS_MAG_FS_12GAUSS
        LPMS_MAG_FS_16GAUSS
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_MagRange(uint8_t range)
{
    uint8_t data;

    if(lpme1_read_reg(CTRL_2_M, &data) != LPME1_OK)
        return LPME1_ERROR;

    data &= ~LPMS_MAG_FS_MASK;

    if(range == LPMS_MAG_FS_4GAUSS)         data |= LPMS_MAG_FS_4GAUSS;
    else if(range == LPMS_MAG_FS_8GAUSS)    data |= LPMS_MAG_FS_8GAUSS;
    else if(range == LPMS_MAG_FS_12GAUSS)   data |= LPMS_MAG_FS_12GAUSS;
    else if(range == LPMS_MAG_FS_16GAUSS)   data |= LPMS_MAG_FS_16GAUSS;

    if(lpme1_write_reg(CTRL_2_M, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Start GYR Calibration
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_start_GyrCalibra(void)
{
    uint8_t data;

    if(lpme1_read_reg(CTRL_1_G, &data) != LPME1_OK)
        return LPME1_ERROR;

    data |= LPMS_GYR_CALIBRA;

    if(lpme1_write_reg(CTRL_1_G, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Start MAG Calibration
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_start_MagCalibra(void)
{
    uint8_t data;

    if(lpme1_read_reg(CTRL_2_M, &data) != LPME1_OK)
        return LPME1_ERROR;

    data |= LPMS_MAG_CALIBRA;

    if(lpme1_write_reg(CTRL_2_M, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}


/**
  *@brief: Set filter mode
  *@para:Mode for the filter
    This parameter can be one of the following values:
        LPMS_FILTER_MODE_GYR
        LPMS_FILTER_MODE_GYR_ACC
        LPMS_FILTER_MODE_GYR_ACC_MAG
        LPMS_FILTER_MODE_MAD_GYR_ACC
        LPMS_FILTER_MODE_MAD_GYR_ACC_MAG
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_filter(uint8_t mode)
{
    uint8_t data;

    if(lpme1_read_reg(FILTER_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    data &= ~LPMS_FILTER_MODE_MASK;

    if(mode == LPMS_FILTER_MODE_GYR)                   data |= LPMS_FILTER_MODE_GYR;
    else if(mode == LPMS_FILTER_MODE_GYR_ACC)          data |= LPMS_FILTER_MODE_GYR_ACC;
    else if(mode == LPMS_FILTER_MODE_GYR_ACC_MAG)      data |= LPMS_FILTER_MODE_GYR_ACC_MAG;
    else if(mode == LPMS_FILTER_MODE_MAD_GYR_ACC)      data |= LPMS_FILTER_MODE_MAD_GYR_ACC;
    else if(mode == LPMS_FILTER_MODE_MAD_GYR_ACC_MAG)  data |= LPMS_FILTER_MODE_MAD_GYR_ACC_MAG;

    if(lpme1_write_reg(FILTER_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Set low pass
  *@para:Value for the LowPass
    This parameter can be one of the following values:
        LPMS_LOW_PASS_OFF
        LPMS_LOW_PASS_ALPHA_01
        LPMS_LOW_PASS_ALPHA_005
        LPMS_LOW_PASS_ALPHA_001
        LPMS_LOW_PASS_ALPHA_0005
        LPMS_LOW_PASS_ALPHA_0001
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_set_LowPass(uint8_t value)
{
    uint8_t data;

    if(lpme1_read_reg(FILTER_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    data &= ~LPMS_LOW_PASS_MASK;

    if(value == LPMS_LOW_PASS_OFF)              data |= LPMS_LOW_PASS_OFF;
    else if(value == LPMS_LOW_PASS_ALPHA_01)    data |= LPMS_LOW_PASS_ALPHA_01;
    else if(value == LPMS_LOW_PASS_ALPHA_005)   data |= LPMS_LOW_PASS_ALPHA_005;
    else if(value == LPMS_LOW_PASS_ALPHA_001)   data |= LPMS_LOW_PASS_ALPHA_001;
    else if(value == LPMS_LOW_PASS_ALPHA_0005)  data |= LPMS_LOW_PASS_ALPHA_0005;
    else if(value == LPMS_LOW_PASS_ALPHA_0001)  data |= LPMS_LOW_PASS_ALPHA_0001;

    if(lpme1_write_reg(FILTER_CONFIG, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Reset the offset
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_reset_offset(void)
{
    uint8_t data;

    if(lpme1_read_reg(OFFSET_SETTING, &data) != LPME1_OK)
        return LPME1_ERROR;

    data |= LPMS_RESET_OFFSET;

    if(lpme1_write_reg(OFFSET_SETTING, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Heading reset function
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_heading_reset(void)
{
    uint8_t data;

    if(lpme1_read_reg(OFFSET_SETTING, &data) != LPME1_OK)
        return LPME1_ERROR;

    data |= LPMS_HEADING_RESET;

    if(lpme1_write_reg(OFFSET_SETTING, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Object reset function
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_object_reset(void)
{
    uint8_t data;

    if(lpme1_read_reg(OFFSET_SETTING, &data) != LPME1_OK)
        return LPME1_ERROR;

    data |= LPMS_OBJECT_RESET;

    if(lpme1_write_reg(OFFSET_SETTING, &data) != LPME1_OK)
        return LPME1_ERROR;

    return LPME1_OK;
}

/**
  *@brief: Convert 4 uint8_t values to float value
  *@para: Pointer to uint8_t array[4];
  *@ret: float value
  */
float uint8_to_float(uint8_t *pu8vals)
{
    DataDecoder decoder;
    for(uint8_t i = 0; i < 4; i++)
    {
        decoder.u8vals[i] = *(pu8vals +i);
    }
    return decoder.fval;
}

/**
  *@brief: Convert uint32_t values to float value
  *@para: Pointer to uint32_t variable
  *@ret: float value
  */
float uint32_to_float(uint32_t *pu32val)
{
    DataDecoder decoder;

    decoder.u32val= *pu32val;

    return decoder.fval;
}


#ifdef EXAMPLE_DEBUG
/* lpme1_example
  * an example function to show how to use this library
  */
void lpme1_example(void)
{
    Lpme1_Data lpme1Data;

    lpme1_get_timestamp(&lpme1Data.time);
    lpme1_get_acc(lpme1Data.acc);
    lpme1_get_gyr(lpme1Data.gyr);
    lpme1_get_mag(lpme1Data.mag);
    lpme1_get_euler(lpme1Data.euler);
    lpme1_get_quat(lpme1Data.quat);
    lpme1_get_linacc(lpme1Data.linAcc);
    lpme1_get_temp(&lpme1Data.temp);
   // lpme1_get_all(&lpme1Data);

    /* Work under LPMS_DATA_FORMAT_32BIT_FLOAT mode */
    /*
    printf("Timestamp: %.3f \r\n",lpme1Data.time);
    printf("AccX: %.3f\tAccY: %.3f\tAccZ: %.3f\t \r\n",lpme1Data.acc[0],lpme1Data.acc[1],lpme1Data.acc[2]);
    printf("GyrX: %.3f\tGyrY: %.3f\tGyrZ: %.3f\t \r\n",lpme1Data.gyr[0],lpme1Data.gyr[1],lpme1Data.gyr[2]);
    printf("MagX: %.3f\tMagY: %.3f\tMagZ: %.3f\t \r\n",lpme1Data.mag[0],lpme1Data.mag[1],lpme1Data.mag[2]);
    printf("EulerX: %f\tEulerY: %f\tEulerZ: %f\t \r\n",lpme1Data.euler[0],lpme1Data.euler[1],lpme1Data.euler[2]);
    printf("QuatW: %f\tQuatX: %f\tQuatY: %f\tQuatZ: %f\t  \r\n",lpme1Data.quat[0],lpme1Data.quat[1],lpme1Data.quat[2],lpme1Data.quat[3]);
    printf("Temperature: %.1f \r\n",lpme1Data.temp);
    printf("\r\n");
	*/
}

void lpme1_config_example(void)
{
    //uint8_t regdata = 0;
    //uint8_t configbuf[10];

    lpme1_config_enable();      //registers write enable
    HAL_Delay(2);               //wait for the sensor to update the register, delay 2.5ms or longer

    /*
    lpme1_sys_reboot();         //rebooot the sensor, all registers reset to default value.
    HAL_Delay(80);              //when reboot the sensor, delay 200ms or longer

    lpme1_config_enable();      //registers write enable
    HAL_Delay(2);

    lpme1_sys_reset();          //Reset all the registers
    HAL_Delay(10);              //when updata all the config registers in one time, delay about 20ms or longer

    lpme1_config_enable();      //registers write enable
    HAL_Delay(2);
    */

    lpme1_set_DataOutput(LPMS_ALLDATA_EN);
    HAL_Delay(2);

    lpme1_set_Freq(LPMS_DATA_FREQ_100HZ);
    HAL_Delay(2);

    lpme1_set_AccRange(LPMS_ACC_FS_4G);
    HAL_Delay(2);

    lpme1_set_filter(LPMS_FILTER_MODE_GYR_ACC);
    HAL_Delay(2);

    //Other register configuration, refer to the Functions in this file

    lpme1_config_disable();    //registers write disable
    HAL_Delay(2);



    /* write buffer example */
    /*
    lpme1_read_buffer(FUN_CONFIG, configbuf, 10);
    configbuf[FUN_CONFIG] |= LPMS_FUN_CFG_EN;
    configbuf[SYS_CONFIG] |= LPMS_LED_EN;
    configbuf[DATA_CTRL] &= ~LPMS_DATA_FREQ_MASK;
    configbuf[DATA_CTRL] |= LPMS_DATA_FREQ_100HZ;
    configbuf[DATA_ENABLE] = LPMS_ALLDATA_EN;
    lpme1_write_buffer(FUN_CONFIG, configbuf, 10);

    HAL_Delay(10);

    lpme1_config_disable();    //registers write disable
    */
}

#endif/*DEBUG*/


#ifdef __cplusplus
}
#endif /* __cplusplus */
