#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
Graph *newGraph(){
    Graph *graph = (Graph*)calloc(1, sizeof(Graph));
    return graph;
}

Edge *newEdge(Actor *actor, Movie *movie){
    Edge *new = (Edge*)malloc(sizeof(Edge));
    new->actor_id = actor->index;
    new->movie_id = movie->index;
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
    
    Actor *aux;
    
    aux = graph->actorlist.list[nactor_id];

    edge->next = aux->head;
    aux->head = edge;

    return SUCCESS;
}

int checkActor(Graph *graph, char *name){
    int i;
    
    for(i=0; i < graph->actorlist.nActor; i++){
        if(!strcmp(graph->actorlist.list[i]->name, name))
            return i;
    }

    return 0;
}


int readBK(Graph *bk){
    if(!bk) return ERROR;
    char *nome = (char*)malloc(200*sizeof(char));
    while (fscanf(stdin, "%[^/]/", nome) != EOF) {

        printf("%s\n",nome);
        
    }
    return SUCCESS;
}


int printGraph(Graph *graph){
    if(!graph) return ERROR;
    int i;
    for(i =0; i <graph->actorlist.nActor; i++){
        printf("Ator: %s KB: %d \n",graph->actorlist.list[i]->name,graph->actorlist.list[i]->index);
    }

    for(i =0; i <graph->movieList.nMovie; i++){
        printf("Filme: %s\n",graph->movieList.list->name);
    }
    return SUCCESS;
}
