#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

 
Graph *newGraph(){
    Graph *graph = (Graph*)calloc(1, sizeof(Graph));
    return graph;
}

Edge *newNode(Actor actor, Movie movie){
    Edge *new = (Edge*)malloc(sizeof(Edge));
    new->actor_id = actor.index;
    new->movie_id = movie.index;
    new->next = NULL;
    new->KB = -1;
    return new;
}

Actor *newActor(char *name,int index){
    Actor *new  = (Actor*)malloc(sizeof(Actor));
    new->name = name;
    new->index = index;
    return new;
}

Movie *newMovie(char *name,int index){
    Movie *new = (Movie*)malloc(sizeof(Movie));
    new->name = name;
    new->index = index;
    return new;
}


int insertNode(Graph *graph, Edge *node, int nactor_id){
    if(!graph || !node) return ERROR;

    int i = 0;
    
    while(i < graph->nElement && graph->list[i]->actor_id != nactor_id)
        i++;

    node->next = graph->list[i]->next;
    graph->list[i]->next = node;

    return SUCCESS;
}



int readBK();