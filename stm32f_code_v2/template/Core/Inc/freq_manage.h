/*
 * freq_manage.h
 *
 *  Created on: Aug 21, 2023
 *      Author: loict
 */

#ifndef SRC_FREQ_MANAGE_H_
#define SRC_FREQ_MANAGE_H_

#include "stm32f3xx_hal.h"

void change_freq(int f);
void Sleep(int time, RTC_HandleTypeDef* hrtc_addr);
void disable_pll();
void enable_hse();

#endif /* SRC_FREQ_MANAGE_H_ */
