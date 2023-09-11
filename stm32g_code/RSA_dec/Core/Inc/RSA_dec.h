/*
 * RSA_dec.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_RSA_DEC_H_
#define INC_RSA_DEC_H_
#define SIZE 500


void decrypt();

__attribute__((section (".ccmram")))
void decrypt_ccm();

#endif /* INC_RSA_DEC_H_ */
