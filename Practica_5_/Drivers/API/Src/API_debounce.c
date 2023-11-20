/*
 * API_debounce.c
 *
 *  Created on: Nov 12, 2023
 *      Author: Verónica Ruíz Galván
 */

#include "API_debounce.h"

/*Se definen los diferentes estados para la FEM*/
typedef enum
{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
} debounceState_t;

/*Se crean las diferentes variables*/
static debounceState_t estadoActual;
static delay_t tiempoRetardo;
static bool_t keyButtonDesc;
static bool_t keyButtonAsc;

/*Se inicializa la FEM indicando el estado inicial e inicializando el delay*/
void debounceFSM_Init()
{
	delayInit(&tiempoRetardo, TIEMPO_RETARDO);
	estadoActual = BUTTON_UP;
}

/*Contiene la trancisicion de estados en base al gráfico de transicion de estados*/
void debounceFSM_Update()
{
	switch (estadoActual)
	{
	case BUTTON_UP: if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
						{
							estadoActual= BUTTON_FALLING;
							delayRead(&tiempoRetardo);
						}
	break;
	case BUTTON_FALLING: if (delayRead(&tiempoRetardo))
						{
							if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)){estadoActual =BUTTON_UP;}

							else
							{
								button_Pressed();
								estadoActual =BUTTON_DOWN;
							}
						}

	break;
	case BUTTON_DOWN: if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
							{
								estadoActual= BUTTON_RISING;
								delayRead(&tiempoRetardo);
							}
	break;
	case BUTTON_RISING: if (delayRead(&tiempoRetardo))
							{
								if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
								{
								estadoActual =BUTTON_DOWN;

								}
								else
								{
								button_Released();
								estadoActual =BUTTON_UP;
								}
							}

	break;
	default: estadoActual= BUTTON_UP;


	}

}


void button_Pressed()
{
	keyButtonDesc= true;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

}

void button_Released()
{
	keyButtonAsc= true;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

}

bool_t readKeyDesc()
{
	if(keyButtonDesc)
	{
		keyButtonDesc=false;
		return true;

	}
	return false;

}

bool_t readKeyAsc()
{
	if(keyButtonAsc)
	{
		keyButtonAsc=false;
		return true;

	}
	return false;

}



