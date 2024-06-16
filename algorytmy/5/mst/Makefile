all: astyle

prim: prim.c 
	gcc -Wpedantic -Wall -Wextra -o prim  prim.c

clean:
	rm prim *.orig 

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name prim.c generate_graph.h 

