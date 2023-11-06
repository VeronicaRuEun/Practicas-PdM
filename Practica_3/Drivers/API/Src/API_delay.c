/*
 * API_delay.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Veronica Ruiz
 */

#include "API_delay.h"

/*constantes para control de parámetros para el tiempo (ms) de delay definidos por el
programador c:*/

#define DELAY_MAX 1000
#define DELAY_MIN 50

/*funcion privada: revisa que el rango de "duration" sea válido
retornando un valor valido*/

static tick_t checkDuration (tick_t duration)
{
	if(DELAY_MAX < duration) {return DELAY_MAX;}
	else if(DELAY_MIN > duration) {return DELAY_MIN;}
	else {duration;}
}

/*Implementacion de funciones publicas*/

void delayInit( delay_t * delay, tick_t duration )
{
	/*asigna en delay.duracion la duracion definida despues de revisar el rango
	con la funcion checkDuration*/

	delay->duration = checkDuration(duration);

	delay->running = false; // asigna en delay.running "falso"
}

//Funcion de delayRead con retorno de dato tipo bool_t (bool)
bool_t delayRead( delay_t * delay )
{

	/*verifica el estado de delay.running
	si delay.running es falso, empieza conteo y cambia su estado a verdadero*/
	if(delay->running == false)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;

	}
	/*si delay.running es verdadero, revisa si se ha alcanzado el periodo designado
	si se alcanzó, retorna "verdadero", y delay.running cambia a "falso";
	en caso contrario, retorna "falso"*/
	else
	{
		if((HAL_GetTick()-delay->startTime) >= delay->duration)
		{
			delay->running = false;
			return true;
		}


	}

	return false;
}

//Funcion de delayWrite sin retorno
void delayWrite( delay_t * delay, tick_t duration)
{
	/*Asigna un valor de duracion existente despues de revisar el rango
	con la funcion checkDuration*/
	delay->duration = checkDuration(duration);

}

