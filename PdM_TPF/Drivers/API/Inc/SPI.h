/*
 * SPI.h
 *
 *      Author: eunchan
 */

#ifndef API_INC_SPI_H_
#define API_INC_SPI_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"

/*Definicion de GPIO y pines para SPI*/
#define SPI1_PORT GPIOA
#define SPI1_PORT_MISO GPIOA
#define SPI1_PIN_MISO GPIO_PIN_6
#define SPI1_PORT_MOSI GPIOA
#define SPI1_PIN_MOSI GPIO_PIN_7
#define SPI1_PORT_SCLK GPIOA
#define SPI1_PIN_SCLK GPIO_PIN_5
#define SPI1_PORT_CS GPIOA
#define SPI1_PIN_CS GPIO_PIN_4

/*Prototipos de funciones para SPI*/
void SPI_Gpio(void);
bool SPI_Init(void);
void SPI_CS_Low(void);
void SPI_CS_High(void);
void SPI_Transmit(uint8_t *pData, uint8_t size);
void SPI_TransmitReceive(uint8_t address, uint8_t *pData, uint8_t size);

#endif /* API_INC_SPI_H_ */
