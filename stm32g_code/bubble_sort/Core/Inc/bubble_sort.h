/*
 * bubble_sort.h
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */

#ifndef INC_BUBBLE_SORT_H_
#define INC_BUBBLE_SORT_H_
#include <string.h>
#define FALSE 0
#define TRUE 1
#define NUMELEMS 1000  // Defines how much elements will be sorted
#define MAXDIM   (NUMELEMS+1)




__attribute__((section(".ccmram")))
void BubbleSortCCM(int Array[]);

void BubbleSort(int Array[]);
void bubble_main();
__attribute__((section(".ccmram")))
void bubble_main_ccm();
void init_tab();

#endif /* INC_BUBBLE_SORT_H_ */
