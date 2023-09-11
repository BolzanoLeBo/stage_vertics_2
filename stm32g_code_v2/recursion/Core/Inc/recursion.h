/*
 * recursion.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_RECURSION_H_
#define INC_RECURSION_H_

#define INPUT 25
#define MAX_REP 1


int recursion_fib( int i );
void recursion_main( void );
void recursion_init( void );
int recursion_return( void );
int main_rec ( void );

__attribute__((section(".ccmram")))
int recursion_fib_ccm( int i );
__attribute__((section(".ccmram")))
void recursion_main_ccm( void );
__attribute__((section(".ccmram")))
void recursion_init_ccm( void );
__attribute__((section(".ccmram")))
int recursion_return_ccm( void );
__attribute__((section(".ccmram")))
int main_rec_ccm( void );


__attribute__((section(".RamFunc")))
int recursion_fib_ram( int i );
__attribute__((section(".RamFunc")))
void recursion_main_ram( void );
__attribute__((section(".RamFunc")))
void recursion_init_ram( void );
__attribute__((section(".RamFunc")))
int recursion_return_ram( void );
__attribute__((section(".RamFunc")))
int main_rec_ram( void );

__attribute__((section(".ram2")))
int recursion_fib_ram2( int i );
__attribute__((section(".ram2")))
void recursion_main_ram2( void );
__attribute__((section(".ram2")))
void recursion_init_ram2( void );
__attribute__((section(".ram2")))
int recursion_return_ram2( void );
__attribute__((section(".ram2")))
int main_rec_ram2( void );

#endif /* INC_RECURSION_H_ */
