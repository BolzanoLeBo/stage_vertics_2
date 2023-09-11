/*
 * freq_manage.c
 *
 *  Created on: Aug 21, 2023
 *      Author: loict
 */

#include "freq_manage.h"
static int pll_on = 1;
static int current_frequency = 0;
void Error(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

void enable_hse()
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
  {
    ;
  }

}

void disable_pll()
{
  pll_on = 0;
  enable_hse();
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  /* -1- Select HSE as system clock source to allow modification of the PLL configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }

}




void Sleep(int time, RTC_HandleTypeDef* hrtc_addr)
{
  current_frequency = HAL_RCC_GetHCLKFreq()/1000000;
  uint32_t counter = (uint32_t) ((float) time*2.5);/*divide by (16/40)*/
  HAL_SuspendTick();

  HAL_RTCEx_SetWakeUpTimer_IT(hrtc_addr , counter, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
  /* Enter sleep or stop mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  //HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
  /* Wake up*/
  HAL_RTCEx_DeactivateWakeUpTimer(hrtc_addr);
  HAL_ResumeTick();
  //When wake up from STOP Sysclk source is HSI

  if (pll_on)
    {
      change_freq(current_frequency);
    }
  else
    {
      disable_pll();
    }
  /*int r = __HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK;
  int f = HAL_RCC_GetSysClockFreq();*/
}

void change_freq(int f)
{

  int tab_mul[8] = {RCC_PLL_MUL2, RCC_PLL_MUL3, RCC_PLL_MUL4, RCC_PLL_MUL5,
                 RCC_PLL_MUL6, RCC_PLL_MUL7, RCC_PLL_MUL8, RCC_PLL_MUL9};
  pll_on = 1;
  current_frequency = f;
  int latency, mul;
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* -1- Select HSE as system clock source to allow modification of the PLL configuration */
  enable_hse();
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }
  if (f <= 24)
  {
    latency = FLASH_LATENCY_0;
  }
  else if (f > 24 && f<= 48)
  {
    latency = FLASH_LATENCY_1;
  }
  else if (f <= 72 && f > 48)
  {
    latency = FLASH_LATENCY_2;
  }
  else
  {
    Error();
  }
  mul = tab_mul[(f/8)-2];

  /* -2- Enable HSE  Oscillator, select it as PLL source and finally activate the PLL */
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState        = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLMUL      = mul;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }

  /* -3- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType       = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider  = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider  = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, latency) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }
}




