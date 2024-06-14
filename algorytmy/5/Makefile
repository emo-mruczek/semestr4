all: astyle

tests: tests.c
	gcc -Wpedantic -Wall -Wextra -fopenmp -o tests tests.c -ldl

kruskal: kruskal.c
	gcc -Wpedantic -Wall -Wextra -o kruskal kruskal.c

prim: prim.c 
	gcc -Wpedantic -Wall -Wextra -o prim  prim.c

clean:
	rm kruskal prim tests *.orig 

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name prim.c generate_graph.h kruskal.c prim.h kruskal.h tests.c

