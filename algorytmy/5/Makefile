all: generate_graph

generate_graph: astyle generate_graph.c
	gcc -Wpedantic -Wall -Wextra -o generate_graph generate_graph.c

clean:
	trash generate_graph

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name generate_graph.c

