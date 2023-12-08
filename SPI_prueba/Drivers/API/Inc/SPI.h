/*
 * SPI.h
 *
 *  Created on: Dec 6, 2023
 *      Author: eunchan
 */

#ifndef API_INC_SPI_H_
#define API_INC_SPI_H_


#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"



void SPI_Gpio(void);
bool SPI_Init(void);
void SPI_CS_Bajo(void);
void SPI_CS_Alto(void);
void SPI_Transmit(uint8_t *pData, uint8_t size);
void SPI_Receive(uint8_t *pData, uint8_t size);

#endif /* API_INC_SPI_H_ */
