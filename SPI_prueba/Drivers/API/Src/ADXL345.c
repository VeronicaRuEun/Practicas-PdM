/*
 * ADXL345.c
 *
 *  Created on: Dec 6, 2023
 *      Author: eunchan
 */
#include "SPI.h"
#include "ADXL345.h"
/*MAPA DE REGISTROS*/


#define RESET_VALUE 0X00

#define ENABLE_MB_E 0x40
#define ENABLE_MB_L 0xC0
#define ENABLE_B_E 0x40
#define ENABLE_B_L 0xC0

#define NUM_BYTE_E 2
#define NUM_BYTE_L 1
#define NUM_BYTE_XYZ 6

/*Funcion de escritura
void adxl345_Escritura (uint8_t address, uint8_t val)
{
	uint8_t byte[NUM_BYTE_E];
	address = address|ENABLE_MB_E;
	//byte[0] = address|ENABLE_MB_E;
	//byte[1] = val;
	SPI_CS_Bajo();
	//HAL_GPIO_WritePin (SPI_PORT_CS, SPI_PIN_CS, SPI_PIN_CS_OFF);

	SPI_Transmit(byte,NUM_BYTE_E);
	//HAL_SPI_Transmit (&hspi1, byte, NUM_BYTE_E, TIMEOUT); //Funcion SPI

	SPI_CS_Alto();
	//HAL_GPIO_WritePin (SPI_PORT_CS, SPI_PIN_CS, SPI_PIN_CS_ON);
}

uint8_t adxl345_Lectura (uint8_t address)
{
	uint8_t byte_xyzLec[6];
	address = address| ENABLE_MB_L;

	SPI_CS_Bajo();
	SPI_Transmit(address, NUM_BYTE_L);
	SPI_Receive(byte_xyzLec, NUM_BYTE_XYZ);
	SPI_CS_Alto();

	return byte_xyzLec;
}

void adxl345_init (void)
{
	adxl345_Escritura(ADXL_DATA_FORMAT, DATA_FORMAT4G);  // formato de darto +-4g
	adxl345_Escritura (ADXL_POWER_CTL, RESET_VALUE);
	adxl345_Escritura (ADXL_POWER_CTL, P_CTL_MEAS_FREQ8);  // power_cntl Medicion y "Wake up" a 8hz

}
*/
