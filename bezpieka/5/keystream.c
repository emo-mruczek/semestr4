#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// w ogóle gówniana ta implementacja, bo zakladam, ze musza byc tej samej dlugosci
// also bez sensu to dziala, bo i tak musze na to patrzec samemu i zdecydowac, czy to ma sens???
// nie mam pojecia, jak to sprawdzic w ogole

// straight from internet cuz it was boring to write myself

int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

// tez z neta!
unsigned char* hexStringToBytes(const char* hexStr, size_t* byteArrayLength) {
    size_t hexStrLength = strlen(hexStr);
    if (hexStrLength % 2 != 0) {
        return NULL;
    }

    *byteArrayLength = hexStrLength / 2;
    unsigned char* byteArray = (unsigned char*)malloc(*byteArrayLength);

    for (size_t i = 0; i < *byteArrayLength; ++i) {
        int highNibble = hexCharToInt(hexStr[2 * i]);
        int lowNibble = hexCharToInt(hexStr[2 * i + 1]);

        if (highNibble == -1 || lowNibble == -1) {
            free(byteArray);
            return NULL;
        }

        byteArray[i] = (highNibble << 4) | lowNibble;
    }

    return byteArray;
}

// you guess - not mine either
void xorAndPrint(const unsigned char* byteArray1, const unsigned char* byteArray2, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%02x", byteArray1[i] ^ byteArray2[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {

    /*if (argc < 3) {
        fprintf(stderr, "Enter two valid cryptograms.");
    }

    char *first = argv[1];
    char *second = argv[2];*/

    const char* hexCiphertext1 = "99 C9 19 6F 4A 4A F1 5E 10 F5";
    const char* hexCiphertext2 = "85 DF 1E 64 5B 58 F5 56 07 EE";

    size_t length1, length2;
    unsigned char* ciphertext1 = hexStringToBytes(hexCiphertext1, &length1);
    unsigned char* ciphertext2 = hexStringToBytes(hexCiphertext2, &length2);

    if (!ciphertext1 || !ciphertext2) {
        fprintf(stderr, "Invalid hex string.\n");
        return 1;
    }

    if (length1 != length2) {
        fprintf(stderr, "Ciphertexts must be of the same length.\n");
        free(ciphertext1);
        free(ciphertext2);
        return 1;
    }


    xorAndPrint(ciphertext1, ciphertext2, length1);

    free(ciphertext1);
    free(ciphertext2);

    // encr xor encr = (plain xor key) xor (plain xor key) = plain xor plain
    return 0;
}
