/*
 * FFT.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_FFT_H_
#define INC_FFT_H_

#define NUMBER_OF_BITS 13    /* fract format 1.NUMBER_OF_BITS = 1.13 */

#define BITS_PER_TWID 13     /* bits per twiddle coefficient */
#define SHIFT BITS_PER_TWID  /* fractional shift after each multiplication */
#define N_FFT 256
//#define INPUT_DATA_ON_CCM
//#define DATA_ON_CCM

__attribute__((section(".ccmram")))
void fft_bit_reduct_ccm( register int *int_pointer );

__attribute__((section(".ccmram")))
float fft_exp2f_ccm( float x );

__attribute__((section(".ccmram")))
float fft_modff_ccm( float x, float *intpart );

__attribute__((section(".ccmram")))
int fft_convert_ccm( float value );

__attribute__((section(".ccmram")))
void fft_float2fract_ccm( void );

__attribute__((section(".ccmram")))
void fft_pin_down_ccm( int input_data[  ] );

__attribute__((section(".ccmram")))
void fft_init_ccm( void );

__attribute__((section(".ccmram")))
void fft_main_ccm( void );

float fft_exp2f( float x );
float fft_modff( float x, float *intpart );
int fft_convert( float value );
void fft_float2fract( void );
void fft_pin_down( int input_data[  ] );
void fft_init( void );
void fft_main( void );

#endif /* INC_FFT_H_ */
