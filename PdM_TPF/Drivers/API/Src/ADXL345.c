/*
 * ADXL345.c
 *
 *      Author: eunchan
 */

#include "ADXL345.h"

uint8_t data_rec[6]; //vector para almacenar X0,X1,Y0,Y1,Z0 y Z1
int16_t x, y, z; //almacenan los valores MSB y LSB de cada eje
float xg, yg, zg; //almacena valores con conversion medibles
float accComp[3]; //almacena valores de aceleracion convertidos

/*Configuracion para cantidad de bytes de Lectura/Escritura*/
#define NUM_BYTE_WRITE 1
#define NUM_BYTES_WRITE 2
#define NUM_BYTES_READ 6

/*Configuracion para Inicializacion de ADXL345*/
#define RESET_VALUE 0X00
#define ADXL345_RATE 0x0A
#define ADXL345_FULLRES 0x0B
#define ADXL345_MODE_MEASURE 0x08

/*Configuracion para Multibyte en Escritura (E) y Lectura (L)*/
#define ENABLE_MB_E 0x40
#define ENABLE_MB_L 0xC0

/*Configuracion para orden de lecturas de aceleraciones XYZ*/
#define ADXL_LSB_X0 0
#define ADXL_LSB_X1 1
#define ADXL_LSB_Y0 2
#define ADXL_LSB_Y1 3
#define ADXL_LSB_Z0 4
#define ADXL_LSB_Z1 5
#define SIZE_BYTE 8

/*Configuracion para calibracion:
 * Estos valores de offset son específicos para el sensor utilizado y la
 * resolucion de rango de 16g es aproximadamente 0.0035~0.0039 g/LSB
 * */
#define CONST_16G 0.0035
#define X_OFFSET 166
#define Y_OFFSET 76
#define Z_OFFSET 1436
#define BASE_OFF 256

/*Escritura en una addres de ADXL345:
 * @entradas: address (la direccion deseada a leer o comando)
 * @entradas: valor (lo que se quiere escribir en ese registro/address)
 * 1. Se activa el bit MB (multibyte) para avisar al ADXL345 que recibirá mas de un byte
 * (direccion y lo que se quiere escribir) y R/W =0 para escritura
 * (esto ya está en el macro ENABLE_MB_E que hace referencia a MB= multibyte y E=escritura)
 * 2. Se realiza la transmision SPI
 * @retorno: ninguno
 * */
void adxl_write(uint8_t address, uint8_t value) {
	uint8_t data[2];
	data[0] = address | ENABLE_MB_E; // Multibyte activo y modo escritura activo
	data[1] = value;

	SPI_Transmit((uint8_t*) &data, NUM_BYTES_WRITE);

}

/*Lectura en una addres de ADXL345:
 * @entradas: address (la direccion deseada a leer o comando)
 * 1. Se activa el bit MB (multibyte) para avisar al ADXL345 que enviará mas de un byte
 * (datos de la direccion) y el bit R/W =1 para lectura
 * (esto ya está en el macro ENABLE_MB_L que hace referencia a MB= multibyte y L=lectura)
 * 2. Se realiza la transmision y recepcion SPI
 * @retorno: ninguno
 * */
void adxl_read(uint8_t address) {
	address |= ENABLE_MB_L; //Multibyte activo y Lectura activo

	SPI_TransmitReceive(address, (uint8_t*) &data_rec, NUM_BYTES_READ);
}

/*Inicializa el módulo ADXL345:
 * @entradas: ninguna
 * 1. Se configura la tasa de bits deseados
 * 2. Se configura el control de formato (se selecciona el rango g =16g (ADXL345_FULLRES) ya que Z sólo arrojaba lecturas en
 * este rango)
 * 3. Se hace un reseteo en los bits del modo de funcionamiento
 * 4. Se configura el modo de funcionamiento
 * @retorno: ninguno
 * */
void adxl_init(void) {
	adxl_write(ADXL_BW_RATE, ADXL345_RATE);  // configuracion de la tasa de bits
	adxl_write(ADXL_DATA_FORMAT, ADXL345_FULLRES); // cofiguracion del formato a full resolution para que z obtenga lecturas
	adxl_write(ADXL_POWER_CTL, RESET_VALUE);  // resetea los Bits
	adxl_write(ADXL_POWER_CTL, ADXL345_MODE_MEASURE); // power_cntl modo medicion
}

/*Obtiene las aceleraciones XYZ del ADXL345:
 * @entradas: ninguna
 * 1. Se hace una lectura en la address correspondiente a X0
 * 2. Se suman los valores MSB+LSB de cada eje (x,y,z)
 * 3. En un vector de aceleraciones, se almacenan los valores convertidos
 * a unidades SI,(m/s²), con su respectiva calibracion
 * @retorno: accComp (vector de aceleraciones x,y,z)
 * */

float* adxl_ObtenerAcc(void) {
	adxl_read(ADXL_DATAX0);

	x = ((data_rec[ADXL_LSB_X1] << SIZE_BYTE) | data_rec[ADXL_LSB_X0]);
	y = ((data_rec[ADXL_LSB_Y1] << SIZE_BYTE) | data_rec[ADXL_LSB_Y0]);
	z = ((data_rec[ADXL_LSB_Z1] << SIZE_BYTE) | data_rec[ADXL_LSB_Z0]);

	accComp[0] = (x + X_OFFSET) * CONST_16G;
	accComp[1] = (y - Y_OFFSET) * CONST_16G;
	accComp[2] = (z - Z_OFFSET + BASE_OFF) * CONST_16G;

	return accComp;
}
