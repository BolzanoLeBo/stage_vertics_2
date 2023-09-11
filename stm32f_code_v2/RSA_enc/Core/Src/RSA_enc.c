/*
 * RSA_enc.c
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */


#include "RSA_enc.h"

int* ro_data;
char plaintext[SIZE]="To be, or not to be, that is the question: Whether tis nobler in the mind to suffer The slings and a"
"To be, or not to be, that is the question: Whether tis nobler in the mind to suffer The slings and a"
"To be, or not to be, that is the question: Whether tis nobler in the mind to suffer The slings and a"
"To be, or not to be, that is the question: Whether tis nobler in the mind to suffer The slings and a"
"To be, or not to be, that is the question: Whether tis nobler in the mind to suffer The slings and a";
int c[SIZE];

int ro_data_src[3] = {7, 221, 55};


void encrypt(){
  for (int i = 0; i<MAX_REP; i++)
  {
    ro_data = ro_data_src;
    /* encrypt each plaintext element, c[] is the encripted array*/
    int temp_crypted_element=1;
    for(int i=0;i<SIZE;i++){
       for(int j=0;j</*key_info.e*/ro_data[0];j++){
         temp_crypted_element= temp_crypted_element * plaintext[i] % ro_data[1];
       }
       c[i]=temp_crypted_element;
       temp_crypted_element=1;
    }


  }

}


void encrypt_ccm(){
  for (int i = 0; i<MAX_REP; i++)
  {
    ro_data = ro_data_src;
    /* encrypt each plaintext element, c[] is the encripted array*/
    int temp_crypted_element=1;
    for(int i=0;i<SIZE;i++){
       for(int j=0;j</*key_info.e*/ro_data[0];j++){
         temp_crypted_element= temp_crypted_element * plaintext[i] % ro_data[1];
       }
       c[i]=temp_crypted_element;
       temp_crypted_element=1;
    }
  }

}


void encrypt_ram(){
  for (int i = 0; i<MAX_REP; i++)
  {
    ro_data = ro_data_src;
    /* encrypt each plaintext element, c[] is the encripted array*/
    int temp_crypted_element=1;
    for(int i=0;i<SIZE;i++){
       for(int j=0;j</*key_info.e*/ro_data[0];j++){
         temp_crypted_element= temp_crypted_element * plaintext[i] % ro_data[1];
       }
       c[i]=temp_crypted_element;
       temp_crypted_element=1;
    }
  }

}

