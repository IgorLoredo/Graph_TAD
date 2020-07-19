#include "Graph.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue *newQueue(){
    Queue *new = (Queue*)calloc(1,sizeof(Queue));
    new->tam =0;
    new->front  = 0;
    return new;
}

void push(Queue *queue,int val){
    queue->Queue = (Queue*)realloc(queue->Queue, sizeof(Queue)*(queue->tam+1));
    queue->Queue[queue->tam] = val;
    queue->tam += 1;
}

// retorna front, o primeiro item da fila
int pop(Queue *queue){
    int front = queue->Queue[queue->front];
    memcpy(queue,&queue[1],(queue->tam)*sizeof(int));
    queue->tam--;
    return front;
}

