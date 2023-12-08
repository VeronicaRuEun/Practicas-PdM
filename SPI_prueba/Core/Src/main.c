/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
	IDDLE_EN_LCD,
	LECTURA_A_LCD
} debounceState_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define SPI1_PORT GPIOA
#define SPI1_PORT_MISO GPIOA
#define SPI1_PIN_MISO GPIO_PIN_6
#define SPI1_PORT_MOSI GPIOA
#define SPI1_PIN_MOSI GPIO_PIN_7
#define SPI1_PORT_SCLK GPIOA
#define SPI1_PIN_SCLK GPIO_PIN_5
#define SPI1_PORT_CS GPIOA
#define SPI1_PIN_CS GPIO_PIN_4

#define SPI1_PIN_CS_ON GPIO_PIN_SET
#define SPI1_PIN_CS_OFF GPIO_PIN_RESET

#define TIMEOUT 100

#define ADXL_DEVID 0x00
#define ADXL_THRESH_TAP 0x1D
#define ADXL_OFSX 0x1E
#define ADXL_OFSY 0x1F
#define ADXL_OFSZ 0x20
#define ADXL_DUR 0X21
#define ADXL_LATENT 0X22
#define ADXL_WINDOW 0X23
#define ADXL_THRESH_ACT 0x24
#define ADXL_THRESH_INACT 0x25
#define ADXL_TIME_INACT 0x26
#define ADXL_ACT_INACT_CTL 0X27
#define ADXL_THRESH_FF 0X28
#define ADXL_TIME_FF 0X29
#define ADXL_TAP_AXES 0X2A
#define ADXL_ACT_TAP_STATUS 0X2B
#define ADXL_BW_RATE 0X2C
#define ADXL_POWER_CTL 0X2D
#define ADXL_INT_ENABLE 0X2E
#define ADXL_INT_MAP 0X2F
#define ADXL_INT_SOURCE 0X30
#define ADXL_DATA_FORMAT 0X31
#define ADXL_DATAX0 0X32
#define ADXL_DATAX1 0X33
#define ADXL_DATAY0 0X34
#define ADXL_DATAY1 0X35
#define ADXL_DATAZ0 0X36
#define ADXL_DATAZ1 0X37
#define ADXL_FIFO_CTL 0X38
#define ADXL_FIFO_STATUS 0X39
/*Configuracion Reg ADXL_POWER_CTL Medicion y Frecuencia*/
#define P_CTL_MEAS_FREQ8 0x08
#define P_CTL_MEAS_FREQ4 0x09
#define P_CTL_MEAS_FREQ2 0x0A
#define P_CTL_MEAS_FREQ1 0x0B

/*Configuracion Reg ADXL_DATA_FORMAT Rango */
#define DATA_FORMAT2G 0x00
#define DATA_FORMAT4G 0x01
#define DATA_FORMAT8G 0x02
#define DATA_FORMAT16G 0x03

#define RESET_VALUE 0X00

#define ENABLE_MB_E 0x40
#define ENABLE_MB_L 0xC0
#define ENABLE_B_E 0x40
#define ENABLE_B_L 0xC0

#define NUM_BYTE_E 2
#define NUM_BYTE_L 1
#define NUM_BYTE_XYZ 6
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t byte_xyzLec[10];
int8_t x,y,z;
float xg, yg, zg;

 debounceState_t estadoActual;
//delay_t tiempoRetardo;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/*Funcion de escritu100 msra*/
void adxl345_Escritura (uint8_t address, uint8_t val)
{
	//uint8_t byte[NUM_BYTE_E];
	//byte[0] = address;
	//byte[1] = val;
	//SPI_CS_Bajo();
	HAL_GPIO_WritePin (SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_OFF);

	HAL_SPI_Transmit (&hspi1, (uint8_t*)&address, 1, TIMEOUT); //Funcion SPI
	//SPI_Transmit(byte,NUM_BYTE_E);
	HAL_SPI_Transmit (&hspi1, (uint8_t*)&val, 1, TIMEOUT); //Funcion SPI

	//SPI_CS_Alto();
	HAL_GPIO_WritePin (SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_ON);
}

void adxl345_Lectura (uint8_t address)
{
	address = address| 0x80;

	HAL_GPIO_WritePin (SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_OFF);

	HAL_SPI_Transmit (&hspi1, (uint8_t*)&address, 1, TIMEOUT);

	HAL_SPI_Receive(&hspi1, byte_xyzLec, 1, TIMEOUT);

	HAL_GPIO_WritePin (SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_ON);


}

void adxl345_init (void)
{

	adxl345_Escritura(ADXL_BW_RATE, 0X0E);  // formato de dato +-4g
	HAL_Delay(50);

	adxl345_Escritura(ADXL_DATA_FORMAT, 0x0A);  // formato de dato +-4g
	HAL_Delay(50);

	adxl345_Escritura (ADXL_POWER_CTL, P_CTL_MEAS_FREQ8);  // power_cntl Medicion y "Wake up" a 8hz
	HAL_Delay(50);


}


void debounceFSM_Init()
{
	//delayInit(&tiempoRetardo, TIEMPO_RETARDO);
	estadoActual = IDDLE_EN_LCD;
}

void debounceFSM_Update()
{
	switch (estadoActual)
	{
	case IDDLE_EN_LCD: 	//RUTINA PARA MOSTRAR A LCD
						if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
						{
							estadoActual= LECTURA_A_LCD;
							//delayRead(&tiempoRetardo);
						}
					   else
					   {
						   estadoActual= IDDLE_EN_LCD;
					   }
	break;

	case LECTURA_A_LCD: 	//RUTINA PARA MOSTRAR A LCD
							if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
							{
								estadoActual= LECTURA_A_LCD;
							}
							else
							{
								estadoActual= LECTURA_A_LCD;
							}


	break;
	default: estadoActual= IDDLE_EN_LCD;


	}

}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin (SPI1_PORT_CS, SPI1_PIN_CS, SPI1_PIN_CS_ON);




  adxl345_init();

  //adxl345_Lectura(ADXL_DEVID);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  //x = ((byte_xyzLec[1]<<8)|byte_xyzLec[0]);
	  //y = ((byte_xyzLec[3]<<8)|byte_xyzLec[2]);
	  //z = ((byte_xyzLec[5]<<8)|byte_xyzLec[4]);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
