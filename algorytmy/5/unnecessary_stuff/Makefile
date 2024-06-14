all: prim

prim: astyle generate_graph.o prim.c 
	gcc -Wpedantic -Wall -Wextra -o prim generate_graph.o prim.c

generate_graph: generate_graph.c
	gcc -Wpedantic -Wall -Wextra -c generate_graph.o generate_graph.c

clean:
	trash *.o prim *.orig

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name generate_graph.c generate_graph.h prim.c

