/*
 * API_uart.h
 *
 *  Created on: Nov 16, 2023
 *      Author: eunchan
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#ifndef __STDINT_H_
#include <stdint.h>
#endif

#ifndef __STDBOOL_H_
#include <stdbool.h>
#endif

#include "stm32f4xx_hal.h"
#include "API_delay.h"



/*Prototipos de funciones para UART*/
bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* API_INC_API_UART_H_ */
