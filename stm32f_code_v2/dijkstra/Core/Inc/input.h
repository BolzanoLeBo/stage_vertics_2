#ifndef INPUT_H
#define INPUT_H

#define NUM_NODES 50


#ifdef INPUT_CCM
__attribute__((section(".ccmramdata")))
#endif
extern unsigned char dijkstra_AdjMatrix[ NUM_NODES ][ NUM_NODES ];

#endif  /* INPUT_H */
