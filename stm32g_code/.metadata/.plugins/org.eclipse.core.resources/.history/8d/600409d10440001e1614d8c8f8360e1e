/*
 * freq_manage.c
 *
 *  Created on: Aug 21, 2023
 *      Author: loict
 */

#include "freq_manage.h"
int current_frequency;
int pll_on = 1;

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

void Sleep(int time, RTC_HandleTypeDef* hrtc_addr)
{
  uint32_t counter = (uint32_t) ((float) time*2);/*divide by (16/32)*/

  HAL_SuspendTick();

  HAL_RTCEx_SetWakeUpTimer_IT(hrtc_addr, counter, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
  /* Enter sleep or stop mode */
  //HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  HAL_PWREx_EnterSTOP1Mode(PWR_STOPENTRY_WFI);
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
}
void change_freq(int f)
{
  pll_on = 1;
  int latency = FLASH_LATENCY_4;
  int latency_tab[5] = {FLASH_LATENCY_0,FLASH_LATENCY_1,FLASH_LATENCY_2,FLASH_LATENCY_3,FLASH_LATENCY_4};
  int freq_scale_boost[5] = {34,68,102,136,85};
  int freq_scale_normal[5] = {30,60,90,120,150};
  int freq_scale_low[5] = {12,24,26,26,26};
  //if we are in boost mode there is not the same wait states
  int* selector;
  if (READ_BIT(PWR->CR1, PWR_CR1_VOS) == PWR_REGULATOR_VOLTAGE_SCALE2)
  {
    if (f <= 26)
    {
      selector = freq_scale_low;
    }
    else
    {
      Error();
    }
  }

  else if (READ_BIT(PWR->CR5, PWR_CR5_R1MODE))
  {
    selector = freq_scale_normal;
  }
  else
  {
    selector = freq_scale_boost;
  }

  int mul = f/2;

  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  for (int i = 4; i >= 0; i--)
  {
    if (mul <= selector[i])
    {
      latency = latency_tab[i];
    }
  }

  /* -1- Select HSI as system clock source to allow modification of the PLL configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, latency) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }
  /* -2- Enable HSI  Oscillator, select it as PLL source and finally activate the PLL */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  if (f <= 42)
  {
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV8;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  }
  else
  {
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  }
  RCC_OscInitStruct.PLL.PLLN = mul;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }

  /* -3- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, latency) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }
  current_frequency = f;
}

void range1_to_range2()
{
  if (READ_BIT(PWR->CR1, PWR_CR1_VOS) != PWR_REGULATOR_VOLTAGE_SCALE2)
  {
    //Reduce the system frequency to a value lower than 26 MHz
    change_freq(26);
    //the system clock must be divided by 2 using the AHB prescaler
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    HAL_RCC_GetClockConfig(&RCC_ClkInitStruct,FLASH_LATENCY_0 );
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
      /* Initialization Error */
      Error();
    }
    //Program the VOS bits to “10�? in the PWR_CR1 register
    MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_REGULATOR_VOLTAGE_SCALE2);
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    //Adjust number of wait states according new frequency target in Range 2
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
      /* Initialization Error */
      Error();
    }
  }
}

void range2_to_range1()
{
  if (READ_BIT(PWR->CR1, PWR_CR1_VOS) == PWR_REGULATOR_VOLTAGE_SCALE2)
  {
    //Program the VOS bits to “01�? in the PWR_CR1 register
    MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_REGULATOR_VOLTAGE_SCALE1);
    //Wait until the VOSF flag is cleared in the PWR_SR2 register
    while (READ_BIT(PWR->SR2, PWR_SR2_VOSF))
    {
      ;
    }
    //Adjust number of wait states according new frequency target in Range 1
    SET_BIT(PWR->CR5, PWR_CR5_R1MODE);
    change_freq(current_frequency);
  }
}

void boost_mode()
{
  if (READ_BIT(PWR->CR1, PWR_CR1_VOS) == PWR_REGULATOR_VOLTAGE_SCALE1)
  {
    CLEAR_BIT(PWR->CR5, PWR_CR5_R1MODE);
  }
}

void disable_pll()
{
  pll_on = 0;
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  /* -1- Select HSI as system clock source to allow modification of the PLL configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error();
  }

}





