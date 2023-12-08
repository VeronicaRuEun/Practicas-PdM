/*
 * I2C.c
 *
 *  Created on: Nov 25, 2023
 *      Author: eunchan
 */

#include "I2C.h"

#define TRIALS_IDR 1
#define TIMEOUT 10

I2C_HandleTypeDef I2C1_handle;
uint8_t addDevice;


void I2C_Gpio(void)
{

	GPIO_InitTypeDef gpio_I2C = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();

	gpio_I2C.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	gpio_I2C.Mode = GPIO_MODE_AF_OD;
	gpio_I2C.Pull = GPIO_PULLUP;
	gpio_I2C.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_I2C.Alternate = GPIO_AF4_I2C1;

	HAL_GPIO_Init(GPIOB, &gpio_I2C);

}

bool I2C_Init(void)
{
	I2C_Gpio();
	__HAL_RCC_I2C1_CLK_ENABLE();

	I2C1_handle.Instance = I2C1;

	I2C1_handle.Init.ClockSpeed = 100000;
	I2C1_handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	I2C1_handle.Init.OwnAddress1 = 0;
	I2C1_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C1_handle.Init.OwnAddress2 = 0;
	I2C1_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2C1_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C1_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if(HAL_I2C_Init(&I2C1_handle) != HAL_OK)
	{
		return false;
	}
	return true;
}

/*Escaner para buscar la direccion del módulo I2C utilizado*/
uint8_t I2C_ScanAdress(void)
{
	uint8_t isReady;
	uint8_t addCount=0;

	while(isReady != HAL_OK)
	{

		isReady = HAL_I2C_IsDeviceReady(&I2C1_handle, addCount<<1, TRIALS_IDR, TIMEOUT);
		addCount++;
	}

	addDevice = addCount<<1;
	addCount=0;
	return addDevice;

}

void I2C_Transmit(uint16_t DevAddress, uint8_t *pData)
{
	HAL_I2C_Master_Transmit(&I2C1_handle, addDevice, pData, sizeof(pData), TIMEOUT);
}

