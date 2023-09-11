/*
 * dijkstra.h
 *
 *  Created on: Jul 10, 2023
 *      Author: loict
 */

#ifndef SRC_PETRINET_H_
#define SRC_PETRINET_H_

#ifdef PROFILING
#include <stdio.h>
#endif



/*
  Forward declaration of functions
*/
void petrinet_init( void );
void petrinet_main( void );

__attribute__((section(".ccmram")))
void petrinet_init_ccm( void );
__attribute__((section(".ccmram")))
void petrinet_main_ccm( void );



#endif /* SRC_PETRINET_H_ */
