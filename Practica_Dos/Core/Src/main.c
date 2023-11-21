
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define cicTr 2 //cte. para dividir el ciclo de trabajo
#define noSec 3 //número de secuencias
#define noCicTr 5 //número de veces a parpadear
#define valInCont 0 //cte. para inicializar contador
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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

  SystemClock_Config();
  MX_GPIO_Init();

/* USER CODE BEGIN 2 */
    delay_t  delay; //crea tipo de dato delay_t llamado delay
    delay_t * punt_Delay = NULL; //puntero tipo delay_t inicializado
    punt_Delay = &delay; //puntero almacena la direccion de la variable delay
  	tick_t duration = 1000; //se designa una duracion de 1000 ms
  	bool_t retDelRead; // variable tipo bool_t para guardar el retorno de delayRead
  	delayInit(punt_Delay,duration); //asignacion de datos para la funcion delayInit
  	//contador para la secuencia del led
  	uint8_t contador = valInCont;
  	//vector que define las diferencies duraciones del periodo para secuencia
  	uint32_t v_Duracion [noSec]={1000,200,100};
/* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //Casos para el Punto 3 de la practica
	  if(contador<noCicTr*cicTr){delayWrite(punt_Delay,v_Duracion[0]/cicTr);}
	  if(contador>=noCicTr*cicTr && contador< 2*noCicTr*cicTr){delayWrite(punt_Delay, v_Duracion[1]/cicTr);}
	  if(contador>=2*noCicTr*cicTr && contador< 3*noCicTr*cicTr){delayWrite(punt_Delay,v_Duracion[2]/cicTr);}
	  if(contador>=3*noCicTr*cicTr){contador=valInCont;}

	  //Leer valor arrojado de la función delayRead y asignar a variable
	  retDelRead = delayRead(punt_Delay);
    /* USER CODE END WHILE */

	  //Si se alcanza la duracion, se niega el estado del led con Toggle
	  if(retDelRead)
	  {
	  //GPIOC 13 es la salida del Led de la placa F401RCT6
	  HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);

	  //Contador para casos del Punto 3 de la práctica
	  contador++;
	  }








    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

//Funcion de delayInit sin retorno
void delayInit( delay_t * delay, tick_t duration )
{
	delay->duration= duration; //asigna en delay.duracion la duracion definida en la funcion
	delay->running = false; // asigna en delay.running "falso"
}

//Funcion de delayRead con retorno de dato tipo bool_t (bool)
bool_t delayRead( delay_t * delay )
{

	//verifica el estado de delay.running
	//si delay.running es falso, empieza conteo y cambia su estado a verdadero
	if(delay->running == false)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;

	}
	//si delay.running es verdadero, revisa si se ha alcanzado el periodo designado
	//si se alcanzó, retorna "verdadero", y delay.running cambia a "falso";
	//en caso contrario, retorna "falso"
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
	//Asigna un valor de duracion existente a delay.duration
	delay->duration= duration;
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
