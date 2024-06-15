 
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "generate_graph.h"
#include "kruskal.h"
#include "prim.h"

int main() {

 uint64_t n = 10000;

            printf("test");

            double **graph = (double **)malloc(n *sizeof(double *));

            for (int i = 0; i < n; i++) {
                graph[i] = (double *)malloc(n *sizeof(double));
            }

    make_graph(n, graph);

    printf("\nGraf:\n");

   // for (int i = 0; i < n; i++) {
      //  for (int j = 0; j < n; j++) {
    //        printf("%.6f ", graph[i][j]);
  //      }
//
     //   printf("\n");
    //}



            printf("test1\n");

            kruskalMST(n, graph);
printf("dupadupa\n");
    primMST(n, graph);
printf("testststs\n");
    
            for (int i = 0; i < n; i++) {
                free(graph[i]);
            }

            free(graph);

    return 0;
}
