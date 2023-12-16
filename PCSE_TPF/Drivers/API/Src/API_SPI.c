/*
 * API_SPI.c
 *
 *      Author: eunchan
 */

#include "API_SPI.h"

#define SPI1_PIN_CS_ON GPIO_PIN_SET
#define SPI1_PIN_CS_OFF GPIO_PIN_RESET



SPI_HandleTypeDef SPI_handle;

/*Configuracion de GPIO para SPI
 * @entradas: ninguna
 * 1. Se hace la configuracion de los GPIO para SPI utilizados
 * * @retorno: ninguno
 * */
void SPI_Gpio(void) {

	GPIO_InitTypeDef gpio_SPI = { 0 };
	__HAL_RCC_GPIOA_CLK_ENABLE();

	gpio_SPI.Pin = SPI1_PIN_SCLK | SPI1_PIN_MISO | SPI1_PIN_MOSI;
	gpio_SPI.Mode = GPIO_MODE_AF_PP;
	gpio_SPI.Pull = GPIO_NOPULL;
	gpio_SPI.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_SPI.Alternate = GPIO_AF5_SPI1;

	HAL_GPIO_Init(SPI1_PORT, &gpio_SPI);

}

/*Inicializacion de SPI:
 * @entradas: ninguna
 * 1. Se hace la inicializacion del SPI seleccionado con su respectiva configuración
 * * @retorno: estado de Inicializacion
 * */
bool SPI_Init(void) {
	SPI_CS_High();
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

	if (HAL_SPI_Init(&SPI_handle) != HAL_OK) {
		return false;
	}
	return true;
}

/*Habilita CS del dispositivo para comunicarse por SPI:
 * @entradas: ninguna
 * 1. Se habilita el pin CS del dispositivo SPI con el que se va a comunicar
 * @retorno: ninguno
 * */
void SPI_CS_Low(void) {
	HAL_GPIO_WritePin(SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_OFF);
}

/*Deshabilita CS del dispositivo para comunicarse por SPI:
 * @entradas: ninguna
 * 1. Se deshabilita el pin CS del dispositivo SPI con el que se va a comunicar
 * @retorno: ninguno
 * */
void SPI_CS_High(void) {
	HAL_GPIO_WritePin(SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_ON);
}


