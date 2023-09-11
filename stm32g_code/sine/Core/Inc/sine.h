/*
 * sine.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_SINE_H_
#define INC_SINE_H_

//#define FUNCTIONS_DATA_IN_FLASH
//#define FUNCTIONS_DATA_IN_CCM
//#define FUNCTIONS_DATA_IN_RAM
/*input data allocation*/
//#define INPUT_DATA_IN_CCM


__attribute__((section(".ccmram")))
void computeArraySin_ccm(float * arr_input, float * arr_keys , float * arr_values, int n_lut, int n_input);

void computeArraySin(float * arr_input, float * arr_keys , float * arr_values, int n_lut, int n_input);

void sine_main();

__attribute__((section(".ccmram")))
void sine_main_ccm();
#endif /* INC_SINE_H_ */
