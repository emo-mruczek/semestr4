all: main

main: main.cpp RSA_lib.o
	g++ -o main main.cpp RSA_lib.o -lm

RSA_lib.o: RSA_lib.cpp RSA_lib.h
	g++ -c -o RSA_lib.o RSA_lib.cpp -lm

clean: 
	rm -f main RSA_lib.o
