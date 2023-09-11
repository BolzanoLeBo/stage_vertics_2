/*
 * recursion.c
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */


#include "recursion.h"

int recursion_result;
int recursion_input;


void recursion_init()
{
  int volatile temp_input = INPUT;
  recursion_input = temp_input;
}


int recursion_fib( int i )
{
  if ( i == 0 )
    return 1;
  if ( i == 1 )
    return 1;

  return recursion_fib( i - 1 ) + recursion_fib( i - 2 );
}

int recursion_return()
{
  return ( recursion_result  + ( -89 ) ) != 0;
}

void recursion_main( void )
{
  recursion_result = recursion_fib( recursion_input );
}

int main_rec( void )
{
  for (int i = 0; i < MAX_REP; i++)
  {
    recursion_init();
    recursion_main();
  }
  return ( recursion_return() );
}

void recursion_init_ccm( void )
{
  int volatile temp_input = INPUT;
  recursion_input = temp_input;
}


int recursion_fib_ccm( int i )
{
  if ( i == 0 )
    return 1;
  if ( i == 1 )
    return 1;

  return recursion_fib_ccm( i - 1 ) + recursion_fib_ccm( i - 2 );
}

int recursion_return_ccm()
{
  return ( recursion_result  + ( -89 ) ) != 0;
}

void recursion_main_ccm( void )
{
  recursion_result = recursion_fib_ccm( recursion_input );
}

int main_rec_ccm( void )
{
  for (int i = 0; i < MAX_REP; i++)
  {
    recursion_init_ccm();
    recursion_main_ccm();
  }
  return ( recursion_return_ccm() );
}


void recursion_init_ram( void )
{
  int volatile temp_input = INPUT;
  recursion_input = temp_input;
}


int recursion_fib_ram( int i )
{
  if ( i == 0 )
    return 1;
  if ( i == 1 )
    return 1;

  return recursion_fib_ram( i - 1 ) + recursion_fib_ram( i - 2 );
}

int recursion_return_ram()
{
  return ( recursion_result  + ( -89 ) ) != 0;
}

void recursion_main_ram( void )
{
  recursion_result = recursion_fib_ram( recursion_input );
}

int main_rec_ram( void )
{
  for (int i = 0; i < MAX_REP; i++)
  {
    recursion_init_ram();
    recursion_main_ram();
  }
  return ( recursion_return_ram() );
}




