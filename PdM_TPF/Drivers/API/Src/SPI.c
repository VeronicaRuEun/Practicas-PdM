/*
 * SPI.c
 *
 *      Author: eunchan
 */

#include "SPI.h"

#define SPI1_PIN_CS_ON GPIO_PIN_SET
#define SPI1_PIN_CS_OFF GPIO_PIN_RESET

#define TIMEOUT 100
#define SIZE_ADDR 1

SPI_HandleTypeDef SPI_handle;
uint8_t address;

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

/*Transmision de datos a SPI:
 * @entradas: size (numero de datos a enviar)
 * @entradas: pData (datos a enviar al dispositivo)
 * 1. Se habilita el dispositivo SPI con el que se va a comunicar
 * 2. Se auxilia de la funcion SPI_Transmit de HAL
 * 3. Se deshabilita el dispositivo SPI con el que se va a comunicar
 * * @retorno: ninguno
 * */
void SPI_Transmit(uint8_t *pData, uint8_t size) {
	SPI_CS_Low();
	HAL_SPI_Transmit(&SPI_handle, pData, size, TIMEOUT);
	SPI_CS_High();
}

/*Transmision de direccion y Recepcion de datos  SPI:
 * @entradas: address (direccion de la cual se quieren leer datos)
 * @entradas: size (numero de datos a recibir)
 * @entradas: pData (para guardar datos recibidos)
 * 1. Se habilita el dispositivo SPI con el que se va a comunicar
 * 2. Se auxilia de la funcion SPI_Transmit de HAL para enviar la direccion
 * 3. Se auxilia de la funcion SPI_Receive de HAL para recibir datos de la direccion transmitida
 * 3. Se deshabilita el dispositivo SPI con el que se va a comunicar
 * * @retorno: ninguno
 * */
void SPI_TransmitReceive(uint8_t address, uint8_t *pData, uint8_t size) {
	SPI_CS_Low();
	HAL_SPI_Transmit(&SPI_handle, &address, SIZE_ADDR, TIMEOUT);
	HAL_SPI_Receive(&SPI_handle, pData, size, TIMEOUT);
	SPI_CS_High();

}
