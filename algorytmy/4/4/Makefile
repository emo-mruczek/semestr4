all: rb

rb: astyle rb.c asc ran tests
	gcc -Wpedantic -Wall -Wextra -o rb rb.c

asc: generate_ascending.c
	gcc -Wpedantic -Wall -Wextra -o generate_ascending generate_ascending.c

ran: generate_random.c
	gcc -Wpedantic -Wall -Wextra -o generate_random generate_random.c

tests: tests.c
	gcc -Wpedantic -Wall -Wextra -fopenmp -o tests tests.c -ldl

clean:
	trash rb generate_ascending generate_random tests *.orig

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name rb.c generate_ascending.c generate_random.c tests.c

