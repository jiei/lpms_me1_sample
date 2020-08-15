/***********************************************************************
**
**
** Copyright (C) 2013 LP-Research
** All rights reserved.
** Contact: LP-Research (info@lp-research.com)
***********************************************************************/

/**********************************************************************
  * Low level driver for lpms-me1 motion sensor
  * Based om stm32 platform 
  * Use stm32 hal driver library :SM32F4Cube
  * Test on STM32F411RE Nucleo

**********************************************************************/

#include "lpme1_driver.h"

#ifdef USE_HAL_DRIVER
/**
  *@brief: Read register value from lpms-me1 motion sensor
  *@para: regaddr, register address to be read
  *@para: buf, Pointer to uint8_t variable use to save read value
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_read_reg(uint8_t regaddr,uint8_t *buf)
{
#ifdef USE_IIC
    if(HAL_I2C_Mem_Read(&LPME1_HI2C, LPME1_I2C_ADRRESS, regaddr,
                        I2C_MEMADD_SIZE_8BIT, buf, 1, LPME1_MAX_TIMEOUT)==HAL_OK)
        return LPME1_OK;
    else
        return LPME1_ERROR;

#elif defined USE_SPI
    regaddr |= 0x80;
	uint8_t temp = 0xFF;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(&LPME1_HSPI, &regaddr, 1, LPME1_MAX_TIMEOUT) != HAL_OK) return LPME1_ERROR;
  	if(HAL_SPI_TransmitReceive(&LPME1_HSPI, &temp, buf, 1, LPME1_MAX_TIMEOUT) != HAL_OK) return LPME1_ERROR;
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    temp = 20; while(temp--);   //give slave some time
	
    return LPME1_OK;
#endif
}
/**
  *@brief: Write value  to lpms-me1 motion sensor register
  *@para: regaddr, register address to be write
  *@para: buf, Pointer to uint8_t variable saved the data to be write
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_write_reg(uint8_t regaddr,uint8_t *buf)
{
#ifdef USE_IIC
    if(HAL_I2C_Mem_Write(&LPME1_HI2C, LPME1_I2C_ADRRESS, regaddr,
                         I2C_MEMADD_SIZE_8BIT, buf, 1, LPME1_MAX_TIMEOUT)==HAL_OK)
        return LPME1_OK;
    else
        return LPME1_ERROR;

#elif defined USE_SPI
    regaddr &= (~0x80);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(&LPME1_HSPI, &regaddr, 1, LPME1_MAX_TIMEOUT) != HAL_OK) return LPME1_ERROR;
	if(HAL_SPI_Transmit(&LPME1_HSPI, buf, 1, LPME1_MAX_TIMEOUT) != HAL_OK) return LPME1_ERROR;
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	uint8_t i = 20;while(i--);
	
    return LPME1_OK;
#endif
}
/**
  *@brief: Read a set of registers from lpms-me1 motion sensor
  *@para: regaddr, register start address to be read
  *@para: buf, Pointer to uint8_t array use to save read datas
  *@para: len, data length to be read
  *@ret: Status, return LPME1_OK if read success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_read_buffer(uint8_t regaddr,uint8_t *buf,uint8_t len)
{
#ifdef USE_IIC
    if(HAL_I2C_Mem_Read(&LPME1_HI2C, LPME1_I2C_ADRRESS, regaddr,
                        I2C_MEMADD_SIZE_8BIT, buf, len, LPME1_MAX_TIMEOUT)==HAL_OK)
        return LPME1_OK;
    else
        return LPME1_ERROR;
 
#elif defined USE_SPI
    regaddr |= 0x80;
	uint8_t temp[LPME1_ALL_REG_SIZE];
	for(uint8_t i=0; i<len; i++)temp[i] = 0xFF;
	uint8_t i = 10;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(&LPME1_HSPI, &regaddr, 1, LPME1_MAX_TIMEOUT) != HAL_OK) return LPME1_ERROR;
  	if(HAL_SPI_TransmitReceive(&LPME1_HSPI, temp, buf, len, LPME1_MAX_TIMEOUT) != HAL_OK) return LPME1_ERROR;
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	while(i--);
	
    return LPME1_OK;
#endif
}

/**
  *@brief: Write a set of registers to lpms-me1 motion sensor
  *@para: regaddr, register start address to be wtite
  *@para: buf, Pointer to uint8_t array use to save wtire datas
  *@para: len, data length to be write
  *@ret: Status, return LPME1_OK if write success otherwise return LPME1_ERROR
  */
lpme1_status_t lpme1_write_buffer(uint8_t regaddr,uint8_t *buf,uint8_t len)
{
#ifdef USE_IIC
    if(HAL_I2C_Mem_Write(&LPME1_HI2C, LPME1_I2C_ADRRESS, regaddr,
                        I2C_MEMADD_SIZE_8BIT, buf, len, LPME1_MAX_TIMEOUT)==HAL_OK)
        return LPME1_OK;
    else
        return LPME1_ERROR;
 
#elif defined USE_SPI
    regaddr &= ~0x80;
	uint8_t temp[LPME1_ALL_REG_SIZE];
	for(uint8_t i=0; i<len; i++)temp[i] = 0xFF;
	uint8_t i = 10;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(&LPME1_HSPI, &regaddr, 1, LPME1_MAX_TIMEOUT) != HAL_OK) return LPME1_ERROR;
  	if(HAL_SPI_TransmitReceive(&LPME1_HSPI, buf, temp, len, LPME1_MAX_TIMEOUT) != HAL_OK) return LPME1_ERROR;
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	while(i--);
	
    return LPME1_OK;
#endif
}

#endif/*USE_HAL_DRIVER*/
