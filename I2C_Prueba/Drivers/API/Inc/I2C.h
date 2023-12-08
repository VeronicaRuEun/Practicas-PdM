/*
 * I2C.h
 *
 *  Created on: Nov 25, 2023
 *      Author: eunchan
 */

#ifndef API_INC_I2C_H_
#define API_INC_I2C_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"

#define TIMEOUT 10

void I2C_Gpio(void);
bool I2C_Init(void);
uint8_t I2C_ScanAdress(void);
void I2C_Transmit(uint16_t DevAddress, uint8_t *pData);

#endif /* API_INC_I2C_H_ */
