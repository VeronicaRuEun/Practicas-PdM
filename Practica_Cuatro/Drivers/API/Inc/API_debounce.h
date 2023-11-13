/*
 * API_debounce.h
 *
 *  Created on: Nov 12, 2023
 *      Author: eunchan
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_
#endif /* API_INC_API_DEBOUNCE_H_ */


#ifndef __STDINT_H_
#include <stdint.h>
#endif

#ifndef __STDBOOL_H_
#include <stdbool.h>
#endif

#include "stm32f4xx_hal.h"
#include "API_delay.h"

#define TIEMPO_RETARDO 40 //tiempo de anti-rebote


/*Prototipo de funciones*/
void debounceFSM_Init(); // carga el estado inicial
void debounceFSM_Update(); //Lee las entradas, resuelve la lógica de transición de estados y actualiza las salidas

void button_Pressed(); //verifica cuando el boton fue presionado
void button_Released(); //verifica que no ha sido presionado el boton
bool_t readKey(); //verifica cuando el boton es presionado

