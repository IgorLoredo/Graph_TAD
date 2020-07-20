/* Igor Guilherme Pereira Loredo - 11275071 */
/* Natã Silva Botelho            - 11275105 */

#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
Graph *newGraph(){
    Graph *graph = (Graph*)calloc(1, sizeof(Graph));
    return graph;
}

Edge *newEdge(int actorIndex, int movieIndex){
    Edge *new = (Edge*)malloc(sizeof(Edge));
    new->actor_id = actorIndex;
    new->movie_id = movieIndex;
    new->next = NULL;
    return new;
}

Node *newNode(char *name, int index, int type){
    Node *new  = (Node*)malloc(sizeof(Node));
    new->name = (char*) malloc (strlen(name));
    memcpy(new->name, name, strlen(name));
    new->index = index;
    new->type = type;
    new->head = NULL;

    return new;
}

/*
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
}*/

int insertNode(Graph *graph, Node *newNode){
    graph->nodeList.list = (Node**) realloc (graph->nodeList.list, sizeof(Node*)*(graph->nodeList.nNodes+1));
    graph->nodeList.list[graph->nodeList.nNodes] = newNode;
    graph->nodeList.nNodes++;
    
    return SUCCESS;
}

int insertEdge(Graph *graph, Edge *edge){
    if(!graph || !edge) return ERROR;
    
    Edge *auxEdge = (Edge*) malloc (sizeof(Edge));
    memcpy(auxEdge, edge, sizeof(Edge));

    edge->next = graph->nodeList.list[edge->actor_id]->head;
    graph->nodeList.list[edge->actor_id]->head = edge;

    auxEdge->next = graph->nodeList.list[edge->movie_id]->head;
    graph->nodeList.list[edge->movie_id]->head = auxEdge;

    /*edge->next = graph->actorlist.list[edge->actor_id]->head;
    graph->actorlist.list[edge->actor_id]->head = edge;;
    
    movieEdge->next = graph->movieList.list[edge->movie_id]->head;
    graph->movieList.list[movieEdge->movie_id]->head = movieEdge;*/

    //printf("ator %s conectado no filme %s, filme %s conectado em ator %s\n", graph->nodeList.list[edge->actor_id]->name, graph->nodeList.list[edge->movie_id]->name, graph->nodeList.list[edge->movie_id]->name, graph->nodeList.list[edge->actor_id]->name);

    return SUCCESS;
}

int checkActor(Graph *graph, char *name){
    int i;
    
    for(i=0; i < graph->nodeList.nNodes; i++){
        if(graph->nodeList.list[i]->type == ACTOR && !strcmp(graph->nodeList.list[i]->name, name))
            return i;
    }

    return 0;
}


int readData(Graph *graph){ 
    char *name = (char*)malloc(200*sizeof(char));
    char *kevinB = "Bacon, Kevin";
    char auxchar;
    int flag = 1, actorIndex, movieIndex;
    /*Movie *auxMovie;
    Actor *auxActor;*/
    Node *auxNode;
    Edge *auxEdge;
    FILE *datafile = fopen("input-top-grossing.txt", "r");
    
    while (fscanf(datafile, "%[^/||^\n]%c", name, &auxchar) != EOF) {
        if(flag){
            auxNode = newNode(name, graph->nodeList.nNodes, MOVIE);
            insertNode(graph, auxNode);
            movieIndex = auxNode->index;
            //auxMovie = newMovie(name, graph->movieList.nMovie);
            //insertMovie(graph, auxMovie);
        }
        else{
            actorIndex = checkActor(graph, name);

            if(!strcmp(name, kevinB)){   //checa se e o kevin bacon
                auxNode = newNode(name, 0, ACTOR);
                if(!graph->nodeList.list[0])    
                    insertNode(graph, auxNode);
            }
                //auxActor = newActor(name, 0);
            else if(actorIndex != 0)    //checa se o ator ja foi insertido
                auxNode = newNode(name, actorIndex, ACTOR);
                //auxActor = newActor(name, actorIndex);
            else {                       //caso nao seja nenhuma opcao anterior, insere um novo ator
                auxNode = newNode(name, graph->nodeList.nNodes, ACTOR);
                insertNode(graph, auxNode);
                //auxActor = newActor(name, graph->actorlist.nActor);
                //insertActor(graph, auxActor);
            }   
            
            auxEdge = newEdge(auxNode->index, movieIndex);
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
    for(i=0; i<graph->nodeList.nNodes; i++){
        if(graph->nodeList.list[i]->type == ACTOR && !strcmp(graph->nodeList.list[i]->name, name))
            return i;
    }

    return ERROR;
}


int printGraph(Graph *graph){
    if(!graph) return ERROR;
    int i;
    for(i = 0; i <graph->nodeList.nNodes; i++){
        printf("Ator: %s KB: %d \n",graph->nodeList.list[i]->name, graph->nodeList.list[i]->index);
    }

    /*for(i =0; i <graph->movieList.nMovie; i++){
        printf("Filme: %s\n",graph->movieList.list[i]->name);
    } */
    return SUCCESS;
}

Edge *first_adj(Graph *graph, int v){
    if(graph->nodeList.list[v]->head)
        return graph->nodeList.list[v]->head;

    return NULL;
}

Edge *next_adj(Graph *graph, Edge *pointer){
    if(pointer->next)
        return pointer->next;

    return NULL;
}

void searchActorKB(Graph *graph, int index){
    int i, pointer;
    Edge *auxPointer;

    Queue *queue = newQueue();
    int *color = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);
    int *prev = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);

    for(i = 0 ; i < graph->nodeList.nNodes; i++){
        color[i] = 0;
        prev[i] = -1;
    }
    
    /*coloca a cor cinza */
    color[index] = 1;
    push(queue, index);

    while(queue->tam >= 0){
        index = pop(queue);
        auxPointer = first_adj(graph, index);
        color[auxPointer->movie_id] = 1;
        push(queue, auxPointer->movie_id);

        while(auxPointer){
            pointer = auxPointer->actor_id;
            if(color[pointer] == 0){
                color[pointer] = 1;
                push(queue, pointer);
                prev[pointer] = index;
            }
            auxPointer = next_adj(graph, auxPointer);
        }
        color[pointer] = 2;
    }
    if(prev[0] == -1){
        printf("Ator nao tem ligacao com Kevin Bacon\n");
    }

}
