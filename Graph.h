/* Igor Guilherme Pereira Loredo - 11275071 */
/* Natã Silva Botelho            - 11275105 */

#ifndef _GRAPH_KB
#define _GRAPH_KB

//MACROS
#define ERROR -1
#define SUCCESS 1
#define ACTOR 1
#define MOVIE 2

//STRUCTS
typedef struct edge Edge;
struct edge{
    int actor_id;
    int movie_id;
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

/*
typedef struct actor{
    char *name;
    int index;
    Edge *head;
}Actor;


typedef struct movie{
    char *name;
    int index;
    Edge *head;
}Movie;

typedef struct list_movie{
   Movie **list;
   int nMovie;
}List_movie;

typedef struct list_actor{
   Actor **list;
   int nActor;
}List_actor; */

typedef struct graph{
   //List_actor actorlist;
   //List_movie movieList;
   List nodeList;
}Graph;

//FUNCOES
Graph *newGraph();

Edge *newEdge(int, int);

Node *newNode(char*, int, int);
/*Actor *newActor(char *, int);

Movie *newMovie(char *, int);

int insertActor(Graph *, Actor *);

int insertMovie(Graph *, Movie *);*/

int insertNode(Graph *, Node *);

int insertEdge(Graph *, Edge *);

int checkActor(Graph *, char *);

int readData(Graph *);

int getActor(Graph *, char*);

int printGraph(Graph *);

void searchActorKB(Graph *, int );

void getKBworld(Graph *, int);

void freeGraph(Graph*);

#endif
