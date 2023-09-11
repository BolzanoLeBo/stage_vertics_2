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

#define RORAM
//#define ROCCM
//#define ROFLASH
//#define RORAM2

void pointer_chase_flash(void ** p0);

void pointer_chase_ccm(void ** p0) __attribute__((section(".ccmram"))) ;

void pointer_chase_ram(void ** p0) __attribute__((section(".RamFunc"))) ;

void pointer_chase_ram2(void ** p0) __attribute__((section(".ram2")));

void pointer_main();

__attribute__((section(".ccmram")))
void pointer_main_ccm();

__attribute__((section(".RamFunc")))
void pointer_main_ram();

__attribute__((section(".ram2")))
void pointer_main_ram2();

#endif /* INC_POINTER_CHASE_H_ */
