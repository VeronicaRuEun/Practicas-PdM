/*
 * API_LCD.c
 *
 *      Author: eunchan
 */


#include "API_LCD.h"
#include "API_I2C.h"
#include "API_LCD_port.h"

/*Configuracion para LCD*/
#define TIME_LCD 50
#define INIT_VAL 0
#define LONG_NIBBLE 4

/*Posiciones de bit correspondientes*/
#define BIT_7 7
#define BIT_6 6
#define BIT_5 5
#define BIT_4 4
#define BIT_BL 3
#define BIT_E 2
#define BIT_RW 1
#define BIT_RS 0

/*Valores definidos para LCD*/
#define BL_VAL 1
#define RW_VAL 0
#define E_VAL_ON 1
#define E_VAL_OFF 0
#define RS_VAL_ON 1
#define RS_VAL_OFF 0
#define DATO_LCD 4

//Comandos de inicializacion
#define INST_INI1 0X30
#define INST_INI2 0X20

//Comando 4 bits
#define MODO4BITS 0x28

//Tiempos para inicializacion
#define DELAY50MS 50
#define DELAY10MS 10
#define DELAY5MS 5
#define DELAY2MS 2
#define DELAY1MS 1

//Control de 4bits (nibbles)
#define NIBBLE_CONTROL	0x0F

//Configuracion de display para 4 bits
#define DISP_N1F0 0X28
#define DISP_OFF 0x08
#define DISP_ON 0x0C
#define DISP_CLEAR 0x01
#define DISP_ENTRYMODE 0x06

//Configuracion para la posicion del cursor en LCD 16x2
#define DISP_POS_LINE1 0x80
#define DISP_POS_LINE2 0xC0

#define DISP_LINEA_MIN 1
#define DISP_LINEA_MAX 2

extern I2C_HandleTypeDef I2C1_handle;

void LCD_Delay(uint16_t delayLCD);

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

/*Inicializacion de LCD:
 * @entradas: DevAddress (Direccion del dispositivo LCD)
 * 1. Se hace una inicializacion correspondiente a la Hoja de datos del LCD
 * * @retorno: ninguno
 * */

void LCD_Init(uint8_t DevAddress) {
	//LCD_Gpio();

	/*Inicializacion para interfaz 4-bit*/
	LCD_Delay(DELAY50MS);
	LCD_inst(INST_INI1, DevAddress);
	LCD_Delay(DELAY5MS);
	LCD_inst(INST_INI1, DevAddress);
	LCD_Delay(DELAY1MS);
	LCD_inst(INST_INI1, DevAddress);
	LCD_Delay(DELAY10MS);
	LCD_inst(INST_INI2, DevAddress); /*Configura DL de 4-bit*/
	LCD_Delay(DELAY10MS);

	LCD_inst( DISP_N1F0, DevAddress); /*Configura display*/
	LCD_Delay(DELAY1MS);
	LCD_inst(DISP_OFF, DevAddress); /*Apaga display*/
	LCD_Delay(DELAY1MS);
	LCD_inst(DISP_CLEAR, DevAddress); /*Limpia display*/
	LCD_Delay(DELAY2MS);
	LCD_inst(DISP_ENTRYMODE, DevAddress);
	LCD_Delay(DELAY1MS);
	LCD_inst(DISP_ON, DevAddress);
}

/*Envío de instrcciones/comandos al LCD:
 * @entradas: DevAddress (Direccion del dispositivo LCD)
 * @entradas: inst (instruccion/comando de 8 bits)
 * 1. Separa la instruccion en dos nibles: MSB y LSB
 * 2. En un vector se almacenan los nibles con los valores de RS y E
 * (Envía Instrucciones al LCD, por tanto, RS = 0 siempre)
 * 3. Se hace una transmision I2C
 * * @retorno: ninguno
 * */
void LCD_inst(uint8_t inst, uint8_t DevAddress) {
	uint8_t instMSB = (inst >> LONG_NIBBLE) & 0X0F;
	uint8_t instLSB = (inst) & 0X0F;

	uint8_t palabra[DATO_LCD];
	palabra[0] = LCD_enviaNibble(instMSB, RS_VAL_OFF, E_VAL_ON);
	palabra[1] = LCD_enviaNibble(instMSB, RS_VAL_OFF, E_VAL_OFF);
	palabra[2] = LCD_enviaNibble(instLSB, RS_VAL_OFF, E_VAL_ON);
	palabra[3] = LCD_enviaNibble(instLSB, RS_VAL_OFF, E_VAL_OFF);
	LCD_enviarByte(DevAddress ,palabra);
}

/*Envío de nibbles al LCD:
 * @entradas: nible (MSB y LSB)
 * @entradas: rs_bit Bit RC
 * @entradas: e_bit Bir Enable
 * 1. Almacena el nible con los valores correspondientes a BL, E, RW, RS
 * * @retorno: bufferDatos (nible+4 valores)
 * */
uint8_t LCD_enviaNibble(uint8_t nibble, uint8_t rs_bit, uint8_t e_bit) {
	uint8_t bufferDatos = nibble << BIT_4 | BL_VAL << BIT_BL | e_bit << BIT_E
			| RW_VAL << BIT_RW | rs_bit;
	return bufferDatos;

}

/*Limpieza del LCD:
 * @entradas: DevAddress (Direccion del dispositivo LCD)
 * * 1. Envía el comando de limpiez para LCD
 * * @retorno: ninguno
 * */
void LCD_limpiar(uint8_t DevAddress) {
	LCD_inst(DISP_CLEAR, DevAddress);
	LCD_Delay(TIME_LCD);

}

/*Envío de caracteres al LCD:
 * @entradas: DevAddress (Direccion del dispositivo LCD)
 * @entradas: car (caracter)
 * 1. Separa la instruccion en dos nibles: MSB y LSB
 * 2. En un vector se almacenan los nibles con los valores de RS y E
 * (Envía caracteres al LCD, por tanto, RS = 1 siempre)
 * 3. Se hace una transmision I2C
 * * @retorno: ninguno
 * */
void LCD_car(char car, uint8_t DevAddress) {
	uint8_t carMSB = (car >> LONG_NIBBLE) & 0X0F;
	uint8_t carLSB = (car) & 0X0F;

	uint8_t palabra[DATO_LCD];

	palabra[0] = LCD_enviaNibble(carMSB, RS_VAL_ON, E_VAL_ON);
	palabra[1] = LCD_enviaNibble(carMSB, RS_VAL_ON, E_VAL_OFF);
	palabra[2] = LCD_enviaNibble(carLSB, RS_VAL_ON, E_VAL_ON);
	palabra[3] = LCD_enviaNibble(carLSB, RS_VAL_ON, E_VAL_OFF);
	LCD_enviarByte(DevAddress ,palabra);
}

/*Envío de cadena de caracteres al LCD:
 * @entradas: DevAddress (Direccion del dispositivo LCD)
 * @entradas: *str_car (cadena de caracteres)
 * 1. Verifica que la cadena no esté vacía
 * 2. Ejecuta el envío de caracteres hasta que se encuentre con el elemento "\0"
 * * @retorno: ninguno
 * */
void LCD_string(char *str_car, uint8_t DevAddress) {
	uint8_t cont = 0;

	while (str_car[cont] != '\0')

	{
		LCD_car(str_car[cont], DevAddress);
		cont++;
	}
}

/*Configura pocision de texto en el LCD:
 * @entradas: DevAddress (Direccion del dispositivo LCD)
 * @entradas: numLinea (Dado que es un display de 2 renglones, solo se puede elegir entre 1 y 2)
 * @entradas: numColumna (Dado que es un display de 16 columnas, solo se puede elegir entre 0-15)
 * 1. Al elegir la línea, se suma con la columna y es enviado como instruccion
 * * @retorno: ninguno
 * */
void LCD_Pos(uint8_t numLinea, uint8_t num_Col, uint8_t DevAddress) {
	uint8_t inst_disp = 0;

	if (numLinea == 1) {
		inst_disp = DISP_POS_LINE1 | num_Col;
		LCD_inst(inst_disp, DevAddress);
	} else if (numLinea == 2) {
		inst_disp = DISP_POS_LINE2 | num_Col;
		LCD_inst(inst_disp, DevAddress);
	}
}

/*Retardo paraLCD:
 * @entradas: delayLCD (valor de retardo)
 * 1. Se auxilia con la funcion Delay de HAL
 * * @retorno: ninguno
 * */
void LCD_Delay(uint16_t delayLCD) {
	HAL_Delay(delayLCD);
}
