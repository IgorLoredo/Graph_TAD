#ifndef _GRAPH_KB
#define _GRAPH_KB

//MACROS
#define ERROR -1
#define SUCCESS 1

//STRUCTS
typedef struct edge Edge;
struct edge{
    int actor_id;
    int movie_id;
    int KB;
    Edge *next;
};

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
}List_actor;

typedef struct graph{
   List_actor actorlist;
   List_movie movieList;
}Graph;

//FUNCOES
Graph *newGraph();

Edge *newEdge(Actor *, Movie *);

Actor *newActor(char *, int);

Movie *newMovie(char *, int);

int insertActor(Graph *, Actor *);

int insertMovie(Graph *, Movie *);

int insertEdge(Graph *, Edge *);

int checkActor(Graph *, char *);

int insertGraph();

int readData(Graph *);

int getActor(Graph *, char*);

int printGraph(Graph *);

void seachActorKB(Graph *, int );

#endif
