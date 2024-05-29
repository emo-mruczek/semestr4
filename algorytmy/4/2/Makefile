all: bst

bst: astyle bst.c asc ran
	gcc -Wpedantic -Wall -Wextra -o bst bst.c

asc: generate_ascending.c
	gcc -Wpedantic -Wall -Wextra -o generate_ascending generate_ascending.c

ran: generate_random.c
	gcc -Wpedantic -Wall -Wextra -o generate_random generate_random.c

clean:
	trash bst generate_ascending generate_random

astyle:
	astyle bst.c generate_ascending.c generate_random.c

