/* Igor Guilherme Pereira Loredo - 11275071 */
/* Natã Silva Botelho            - 11275105 */

#ifndef _Queue_h
#define _Queue_h

#include "Graph.h"

/*STRUCT*/
typedef struct queue{
    int *Queue;
    int size;
    int first;
}Queue;

/*FUNCTIONS*/
Queue *newQueue();

void push(Queue *,int );

int empty(Queue*);

int pop(Queue*);

#endif
