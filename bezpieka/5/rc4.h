#ifndef RC4_H
#define RC4_H

void encode_rc4(char *input, unsigned char *output, char *key);

void decode_rc4(unsigned char *input, char *output, char *key);

bool is_same_key(unsigned char *input1, unsigned char *input2);  
#endif
