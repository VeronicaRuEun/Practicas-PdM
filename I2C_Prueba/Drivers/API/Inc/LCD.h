/*
 * LCD.h
 *
 *  Created on: Nov 30, 2023
 *      Author: eunchan
 */

#ifndef API_INC_LCD_H_
#define API_INC_LCD_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"

#include "stm32f4xx_hal.h"

//void LCD_Gpio(void);
void LCD_Init(uint8_t DevAddress);
void LCD_inst(uint8_t inst,uint8_t DevAddress);
uint8_t LCD_enviaNibble(uint8_t nibble, uint8_t rs_bit, uint8_t e_bit);
void LCD_limpiar(uint8_t DevAddress);
//void LCD_cursor(uint8_t x, uint8_t y);
void LCD_car(char car,uint8_t DevAddress);
void LCD_string(char *str_car, uint8_t DevAddress);

#endif /* API_INC_LCD_H_ */
