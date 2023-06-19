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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ringbuffer.h"
#include "string.h"
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
 UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
 uint8_t rx1[1] = {'\0',};
 uint8_t tx1[1] = {'\0',};
 RingBuffer txBuf;
 uint8_t buffer[32];
 uint8_t l = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
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

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_UART_Receive_IT(&huart1, rx1, sizeof(rx1));
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	if(huart1.RxState == HAL_UART_STATE_READY)
	{
		HAL_UART_Receive_IT(&huart1, rx1, sizeof(rx1));
	}
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

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED01_Pin|LED02_Pin|LED03_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED01_Pin LED02_Pin LED03_Pin */
  GPIO_InitStruct.Pin = LED01_Pin|LED02_Pin|LED03_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		tx1[0] = '\0';

		if(RingBuffer_GetDataLength(&txBuf) > 0)
		{
			RingBuffer_Read(&txBuf, tx1, 1);
			HAL_UART_Transmit_IT(huart, tx1, 1);
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1) {
		tx1[0] = rx1[0];

		if(HAL_UART_Transmit_IT(&huart1, tx1, sizeof(tx1)) != HAL_OK) {
			if(RingBuffer_Write(&txBuf, tx1, sizeof(tx1)) != RING_BUFFER_OK) { }
		}

		if(rx1[0] != '\r' && l < 30) {
			buffer[l] = rx1[0];
			l++;
		}
		else {
			if(strncmp(buffer, "led01 on", sizeof("led01 on") -1) == 0) {
				HAL_GPIO_WritePin(LED01_GPIO_Port, LED01_Pin, GPIO_PIN_SET);
				if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)"led01 is ON\r\n", sizeof("led01 is ON\r\n")) != HAL_OK) {
					if(RingBuffer_Write(&txBuf, (uint8_t *)"led01 is ON\r\n", sizeof("led01 is ON\r\n")) != RING_BUFFER_OK) { }
				}
			}
			else if(strncmp(buffer, "led01 off", sizeof("led01 off") -1) == 0) {
				HAL_GPIO_WritePin(LED01_GPIO_Port, LED01_Pin, GPIO_PIN_RESET);
				if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)"led01 is OFF\r\n", sizeof("led01 is OFF\r\n")) != HAL_OK) {
					if(RingBuffer_Write(&txBuf, (uint8_t *)"led01 is OFF\r\n", sizeof("led01 is OFF\r\n")) != RING_BUFFER_OK) { }
				}
			}
			else if(strncmp(buffer, "led02 on", sizeof("led02 on") -1) == 0) {
				HAL_GPIO_WritePin(LED02_GPIO_Port, LED02_Pin, GPIO_PIN_SET);
				if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)"led02 is ON\r\n", sizeof("led02 is ON\r\n")) != HAL_OK) {
					if(RingBuffer_Write(&txBuf, (uint8_t *)"led02 is ON\r\n", sizeof("led02 is ON\r\n")) != RING_BUFFER_OK) { }
				}
			}
			else if(strncmp(buffer, "led02 off", sizeof("led02 off") -1) == 0) {
				HAL_GPIO_WritePin(LED02_GPIO_Port, LED02_Pin, GPIO_PIN_RESET);
				if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)"led02 is OFF\r\n", sizeof("led02 is OFF\r\n")) != HAL_OK) {
					if(RingBuffer_Write(&txBuf, (uint8_t *)"led02 is OFF\r\n", sizeof("led02 is OFF\r\n")) != RING_BUFFER_OK) { }
				}
			}
			else if(strncmp(buffer, "led03 on", sizeof("led03 on") -1) == 0) {
				HAL_GPIO_WritePin(LED03_GPIO_Port, LED03_Pin, GPIO_PIN_SET);
				if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)"led03 is ON\r\n", sizeof("led03 is ON\r\n")) != HAL_OK) {
					if(RingBuffer_Write(&txBuf, (uint8_t *)"led03 is ON\r\n", sizeof("led03 is ON\r\n")) != RING_BUFFER_OK) { }
				}
			}
			else if(strncmp(buffer, "led03 off", sizeof("led03 off") -1) == 0) {
				HAL_GPIO_WritePin(LED03_GPIO_Port, LED03_Pin, GPIO_PIN_RESET);
				if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)"led03 is OFF\r\n", sizeof("led03 is OFF\r\n")) != HAL_OK) {
					if(RingBuffer_Write(&txBuf, (uint8_t *)"led03 is OFF\r\n", sizeof("led03 is OFF\r\n")) != RING_BUFFER_OK) { }
				}
			}
			memset(buffer, 0, sizeof(buffer));
			l = 0;
			HAL_UART_Transmit_IT(&huart1, "\n\r", sizeof("\n\r"));
		}
		HAL_UART_Receive_IT(&huart1, rx1, sizeof(rx1));
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
