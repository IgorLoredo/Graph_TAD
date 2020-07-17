#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>




Graph *newGraph(){
    return (Graph)calloc(1,sizeof(Graph));
}

Node *newNode(Char *element,int id){
    Node *new = (Node*)malloc(sizeof(Node));
    new->Element = element;
    new->id;
    return new;
}

 