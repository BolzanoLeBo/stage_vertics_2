
#include "dijkstra.h"

struct _NODE dijkstra_rgnNodes[ NUM_NODES ];

#ifdef INPUT_RAM2
__attribute__((section(".ram2data")))
#endif
int dijkstra_queueCount;


#ifdef INPUT_RAM2
__attribute__((section(".ram2data")))
#endif
int dijkstra_queueNext;

#ifdef INPUT_RAM2
__attribute__((section(".ram2data")))
#endif
struct _QITEM *dijkstra_queueHead;

#ifdef INPUT_RAM2
__attribute__((section(".ram2data")))
#endif
struct _QITEM dijkstra_queueItems[ QUEUE_SIZE ];

int dijkstra_checksum = 0;

void dijkstra_init( void )
{
  int i, k;
  volatile int x = 0;

  for ( i = 0; i < NUM_NODES; i++ ) {

    for ( k = 0; k < NUM_NODES; k++ )
      dijkstra_AdjMatrix[ i ][ k ] ^= x;
  }

  dijkstra_queueCount = 0;
  dijkstra_queueNext = 0;
  dijkstra_queueHead = ( struct _QITEM * )0;

  dijkstra_checksum = 0;
}

int dijkstra_return( void )
{
  return ( ( dijkstra_checksum == 25 ) ? 0 : -1 );
}

int dijkstra_enqueue( int node, int dist, int prev )
{
  struct _QITEM *newItem = &dijkstra_queueItems[ dijkstra_queueNext ];
  struct _QITEM *last = dijkstra_queueHead;

  if ( ++dijkstra_queueNext >= QUEUE_SIZE )
    return OUT_OF_MEMORY;
  newItem->node = node;
  newItem->dist = dist;
  newItem->prev = prev;
  newItem->next = 0;

  if ( !last )
    dijkstra_queueHead = newItem;
  else {
    /* TODO: where does this magic loop bound come from? */

    while ( last->next )
      last = last->next;
    last->next = newItem;
  }
  dijkstra_queueCount++;
  return 0;
}

void dijkstra_dequeue( int *node, int *dist, int *prev )
{
  if ( dijkstra_queueHead ) {
    *node = dijkstra_queueHead->node;
    *dist = dijkstra_queueHead->dist;
    *prev = dijkstra_queueHead->prev;
    dijkstra_queueHead = dijkstra_queueHead->next;
    dijkstra_queueCount--;
  }
}

int dijkstra_qcount( void )
{
  return ( dijkstra_queueCount );
}

int dijkstra_find( int chStart, int chEnd )
{
  int ch;
  int prev, node = 0;
  int cost, dist = 0;
  int i;


  for ( ch = 0; ch < NUM_NODES; ch++ ) {
    dijkstra_rgnNodes[ ch ].dist = NONE;
    dijkstra_rgnNodes[ ch ].prev = NONE;
  }

  if ( chStart == chEnd ) {
  } else {
    dijkstra_rgnNodes[ chStart ].dist = 0;
    dijkstra_rgnNodes[ chStart ].prev = NONE;

    if ( dijkstra_enqueue ( chStart, 0, NONE ) == OUT_OF_MEMORY )
      return OUT_OF_MEMORY;

    /* TODO: where does this magic loop bound come from? */

    while ( dijkstra_qcount() > 0 ) {
      dijkstra_dequeue ( &node, &dist, &prev );

      for ( i = 0; i < NUM_NODES; i++ ) {
        if ( ( cost = dijkstra_AdjMatrix[ node ][ i ] ) != NONE ) {
          if ( ( NONE == dijkstra_rgnNodes[ i ].dist ) ||
               ( dijkstra_rgnNodes[ i ].dist > ( cost + dist ) ) ) {
            dijkstra_rgnNodes[ i ].dist = dist + cost;
            dijkstra_rgnNodes[ i ].prev = node;
            if ( dijkstra_enqueue ( i, dist + cost, node ) == OUT_OF_MEMORY )
              return OUT_OF_MEMORY;
          }
        }
      }
    }
  }
  return 0;
}

void  dijkstra_main( void )
{
  int i, j;

  /* finds 20 shortest paths between nodes */
  for ( i = 0, j = NUM_NODES / 2; i < 20; i++, j++ ) {
    j = j % NUM_NODES;
    if ( dijkstra_find( i, j ) == OUT_OF_MEMORY ) {
      dijkstra_checksum += OUT_OF_MEMORY;
      return;
    } else
      dijkstra_checksum += dijkstra_rgnNodes[ j ].dist;
    dijkstra_queueNext = 0;
  }
}

int main_dij( void )
{

  for (int i = 0; i<MAX_REP; i++)
  {
    dijkstra_init();
    dijkstra_main();
  }

  return ( dijkstra_return() );
}



//---------CCM----------------------


void dijkstra_init_ccm( void )
{
  int i, k;
  volatile int x = 0;

  for ( i = 0; i < NUM_NODES; i++ ) {

    for ( k = 0; k < NUM_NODES; k++ )
      dijkstra_AdjMatrix[ i ][ k ] ^= x;
  }

  dijkstra_queueCount = 0;
  dijkstra_queueNext = 0;
  dijkstra_queueHead = ( struct _QITEM * )0;

  dijkstra_checksum = 0;
}

int dijkstra_return_ccm( void )
{
  return ( ( dijkstra_checksum == 25 ) ? 0 : -1 );
}

int dijkstra_enqueue_ccm( int node, int dist, int prev )
{
  struct _QITEM *newItem = &dijkstra_queueItems[ dijkstra_queueNext ];
  struct _QITEM *last = dijkstra_queueHead;

  if ( ++dijkstra_queueNext >= QUEUE_SIZE )
    return OUT_OF_MEMORY;
  newItem->node = node;
  newItem->dist = dist;
  newItem->prev = prev;
  newItem->next = 0;

  if ( !last )
    dijkstra_queueHead = newItem;
  else {
    /* TODO: where does this magic loop bound come from? */

    while ( last->next )
      last = last->next;
    last->next = newItem;
  }
  dijkstra_queueCount++;
  return 0;
}

void dijkstra_dequeue_ccm( int *node, int *dist, int *prev )
{
  if ( dijkstra_queueHead ) {
    *node = dijkstra_queueHead->node;
    *dist = dijkstra_queueHead->dist;
    *prev = dijkstra_queueHead->prev;
    dijkstra_queueHead = dijkstra_queueHead->next;
    dijkstra_queueCount--;
  }
}

int dijkstra_qcount_ccm( void )
{
  return ( dijkstra_queueCount );
}

int dijkstra_find_ccm( int chStart, int chEnd )
{
  int ch;
  int prev, node = 0;
  int cost, dist = 0;
  int i;


  for ( ch = 0; ch < NUM_NODES; ch++ ) {
    dijkstra_rgnNodes[ ch ].dist = NONE;
    dijkstra_rgnNodes[ ch ].prev = NONE;
  }

  if ( chStart == chEnd ) {
  } else {
    dijkstra_rgnNodes[ chStart ].dist = 0;
    dijkstra_rgnNodes[ chStart ].prev = NONE;

    if ( dijkstra_enqueue_ccm ( chStart, 0, NONE ) == OUT_OF_MEMORY )
      return OUT_OF_MEMORY;

    /* TODO: where does this magic loop bound come from? */

    while ( dijkstra_qcount_ccm() > 0 ) {
      dijkstra_dequeue_ccm ( &node, &dist, &prev );

      for ( i = 0; i < NUM_NODES; i++ ) {
        if ( ( cost = dijkstra_AdjMatrix[ node ][ i ] ) != NONE ) {
          if ( ( NONE == dijkstra_rgnNodes[ i ].dist ) ||
               ( dijkstra_rgnNodes[ i ].dist > ( cost + dist ) ) ) {
            dijkstra_rgnNodes[ i ].dist = dist + cost;
            dijkstra_rgnNodes[ i ].prev = node;
            if ( dijkstra_enqueue_ccm ( i, dist + cost, node ) == OUT_OF_MEMORY )
              return OUT_OF_MEMORY;
          }
        }
      }
    }
  }
  return 0;
}

void  dijkstra_main_ccm( void )
{
  int i, j;

  /* finds 20 shortest paths between nodes */
  for ( i = 0, j = NUM_NODES / 2; i < 20; i++, j++ ) {
    j = j % NUM_NODES;
    if ( dijkstra_find_ccm( i, j ) == OUT_OF_MEMORY ) {
      dijkstra_checksum += OUT_OF_MEMORY;
      return;
    } else
      dijkstra_checksum += dijkstra_rgnNodes[ j ].dist;
    dijkstra_queueNext = 0;
  }
}

int main_dij_ccm( void )
{
  for (int i = 0; i<MAX_REP; i++)
  {
    dijkstra_init_ccm();
    dijkstra_main_ccm();
  }

  return ( dijkstra_return_ccm() );
}



//---------ram----------------------


void dijkstra_init_ram( void )
{
  int i, k;
  volatile int x = 0;

  for ( i = 0; i < NUM_NODES; i++ ) {

    for ( k = 0; k < NUM_NODES; k++ )
      dijkstra_AdjMatrix[ i ][ k ] ^= x;
  }

  dijkstra_queueCount = 0;
  dijkstra_queueNext = 0;
  dijkstra_queueHead = ( struct _QITEM * )0;

  dijkstra_checksum = 0;
}

int dijkstra_return_ram( void )
{
  return ( ( dijkstra_checksum == 25 ) ? 0 : -1 );
}

int dijkstra_enqueue_ram( int node, int dist, int prev )
{
  struct _QITEM *newItem = &dijkstra_queueItems[ dijkstra_queueNext ];
  struct _QITEM *last = dijkstra_queueHead;

  if ( ++dijkstra_queueNext >= QUEUE_SIZE )
    return OUT_OF_MEMORY;
  newItem->node = node;
  newItem->dist = dist;
  newItem->prev = prev;
  newItem->next = 0;

  if ( !last )
    dijkstra_queueHead = newItem;
  else {
    /* TODO: where does this magic loop bound come from? */

    while ( last->next )
      last = last->next;
    last->next = newItem;
  }
  dijkstra_queueCount++;
  return 0;
}

void dijkstra_dequeue_ram( int *node, int *dist, int *prev )
{
  if ( dijkstra_queueHead ) {
    *node = dijkstra_queueHead->node;
    *dist = dijkstra_queueHead->dist;
    *prev = dijkstra_queueHead->prev;
    dijkstra_queueHead = dijkstra_queueHead->next;
    dijkstra_queueCount--;
  }
}

int dijkstra_qcount_ram( void )
{
  return ( dijkstra_queueCount );
}

int dijkstra_find_ram( int chStart, int chEnd )
{
  int ch;
  int prev, node = 0;
  int cost, dist = 0;
  int i;


  for ( ch = 0; ch < NUM_NODES; ch++ ) {
    dijkstra_rgnNodes[ ch ].dist = NONE;
    dijkstra_rgnNodes[ ch ].prev = NONE;
  }

  if ( chStart == chEnd ) {
  } else {
    dijkstra_rgnNodes[ chStart ].dist = 0;
    dijkstra_rgnNodes[ chStart ].prev = NONE;

    if ( dijkstra_enqueue_ram ( chStart, 0, NONE ) == OUT_OF_MEMORY )
      return OUT_OF_MEMORY;

    /* TODO: where does this magic loop bound come from? */

    while ( dijkstra_qcount_ram() > 0 ) {
      dijkstra_dequeue_ram ( &node, &dist, &prev );

      for ( i = 0; i < NUM_NODES; i++ ) {
        if ( ( cost = dijkstra_AdjMatrix[ node ][ i ] ) != NONE ) {
          if ( ( NONE == dijkstra_rgnNodes[ i ].dist ) ||
               ( dijkstra_rgnNodes[ i ].dist > ( cost + dist ) ) ) {
            dijkstra_rgnNodes[ i ].dist = dist + cost;
            dijkstra_rgnNodes[ i ].prev = node;
            if ( dijkstra_enqueue_ram ( i, dist + cost, node ) == OUT_OF_MEMORY )
              return OUT_OF_MEMORY;
          }
        }
      }
    }
  }
  return 0;
}

void  dijkstra_main_ram( void )
{
  int i, j;

  /* finds 20 shortest paths between nodes */
  for ( i = 0, j = NUM_NODES / 2; i < 20; i++, j++ ) {
    j = j % NUM_NODES;
    if ( dijkstra_find_ram( i, j ) == OUT_OF_MEMORY ) {
      dijkstra_checksum += OUT_OF_MEMORY;
      return;
    } else
      dijkstra_checksum += dijkstra_rgnNodes[ j ].dist;
    dijkstra_queueNext = 0;
  }
}

int main_dij_ram( void )
{
  for (int i = 0; i<MAX_REP; i++)
  {
    dijkstra_init_ram();
    dijkstra_main_ram();
  }
  return ( dijkstra_return_ram() );
}


//---------ram2----------------------


void dijkstra_init_ram2( void )
{
  int i, k;
  volatile int x = 0;

  for ( i = 0; i < NUM_NODES; i++ ) {

    for ( k = 0; k < NUM_NODES; k++ )
      dijkstra_AdjMatrix[ i ][ k ] ^= x;
  }

  dijkstra_queueCount = 0;
  dijkstra_queueNext = 0;
  dijkstra_queueHead = ( struct _QITEM * )0;

  dijkstra_checksum = 0;
}

int dijkstra_return_ram2( void )
{
  return ( ( dijkstra_checksum == 25 ) ? 0 : -1 );
}

int dijkstra_enqueue_ram2( int node, int dist, int prev )
{
  struct _QITEM *newItem = &dijkstra_queueItems[ dijkstra_queueNext ];
  struct _QITEM *last = dijkstra_queueHead;

  if ( ++dijkstra_queueNext >= QUEUE_SIZE )
    return OUT_OF_MEMORY;
  newItem->node = node;
  newItem->dist = dist;
  newItem->prev = prev;
  newItem->next = 0;

  if ( !last )
    dijkstra_queueHead = newItem;
  else {
    /* TODO: where does this magic loop bound come from? */

    while ( last->next )
      last = last->next;
    last->next = newItem;
  }
  dijkstra_queueCount++;
  return 0;
}

void dijkstra_dequeue_ram2( int *node, int *dist, int *prev )
{
  if ( dijkstra_queueHead ) {
    *node = dijkstra_queueHead->node;
    *dist = dijkstra_queueHead->dist;
    *prev = dijkstra_queueHead->prev;
    dijkstra_queueHead = dijkstra_queueHead->next;
    dijkstra_queueCount--;
  }
}

int dijkstra_qcount_ram2( void )
{
  return ( dijkstra_queueCount );
}

int dijkstra_find_ram2( int chStart, int chEnd )
{
  int ch;
  int prev, node = 0;
  int cost, dist = 0;
  int i;


  for ( ch = 0; ch < NUM_NODES; ch++ ) {
    dijkstra_rgnNodes[ ch ].dist = NONE;
    dijkstra_rgnNodes[ ch ].prev = NONE;
  }

  if ( chStart == chEnd ) {
  } else {
    dijkstra_rgnNodes[ chStart ].dist = 0;
    dijkstra_rgnNodes[ chStart ].prev = NONE;

    if ( dijkstra_enqueue_ram2 ( chStart, 0, NONE ) == OUT_OF_MEMORY )
      return OUT_OF_MEMORY;

    /* TODO: where does this magic loop bound come from? */

    while ( dijkstra_qcount_ram2() > 0 ) {
      dijkstra_dequeue_ram2 ( &node, &dist, &prev );

      for ( i = 0; i < NUM_NODES; i++ ) {
        if ( ( cost = dijkstra_AdjMatrix[ node ][ i ] ) != NONE ) {
          if ( ( NONE == dijkstra_rgnNodes[ i ].dist ) ||
               ( dijkstra_rgnNodes[ i ].dist > ( cost + dist ) ) ) {
            dijkstra_rgnNodes[ i ].dist = dist + cost;
            dijkstra_rgnNodes[ i ].prev = node;
            if ( dijkstra_enqueue_ram2 ( i, dist + cost, node ) == OUT_OF_MEMORY )
              return OUT_OF_MEMORY;
          }
        }
      }
    }
  }
  return 0;
}

void  dijkstra_main_ram2( void )
{
  int i, j;

  /* finds 20 shortest paths between nodes */
  for ( i = 0, j = NUM_NODES / 2; i < 20; i++, j++ ) {
    j = j % NUM_NODES;
    if ( dijkstra_find_ram2( i, j ) == OUT_OF_MEMORY ) {
      dijkstra_checksum += OUT_OF_MEMORY;
      return;
    } else
      dijkstra_checksum += dijkstra_rgnNodes[ j ].dist;
    dijkstra_queueNext = 0;
  }
}

int main_dij_ram2( void )
{
  for (int i = 0; i<MAX_REP; i++)
  {
    dijkstra_init_ram2();
    dijkstra_main_ram2();
  }


  return ( dijkstra_return_ram2() );
}
