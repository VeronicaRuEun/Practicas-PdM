/*
 * API_ADXL345_port.h
 *
 *      Author: eunchan
 */

#ifndef API_INC_API_ADXL345_PORT_H_
#define API_INC_API_ADXL345_PORT_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "string.h"

void adxl_enviarDatos(uint8_t DevAddress ,uint8_t *dato);
void adxl_obtenDatos(uint8_t DevAddress ,uint8_t *dato);

#endif /* API_INC_API_ADXL345_PORT_H_ */
