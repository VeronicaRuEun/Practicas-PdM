/*
 * LCD.h
 *
 *  Created on: Dec 14, 2023
 *      Author: eunchan
 */

#ifndef API_INC_LCD_H_
#define API_INC_LCD_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"
#include "I2C.h"
#include "API_delay.h"

#include "stm32f4xx_hal.h"

/*Configuracion para la pocision en el LCD*/
#define LINE_SUP 1
#define LINE_INF 2
#define COL_0 0
#define COL_1 1
#define COL_2 2
#define COL_3 3
#define COL_4 4
#define COL_5 5
#define COL_6 6
#define COL_7 7
#define COL_8 8
#define COL_9 9
#define COL_10 10
#define COL_11 11
#define COL_12 12
#define COL_13 13
#define COL_14 14
#define COL_15 15

/*Prototipos de funciones utilizadas*/
//void LCD_Gpio(void);
void LCD_Init(uint8_t DevAddress);
void LCD_inst(uint8_t inst, uint8_t DevAddress);
uint8_t LCD_enviaNibble(uint8_t nibble, uint8_t rs_bit, uint8_t e_bit);
void LCD_limpiar(uint8_t DevAddress);
void LCD_car(char car, uint8_t DevAddress);
void LCD_string(char *str_car, uint8_t DevAddress);
void LCD_Pos(uint8_t numLinea, uint8_t num_Col, uint8_t DevAddress);

#endif /* API_INC_LCD_H_ */
