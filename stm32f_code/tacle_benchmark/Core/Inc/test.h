/*
 * test.h
 *
 *  Created on: Jun 27, 2023
 *      Author: loict
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_
#include <stdio.h>
#include <stdlib.h>
/*
  Macro definitions
*/

#define X 20 /* first dimension of array A */
#define Y 20 /* second dimension of array A, first dimension of array B */
#define Z 20 /* second dimension of array B */


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
#endif
