#ifndef Graph
#define Graph


#define ERRO -1
#define SUCESS 1

typedef struct node{
    struct *node;
    int id;
    char *Element;
}Node;


typedef struct graph{
   Node **root;
   int nElement;
}Graph;

Graph *newGraph();

Node *newNode(Char *element,int id);

int addGraph(Graph *,Node*);



#endif
