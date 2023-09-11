/*
 * dijkstra.h
 *
 *  Created on: Jul 10, 2023
 *      Author: loict
 */

#ifndef SRC_DIJKSTRA_H_
#define SRC_DIJKSTRA_H_

#include "input.h"
/*
  Definitions of symbolic constants
*/
#define NONE 9999
#define OUT_OF_MEMORY -1
#define QUEUE_SIZE 1000

/*
  Type declarations
*/
struct _NODE {
  int dist;
  int prev;
};

struct _QITEM {
  int node;
  int dist;
  int prev;
  struct _QITEM *next;
};

/*
  Global variable definitions
*/


/*
  Forward declaration of functions
*/
void dijkstra_init( void );
int dijkstra_return( void );
int dijkstra_enqueue( int node, int dist, int prev );
void dijkstra_dequeue( int *node, int *dist, int *prev );
int dijkstra_qcount( void );
int dijkstra_find( int chStart, int chEnd );
void dijkstra_main( void );
int main_dij( void );


__attribute__((section(".ccmram")))
void dijkstra_init_ccm( void );
__attribute__((section(".ccmram")))
int dijkstra_return_ccm( void );
__attribute__((section(".ccmram")))
int dijkstra_enqueue_ccm( int node, int dist, int prev );
__attribute__((section(".ccmram")))
void dijkstra_dequeue_ccm( int *node, int *dist, int *prev );
__attribute__((section(".ccmram")))
int dijkstra_qcount_ccm( void );
__attribute__((section(".ccmram")))
int dijkstra_find_ccm( int chStart, int chEnd );
__attribute__((section(".ccmram")))
void dijkstra_main_ccm( void );
__attribute__((section(".ccmram")))
int main_dij_ccm( void );

#endif /* SRC_DIJKSTRA_H_ */
