/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define NUMBER_OF_BITS 13    /* fract format 1.NUMBER_OF_BITS = 1.13 */

#define BITS_PER_TWID 13     /* bits per twiddle coefficient */
#define SHIFT BITS_PER_TWID  /* fractional shift after each multiplication */
//#define INPUT_DATA_ON_CCM
//#define DATA_ON_CCM



#define N_FFT 256
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
//change SYSCLK source to PLL
void change_to_PLL();
//used to seperate code executions
void Sleep(int time);
//change the PLL output frequency
void change_freq(int mul);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void tested_code()
{
  fft_init();
  fft_main();
  Sleep(200);
  fft_init_ccm();
  fft_main_ccm();
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /*Multiplicators for 24         48           72     MHz*/
  int mul[3] = {RCC_PLL_MUL3,RCC_PLL_MUL6,RCC_PLL_MUL9};
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(HAL_RTC_GetState(&hrtc) != HAL_RTC_STATE_READY )
  {
    ;
  }
  for (int i = 0; i<3; i++)
  {
    change_freq(mul[i]);
    Sleep(500);

    tested_code();

    Sleep(500);
  }

  HAL_SuspendTick();
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pins : PE2 PE3 PE4 PE5
                           PE6 PE7 PE8 PE9
                           PE10 PE11 PE12 PE13
                           PE14 PE15 PE0 PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC13 PC14 PC15 PC0
                           PC1 PC2 PC3 PC4
                           PC5 PC6 PC7 PC8
                           PC9 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PF9 PF10 PF2 PF4
                           PF6 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_2|GPIO_PIN_4
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 PA10 PA11
                           PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB3 PB4 PB5
                           PB6 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11
                           PD12 PD13 PD14 PD15
                           PD0 PD1 PD2 PD3
                           PD4 PD5 PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void change_to_PLL()
{
  int latency;
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  //Re-enable HSE oscillator on PLL
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState        = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_ON;
  //RCC_OscInitStruct.PLL.PLLMUL      = RCC_PLL_MUL9;

  switch(RCC_OscInitStruct.PLL.PLLMUL)
  {
  case RCC_PLL_MUL3:
    latency = FLASH_LATENCY_0;
    break;
  case RCC_PLL_MUL6:
    latency = FLASH_LATENCY_1;
    break;
  case RCC_PLL_MUL9:
    latency = FLASH_LATENCY_2;
    break;
  default:
    latency = FLASH_LATENCY_0;
  }
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  /* Initialization Error */
  Error_Handler();
  }

  //Select the PLL as SYSCLK source
  RCC_ClkInitStruct.ClockType       = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider  = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider  = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, latency) != HAL_OK)
  {

  /* Initialization Error */
  Error_Handler();
  }
  //Disable the HSI (not used)
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState        = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  //Initialization Error
  Error_Handler();
  }
}

void Sleep(int time)
{
  uint32_t counter = (uint32_t) ((float) time*2.5);/*divide by (16/40)*/

  HAL_SuspendTick();

  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, counter, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
  /* Enter sleep or stop mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  //HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
  /* Wake up*/
  HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
  HAL_ResumeTick();
  //When wake up from STOP Sysclk source is HSI
  change_to_PLL();
  /*int r = __HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK;
  int f = HAL_RCC_GetSysClockFreq();*/
}

void change_freq(int mul)
{
  int latency;
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* -1- Select HSE as system clock source to allow modification of the PLL configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  switch(mul)
  {
  case RCC_PLL_MUL3:
    latency = FLASH_LATENCY_0;
    break;
  case RCC_PLL_MUL6:
    latency = FLASH_LATENCY_1;
    break;
  case RCC_PLL_MUL9:
    latency = FLASH_LATENCY_2;
    break;
  default:
    latency = FLASH_LATENCY_0;
  }
  /* -2- Enable HSE  Oscillator, select it as PLL source and finally activate the PLL */
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState        = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLMUL      = mul;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* -3- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType       = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider  = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider  = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, latency) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
