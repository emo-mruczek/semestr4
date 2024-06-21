//https://github.com/Abhinavvenkatadri/03-Data-Structures/blob/master/Lec%2011%20-%20Miscellaneous%20Problems%20BT/9_Pass_information_to_all_nodes.cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <inttypes.h>
#include "generate_graph.h"

int64_t max_value_of_two(int64_t a, int64_t b) {
    return (a > b ? a : b);
}

int64_t max_value(int64_t *rounds, int64_t size) {
    int64_t max_round = rounds[0];

    for (int64_t i = 1; i < size; i++) {
        if (max_round < rounds[i]) {
            max_round = rounds[i];
        }
    }

    return max_round;
}

int64_t make_round(int64_t vertice, bool *VISITED, bool MST[7][7], int64_t size) {

    int64_t rounds = -1;
    int64_t *children_rounds = (int64_t *)malloc(size *sizeof(int64_t));
    VISITED[vertice] = true;

    int64_t ind = 0;

    for (int64_t i = 0; i < size; i++ ) {
        if (MST[vertice][i] == true) {
            if (VISITED[i] == false) {
                int64_t child_rounds = make_round(i, VISITED, MST, size);
                children_rounds[ind] = child_rounds;
                ind++;
            }
        }
    }

    if (ind != 0) {
        rounds = max_value(children_rounds, ind);
        rounds = max_value_of_two(rounds, ind);
    }

    free(children_rounds);

    return rounds + 1;
}

int64_t calculate_rounds(bool MST[7][7], int64_t size) {
    printf("\nLicze liczbe rund...\n");

    bool *VISITED = (bool *)malloc(size *sizeof(int64_t));

    int64_t rand_vertice = 0;

    printf("Wybrany wierzcholek: %" PRId64, rand_vertice);

    for (int64_t i = 1; i < size; i++) {
        VISITED[i] = false;
    }

    int64_t min_rounds = make_round(rand_vertice, VISITED, MST, size);

    free(VISITED);

    return min_rounds;
}

int main() {
    printf("\nMST:\n");
    printf("wierzcholek \twaga\n");


    int64_t size = 7;

  

   bool MST[7][7] = {{0,1,0,1,0,1,0},{1,0,1,0,0,0,0}, {0,1,0,0,0,0,0}, {1,0,0,0,1,0,0}, {0,0,0,1,0,0,0}, {1,0,0,0,0,0,1}, {0,0,0,0,0,1,0}};

    


    printf("\nMST:\n");

    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            printf("%d ", MST[i][j]);
        }

        printf("\n");
    }

    int64_t rounds = calculate_rounds(MST, size);

    printf("\nPotrzebne rundy: %" PRIu64 "\n", rounds);




    return 0;
}


