/*
 * I2C.h
 *
 *      Author: eunchan
 */

#ifndef API_INC_I2C_H_
#define API_INC_I2C_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"

/*Definicion de GPIO y pines para I2C*/
#define I2C1_PORT_SCL GPIOB
#define I2C1_PIN_SCL GPIO_PIN_6
#define I2C1_PORT_SDA GPIOB
#define I2C1_PIN_SDA GPIO_PIN_7

/*Prototipos de funciones para I2C*/
void I2C_Gpio(void);
bool I2C_Init(void);
uint8_t I2C_ScanAdress(void);
void I2C_Transmit(uint16_t DevAddress, uint8_t *pData);

#endif /* API_INC_I2C_H_ */
