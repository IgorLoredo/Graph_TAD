#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

void menu(){
    printf("\n    Six Degrees of Kevin Bacon");
    printf("\n    Numero de Kevin Bacon      - 1");
    printf("\n    Mundo de Kevin Bacon - 2");
    printf("\n    Terminar - 3\n");
}

void menuInsert(){
    printf("\n    Inserir Arquivo - 1");
    printf("\n    Inserir manual - 2");
    printf("\n    Sair           - 3\n");
}

int main() {
    Graph *graph = newGraph(); 

    readData(graph);
    seachActorKB(graph,0);
    /*int flag = 1;
    char *nome = (char*)malloc(200*sizeof(char));
    do{
       menu();
       scanf("%d",&flag);
       if(flag == 1){
           menuInsert();
           scanf("%d", &flag);
 printGraph(graph);
   }while(flag); */

  

   return 0;
} 