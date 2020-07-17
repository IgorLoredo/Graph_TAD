#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>




Graph *newGraph(){
    Graph *graph = (Graph*)calloc(1,sizeof(Graph));
    return graph;
}

Node *newNode(Actor actor, Movie movie){
    Node *new = (Node*)malloc(sizeof(Node));
    new->actor_id = actor.index;
    new->movie_id = movie.index;
    new->next = NULL;
    new->KB = 0;
    return new;
}

int insertNode(Graph *graph, Node *node, int nactor_id){
    if(!graph || !node) return ERROR;

    int i = 0;
    
    while(i < graph->nElement && graph->list[i]->actor_id != nactor_id)
        i++;

    node->next = graph->list[i]->next;
    graph->list[i]->next = node;

    return SUCCESS;
}