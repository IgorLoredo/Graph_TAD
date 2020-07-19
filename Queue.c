#include "Graph.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue *newQueue(){
    Queue *new = (Queue*)calloc(1,sizeof(Queue));
    new->tam =0;
    queue->front  = -1
    return new;
}

void push(Queue *queue,int val){
    queue->Queue = (Queue*)realloc(queue->Queue, sizeof(Queue)*(queue->tam+1));
    queue->Queue[queue->front+1] = val;
    queue
    queue->tam += 1;
}

// retorna front, o primeiro item da fila
int pop(Queue *queue){
    int front = queue->Queue[queue];
    memcpy(queue,&queue[1],(*n_elem)*sizeof(int));
    (*n_elem)--;
    return front;
}



