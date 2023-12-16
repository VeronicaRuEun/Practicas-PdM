/*
 * API_ADXL345_port.c
 *
 *      Author: eunchan
 */

#include "API_ADXL345_port.h"
#include "API_SPI.h"
#include "API_ADXL345.h"

extern SPI_HandleTypeDef SPI_handle;


/*Envío de datos al ADXL345 por SPI
 * @entradas: DevAddress (registro al que se quiere enviar datos)
 * @entradas: dato (dato a enviar al ADXL345)
 * @retorno: ninguno
 * */
void adxl_enviarDatos(uint8_t DevAddress ,uint8_t *dato)
{
	SPI_CS_Low();
	HAL_SPI_Transmit(&SPI_handle, dato, NUM_BYTES_WRITE, TIMEOUTSPI);
	SPI_CS_High();

}

/*Obtención de datos al ADXL345 por SPI
 * @entradas: DevAddress (registro del que se quiere obtener datos)
 * @entradas: dato (almacena los datos solicitados)
 * @retorno: ninguno
 * */
void adxl_obtenDatos(uint8_t DevAddress ,uint8_t *dato)
{
	SPI_CS_Low();
	HAL_SPI_Transmit(&SPI_handle, &DevAddress, SIZE_ADDR, TIMEOUTSPI);
	HAL_SPI_Receive(&SPI_handle, dato, NUM_BYTES_READ, TIMEOUTSPI);
	SPI_CS_High();
}
