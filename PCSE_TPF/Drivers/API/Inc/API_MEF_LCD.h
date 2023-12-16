/*
 * API_MEF_LCD.h
 *
 *      Author: eunchan
 */

#ifndef API_INC_API_MEF_LCD_H_
#define API_INC_API_MEF_LCD_H_

#ifndef __STDINT_H_
#include <stdint.h>
#endif

#ifndef __STDBOOL_H_
#include <stdbool.h>
#endif

#include "stm32f4xx_hal.h"
#include "API_delay.h"
#include "API_debounce.h"
#include "API_ADXL345.h"
#include "API_LCD.h"
#include "API_I2C.h"
#include "stdio.h"

/*Configuracion de LED activo mientras se está en el estado de Lectura de XYZ*/
#define LED_GPIO_LECTURAXYZ GPIOA
#define LED_PIN_LECTURAXYZ GPIO_PIN_2

/*Prototipos de funciones decesarias para la MEF del LCD*/
void LCDMEF_Init(void);
void LCDMEF_Update(void);
void TxtIddle(void);
void MostrarXYZ(void);
void mefLCD_Delay(uint16_t delay_mefLCD);

#endif /* API_INC_API_MEF_LCD_H_ */
