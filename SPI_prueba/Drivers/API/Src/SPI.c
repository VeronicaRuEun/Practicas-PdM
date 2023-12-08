/*
 * SPI.c
 *
 *  Created on: Dec 6, 2023
 *      Author: eunchan
 */

#include "SPI.h"

#define SPI1_PORT GPIOA
#define SPI1_PORT_MISO GPIOA
#define SPI1_PIN_MISO GPIO_PIN_6
#define SPI1_PORT_MOSI GPIOA
#define SPI1_PIN_MOSI GPIO_PIN_7
#define SPI1_PORT_SCLK GPIOA
#define SPI1_PIN_SCLK GPIO_PIN_5
#define SPI1_PORT_CS GPIOA
#define SPI1_PIN_CS GPIO_PIN_4

#define SPI1_PIN_CS_ON GPIO_PIN_SET
#define SPI1_PIN_CS_OFF GPIO_PIN_RESET

#define TIMEOUT 100

SPI_HandleTypeDef SPI_handle;
uint8_t address;


void SPI_Gpio(void)
{

	GPIO_InitTypeDef gpio_SPI = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();

	gpio_SPI.Pin = SPI1_PIN_SCLK | SPI1_PIN_MISO | SPI1_PIN_MOSI;
	gpio_SPI.Mode = GPIO_MODE_AF_PP;
	gpio_SPI.Pull = GPIO_NOPULL;
	gpio_SPI.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_SPI.Alternate = GPIO_AF5_SPI1;

	HAL_GPIO_Init(SPI1_PORT, &gpio_SPI);

}

bool SPI_Init(void)
{
	SPI_Gpio();
	__HAL_RCC_SPI1_CLK_ENABLE();

	SPI_handle.Instance = SPI1;
	SPI_handle.Init.Mode = SPI_MODE_MASTER;
	SPI_handle.Init.Direction = SPI_DIRECTION_2LINES;
	SPI_handle.Init.DataSize = SPI_DATASIZE_8BIT;
	SPI_handle.Init.CLKPolarity = SPI_POLARITY_HIGH;
	SPI_handle.Init.CLKPhase = SPI_PHASE_2EDGE;
	SPI_handle.Init.NSS = SPI_NSS_SOFT;
	SPI_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	SPI_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI_handle.Init.TIMode = SPI_TIMODE_DISABLE;
	SPI_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI_handle.Init.CRCPolynomial = 10;


	if(HAL_SPI_Init(&SPI_handle) != HAL_OK)
	{
		return false;
	}
	return true;
}

void SPI_CS_Bajo(void)
{
	HAL_GPIO_WritePin (SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_OFF);
}
void SPI_CS_Alto(void)
{
	HAL_GPIO_WritePin (SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_ON);
}

void SPI_Transmit(uint8_t *pData, uint8_t size)
{
	HAL_SPI_Transmit(&SPI_handle, pData, size, TIMEOUT);
}

void SPI_Receive(uint8_t *pData, uint8_t size)
{
	HAL_SPI_Receive(&SPI_handle, pData, size, TIMEOUT);
}

