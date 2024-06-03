all: splay

splay: astyle splay.c asc ran tests
	gcc -Wpedantic -Wall -Wextra -o splay splay.c

asc: generate_ascending.c
	gcc -Wpedantic -Wall -Wextra -o generate_ascending generate_ascending.c

ran: generate_random.c
	gcc -Wpedantic -Wall -Wextra -o generate_random generate_random.c

tests: tests.c
		gcc -Wpedantic -Wall -Wextra -fopenmp -o tests tests.c -ldl

clean:
	trash splay generate_ascending generate_random *.orig tests

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name splay.c generate_ascending.c generate_random.c tests.c
 
