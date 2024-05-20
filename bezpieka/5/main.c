#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "rc4.h"

int main(int argc, char **argv) {
    
     if (argc < 3) {
        fprintf(stderr, "Enter name of a file.");
    }
/*
    char *name = argv[1];
    FILE *fptr = NULL;
    fptr = fopen(name, "r");

    if (!fptr) {
        fprintf(stderr, "Opening a file %s failed.", name);
    }

    fseek(fptr, 0, SEEK_END);
    uint32_t size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *input = (char*)malloc(size);
    fread(input, 1, size, fptr);
    fclose(fptr);
    char *key = "dupa";
    char *output = malloc(sizeof(int) * size);

    encode_rc4(input, output, key);
    

    printf("%d %d %d %d\n", key[0], key[1], key[2], key[3] );*/

    char *key = argv[1];
    char *input = argv[2];

    unsigned char *output = malloc(sizeof(int) * strlen(input));

    printf("%s\n", input);

    encode_rc4(input, output, key);

    for (size_t i = 0; i < strlen(input); i++) {
        printf("%02hhX ", output[i]);
    }

    free(output);
    return 0;
}
