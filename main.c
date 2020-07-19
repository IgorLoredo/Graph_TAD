#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

void menu(){
    printf("\n    Six Degrees of Kevin Bacon");
    printf("\n    Inserir      - 1");
    printf("\n    Calcular KB - 2");
    printf("\n    Terminar - 3\n");
}

void menuInsert(){
    printf("\n    Inserir Arquivo - 1");
    printf("\n    Inserir manual - 2");
    printf("\n    Sair           - 3\n");
}

int main() {
    Graph *graph = newGraph(); 
    /*int flag = 1;
    char *nome = (char*)malloc(200*sizeof(char));
    do{
       menu();
       scanf("%d",&flag);
       if(flag == 1){
           menuInsert();
           scanf("%d", &flag);

   }while(flag); */
   readData(graph);
   printGraph(graph);
   return 0;
} 