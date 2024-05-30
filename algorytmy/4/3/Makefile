all: rb

rb: astyle rb.c asc ran
	gcc -Wpedantic -Wall -Wextra -o rb rb.c

asc: generate_ascending.c
	gcc -Wpedantic -Wall -Wextra -o generate_ascending generate_ascending.c

ran: generate_random.c
	gcc -Wpedantic -Wall -Wextra -o generate_random generate_random.c

clean:
	trash rb generate_ascending generate_random *.orig

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name rb.c generate_ascending.c generate_random.c

