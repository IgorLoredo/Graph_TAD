#ifndef _Queue_h
#define _Queue_h

#include "Graph.h"

typedef struct queue{
    int *Queue;
    int tam;
    int front;
}Queue;

Queue *newQueue();

void push(Queue *,int );

int pop(Queue*);

#endif // !Queue_h
