/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#include "main.h"
#include "KEYPAD.h"
#include "KEYPAD_cfg.h"

uint8_t gu8_KeyStatesArr[KEYS] = {0};
uint8_t SysTicks = 0;

#define KEY_1       0
#define KEY_2       1
#define KEY_3       2
#define KEY_4       3
#define KEY_5       4
#define KEY_6       5
#define KEY_7       6
#define KEY_8       7
#define KEY_9       8

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void SysTick_CallBack(void);

char sifra[3]={0};
char pass[3]={1,2,3};//PIN
char tacno=0;
int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  KEYPAD_Init(0, gu8_KeyStatesArr);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
  char state=0;


  while (1)
  {

	  //Normalno/pocetno stanje, zakljucano
	  if(state==0){
	          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); //Relej senzor
	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET); // Zuta dioda
	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET); //crvena d
	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); //zelena d
	          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); /// Relej vrata
	  }
	  //Otkljucano
	  if(state==1){
	  	          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); // Relej senzor
	  	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); // zuta d
	  	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET); // crvena d
	  	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);  //  zelena d
	  	          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); // relej vrata
	  	  }
	  //singal senzor
	  if(!(GPIOB->IDR & 0x0002)){
		  state=2; //senzor
	  }
	  //Alarm
	  if(state==2){
	  	          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); // Relej senzor
	  	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET); //zuta d
	  	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET); //crvena d
	  	          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); //zelena d

	  	  }
	  //taster reset
	  if(GPIOC->IDR & 0x0800){
	  		  state=0;
	  	  }

	  //otvaranje taster/ukucavanje PIN-a
	  if(GPIOB->IDR & 0x0001){
		  char brojac=0; //sifra

		  while(1){

			    if(gu8_KeyStatesArr[KEY_1] == KEY_PRESSED)
			    {
			    sifra[brojac]=1;
			    brojac++;
			    while(gu8_KeyStatesArr[KEY_1] == KEY_PRESSED);
			    }
			    if(gu8_KeyStatesArr[KEY_2] == KEY_PRESSED)
			    {
			    	sifra[brojac]=2;
			    	brojac++;
			    while(gu8_KeyStatesArr[KEY_2] == KEY_PRESSED);
			    }
			    if(gu8_KeyStatesArr[KEY_3] == KEY_PRESSED)
			    {
			    	sifra[brojac]=3;
			    				    	brojac++;
			    while(gu8_KeyStatesArr[KEY_3] == KEY_PRESSED);
			    }
			    if(gu8_KeyStatesArr[KEY_4] == KEY_PRESSED)
			    {
			    	sifra[brojac]=4;
			    				    	brojac++;
			    while(gu8_KeyStatesArr[KEY_4] == KEY_PRESSED);
			    }
			    if(gu8_KeyStatesArr[KEY_5] == KEY_PRESSED)
			    {
			    	sifra[brojac]=5;
			    				    	brojac++;
			    while(gu8_KeyStatesArr[KEY_5] == KEY_PRESSED);
			    }
			    if(gu8_KeyStatesArr[KEY_6] == KEY_PRESSED)
			    {
			    	sifra[brojac]=6;
			    				    	brojac++;
			    while(gu8_KeyStatesArr[KEY_6] == KEY_PRESSED);
			    }
			    if(gu8_KeyStatesArr[KEY_7] == KEY_PRESSED)
			    {
			    	sifra[brojac]=7;
			    				    	brojac++;
			    while(gu8_KeyStatesArr[KEY_7] == KEY_PRESSED);
			    }
			    if(gu8_KeyStatesArr[KEY_8] == KEY_PRESSED)
			    {
			    	sifra[brojac]=8;
			    				    	brojac++;
			    while(gu8_KeyStatesArr[KEY_8] == KEY_PRESSED);
			    }
			    if(gu8_KeyStatesArr[KEY_9] == KEY_PRESSED)
			    {
			    	sifra[brojac]=9;
			    				    	brojac++;
			    while(gu8_KeyStatesArr[KEY_9] == KEY_PRESSED);
			    }

			    if (brojac==3){ //Posle unosa 3 cifre prekida unos
			    	break;
			    }
		  }

		  for(int i=0; i<3; i++){ //provera PIN-a
			  if(sifra[i]!=pass[i]){
				  tacno=0;
				  break;
			  } else
				  tacno = 1;
		  }
		  //Promena stanja ako je PIN dobar
		  if(tacno==1){
			  state=1;
			  tacno=0;
		  }



	  }

  }

}

void SysTick_CallBack(void)
  {
      SysTicks++;
      if(SysTicks == 5) // Each 5msec
      {
      KEYPAD_Scan(0);
      SysTicks = 0;
      }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
