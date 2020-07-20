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
    graph->actorlist.list = (Actor**) realloc (graph->actorlist.list, sizeof(Actor*)*(graph->actorlist.nActor+1));
    graph->actorlist.list[newActor->index] = newActor;
    //printf("%s %d\n", graph->actorlist.list[newActor->index]->name, graph->actorlist.list[newActor->index]->index);
    graph->actorlist.nActor++;

    return SUCCESS;
}

int insertMovie(Graph *graph, Movie *newMovie){
    graph->movieList.list = (Movie**) realloc (graph->movieList.list, sizeof(Movie*)*(graph->movieList.nMovie+1));
    graph->movieList.list[graph->movieList.nMovie] = newMovie;
    //printf("%s %d\n", graph->movieList.list[newMovie->index]->name, graph->movieList.list[newMovie->index]->index);
    graph->movieList.nMovie++;

    return SUCCESS;
}

int insertEdge(Graph *graph, Edge *edge){
    if(!graph || !edge) return ERROR;
    
    Edge *movieEdge = (Edge*) malloc (sizeof(Edge));
    memcpy(movieEdge, edge, sizeof(Edge));
    
    edge->next = graph->actorlist.list[edge->actor_id]->head;
    graph->actorlist.list[edge->actor_id]->head = edge;;
    
    movieEdge->next = graph->movieList.list[edge->movie_id]->head;
    graph->movieList.list[movieEdge->movie_id]->head = movieEdge;

    printf("ator %s conectado no filme %s, filme %s conectado em ator %s\n", graph->actorlist.list[edge->actor_id]->name, graph->movieList.list[edge->movie_id]->name, graph->movieList.list[movieEdge->movie_id]->name, graph->actorlist.list[movieEdge->actor_id]->name);

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


int readData(Graph *graph){ 
    char *name = (char*)malloc(200*sizeof(char));
    char *kevinB = "Bacon, Kevin";
    char auxchar;
    int flag = 1, actorIndex;
    Movie *auxMovie;
    Actor *auxActor;
    Edge *auxEdge;
    FILE *datafile = fopen("input-top-grossing.txt", "r");
    
    while (fscanf(datafile, "%[^/||^\n]%c", name, &auxchar) != EOF) {
        if(flag){
            auxMovie = newMovie(name, graph->movieList.nMovie);
            insertMovie(graph, auxMovie);
        }
        else{
            actorIndex = checkActor(graph, name);
            if(!strcmp(name, kevinB))   //checa se e o kevin bacon
                auxActor = newActor(name, 0);
            else if(actorIndex != 0)    //checa se o ator ja foi insertido
                auxActor = newActor(name, actorIndex);
            else {                       //caso nao seja nenhuma opcao anterior, insere um novo ator
                auxActor = newActor(name, graph->actorlist.nActor);
                insertActor(graph, auxActor);
            }   
            
            auxEdge = newEdge(auxActor, auxMovie);
            insertEdge(graph, auxEdge);
            //printf("aresta entre %s e %s criada\n", graph->actorlist.list[auxEdge->actor_id]->name, graph->movieList.list[auxEdge->movie_id]->name);
        }


        if(auxchar == '\n') flag = 1;
        else if(auxchar == '/') flag = 0;

        free(name);
        name = (char*)malloc(200*sizeof(char));
    }
    return SUCCESS;
}

int getActor(Graph *graph, char *name){
    int i;
    for(i=0; i<graph->actorlist.nActor; i++){
        if(!strcmp(graph->actorlist.list[i]->name, name))
            return i;
    }

    return ERROR;
}


int printGraph(Graph *graph){
    if(!graph) return ERROR;
    int i;
    for(i =0; i <graph->actorlist.nActor; i++){
        printf("Ator: %s KB: %d \n",graph->actorlist.list[i]->name,graph->actorlist.list[i]->index);
    }

    /*for(i =0; i <graph->movieList.nMovie; i++){
        printf("Filme: %s\n",graph->movieList.list[i]->name);
    } */
    return SUCCESS;
}


void seachActorKB(Graph *graph, int origem){
    int i, orige, prox;
    Queue *fila = newQueue();
    int *cor = (int *)malloc(sizeof(int)*graph->actorlist.nActor);
    int *ante = (int *)malloc(sizeof(int)*graph->actorlist.nActor);
    for(i = 0 ; i < graph->actorlist.nActor;i++){
        cor[i] = 0;
        ante[i] = -1;
    }
    
    /*coloca a cor cinza */
    cor[origem] = 1;
    push(fila,origem);

    while(fila->tam > 0){
        orige = pop(fila);
        
    }
}
