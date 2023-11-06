/*
 * API_delay.h
 *
 *  Created on: Nov 5, 2023
 *      Author: Veronica Ruiz
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_
#endif /* API_INC_API_DELAY_H_ */

#ifndef __STDINT_H_
#include <stdint.h>
#endif

#ifndef __STDBOOL_H_
#include <stdbool.h>
#endif

#include "stm32f4xx_hal.h"

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/*Prototipo de funciones*/

void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

