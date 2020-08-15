/***********************************************************************
**
**
** Copyright (C) 2013 LP-Research
** All rights reserved.
** Contact: LP-Research (info@lp-research.com)
***********************************************************************/
#ifndef __LPME1_H
#define __LPME1_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stdio.h"
#include "stdint.h"

#define USE_IIC

//typedef unsigned          char        uint8_t;
//typedef unsigned           int        uint32_t;

typedef union
{
    uint8_t u8vals[4];
    uint32_t u32val;
    float fval;
} DataDecoder;

typedef enum
{
    LPME1_ERROR = 0,
    LPME1_OK = 1
} lpme1_status_t;

typedef enum
{
    LED_DISABLE = 0,
    LED_ENABLE = 1
} lpme1_Led_Status;

typedef struct
{
    float time;
    float acc[3];
    float gyr[3];
    float mag[3];
    float euler[3];
    float quat[4];
    float linAcc[3];
    float temp;
} Lpme1_Data;


/*
  *System Registers{
  */
#define LPME1_ALL_REG_SIZE  128
#define LPME1_DATA_SIZE     84

#define DATA_BASE           0x20//Data register start address

#define FUN_CONFIG          0x00
#define SYS_CONFIG          0x01
#define DATA_CTRL           0x02
#define DATA_ENABLE         0x03
#define CTRL_0_A            0x04
#define CTRL_1_G            0x05
#define CTRL_2_M            0x06
#define STATUS              0x07
#define FILTER_CONFIG       0x08
#define OFFSET_SETTING      0x09

//Data Register
#define TIMESTAMP_0 (DATA_BASE + 0)
#define TIMESTAMP_1 (DATA_BASE + 1)
#define TIMESTAMP_2 (DATA_BASE + 2)
#define TIMESTAMP_3 (DATA_BASE + 3)
#define ACC_X_0     (DATA_BASE + 4)
#define ACC_X_1     (DATA_BASE + 5)
#define ACC_X_2     (DATA_BASE + 6)
#define ACC_X_3     (DATA_BASE + 7)
#define ACC_Y_0     (DATA_BASE + 8)
#define ACC_Y_1     (DATA_BASE + 9)
#define ACC_Y_2     (DATA_BASE + 10)
#define ACC_Y_3     (DATA_BASE + 11)
#define ACC_Z_0     (DATA_BASE + 12)
#define ACC_Z_1     (DATA_BASE + 13)
#define ACC_Z_2     (DATA_BASE + 14)
#define ACC_Z_3     (DATA_BASE + 15)
#define GYR_X_0     (DATA_BASE + 16)
#define GYR_X_1     (DATA_BASE + 17)
#define GYR_X_2     (DATA_BASE + 18)
#define GYR_X_3     (DATA_BASE + 19)
#define GYR_Y_0     (DATA_BASE + 20)
#define GYR_Y_1     (DATA_BASE + 21)
#define GYR_Y_2     (DATA_BASE + 22)
#define GYR_Y_3     (DATA_BASE + 23)
#define GYR_Z_0     (DATA_BASE + 24)
#define GYR_Z_1     (DATA_BASE + 25)
#define GYR_Z_2     (DATA_BASE + 26)
#define GYR_Z_3     (DATA_BASE + 27)
#define MAG_X_0     (DATA_BASE + 28)
#define MAG_X_1     (DATA_BASE + 29)
#define MAG_X_2     (DATA_BASE + 30)
#define MAG_X_3     (DATA_BASE + 31)
#define MAG_Y_0     (DATA_BASE + 32)
#define MAG_Y_1     (DATA_BASE + 33)
#define MAG_Y_2     (DATA_BASE + 34)
#define MAG_Y_3     (DATA_BASE + 35)
#define MAG_Z_0     (DATA_BASE + 36)
#define MAG_Z_1     (DATA_BASE + 37)
#define MAG_Z_2     (DATA_BASE + 38)
#define MAG_Z_3     (DATA_BASE + 39)
#define EULER_X_0   (DATA_BASE + 40)
#define EULER_X_1   (DATA_BASE + 41)
#define EULER_X_2   (DATA_BASE + 42)
#define EULER_X_3   (DATA_BASE + 43)
#define EULER_Y_0   (DATA_BASE + 44)
#define EULER_Y_1   (DATA_BASE + 45)
#define EULER_Y_2   (DATA_BASE + 46)
#define EULER_Y_3   (DATA_BASE + 47)
#define EULER_Z_0   (DATA_BASE + 48)
#define EULER_Z_1   (DATA_BASE + 49)
#define EULER_Z_2   (DATA_BASE + 50)
#define EULER_Z_3   (DATA_BASE + 51)
#define QUAT_W_0    (DATA_BASE + 52)
#define QUAT_W_1    (DATA_BASE + 53)
#define QUAT_W_2    (DATA_BASE + 54)
#define QUAT_W_3    (DATA_BASE + 55)
#define QUAT_X_0    (DATA_BASE + 56)
#define QUAT_X_1    (DATA_BASE + 57)
#define QUAT_X_2    (DATA_BASE + 58)
#define QUAT_X_3    (DATA_BASE + 59)
#define QUAT_Y_0    (DATA_BASE + 60)
#define QUAT_Y_1    (DATA_BASE + 61)
#define QUAT_Y_2    (DATA_BASE + 62)
#define QUAT_Y_3    (DATA_BASE + 63)
#define QUAT_Z_0    (DATA_BASE + 64)
#define QUAT_Z_1    (DATA_BASE + 65)
#define QUAT_Z_2    (DATA_BASE + 66)
#define QUAT_Z_3    (DATA_BASE + 67)
#define LIN_ACC_X_0 (DATA_BASE + 68)
#define LIN_ACC_X_1 (DATA_BASE + 69)
#define LIN_ACC_X_2 (DATA_BASE + 70)
#define LIN_ACC_X_3 (DATA_BASE + 71)
#define LIN_ACC_Y_0 (DATA_BASE + 72)
#define LIN_ACC_Y_1 (DATA_BASE + 73)
#define LIN_ACC_Y_2 (DATA_BASE + 74)
#define LIN_ACC_Y_3 (DATA_BASE + 75)
#define LIN_ACC_Z_0 (DATA_BASE + 76)
#define LIN_ACC_Z_1 (DATA_BASE + 77)
#define LIN_ACC_Z_2 (DATA_BASE + 78)
#define LIN_ACC_Z_3 (DATA_BASE + 79)
#define TEMP_0      (DATA_BASE + 80)
#define TEMP_1      (DATA_BASE + 81)
#define TEMP_2      (DATA_BASE + 82)
#define TEMP_3      (DATA_BASE + 83)


/*
  *}System Registers
  */


/*
  *Register Function{
  */
//Function config
#define LPMS_FUN_CFG_EN         ((uint8_t)0x01<<7)


//System config
#define LPMS_LED_EN             ((uint8_t)0x01<<0)
#define LPMS_SYS_REBOOT         ((uint8_t)0x01<<6)
#define LPMS_SYS_RESET          ((uint8_t)0x01<<7)


//Data control
#define LPMS_DATA_FREQ_MASK     ((uint8_t)0x0F)
#define LPMS_DATA_FREQ_5HZ      ((uint8_t)0x00)
#define LPMS_DATA_FREQ_10HZ     ((uint8_t)0x01)
#define LPMS_DATA_FREQ_50HZ     ((uint8_t)0x02)
#define LPMS_DATA_FREQ_100HZ    ((uint8_t)0x03)
#define LPMS_DATA_FREQ_200HZ    ((uint8_t)0x04)
#define LPMS_DATA_FREQ_400HZ    ((uint8_t)0x05)

#define LPMS_DATA_FORMAT                ((uint8_t)0x01<<4)
#define LPMS_DATA_FORMAT_32BIT_FLOAT    ((uint8_t)0x00<<4)
#define LPMS_DATA_FORMAT_16BIT_UINT     ((uint8_t)0x01<<4)

#define LPMS_RESET_TIME         ((uint8_t)0x01<<5)


//Data enable
#define LPMS_TIME_EN            ((uint8_t)0x01<<0)
#define LPMS_ACC_EN             ((uint8_t)0x01<<1)
#define LPMS_GYR_EN             ((uint8_t)0x01<<2)
#define LPMS_MAG_EN             ((uint8_t)0x01<<3)
#define LPMS_EULER_EN           ((uint8_t)0x01<<4)
#define LPMS_QUAT_EN            ((uint8_t)0x01<<5)
#define LPMS_LINACC_EN          ((uint8_t)0x01<<6)
#define LPMS_TEMP_EN            ((uint8_t)0x01<<7)
#define LPMS_ALLDATA_EN         ((uint8_t)0xFF)


//CONTROL 0 ACC
#define LPMS_ACC_FS_POS         ((uint8_t)0x02)
#define LPMS_ACC_FS_MASK        ((uint8_t)0x03<<2)
#define LPMS_ACC_FS_2G          ((uint8_t)0x00<<2)
#define LPMS_ACC_FS_16G         ((uint8_t)0x01<<2)
#define LPMS_ACC_FS_4G          ((uint8_t)0x02<<2)
#define LPMS_ACC_FS_8G          ((uint8_t)0x03<<2)


//CONTROL 1 GYR
#define LPMS_GYR_FS_POS         ((uint8_t)0x01)
#define LPMS_GYR_FS_MASK        ((uint8_t)0x07<<1)
#define LPMS_GYR_FS_125DPS      ((uint8_t)0x01<<1)
#define LPMS_GYR_FS_245DPS      ((uint8_t)0x00<<1)
#define LPMS_GYR_FS_500DPS      ((uint8_t)0x02<<1)
#define LPMS_GYR_FS_1000DPS     ((uint8_t)0x04<<1)
#define LPMS_GYR_FS_2000DPS     ((uint8_t)0x06<<1)
#define LPMS_GYR_CALIBRA        ((uint8_t)0x01<<7)


//CONTROL 2 MAG
#define LPMS_MAG_FS_POS         ((uint8_t)0x05)
#define LPMS_MAG_FS_MASK        ((uint8_t)0x03<<5)
#define LPMS_MAG_FS_4GAUSS      ((uint8_t)0x00<<5)
#define LPMS_MAG_FS_8GAUSS      ((uint8_t)0x01<<5)
#define LPMS_MAG_FS_12GAUSS     ((uint8_t)0x02<<5)
#define LPMS_MAG_FS_16GAUSS     ((uint8_t)0x03<<5)
#define LPMS_MAG_CALIBRA        ((uint8_t)0x01<<7)


//Status
#define LPMS_DATA_READY                 ((uint8_t)0x01<<0)
#define LPMS_GYR_IS_CALIBRATING         ((uint8_t)0x01<<4)
#define LPMS_MAG_IS_CALIBRATING         ((uint8_t)0x01<<3)


//Filter config
#define LPMS_FILTER_MODE_MASK                   ((uint8_t)0x07)
#define LPMS_FILTER_MODE_GYR                    ((uint8_t)0x00)
#define LPMS_FILTER_MODE_GYR_ACC                ((uint8_t)0x01)
#define LPMS_FILTER_MODE_GYR_ACC_MAG            ((uint8_t)0x02)
#define LPMS_FILTER_MODE_MAD_GYR_ACC            ((uint8_t)0x03)
#define LPMS_FILTER_MODE_MAD_GYR_ACC_MAG        ((uint8_t)0x04)

#define LPMS_LOW_PASS_MASK                      ((uint8_t)0x07<<3)
#define LPMS_LOW_PASS_OFF                       ((uint8_t)0x00<<3)
#define LPMS_LOW_PASS_ALPHA_01                  ((uint8_t)0x01<<3)
#define LPMS_LOW_PASS_ALPHA_005                 ((uint8_t)0x02<<3)
#define LPMS_LOW_PASS_ALPHA_001                 ((uint8_t)0x03<<3)
#define LPMS_LOW_PASS_ALPHA_0005                ((uint8_t)0x04<<3)
#define LPMS_LOW_PASS_ALPHA_0001                ((uint8_t)0x05<<3)


//Offset setting
#define LPMS_OBJECT_RESET       ((uint8_t)0x01<<0)
#define LPMS_HEADING_RESET      ((uint8_t)0x01<<1)
#define LPMS_RESET_OFFSET       ((uint8_t)0x01<<2)


/*
  *}Register Function
  */



/*
  *Read sensor data Functions{
  */
lpme1_status_t lpme1_get_timestamp(float *time);
lpme1_status_t lpme1_get_acc(float *acc);
lpme1_status_t lpme1_get_gyr(float *gyr);
lpme1_status_t lpme1_get_mag(float *mag);
lpme1_status_t lpme1_get_euler(float *euler);
lpme1_status_t lpme1_get_quat(float *quat);
lpme1_status_t lpme1_get_linacc(float *linacc);
lpme1_status_t lpme1_get_temp(float *temp);
lpme1_status_t lpme1_get_all(Lpme1_Data *alldata);
/*
  *}Read sensor data Functions
  */



/*
  *Register config Functions{
  */
lpme1_status_t lpme1_config_enable(void);
lpme1_status_t lpme1_config_disable(void);

lpme1_status_t lpme1_sys_reset(void);
lpme1_status_t lpme1_sys_reboot(void);
lpme1_status_t lpme1_set_led(lpme1_Led_Status status);

lpme1_status_t lpme1_reset_time(void);
lpme1_status_t lpme1_set_DataFormat(uint8_t format);
lpme1_status_t lpme1_set_Freq(uint8_t freq);

lpme1_status_t lpme1_set_DataOutput(uint8_t data);

lpme1_status_t lpme1_set_AccRange(uint8_t range);
lpme1_status_t lpme1_set_GyrRange(uint8_t range);
lpme1_status_t lpme1_set_MagRange(uint8_t range);

lpme1_status_t lpme1_start_GyrCalibra(void);
lpme1_status_t lpme1_start_MagCalibra(void);

lpme1_status_t lpme1_set_filter(uint8_t mode);
lpme1_status_t lpme1_set_LowPass(uint8_t value);

lpme1_status_t lpme1_reset_offset(void);
lpme1_status_t lpme1_heading_reset(void);
lpme1_status_t lpme1_object_reset(void);
/*
  *}Register config Functions
  */


float uint8_to_float(uint8_t *pu8vals);
float uint32_to_float(uint32_t *pu32val);

#define EXAMPLE_DEBUG
#ifdef EXAMPLE_DEBUG
void lpme1_example(void);
void lpme1_config_example(void);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif/*__LPME1_H*/
