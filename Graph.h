#ifndef _GRAPH_KB
#define _GRAPH_KB

#define ERROR -1
#define SUCCESS 1

typedef struct actor{
    char *name;
    int index;
}Actor;

typedef struct movie{
    char *name;
    int index;
}Movie;

typedef struct node Node;
struct node{
    int actor_id;
    int movie_id;
    int KB;
    Node *next;
};

typedef struct graph{
   Node **list;
   int nElement;
}Graph;

Graph *newGraph();

Node *newNode(Actor, Movie);

int insertGraph(Node);

#endif
