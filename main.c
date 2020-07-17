#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>


int  main() {

    char *name = (char*) malloc (50);
    int id;
    Movie *movie;
    Actor *actor;
    Edge *edge;
    Graph *graph = newGraph();

    printf("%d %d\n", graph->actorlist.nActor, graph->movieList.nMovie);

    scanf(" %[^\n]", name);
    movie = newMovie(name, graph->movieList.nMovie);
    printf("%s\n", movie->name);

    insertMovie(graph, movie);

    scanf(" %[^\n]", name);
    actor = newActor(name, graph->actorlist.nActor);
    printf("%s\n", actor->name);

    insertActor(graph, actor);

    edge = newEdge(*actor, *movie);

    insertEdge(graph, edge, 0);



    return 0;
} 