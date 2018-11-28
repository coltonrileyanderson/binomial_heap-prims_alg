OBJS = integer.o string.o real.o scanner.o sll.o dll.o stack.o queue.o bst.o gst.o avl.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : test-dll test-bst test-gst test-avl test-binomial binomial-0-0 binomial-1-10 prim

test-dll : test-dll.o integer.o real.o string.o dll.o
	gcc $(LOPTS) test-dll.o integer.o real.o string.o dll.o -o test-dll

test-bst : test-bst.o $(OBJS)
	gcc $(LOPTS) test-bst.o $(OBJS) -o test-bst

test-gst : test-gst.o $(OBJS)
	gcc $(LOPTS) test-gst.o $(OBJS) -o test-gst

test-avl : test-avl.o $(OBJS)
	gcc $(LOPTS) test-avl.o $(OBJS) -o test-avl

test-binomial : test-binomial.o $(OBJS) binomial.o
	gcc $(LOPTS) test-binomial.o $(OBJS) binomial.o -lm -o test-binomial

binomial-0-0 : binomial-0-0.o $(OBJS) binomial.o
	gcc $(LOPTS) binomial-0-0.o $(OBJS) binomial.o -lm -o binomial-0-0

binomial-1-10 : binomial-1-10.o $(OBJS) binomial.o
	gcc $(LOPTS) binomial-1-10.o $(OBJS) binomial.o -lm -o binomial-1-10

prim : prim.o $(OBJS) edge.o vertex.o
	gcc $(LOPTS) prim.o $(OBJS) edge.o vertex.o binomial.o -lm -o prim

test-dll.o : test-dll.c dll.h integer.h string.h real.h
	gcc $(OOPTS) test-dll.c

test-bst.o : test-bst.c bst.h sll.h queue.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) test-bst.c

test-gst.o : test-gst.c gst.h bst.h sll.h queue.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) test-gst.c

test-avl.o : test-avl.c avl.h bst.h sll.h queue.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) test-avl.c

test-binomial.o : test-binomial.c binomial.h avl.h bst.h dll.h sll.h queue.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) test-binomial.c

binomial-0-0.o : binomial-0-0.c binomial.h avl.h bst.h dll.h sll.h queue.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) binomial-0-0.c

binomial-1-10.o : binomial-1-10.c binomial.h avl.h bst.h dll.h sll.h queue.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) binomial-1-10.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h
	gcc $(OOPTS) queue.c

bst.o : bst.c bst.h
	gcc $(OOPTS) bst.c

gst.o : gst.c gst.h
	gcc $(OOPTS) gst.c

avl.o : avl.c avl.h
	gcc $(OOPTS) avl.c

binomial.o : binomial.c binomial.h
	gcc $(OOPTS) binomial.c

edge.o : edge.c edge.h
	gcc $(OOPTS) edge.c

vertex.o : vertex.c vertex.h
	gcc $(OOPTS) vertex.c

prim.o : prim.c
	gcc $(OOPTS) prim.c

b-0-0 : all
	echo testing binomial
	valgrind --leak-check=full ./binomial-0-0
	echo

b-1-10 : all
	echo testing binomial
	valgrind --leak-check=full ./binomial-1-10
	echo

test : all
	echo testing binomial
	./test-binomial
	echo

v : all
	echo testing prim
	valgrind --leak-check=full ./prim g2
	echo

b : all
	echo testing prim
	valgrind --leak-check=full ./prim booktree.data
	echo

valgrind : all
	echo testing 
	valgrind --leak-check=full ./test-binomial
	echo

clean :
	rm -f $(OBJS) binomial.o test-*.o binomial-0-0.o binomial-1-10.o prim.o edge.o vertex.o test-dll test-avl test-bst test-gst test-binomial binomial-0-0 binomial-1-10 prim