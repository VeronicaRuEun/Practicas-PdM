/*
 * API_MEF_LCD.c
 *
 *      Author: eunchan
 */

#include "API_MEF_LCD.h"

/*Configuraciones para LCD necesitadas*/
#define DIGITAL_OUTPUT_ON GPIO_PIN_SET
#define DIGITAL_OUTPUT_OFF GPIO_PIN_RESET
#define ADDR_LCD 0x27
#define DELAY_MEF_LCD 10

/*Estados definidos para los estados de la pantalla*/
typedef enum {
	IDDLE_LCD, MOSTRAR_XYZ_LCD,

} LCDState_t;

static LCDState_t estadoActual_LCD;

//variable para verificar el estado del boton//
static bool selector = false;

/*Inicilizacion de la MEF para el LCD:
 * @entradas: ninguna
 * 1. Se inicializan los periféricos necesarios para su ejecucion.
 * 2. Se define el estado inicial.
 * @retorno: ninguno
 * */
void LCDMEF_Init() {
	SPI_Init();
	adxl_init();
	I2C_Init();

	LCD_Init(ADDR_LCD);
	debounceFSM_Init();

	estadoActual_LCD = IDDLE_LCD;
}

/*Máquina de estados para lo mostrado en el LCD:
 * @entradas: ninguna
 * 1. Se revisa el estado del botón con ayuda de la funcion readKeyDes,
 * indicando si el boton ha sido presionado y cambia el valor de la variable selector,
 * la cual es utilizada para cambiar de estados en la MEF del LCD.
 * 2. El estado del estadoActual del LCD cambia en base al estado en que se encuentra y el valor de
 * la variable selector.
 * @retorno: ninguno
 * */
void LCDMEF_Update() {
	debounceFSM_Update();

	if (readKeyDesc()) {
		selector = !selector;
	}

	switch (estadoActual_LCD) {
	case IDDLE_LCD:
		TxtIddle();
		if (selector) {
			HAL_GPIO_WritePin(LED_GPIO_LECTURAXYZ, LED_PIN_LECTURAXYZ,
			DIGITAL_OUTPUT_ON);
			LCD_limpiar(ADDR_LCD);
			estadoActual_LCD = MOSTRAR_XYZ_LCD;

		}
		break;
	case MOSTRAR_XYZ_LCD:
		MostrarXYZ();
		if (!selector) {
			HAL_GPIO_WritePin(LED_GPIO_LECTURAXYZ, LED_PIN_LECTURAXYZ,
			DIGITAL_OUTPUT_OFF);
			LCD_limpiar(ADDR_LCD);
			estadoActual_LCD = IDDLE_LCD;

		}

		break;

	default:
		estadoActual_LCD = IDDLE_LCD;

	}

}

/*Texto a mostrar en el LCD_Iddle:
 * @entradas: ninguna
 * 1. Se muestra un texto para el estado Iddle del LCD
 * @retorno: ninguno
 * */
void TxtIddle(void) {
	char LCD_iddle_txt1[] = "Presiona el push";
	char LCD_iddle_txt2[] = " para iniciar";

	LCD_Pos(LINE_SUP, COL_0, ADDR_LCD);
	LCD_string(LCD_iddle_txt1, ADDR_LCD);
	LCD_Pos(LINE_INF, COL_0, ADDR_LCD);
	LCD_string(LCD_iddle_txt2, ADDR_LCD);
}

/*Texto a mostrar en el LCD_Mostrar XYZ:
 * @entradas: ninguna
 * 1. Se escriben en el LCD los valores leídos por el ADXL345, pasando los valores flotantes
 * leídos a char con ayuda de la funcion "sprintf"
 * @retorno: ninguno
 * */
void MostrarXYZ(void) {
	HAL_Delay(100);

	float *accFloat = adxl_ObtenerAcc();

	char xg_char[6];
	sprintf(xg_char, "%.2f", *accFloat);

	char yg_char[6];
	sprintf(yg_char, "%.2f", *(accFloat + 1));

	char zg_char[6];
	sprintf(zg_char, "%.2f", *(accFloat + 2));

	LCD_Pos(LINE_SUP, COL_0, ADDR_LCD);
	LCD_string("x:", ADDR_LCD);
	LCD_Pos(LINE_SUP, COL_2, ADDR_LCD);
	LCD_string(xg_char, ADDR_LCD);

	LCD_Pos(LINE_SUP, COL_9, ADDR_LCD);
	LCD_string("y:", ADDR_LCD);
	LCD_Pos(LINE_SUP, COL_11, ADDR_LCD);
	LCD_string(yg_char, ADDR_LCD);

	LCD_Pos(LINE_INF, COL_0, ADDR_LCD);
	LCD_string("z:", ADDR_LCD);
	LCD_Pos(LINE_INF, COL_2, ADDR_LCD);
	LCD_string(zg_char, ADDR_LCD);
	mefLCD_Delay(DELAY_MEF_LCD);

}

/*Retardo para la MEF del LCD:
 * @entradas: delay_mefLCD (valor de retardo)
 * 1. Se auxilia con la funcion Delay de HAL
 * * @retorno: ninguno
 * */
void mefLCD_Delay(uint16_t delay_mefLCD) {
	HAL_Delay(delay_mefLCD);
}
