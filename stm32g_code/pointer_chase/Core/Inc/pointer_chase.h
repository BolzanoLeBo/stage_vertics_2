/*
 * pointer_cahse.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_POINTER_CHASE_H_
#define INC_POINTER_CHASE_H_


#include "stm32g4xx_hal.h"


#define POINTER_SIZE_1000

//#define RORAM
//#define ROCCM
#define ROFLASH

void pointer_chase_flash(void ** p0);

void pointer_chase_ccm(void ** p0) __attribute__((section(".ccmram"))) ;

void pointer_main();

__attribute__((section(".ccmram")))
void pointer_main_ccm();

#endif /* INC_POINTER_CHASE_H_ */
