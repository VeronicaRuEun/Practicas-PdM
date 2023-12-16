/*
 * API_I2C.c
 *
 *      Author: eunchan
 */

#include "API_I2C.h"


I2C_HandleTypeDef I2C1_handle;
uint8_t addDevice;

/*Configuracion de GPIO para I2C
 * @entradas: ninguna
 * 1. Se hace la configuracion de los GPIO para I2C utilizados
 * * @retorno: ninguno
 * */
void I2C_Gpio(void) {

	GPIO_InitTypeDef gpio_I2C = { 0 };

	gpio_I2C.Pin = I2C1_PIN_SCL | I2C1_PIN_SDA;
	gpio_I2C.Mode = GPIO_MODE_AF_OD;
	gpio_I2C.Pull = GPIO_PULLUP;
	gpio_I2C.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_I2C.Alternate = GPIO_AF4_I2C1;

	HAL_GPIO_Init(GPIOB, &gpio_I2C);

}

/*Inicializacion de I2C:
 * @entradas: ninguna
 * 1. Se hace la inicializacion del I2C seleccionado con su respectiva configuración
 * * @retorno: estado de Inicializacion
 * */
bool I2C_Init(void) {
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

	if (HAL_I2C_Init(&I2C1_handle) != HAL_OK) {
		return false;
	}
	return true;
}
