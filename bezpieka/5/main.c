#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "rc4.h"

void test_key() {
    char *input1 = "hahapapiez";
    char *input2 = "twojastara";
    char *key = "dupa";

    unsigned char *output1 = malloc(sizeof(int) * strlen(input1));
    unsigned char *output2 = malloc(sizeof(int) * strlen(input2));

    encode_rc4(input1, output1, key);
    encode_rc4(input2, output2, key);

    bool ok = is_same_key(output1, output2);
    
    if (ok) {
        printf("Git");
    } else {
        printf("Niegit");
    }
} 


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

    char *encoded = (char *)malloc(strlen(input));

    decode_rc4(output, encoded, key);

    printf("%s\n", encoded);


    test_key();

    free(output);
    return 0;
}
