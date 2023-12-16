/*
 * API_LCD_port.c
 *
 *      Author: eunchan
 */

#include "API_LCD_port.h"
#include "API_I2C.h"

extern I2C_HandleTypeDef I2C1_handle;

void LCD_enviarByte(uint8_t DevAddress ,uint8_t *dato)
{
	HAL_I2C_Master_Transmit(&I2C1_handle, DevAddress << CORRECT_ADDRESS, dato,
				sizeof(dato), TIMEOUT);
}
