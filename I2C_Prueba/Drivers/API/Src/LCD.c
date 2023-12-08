/*
 * LCD.c
 *
 *  Created on: Nov 30, 2023
 *      Author: eunchan
 */


#include "LCD.h"
#include "I2C.h"

#define TIME_LCD 50
#define INIT_VAL 0
#define LONG_NIBBLE 4

#define BIT_7 7
#define BIT_6 6
#define BIT_5 5
#define BIT_4 4
#define BIT_BL 3
#define BIT_E 2
#define BIT_RW 1
#define BIT_RS 0

#define BL_VAL 1
#define RW_VAL 0
#define E_VAL_ON 1
#define E_VAL_OFF 0
#define RS_VAL_ON 1
#define RS_VAL_OFF 0
#define DATO_LCD 4

extern I2C_HandleTypeDef I2C1_handle;


/*void LCD_Gpio(void)
{
	GPIO_InitTypeDef gpioInitLcd={0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpioInitLcd.Pin = D7_LCD_PIN | D6_LCD_PIN | D5_LCD_PIN | D4_LCD_PIN | BL_LCD_PIN | RS_LCD_PIN | E_LCD_PIN | RW_LCD_PIN;
	gpioInitLcd.Mode = GPIO_MODE_OUTPUT_PP;
    gpioInitLcd.Pull = GPIO_NOPULL;
    gpioInitLcd.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    HAL_GPIO_Init(D7_LCD_PORT, &gpioInitLcd);

}*/

void LCD_Init(uint8_t DevAddress)
{
	//LCD_Gpio();
	/*Inicializacion para interfaz 4-bit*/
	HAL_Delay(50);
	LCD_inst(0x30,DevAddress);
	HAL_Delay(5);
	LCD_inst(0x30,DevAddress);
	HAL_Delay(1);
	LCD_inst(0x30,DevAddress);
	HAL_Delay(10);
	LCD_inst(0x20,DevAddress); /*Configura DL de 4-bit*/
	HAL_Delay(10);

	LCD_inst(0x28,DevAddress); /*Configura display*/
	HAL_Delay(1);
	LCD_inst(0x08,DevAddress); /*Apaga display*/
	HAL_Delay(1);
	LCD_inst(0x01,DevAddress); /*Limpia display*/
	HAL_Delay(2);
	LCD_inst(0x06,DevAddress);
	HAL_Delay(1);
	LCD_inst(0x0C,DevAddress);
}

/*Envía Instrucciones al LCD, por tanto, RS = 0 siempre*/
void LCD_inst(uint8_t inst,uint8_t DevAddress)
{
	uint8_t instMSB = (inst>>4)&0X0F;
	uint8_t instLSB = (inst)&0X0F;

	uint8_t palabra[DATO_LCD];
	palabra[0]=LCD_enviaNibble(instMSB, RS_VAL_OFF, E_VAL_ON);
	palabra[1]=LCD_enviaNibble(instMSB, RS_VAL_OFF, E_VAL_OFF);
	palabra[2]=LCD_enviaNibble(instLSB, RS_VAL_OFF, E_VAL_ON);
	palabra[3]=LCD_enviaNibble(instLSB, RS_VAL_OFF, E_VAL_OFF);
	I2C_Transmit(DevAddress, palabra);

}

uint8_t LCD_enviaNibble(uint8_t nibble, uint8_t rs_bit, uint8_t e_bit)
{
	uint8_t bufferDatos = nibble << BIT_4 | BL_VAL << BIT_BL | e_bit << BIT_E |RW_VAL << BIT_RW | rs_bit ;
	return bufferDatos;

}
void LCD_limpiar(uint8_t DevAddress)
{
	LCD_inst(0x01,DevAddress);
	HAL_Delay(TIME_LCD);

}
void LCD_car(char car, uint8_t DevAddress)
{
	uint8_t carMSB = (car>>4)&0X0F;
	uint8_t carLSB = (car)&0X0F;

	uint8_t palabra[DATO_LCD];

	palabra[0]=LCD_enviaNibble(carMSB, RS_VAL_ON, E_VAL_ON);
	palabra[1]=LCD_enviaNibble(carMSB, RS_VAL_ON, E_VAL_OFF);
	//HAL_Delay(TIME_LCD);
	palabra[2]=LCD_enviaNibble(carLSB, RS_VAL_ON, E_VAL_ON);
	palabra[3]=LCD_enviaNibble(carLSB, RS_VAL_ON, E_VAL_OFF);
	I2C_Transmit(DevAddress, palabra);
}
void LCD_string(char *str_car, uint8_t DevAddress)
{
	uint8_t cont=0;
		while(str_car[cont]!='\0')

			{
			LCD_car(str_car[cont],DevAddress);
			cont++;
			}
}
//void LCD_cursor(uint8_t x, uint8_t y);


