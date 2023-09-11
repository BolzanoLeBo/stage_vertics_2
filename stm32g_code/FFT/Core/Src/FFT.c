/*
 * FFT.C
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */
#include "fft.h"

#ifdef DATA_ON_CCM
__attribute__((section(".ccmramdata")))
#endif
int fft_input_data[ 2 * N_FFT ];

#ifdef DATA_ON_CCM
__attribute__((section(".ccmramdata")))
#endif
int fft_twidtable[ 510 ] = { 8192,  0,     8192,  0,     0,     -8192, 8192,  0,     5792,  -5792, 0,
  -8191, -5792, -5792, 8192,  0,     7568,  -3134, 5792,  -5792, 3134,  -7568,
  0,     -8192, -3134, -7568, -5792, -5792, -7568, -3134, 8192,  0,     8034,
  -1598, 7568,  -3134, 6811,  -4551, 5792,  -5792, 4551,  -6811, 3134,  -7568,
  1598,  -8034, 0,     -8192, -1598, -8034, -3134, -7568, -4551, -6811, -5792,
  -5792, -6811, -4551, -7568, -3134, -8034, -1598, 8192,  0,     8152,  -802,
  8034,  -1598, 7839,  -2378, 7568,  -3134, 7224,  -3861, 6811,  -4551, 6332,
  -5196, 5792,  -5792, 5196,  -6332, 4551,  -6811, 3861,  -7224, 3134,  -7568,
  2378,  -7839, 1598,  -8034, 802,   -8152, 0,     -8191, -802,  -8152, -1598,
  -8034, -2378, -7839, -3134, -7568, -3861, -7224, -4551, -6811, -5196, -6332,
  -5792, -5792, -6332, -5196, -6811, -4551, -7224, -3861, -7568, -3134, -7839,
  -2378, -8034, -1598, -8152, -802,  8192,  0,     8182,  -401,  8152,  -802,
  8103,  -1202, 8034,  -1598, 7946,  -1990, 7839,  -2378, 7713,  -2759, 7568,
  -3134, 7405,  -3502, 7224,  -3861, 7026,  -4211, 6811,  -4551, 6579,  -4879,
  6332,  -5196, 6069,  -5501, 5792,  -5792, 5501,  -6069, 5196,  -6332, 4879,
  -6579, 4551,  -6811, 4211,  -7026, 3861,  -7224, 3502,  -7405, 3134,  -7568,
  2759,  -7713, 2378,  -7839, 1990,  -7946, 1598,  -8034, 1202,  -8103, 802,
  -8152, 401,   -8182, 0,     -8192, -401,  -8182, -802,  -8152, -1202, -8103,
  -1598, -8034, -1990, -7946, -2378, -7839, -2759, -7713, -3134, -7568, -3502,
  -7405, -3861, -7224, -4211, -7026, -4551, -6811, -4879, -6579, -5196, -6332,
  -5501, -6069, -5792, -5792, -6069, -5501, -6332, -5196, -6579, -4879, -6811,
  -4551, -7026, -4211, -7224, -3861, -7405, -3502, -7568, -3134, -7713, -2759,
  -7839, -2378, -7946, -1990, -8034, -1598, -8103, -1202, -8152, -802,  -8182,
  -401,  8192,  0,     8189,  -201,  8182,  -401,  8169,  -602,  8152,  -802,
  8130,  -1002, 8103,  -1202, 8071,  -1400, 8034,  -1598, 7992,  -1794, 7946,
  -1990, 7895,  -2184, 7839,  -2378, 7778,  -2569, 7713,  -2759, 7643,  -2948,
  7568,  -3134, 7489,  -3319, 7405,  -3502, 7317,  -3683, 7224,  -3861, 7127,
  -4037, 7026,  -4211, 6921,  -4382, 6811,  -4551, 6697,  -4717, 6579,  -4879,
  6458,  -5039, 6332,  -5196, 6203,  -5350, 6069,  -5501, 5933,  -5648, 5792,
  -5792, 5648,  -5933, 5501,  -6069, 5350,  -6203, 5196,  -6332, 5039,  -6458,
  4879,  -6579, 4717,  -6697, 4551,  -6811, 4382,  -6921, 4211,  -7026, 4037,
  -7127, 3861,  -7224, 3683,  -7317, 3502,  -7405, 3319,  -7489, 3134,  -7568,
  2948,  -7643, 2759,  -7713, 2569,  -7778, 2378,  -7839, 2184,  -7895, 1990,
  -7946, 1794,  -7992, 1598,  -8034, 1400,  -8071, 1202,  -8103, 1002,  -8130,
  802,   -8152, 602,   -8169, 401,   -8182, 201,   -8189, 0,     -8192, -201,
  -8189, -401,  -8182, -602,  -8169, -802,  -8152, -1002, -8130, -1202, -8103,
  -1400, -8071, -1598, -8034, -1794, -7992, -1990, -7946, -2184, -7895, -2378,
  -7839, -2569, -7778, -2759, -7713, -2948, -7643, -3134, -7568, -3319, -7489,
  -3502, -7405, -3683, -7317, -3861, -7224, -4037, -7127, -4211, -7026, -4382,
  -6921, -4551, -6811, -4717, -6697, -4879, -6579, -5039, -6458, -5196, -6332,
  -5350, -6203, -5501, -6069, -5648, -5933, -5792, -5792, -5933, -5648, -6069,
  -5501, -6203, -5350, -6332, -5196, -6458, -5039, -6579, -4879, -6697, -4717,
  -6811, -4551, -6921, -4382, -7026, -4211, -7127, -4037, -7224, -3861, -7317,
  -3683, -7405, -3502, -7489, -3319, -7568, -3134, -7643, -2948, -7713, -2759,
  -7778, -2569, -7839, -2378, -7895, -2184, -7946, -1990, -7992, -1794, -8034,
  -1598, -8071, -1400, -8103, -1202, -8130, -1002, -8152, -802,  -8169, -602,
  -8182, -401,  -8189, -201 };


/* 1024 real values as input data in float format */
#ifdef INPUT_DATA_ON_CCM
__attribute__((section(".ccmramdata")))
#endif
float fft_input[ 256 ] = {
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f,
  0.243f,  0.323f, 0.505f, -0.176f, -0.87f, 0.353f,  -0.344f, -0.443f,
  -0.434f, -0.32f, 0.232f, -0.454f, -0.32f, -0.323f, -0.733f, 0.54f

};

#ifdef DATA_ON_CCM
__attribute__((section(".ccmramdata")))
#endif
int fft_inputfract[ N_FFT ];




__attribute__((section(".ccmram")))

void fft_bit_reduct_ccm( register int *int_pointer )
{
  register int i, j = 0  ;
  register int tmpr, max = 2, m, n = N_FFT << 1 ;

  /* do the bit reversal scramble of the input data */
  for ( i = 0; i < ( n - 1 ) ; i += 2 ) {
    if ( j > i ) {
      tmpr = *( int_pointer + j ) ;
      *( int_pointer + j ) = *( int_pointer + i ) ;
      *( int_pointer + i ) = tmpr ;

      tmpr = *( int_pointer + j + 1 ) ;
      *( int_pointer + j + 1 ) = *( int_pointer + i + 1 ) ;
      *( int_pointer + i + 1 ) = tmpr ;
    }

    m = N_FFT;

    while ( m >= 2 && j >= m ) {
      j -= m ;
      m >>= 1;
    }
    j += m ;
  }

  {
    register int *data_pointer = &fft_twidtable[ 0 ] ;
    register int *p, *q ;
    register int tmpi, fr = 0, level, k, l ;

    while ( n > max ) {
      level = max << 1;


      for ( m = 1; m < max; m += 2 ) {
        l = *( data_pointer + fr );
        k = *( data_pointer + fr + 1 ) ;
        fr += 2 ;


        for ( i = m; i <= n; i += level ) {
          j = i + max;
          p = int_pointer + j;
          q = int_pointer + i;

          tmpr  = l * *( p - 1 );
          tmpr -= ( k * *p );

          tmpi  = l * *p;
          tmpi += ( k * *( p - 1 ) );

          tmpr  = tmpr >> SHIFT ;
          tmpi  = tmpi >> SHIFT ;

          *( p - 1 ) = *( q - 1 ) - tmpr ;
          *p     = *q - tmpi ;

          *( q - 1 ) += tmpr ;
          *q     += tmpi ;
        }
      }

      /* implement unconditional bit reduction */

      {
        register int f;

        p = int_pointer;

        for ( f = 0 ; f < 2 * N_FFT; f++ ) {
          *p = *p >> 1;
          p++;
        }
      }

      max = level;
    }
  }
}


/*
  Initialization- and return-value-related functions
*/

/* conversion function to 1.NUMBER_OF_BITS format */

__attribute__((section(".ccmram")))

float fft_exp2f_ccm( float x )
{
  int i;
  float ret = 2.0f;


  for ( i = 1; i < x; ++i )
    ret *= 2.0f;

  return ret;
}


__attribute__((section(".ccmram")))

float fft_modff_ccm( float x, float *intpart )
{
  if ( intpart ) {
    *intpart = ( int )x;
    return x - *intpart;
  } else
    return x;
}


/* conversion function to 1.NUMBER_OF_BITS format */

__attribute__((section(".ccmram")))

int fft_convert_ccm( float value )
{
  float man, t_val, frac, m, exponent = NUMBER_OF_BITS;
  int rnd_val;
  unsigned long int_val;
  unsigned long pm_val;

  m = fft_exp2f_ccm( exponent + 1 )  - 1;

  t_val = value * m ;
  frac = fft_modff_ccm( t_val, &man );
  if ( frac < 0.0f ) {
    rnd_val = ( -1 );
    if ( frac > -0.5f ) rnd_val = 0;
  } else {
    rnd_val = 1;
    if ( frac < 0.5f ) rnd_val = 0;
  }
  int_val = (long)man + (long)rnd_val;

  pm_val = int_val ;
  return ( ( int ) ( pm_val ) ) ;
}


__attribute__((section(".ccmram")))

void fft_float2fract_ccm( void )
{
  float f ;
  int   j, i ;

  for ( j = 0 ; j < N_FFT ; j++ ) {
    f = fft_input[ j ];
    i = fft_convert_ccm( f );
    fft_inputfract[ j ] = i;
  }
}

__attribute__((section(".ccmram")))

void fft_pin_down_ccm( int input_data[  ] )
{
  /* conversion from input to a 1.13 format */
  fft_float2fract_ccm() ;

  int *pd, *ps, f;

  pd = &input_data[ 0 ];
  ps = &fft_inputfract[ 0 ];

  for ( f = 0; f < N_FFT; f++ ) {
    *pd++ = *ps++  ; /* fill in with real data */
    *pd++ = 0 ;      /* imaginary data is equal zero */
  }
}


__attribute__((section(".ccmram")))

void fft_init_ccm( void )
{
  int i;
  volatile int x = 0;

  fft_pin_down_ccm( &fft_input_data[ 0 ] );

  /* avoid constant propagation of input values */
  for ( i = 0; i < 2 * ( N_FFT - 1 ); i++ ) {
    fft_input_data[ i ] += x;
    fft_twidtable[ i ] += x;
  }
  for ( ; i < 2 * N_FFT; i++ )
    fft_input_data[ i ] += x;

}

/*
  Main functions
*/

__attribute__((section(".ccmram")))

void fft_main_ccm( void )
{
  fft_bit_reduct_ccm( &fft_input_data[ 0 ] );
}


void fft_bit_reduct( register int *int_pointer )
{
  register int i, j = 0  ;
  register int tmpr, max = 2, m, n = N_FFT << 1 ;

  /* do the bit reversal scramble of the input data */
  for ( i = 0; i < ( n - 1 ) ; i += 2 ) {
    if ( j > i ) {
      tmpr = *( int_pointer + j ) ;
      *( int_pointer + j ) = *( int_pointer + i ) ;
      *( int_pointer + i ) = tmpr ;

      tmpr = *( int_pointer + j + 1 ) ;
      *( int_pointer + j + 1 ) = *( int_pointer + i + 1 ) ;
      *( int_pointer + i + 1 ) = tmpr ;
    }

    m = N_FFT;

    while ( m >= 2 && j >= m ) {
      j -= m ;
      m >>= 1;
    }
    j += m ;
  }

  {
    register int *data_pointer = &fft_twidtable[ 0 ] ;
    register int *p, *q ;
    register int tmpi, fr = 0, level, k, l ;

    while ( n > max ) {
      level = max << 1;


      for ( m = 1; m < max; m += 2 ) {
        l = *( data_pointer + fr );
        k = *( data_pointer + fr + 1 ) ;
        fr += 2 ;


        for ( i = m; i <= n; i += level ) {
          j = i + max;
          p = int_pointer + j;
          q = int_pointer + i;

          tmpr  = l * *( p - 1 );
          tmpr -= ( k * *p );

          tmpi  = l * *p;
          tmpi += ( k * *( p - 1 ) );

          tmpr  = tmpr >> SHIFT ;
          tmpi  = tmpi >> SHIFT ;

          *( p - 1 ) = *( q - 1 ) - tmpr ;
          *p     = *q - tmpi ;

          *( q - 1 ) += tmpr ;
          *q     += tmpi ;
        }
      }

      /* implement unconditional bit reduction */

      {
        register int f;

        p = int_pointer;

        for ( f = 0 ; f < 2 * N_FFT; f++ ) {
          *p = *p >> 1;
          p++;
        }
      }

      max = level;
    }
  }
}


/*
  Initialization- and return-value-related functions
*/

/* conversion function to 1.NUMBER_OF_BITS format */

float fft_exp2f( float x )
{
  int i;
  float ret = 2.0f;


  for ( i = 1; i < x; ++i )
    ret *= 2.0f;

  return ret;
}


float fft_modff( float x, float *intpart )
{
  if ( intpart ) {
    *intpart = ( int )x;
    return x - *intpart;
  } else
    return x;
}


/* conversion function to 1.NUMBER_OF_BITS format */

int fft_convert( float value )
{
  float man, t_val, frac, m, exponent = NUMBER_OF_BITS;
  int rnd_val;
  unsigned long int_val;
  unsigned long pm_val;

  m = fft_exp2f( exponent + 1 )  - 1;

  t_val = value * m ;
  frac = fft_modff( t_val, &man );
  if ( frac < 0.0f ) {
    rnd_val = ( -1 );
    if ( frac > -0.5f ) rnd_val = 0;
  } else {
    rnd_val = 1;
    if ( frac < 0.5f ) rnd_val = 0;
  }
  int_val = (long)man + (long)rnd_val;

  pm_val = int_val ;
  return ( ( int ) ( pm_val ) ) ;
}


void fft_float2fract( void )
{
  float f ;
  int   j, i ;

  for ( j = 0 ; j < N_FFT ; j++ ) {
    f = fft_input[ j ];
    i = fft_convert( f );
    fft_inputfract[ j ] = i;
  }
}


void fft_pin_down( int input_data[  ] )
{
  /* conversion from input to a 1.13 format */
  fft_float2fract() ;

  int *pd, *ps, f;

  pd = &input_data[ 0 ];
  ps = &fft_inputfract[ 0 ];

  for ( f = 0; f < N_FFT; f++ ) {
    *pd++ = *ps++  ; /* fill in with real data */
    *pd++ = 0 ;      /* imaginary data is equal zero */
  }
}
void fft_init( void )
{
  int i;
  volatile int x = 0;

  fft_pin_down( &fft_input_data[ 0 ] );

  /* avoid constant propagation of input values */
  for ( i = 0; i < 2 * ( N_FFT - 1 ); i++ ) {
    fft_input_data[ i ] += x;
    fft_twidtable[ i ] += x;
  }
  for ( ; i < 2 * N_FFT; i++ )
    fft_input_data[ i ] += x;

}

/*
  Main functions
*/
void fft_main( void )
{
  fft_bit_reduct( &fft_input_data[ 0 ] );
}
