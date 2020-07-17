#ifndef _GRAPH_KB
#define _GRAPH_KB

#define ERROR -1
#define SUCCESS 1

#include <stdlib.h>
#include <stdio.h>

typedef struct actor{
    char *name;
    int index;
}Actor;

typedef struct movie{
    char *name;
    int index;
}Movie;

typedef struct edge Edge;
struct edge{
    int actor_id;
    int movie_id;
    int KB;
    Edge *next;
};

typedef struct list_movie{
   Movie **list;
   int nMovie;
}List_movie;

typedef struct list_actor{
   Actor **list;
   int nActor;
}List_actor;

typedef struct graph{
   Edge **list;
   int nElement;
   List_movie movieList;
   List_actor actorList;
}Graph;

Graph *newGraph();

Edge *newEdge(Actor, Movie);

Actor *newActor(char *, int);

Movie *newMovie(char *, int);

int insertGraph(Node);

int readKB(FILE *,Graph*,List_movie*,List_actor*);




#endif
