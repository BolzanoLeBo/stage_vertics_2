/*
 * kalman.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_KALMAN_H_
#define INC_KALMAN_H_

#include "stm32g4xx_hal.h"

/*data size*/
#define POINTER_SIZE_2000

typedef struct kalman_filter_param
{
  /* Transition*/
    float A_mat2f[4];
  /* Q covariance with respect to our process model noise. */
    float Q_mat2f[4];
  /* His the observation model, which maps the true state space into the observed space*/
    float H_vec2f[2];
  /* Observation noise: R covariance matrix 1x1 */
    float R_mat1f;
  /* P plus current covariance matrix 2x2: estimate error */
    float P_plus_mat2f[4];
  /* x plus current state vector 2x1: value, speed */
    float x_plus_vec2f[2];
} kalman_filter_param;

float* KalmanFilterStep(float z_plus_0, float z_plus_1, kalman_filter_param* kalman_param);

void KalmanFiltermain( float* posi, float* velo, kalman_filter_param* kalman_param, int n);

__attribute__((section(".ccmram")))
float* KalmanFilterStep_ccm(float z_plus_0, float z_plus_1, kalman_filter_param* kalman_param);

__attribute__((section(".ccmram")))
void KalmanFiltermain_ccm( float* posi, float* velo, kalman_filter_param* kalman_param, int n);


void kal_main();

__attribute__((section(".ccmram")))
void kal_main_ccm();
#endif /* INC_KALMAN_H_ */
