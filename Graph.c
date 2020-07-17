#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
Graph *newGraph(){
    Graph *graph = (Graph*)calloc(1, sizeof(Graph));
    return graph;
}

Edge *newEdge(Actor actor, Movie movie){
    Edge *new = (Edge*)malloc(sizeof(Edge));
    new->actor_id = actor.index;
    new->movie_id = movie.index;
    new->next = NULL;
    new->KB = -1;
    return new;
}

Actor *newActor(char *name, int index){
    Actor *new  = (Actor*)malloc(sizeof(Actor));
    new->name = (char*) malloc (strlen(name));
    memcpy(new->name, name, strlen(name));
    new->index = index;
    return new;
}

Movie *newMovie(char *name, int index){
    Movie *new = (Movie*)malloc(sizeof(Movie));
    new->name = (char*) malloc (strlen(name));
    memcpy(new->name, name, strlen(name));
    new->index = index;
    return new;
}

int insertActor(Graph *graph, Actor *newActor){
    graph->actorlist.nActor++;
    graph->actorlist.list = (Actor**) realloc (graph->actorlist.list, sizeof(Actor*)*(graph->actorlist.nActor));
    graph->actorlist.list[newActor->index] = (Actor*) malloc (sizeof(Actor));

    return SUCCESS;
}

int insertMovie(Graph *graph, Movie *newMovie){
    graph->movieList.list = (Movie*) realloc (graph->movieList.list, sizeof(Movie)*(graph->movieList.nMovie+1));
    graph->movieList.list[graph->movieList.nMovie].name = newMovie->name;
    graph->movieList.list[graph->movieList.nMovie].index = newMovie->index;
    graph->movieList.nMovie++;

    return SUCCESS;
}

int insertEdge(Graph *graph, Edge *edge, int nactor_id){
    if(!graph || !edge || nactor_id < 0 || nactor_id > graph->actorlist.nActor) return ERROR;

    int i = 0;
    Actor *aux;
    
    aux = graph->actorlist.list[nactor_id];

    edge->next = aux->head;
    aux->head = edge;

    return SUCCESS;
}



int readBK();