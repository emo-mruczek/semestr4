all: main

main: main.c rc4.o
	gcc -o main main.c rc4.o

rc4.o: rc4.c rc4.h
	gcc -c -o rc4.o rc4.c 

clean:
	rm -f main *.o
