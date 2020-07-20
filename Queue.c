#include "Graph.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue *newQueue(){
    Queue *new = (Queue*)calloc(1,sizeof(Queue));
    new->tam =0;
<<<<<<< HEAD
    new->front  = 0;
=======
    queue->front  = -1
>>>>>>> 291883890680eb96f975d111d005b5d0a9c6d698
    return new;
}

void push(Queue *queue,int val){
    queue->Queue = (Queue*)realloc(queue->Queue, sizeof(Queue)*(queue->tam+1));
<<<<<<< HEAD
    queue->Queue[queue->tam] = val;
=======
    queue->Queue[queue->front+1] = val;
    queue
>>>>>>> 291883890680eb96f975d111d005b5d0a9c6d698
    queue->tam += 1;
}

// retorna front, o primeiro item da fila
int pop(Queue *queue){
<<<<<<< HEAD
    int front = queue->Queue[queue->front];
    memcpy(queue,&queue[1],(queue->tam)*sizeof(int));
    queue->tam--;
    return front;
}

=======
    int front = queue->Queue[queue];
    memcpy(queue,&queue[1],(*n_elem)*sizeof(int));
    (*n_elem)--;
    return front;
}



>>>>>>> 291883890680eb96f975d111d005b5d0a9c6d698
