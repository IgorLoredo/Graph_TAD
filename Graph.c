/* Igor Guilherme Pereira Loredo - 11275071 */
/* Natã Silva Botelho            - 11275105 */

#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
Graph *newGraph(){
    Graph *graph = (Graph*)calloc(1, sizeof(Graph));
    graph->nodeList.list = (Node**) malloc (sizeof(Node*));
    graph->nodeList.list[0] = (Node*) malloc (sizeof(Node));
    graph->nodeList.list[0]->type = 0;
    return graph;
}

Edge *newEdge(int index){
    Edge *new = (Edge*)malloc(sizeof(Edge));
    new->id = index;
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

int insertNode(Graph *graph, Node *newNode){
    char *kevinB = "Bacon, Kevin";

    if(strcmp(newNode->name, kevinB) != 0){
        graph->nodeList.list = (Node**) realloc (graph->nodeList.list, sizeof(Node*)*(graph->nodeList.nNodes+2));
        graph->nodeList.nNodes++; 
    }

    graph->nodeList.list[newNode->index] = newNode;
    
    return SUCCESS;
}

int insertEdge(Graph *graph, Edge *edge, int index){
    if(!graph || !edge) return ERROR;
    
    Edge *auxEdge = (Edge*) malloc (sizeof(Edge));
    auxEdge->id = index;

    edge->next = graph->nodeList.list[index]->head;
    graph->nodeList.list[index]->head = edge;

    auxEdge->next = graph->nodeList.list[edge->id]->head;
    graph->nodeList.list[edge->id]->head = auxEdge;

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
    Node *auxNode;
    Edge *auxEdge;
    FILE *datafile = fopen("input-top-grossing.txt", "r");
    
    while (fscanf(datafile, "%[^/||^\n]%c", name, &auxchar) != EOF) {
        if(flag){
            auxNode = newNode(name, graph->nodeList.nNodes+1, MOVIE);
            insertNode(graph, auxNode);
            movieIndex = auxNode->index;
        }
        else{
            actorIndex = checkActor(graph, name);

            if(!strcmp(name, kevinB)){   //checa se e o kevin bacon
                auxNode = newNode(name, 0, ACTOR);
                if(graph->nodeList.list[0]->type == 0)   { 
                    insertNode(graph, auxNode);
                }
            }
            else if(actorIndex != 0)    //checa se o ator ja foi insertido
                auxNode = newNode(name, actorIndex, ACTOR);
            else {                       //caso nao seja nenhuma opcao anterior, insere um novo ator
                auxNode = newNode(name, graph->nodeList.nNodes+1, ACTOR);
                insertNode(graph, auxNode);
            }   
            
            auxEdge = newEdge(auxNode->index);
            insertEdge(graph, auxEdge, movieIndex);
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

int first_adj(Graph *graph, int v, Edge **pointer){
    if(graph->nodeList.list[v]->head){
        (*pointer) = graph->nodeList.list[v]->head;
        return (*pointer)->id;
    }

    return ERROR;
}

int next_adj(Graph *graph, Edge **pointer){
    if((*pointer)->next){
        (*pointer) = (*pointer)->next;
        return (*pointer)->id;
    }

    return ERROR;
}

void searchActorKB(Graph *graph, int index){
    int i, pointer, origin = index, aux, kb, track[20];
    Queue *queue = newQueue();
    Edge *auxPointer = (Edge*) malloc (sizeof(Edge));
    int *color = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);
    int *path = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);

    for(i = 0 ; i < graph->nodeList.nNodes; i++){
        color[i] = BRANCO;
        path[i] = -1;
    }
    
    /*coloca a cor cinza */
    color[index] = CINZA;
    push(queue, index);

    while(!empty(queue)){
        index = pop(queue);
        pointer = first_adj(graph, index, &auxPointer);

        while(pointer != ERROR){
            if(color[pointer] == BRANCO){
                color[pointer] = CINZA;
                push(queue, pointer);
                path[pointer] = index;
            }
            pointer = next_adj(graph, &auxPointer);
        }    
        color[index] = PRETO;
    }

    if(path[0] == -1){
        printf("%s nao tem conexao com Kevin Bacon\n", graph->nodeList.list[origin]->name);
        return;
    }

    aux = path[0];
    kb = 0;
    pointer = 0;
    while(aux != -1){
        track[kb] = aux;
        aux = path[aux];
        kb++;
    }

    printf("\n\n%s tem KB = %d\n", graph->nodeList.list[origin]->name, kb/2);
    for(i=kb-1; i>=0; i--){
        aux = track[i];
        if(graph->nodeList.list[aux]->type == ACTOR){
            printf("%s ", graph->nodeList.list[aux]->name);
        }
        else if(graph->nodeList.list[aux]->type == MOVIE){
            printf(" atuou em %s com ", graph->nodeList.list[aux]->name);
        }
        if(i%2 == 1 && i<kb-1){
            printf("\n");
            printf("%s ", graph->nodeList.list[aux]->name);
        }
    }
    printf("%s \n", graph->nodeList.list[0]->name);
}

/*
void getKBworld(Graph *graph, int origem){
    int i, pointer;
    Edge *auxPointer;

    Queue *queue = newQueue();
    int *color = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);
    int *prev = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);

    int *dist = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);

    for(i = 0 ; i < graph->nodeList.nNodes; i++){
        color[i] = 0;
        prev[i] = -1;
        dist[i] = -1;
    }
    
    coloca a cor cinza 
    color[origem] = 1;
    push(queue, origem);

     while(queue->tam >=0){
        origem = pop(queue);
       while(auxPointer != NULL){
            //pointer = auxPointer->actor_id;
            if(color[pointer] == 0){
                color[pointer] = 1;
                push(queue,pointer);
                prev[pointer] = origem;
            }

            auxPointer = next_adj(graph,auxPointer);
        }
     
       color[pointer] =2; 
    }

    for(i = 0; i < graph->nodeList.nNodes;i++){
        if(prev[i] != -1)
        printf("%d ", prev[i]);
    }
    int aux_seach, cont, correct = 0,sum =0;
    float mean = 0, desvion = 0;
    for(i = 0; i < graph->nodeList.nNodes; i++){
        aux_seach = prev[i];
        cont = 0;
        if(aux_seach == -1){
            correct++;
        }
        while(aux_seach != origem &&  aux_seach != -1){
            cont++;            
            aux_seach = prev[aux_seach];
             printf("cont : %d \n", cont);
        }
       
        sum += cont/2;
        dist[i] = (cont/2);

    }

     printf("sum %d\n", sum);
    mean =(float)(sum/(graph->nodeList.nNodes  - correct));
  
    for(i = 0; i < graph->nodeList.nNodes; i++){
        if(dist[i] != -1){
            desvion += pow(dist[i] - mean, 2);
        }
    }
    desvion = sqrt((desvion/(graph->nodeList.nNodes)));
    
    printf("\nMedia dos numeros de Kevin Bacon: %f", mean);
    printf("\nDesvio Padrao numeros de Kevin Bacon: %f", desvion);


}*/



void freeGraph(Graph *graph){
    int i;
    for(i =0;i<graph->nodeList.nNodes;i++){
        free(graph->nodeList.list[i]);
    }
    free(graph);
}