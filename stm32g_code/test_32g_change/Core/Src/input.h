#ifndef INPUT_H
#define INPUT_H

#define NUM_NODES 60
//#define INPUT_CCM

#ifdef INPUT_CCM
__attribute__((section(".ccmramdata")))
#endif
extern unsigned char dijkstra_AdjMatrix[ NUM_NODES ][ NUM_NODES ];

#endif  /* INPUT_H */
