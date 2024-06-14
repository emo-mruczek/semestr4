all: prim

prim: astyle prim.c 
	gcc -Wpedantic -Wall -Wextra -o prim  prim.c

clean:
	trash *.o prim *.orig

astyle:
	astyle --style=attach --break-blocks --pad-oper --pad-header --align-pointer=name --align-reference=name prim.c

