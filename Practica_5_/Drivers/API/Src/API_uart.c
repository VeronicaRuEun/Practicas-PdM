/*
 * API_uart.c
 *
 *  Created on: Nov 16, 2023
 *      Author: eunchan
 */
#include "API_uart.h"


#define TIME_OUT 100 //Tiempo de duracion
UART_HandleTypeDef UART2_U; //Declaracion de estructura handle


/*En esta función se inicializan los parámetros necesarios para UART2*/
bool_t uartInit()
{
	UART2_U.Instance = USART2;
	UART2_U.Init.BaudRate = 9600;
	UART2_U.Init.WordLength= UART_WORDLENGTH_8B;
	UART2_U.Init.StopBits = UART_STOPBITS_1;
	UART2_U.Init.Parity = UART_PARITY_NONE;
	UART2_U.Init.Mode = UART_MODE_TX_RX;
	UART2_U.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART2_U.Init.OverSampling =UART_OVERSAMPLING_16;

	/*Comprueba si se true: si la inicialización es exitosa
	 * y false: si la inicialización no es exitosa*/
	if (HAL_UART_Init(&UART2_U) != HAL_OK)
	{
		return false;
	}

		return true;
}

/* recibe un puntero a un string el cual se desea enviar
 * por la UART completo hasta el caracter ‘\0’ */
void uartSendString(uint8_t * pstring)
{
	uint8_t cont=0;
	while(pstring[cont]!='\0')

		{
		cont++;
		}

		uartSendStringSize(pstring, cont);cont=0;

}

/*Recibe un puntero a un string que se desea enviar por la UART
 *  y un entero con la cantidad de caracteres que debe enviar
 *  utilizando la funcion de Transmit*/
void uartSendStringSize(uint8_t * pstring, uint16_t size)
{
	HAL_UART_Transmit(&UART2_U, pstring, size, TIME_OUT);
}

/*Recibe un puntero a un string que se desea enviar por la UART
 *  y un entero con la cantidad de caracteres que debe recibir
 *  utilizando la funcion de Receive*/

void uartReceiveStringSize(uint8_t * pstring, uint16_t size)
{
	HAL_UART_Receive(&UART2_U, pstring, size, TIME_OUT);
}

