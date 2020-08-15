/***********************************************************************
**
**
** Copyright (C) 2013 LP-Research
** All rights reserved.
** Contact: LP-Research (info@lp-research.com)
***********************************************************************/

#ifndef __LPME1_DRIVER_H
#define __LPME1_DRIVER_H

#include "lpme1.h"
#include "stm32f3xx_hal.h"

#ifdef USE_IIC
  #include "i2c.h"
#elif defined USE_SPI
  #include "spi.h"
#endif

#ifdef USE_IIC
  #define LPME1_I2C_ADRRESS  0x64
  #define LPME1_HI2C hi2c1
#elif defined USE_SPI
  #define LPME1_HSPI hspi1
#endif


#define LPME1_MAX_TIMEOUT 100

lpme1_status_t lpme1_read_reg(uint8_t regaddr,uint8_t *buf);
lpme1_status_t lpme1_write_reg(uint8_t regaddr,uint8_t *buf);
lpme1_status_t lpme1_read_buffer(uint8_t regaddr,uint8_t *buf,uint8_t len);
lpme1_status_t lpme1_write_buffer(uint8_t regaddr,uint8_t *buf,uint8_t len);


#endif/*__LPME1_H*/
