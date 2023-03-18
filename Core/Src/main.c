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
#include "dac.h"
#include "eth.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "gensignal.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int genSigState=0;
uint8_t step_index=0;
int stepMutex=1;
int butt_Mutex=1;  //debounce che usa lo stesso TIM2 0.33s
uint8_t next_step=1;

uint8_t *p_step_index=0;
uint8_t *p_next_step=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
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
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_DAC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  TIM1->CCR1 = 0;
  if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK){
	  /* Starting Error */
	  Error_Handler();
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // gestione stato + LED
	  switch(genSigState){
		case GS_RESET:
			//printf("reset\r\n");
			//step_index=0;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);  //accendo rosso
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);  //accendo blu
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  //accendo verde

			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && butt_Mutex){
				genSigState=FASE1;
				step_index=0; // inizia la prossima fase dall'inizio
				next_step=1;
				butt_Mutex=0;
				printf("\n\n   ---- CASE 1 ----\r\n\n");

				continue;
			}
			break;

		case FASE1:
			//printf("case 1\r\n");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);  //accendo rosso
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);  //accendo blu
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  //accendo verde

			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && butt_Mutex){
				genSigState=FASE2;
				step_index=0;
				next_step=1;
				butt_Mutex=0;
				printf("\n\n   ---- CASE 2 ----\r\n\n");

				continue;
			}
			break;

		case FASE2:
			//printf("case 2\r\n");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);  //accendo rosso
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);  //accendo blu
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  //accendo verde

			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && butt_Mutex){
				genSigState=FASE3;
				step_index=0;
				next_step=1;
				butt_Mutex=0;
				printf("\n\n   ---- CASE 3 ----\r\n\n");

				continue;
			}
			break;

		case FASE3:
			//printf("case 3\r\n");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);  //accendo rosso
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);  //accendo blu
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  //accendo verde

			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && butt_Mutex){
				genSigState=FASE4;
				step_index=0;
				next_step=1;
				butt_Mutex=0;
				printf("\n\n   ---- CASE 4 ----\r\n\n");

				continue;
			}
			break;

		case FASE4:
			//printf("case 4\r\n");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);  //accendo rosso
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);  //accendo blu
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  //accendo verde

			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && butt_Mutex){
				genSigState=FASE5;
				step_index=0;
				next_step=1;
				butt_Mutex=0;
				printf("\n\n   ---- CASE 5 ----\r\n\n");

				continue;
			}
			break;

		case FASE5:
			//printf("case 5\r\n");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);  //accendo rosso
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);  //accendo blu
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  //accendo verde

			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && butt_Mutex){
				genSigState=0; //mi porta allo stato RESET
				step_index=0;
				next_step=1;
				butt_Mutex=0;
				printf("\n\n   ---- RESET ----\r\n\n");

				continue;
			}
			break;

		default:
			genSigState=GS_RESET;
			step_index=0;

			printf("---DEFAULT\r\n");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);  //accendo rosso
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);  //accendo blu
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  //accendo verde
			break;
	  }


	  p_step_index=&step_index;
	  p_next_step=&next_step;

	  // se mutex è ok, avvia prossimo step della fase
	  if(stepMutex==PLAY){
		  PlayStep(genSigState, p_step_index, p_next_step);
		  stepMutex=WAIT;
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 6;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

// Interrupt di TIM2 (0.33s)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2)
	{
		printf("TICK - next_step=%d\r\n", next_step);

		next_step--;
		if(next_step==0 && stepMutex==WAIT){
			stepMutex=PLAY;
			//printf("stepMutex=PLAY\r\n");
		}
		if(butt_Mutex==0){
			butt_Mutex=1;
		}
	}
}

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
