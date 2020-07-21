/* Igor Guilherme Pereira Loredo - 11275071 */
/* Natã Silva Botelho            - 11275105 */

#ifndef _GRAPH_KB
#define _GRAPH_KB

//MACROS
#define ERROR -1
#define SUCCESS 1
#define ACTOR 1
#define MOVIE 2
#define BRANCO 0
#define CINZA 1
#define PRETO 2

//STRUCTS
typedef struct edge Edge;
struct edge{
    int id;
    Edge *next;
};

typedef struct node{
    char *name;
    int index;
    int type;
    Edge *head;
}Node;

typedef struct list{
    Node **list;
    int nNodes;
}List;

typedef struct graph{
   List nodeList;
}Graph;

//FUNCOES
Graph *newGraph();

Edge *newEdge(int);

Node *newNode(char*, int, int);

int insertNode(Graph *, Node *);

int insertEdge(Graph *, Edge *, int);

int checkActor(Graph *, char *);

int readData(Graph *);

int getActor(Graph *, char*);

int printGraph(Graph *);

int first_adj(Graph *, int, Edge **);

int next_adj(Graph *, Edge **);

void searchActorKB(Graph *, int );

void getKBworld(Graph *, int);

void freeGraph(Graph*);

#endif
