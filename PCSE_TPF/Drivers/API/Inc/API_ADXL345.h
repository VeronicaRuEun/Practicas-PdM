/*
 * API_ADXL345.h
 *
 *      Author: eunchan
 */

#ifndef API_INC_API_ADXL345_H_
#define API_INC_API_ADXL345_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"
#include "API_delay.h"

#include "stm32f4xx_hal.h"
#include "API_SPI.h"

/*Configuracion para cantidad de bytes de Lectura/Escritura*/
#define NUM_BYTE_WRITE 1
#define NUM_BYTES_WRITE 2
#define NUM_BYTES_READ 6

/*Comandos de direcciones para ADXL345*/
#define ADXL_DEVID 0x00
#define ADXL_THRESH_TAP 0x1D
#define ADXL_OFSX 0x1E
#define ADXL_OFSY 0x1F
#define ADXL_OFSZ 0x20
#define ADXL_DUR 0X21
#define ADXL_LATENT 0X22
#define ADXL_WINDOW 0X23
#define ADXL_THRESH_ACT 0x24
#define ADXL_THRESH_INACT 0x25
#define ADXL_TIME_INACT 0x26
#define ADXL_ACT_INACT_CTL 0X27
#define ADXL_THRESH_FF 0X28
#define ADXL_TIME_FF 0X29
#define ADXL_TAP_AXES 0X2A
#define ADXL_ACT_TAP_STATUS 0X2B
#define ADXL_BW_RATE 0X2C
#define ADXL_POWER_CTL 0X2D
#define ADXL_INT_ENABLE 0X2E
#define ADXL_INT_MAP 0X2F
#define ADXL_INT_SOURCE 0X30
#define ADXL_DATA_FORMAT 0X31
#define ADXL_DATAX0 0X32
#define ADXL_DATAX1 0X33
#define ADXL_DATAY0 0X34
#define ADXL_DATAY1 0X35
#define ADXL_DATAZ0 0X36
#define ADXL_DATAZ1 0X37
#define ADXL_FIFO_CTL 0X38
#define ADXL_FIFO_STATUS 0X39

/*Configuracion Reg ADXL_POWER_CTL Medicion y Frecuencia*/
#define P_CTL_MEAS_FREQ8 0x08
#define P_CTL_MEAS_FREQ4 0x09
#define P_CTL_MEAS_FREQ2 0x0A
#define P_CTL_MEAS_FREQ1 0x0B

/*Configuracion Reg ADXL_DATA_FORMAT Rango */
#define DATA_FORMAT2G 0x00
#define DATA_FORMAT4G 0x01
#define DATA_FORMAT8G 0x02
#define DATA_FORMAT16G 0x03

/*Valores para inicializacion*/
typedef enum {
	ADXL_OK,
	ADXL_ERROR
} adxlEstado;

/*Prototipo de funciones*/

void adxl_write(uint8_t address, uint8_t value);
void adxl_read(uint8_t address);
adxlEstado adxl_init(void);
float* adxl_ObtenerAcc(void);

#endif /* API_INC_API_ADXL345_H_ */
