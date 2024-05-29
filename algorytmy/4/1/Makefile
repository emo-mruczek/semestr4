all: bst

bst: astyle bst.c asc
	gcc -Wpedantic -Wall -Wextra -o bst bst.c

asc: generate_ascending.c
	gcc -Wpedantic -Wall -Wextra -o generate_ascending generate_ascending.c

clean:
	rm -f bst

astyle:
	astyle bst.c generate_ascending.c

