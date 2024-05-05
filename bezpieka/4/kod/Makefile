all: main

main: main.c RSA_lib.o
	gcc -o main main.c RSA_lib.o -lm

RSA_lib.o: RSA_lib.c RSA_lib.h
	gcc -c -o RSA_lib.o RSA_lib.c -lm

clean: 
	rm -f main RSA_lib.o
