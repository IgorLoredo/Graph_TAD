/* Igor Guilherme Pereira Loredo - 11275071 */
/* Natã Silva Botelho            - 11275105 */

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

void menu(){
    printf("\n Six Degrees of Kevin Bacon\n");
    printf("\n    Numero de Kevin Bacon - 1");
    printf("\n    Mundo de Kevin Bacon  - 2");
    printf("\n    Terminar              - 3\n");
}

int main() {
    Graph *graph = newGraph(); 
    readData(graph);

    int option = 0, actorIndex;
    char *actorName = (char*) malloc (200*sizeof(char)); 

    while(option != 3){
        menu();
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Insira o nome do ator que deseja saber o KB:\n");
            scanf(" %[^\n]s", actorName);
            actorIndex = getActor(graph, actorName);
            if(actorIndex < 0){
                printf("Ator nao encontrado!\n");
                break;
            }
            searchActorKB(graph, actorIndex);
            break;
        
        case 2:
            /*colocar o index do bk*/
            //getKBworld(graph, 0);
            break;
            
        default:
            break;
        }
    }

    freeGraph(graph);
    free(actorName);

    return 0;
} 