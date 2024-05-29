all: bst

bst: astyle bst.c asc ran tests
	gcc -Wpedantic -Wall -Wextra -o bst bst.c

asc: generate_ascending.c
	gcc -Wpedantic -Wall -Wextra -o generate_ascending generate_ascending.c

ran: generate_random.c
	gcc -Wpedantic -Wall -Wextra -o generate_random generate_random.c

tests: tests.c
	gcc -Wpedantic -Wall -Wextra -fopenmp -o tests tests.c -ldl

clean:
	trash bst generate_ascending generate_random tests

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name bst.c generate_ascending.c generate_random.c tests.c

