/* Igor Guilherme Pereira Loredo - 11275071 */
/* Natã Silva Botelho            - 11275105 */

#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
/*create and return a new graph*/
Graph *newGraph(){
    Graph *graph = (Graph*)calloc(1, sizeof(Graph));
    graph->nodeList.list = (Node**) malloc (sizeof(Node*));
    graph->nodeList.list[0] = (Node*) malloc (sizeof(Node));
    graph->nodeList.list[0]->type = 0;
    return graph;
}

/*return a new edge*/
Edge *newEdge(int index){
    Edge *new = (Edge*)malloc(sizeof(Edge));
    new->id = index;
    new->next = NULL;
    return new;
}

/*return a new node*/
Node *newNode(char *name, int index, int type){
    Node *new  = (Node*)malloc(sizeof(Node));
    new->name = (char*) malloc (strlen(name)+1);
    memcpy(new->name, name, strlen(name));
    new->index = index;
    new->type = type;
    new->head = NULL;

    return new;
}

/*insert a node in the graph*/
int insertNode(Graph *graph, Node *newNode){
    char *kevinB = "Bacon, Kevin";

    if(strcmp(newNode->name, kevinB) != 0){
        graph->nodeList.list = (Node**) realloc (graph->nodeList.list, sizeof(Node*)*(graph->nodeList.nNodes+2));
        graph->nodeList.nNodes++; 
    }

    graph->nodeList.list[newNode->index] = newNode;
    
    return SUCCESS;
}

/*insert biderecional edges between a node and its destination*/
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

/*check if an actor is inserted in the graph*/
int checkActor(Graph *graph, char *name){
    int i;
    
    for(i=0; i < graph->nodeList.nNodes; i++){
        if(graph->nodeList.list[i]->type == ACTOR && !strcmp(graph->nodeList.list[i]->name, name))
            return i;
    }
    return 0;
}

/*read data from the input file and insert data on the graph*/
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

            if(!strcmp(name, kevinB)){   /*check if it's kevin bacon*/
                auxNode = newNode(name, 0, ACTOR);
                if(graph->nodeList.list[0]->type == 0)   { 
                    insertNode(graph, auxNode);
                }
            }
            else if(actorIndex != 0)    /*check if the actor is aready inserted*/
                auxNode = newNode(name, actorIndex, ACTOR);
            else {                       /*if it's none of the previous options, insert a new actor*/
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

/*return the index of an actor by name*/
int getActor(Graph *graph, char *name){
    int i;
    for(i=0; i<graph->nodeList.nNodes; i++){
        if(graph->nodeList.list[i]->type == ACTOR && !strcmp(graph->nodeList.list[i]->name, name))
            return i;
    }
    return ERROR;
}

/*check if the node in the passed index exist and then point to its head*/
int first_adj(Graph *graph, int v, Edge **pointer){
    if(graph->nodeList.list[v]->head){
        (*pointer) = graph->nodeList.list[v]->head;
        return (*pointer)->id;
    }
    return ERROR;
}

/*run through the nodes, points to the next node attached and return the id*/
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
        color[i] = WHITE;
        path[i] = -1;
    }
    
    /*mark node with grey color*/
    color[index] = GREY;
    push(queue, index);

    /*depth-first search*/
    while(!empty(queue)){
        index = pop(queue);
        pointer = first_adj(graph, index, &auxPointer);

        while(pointer != ERROR){
            if(color[pointer] == WHITE){
                color[pointer] = GREY;
                push(queue, pointer);
                path[pointer] = index;  /*array that stores the path*/
            }
            pointer = next_adj(graph, &auxPointer);
        }    
        color[index] = BLACK;
    }

    if(path[0] == -1){
        printf("%s there's no conexion with Kevin Bacon!\n", graph->nodeList.list[origin]->name);
        return;
    }

    /*track = array with the traveled path until KB*/
    aux = path[0];
    kb = 0;
    pointer = 0;
    while(aux != -1){
        track[kb] = aux;
        aux = path[aux];
        kb++;
    }

    printf("\n\n%s has KB = %d\n", graph->nodeList.list[origin]->name, kb/2);
    for(i=kb-1; i>=0; i--){
        aux = track[i];
        if(graph->nodeList.list[aux]->type == ACTOR){
            printf("%s ", graph->nodeList.list[aux]->name);
        }
        else if(graph->nodeList.list[aux]->type == MOVIE){
            printf(" acted on %s with ", graph->nodeList.list[aux]->name);
        }
        if(i%2 == 1 && i<kb-1){
            printf("\n");
            printf("%s ", graph->nodeList.list[aux]->name);
        }
    }
    printf("%s \n", graph->nodeList.list[0]->name);
}

/*calculates the world of kevin bacon*/
void getKBworld(Graph *graph, int origin){
    int i, pointer;
    Edge *auxPointer;
    int aux_seach, cont, correct = 0;
    float sum = 0, mean = 0, desvion = 0;

    int *dist = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);
    memset(dist,-1,(sizeof(int))*graph->nodeList.nNodes);
    
    Queue *queue = newQueue();
    int *color = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);
    int *prev = (int *)malloc(sizeof(int)*graph->nodeList.nNodes);
    
    memset(color, WHITE, (sizeof(int))*graph->nodeList.nNodes);
    memset(prev, -1, (sizeof(int))*graph->nodeList.nNodes);

    color[origin] = GREY;
    push(queue, origin);

    while(!empty(queue)){
        origin = pop(queue);
        pointer = first_adj(graph, origin, &auxPointer);
        while(pointer != ERROR){
            if(color[pointer] == WHITE){
                color[pointer] = GREY;
                push(queue, pointer);
                prev[pointer] = origin;
            }
            pointer = next_adj(graph, &auxPointer);   
        }    
        color[origin] = BLACK;
    }

    /*search actors that doesn't have a connection and calculates the mean with the kb values*/
    for(i = 0; i < graph->nodeList.nNodes; i++){
        aux_seach = prev[i];
        cont = 0;

        if(aux_seach == -1) /*check those with kb = 0*/
            correct++;  /*number of actors that doesn't have a connection with KB*/

        while(aux_seach != origin &&  aux_seach != -1){
            cont+=1;            
            aux_seach = prev[aux_seach];
        }

        sum += cont/2;
        dist[i] = (cont/2);
    } 
    mean = (float)(sum/(graph->nodeList.nNodes  - correct)); 
  
    /*sum values and mean calc*/
    for(i = 0; i < graph->nodeList.nNodes; i++){
        if(dist[i] != -1)
            desvion += pow(dist[i] - mean, 2);
    }
    desvion = sqrt((desvion/(graph->nodeList.nNodes)));

    printf("\nMean numbers of Kevin Bacon: %f", mean);
    printf("\nStandard deviation numbers of Kevin Bacon: %f", desvion);
}

/*free the memory of the whole graph*/
void freeGraph(Graph *graph){
    int i;
    for(i =0;i<graph->nodeList.nNodes;i++){
        free(graph->nodeList.list[i]);
    }
    free(graph);
}