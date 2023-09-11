/*
 * mat_mul.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_MAT_MUL_H_
#define INC_MAT_MUL_H_

#include <stdio.h>
#include <stdlib.h>
/*
  Macro definitions
*/

#define X 20 /* first dimension of array A */
#define Y 20 /* second dimension of array A, first dimension of array B */
#define Z 20 /* second dimension of array B */
#define MAX_REP 4
//#define INPUT_RAM2

/*
  Forward declaration of functions
*/

void matrix1_pin_down( int A[  ], int B[  ], int C[  ] );
void matrix1_init( void );
void matrix1_main( void );
int main_mat( void );


void matrix1_pin_down_ccm( int A[  ], int B[  ], int C[  ] )__attribute__((section(".ccmram")));
void matrix1_init_ccm( void )__attribute__((section(".ccmram")));
void matrix1_main_ccm( void )__attribute__((section(".ccmram")));
int main_mat_ccm( void )__attribute__((section(".ccmram")));

void matrix1_pin_down_ram( int A[  ], int B[  ], int C[  ] )__attribute__((section(".RamFunc")));
void matrix1_init_ram( void )__attribute__((section(".RamFunc")));
void matrix1_main_ram( void )__attribute__((section(".RamFunc")));
int main_mat_ram( void )__attribute__((section(".RamFunc")));

void matrix1_pin_down_ram2( int A[  ], int B[  ], int C[  ] )__attribute__((section(".ram2")));
void matrix1_init_ram2( void )__attribute__((section(".ram2")));
void matrix1_main_ram2( void )__attribute__((section(".ram2")));
int main_mat_ram2( void )__attribute__((section(".ram2")));
#endif

