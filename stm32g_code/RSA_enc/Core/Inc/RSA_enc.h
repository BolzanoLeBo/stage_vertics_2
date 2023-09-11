/*
 * RSA_enc.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_RSA_ENC_H_
#define INC_RSA_ENC_H_

#define SIZE 500

void encrypt();

__attribute__((section (".ccmram")))
void encrypt_ccm();
#endif /* INC_RSA_ENC_H_ */
