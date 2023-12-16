/*
 * API_ADXL345_port.c
 *
 *      Author: eunchan
 */

#include "API_ADXL345_port.h"
#include "API_SPI.h"
#include "API_ADXL345.h"

extern SPI_HandleTypeDef SPI_handle;

void adxl_enviarDatos(uint8_t DevAddress ,uint8_t *dato)
{
	//SPI_Transmit(dato, NUM_BYTES_WRITE);
	SPI_CS_Low();
	HAL_SPI_Transmit(&SPI_handle, dato, NUM_BYTES_WRITE, TIMEOUTSPI);
	SPI_CS_High();

}

void adxl_obtenDatos(uint8_t DevAddress ,uint8_t *dato)
{
	//SPI_TransmitReceive(DevAddress, dato, NUM_BYTES_READ);
	SPI_CS_Low();
	HAL_SPI_Transmit(&SPI_handle, &DevAddress, SIZE_ADDR, TIMEOUTSPI);
	HAL_SPI_Receive(&SPI_handle, dato, NUM_BYTES_READ, TIMEOUTSPI);
	SPI_CS_High();
}
