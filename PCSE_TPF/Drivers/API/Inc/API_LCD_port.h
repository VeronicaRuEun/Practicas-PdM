/*
 * API_LCD_port.h
 *
 *      Author: eunchan
 */

#ifndef API_INC_API_LCD_PORT_H_
#define API_INC_API_LCD_PORT_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"

void LCD_enviarByte(uint8_t DevAddress,uint8_t *dato);

#endif /* API_INC_API_LCD_PORT_H_ */
