#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include "dll.h"
#include "sll.h"
#include "queue.h"
//#include "stack.h"
//#include "avl.h"
//#include "bst.h"
//#include "vertex.h"
//#include "edge.h"
#include "binomial.h"

typedef struct node 
	{
	void *value;
	struct node *parent;
	DLL* children;

	void (*display)(void *, FILE *);
    void (*free)(void *);
	} NODE;

/* PUBLIC INTERFACE STRUCT binomial */
struct binomial 
    {
    DLL *rootlist;
    int size;
    NODE *extreme;
    int extremeIndex;
    void (*display)(void *, FILE *);
    int (*comparator)(void *, void *);
    void (*update)(void *, void *);
    void (*free)(void *);
    };
static double binomialHeight(BINOMIAL *b);
static void displayNODE(void *node, FILE *fp);
static void freeNODE(void *node);
static void consolidate(BINOMIAL *b);
static void updateConsolidationArray(NODE **D, NODE *x, BINOMIAL *b);
static NODE *combine(BINOMIAL *b, NODE *i, void *d);
static NODE *bubbleUp(BINOMIAL *b, NODE *n);
static void queueHelper(DLL *items, int lvl, QUEUE *q, int flag);

BINOMIAL *
newBINOMIAL(
	void (*d)(void *,FILE *),
    int (*c)(void *,void *),
    void (*u)(void *,void *),
    void (*f)(void *)){

	BINOMIAL *new = (BINOMIAL *)malloc(sizeof(BINOMIAL));
	assert(new != 0);

	new->rootlist = newDLL(displayNODE, freeNODE);
	new->size = 0;
	new->extreme = 0;
	new->extremeIndex = 0;
	new->display = d;
	new->comparator = c;
	new->update = u;
	new->free = f;

	return new;
}

NODE *
newNODE(void *v, void (*d)(void *,FILE *), void (*f)(void *)) {
	NODE *new = (NODE *)malloc(sizeof(NODE));
	new->value = v;
	new->parent = new;
	new->children = newDLL(displayNODE, freeNODE);

	new->display = d;
	new->free = f;

	return new;
}

// calculates the max height of the binomial heap
// which is equal to log(base2) of binomial heap size
// ** used in consolidate, display, and free **
static double 
binomialHeight(BINOMIAL *b) {
	int b_size = b->size;

	double top_log = log(b_size);
	double bottom_log = log(2);

	double rtnval = top_log/bottom_log;

	return rtnval;
}

static void
displayNODE(void *node, FILE *fp){
	NODE *n = (NODE *)node;

	n->display(n->value, fp);
}

static void
freeNODE(void *node){
	NODE *n = (NODE *)node;

	if (n != 0){
		if (n->free != 0){
			n->free(n->value);
		}
		free(n);
	}
}

static void
consolidate(BINOMIAL *b) {
	//create consolidation array D
	int s = 0;
	double array_D_size = binomialHeight(b);
	s = (int)(array_D_size) + 1;
	NODE *D[s];

	int i = 0;
	for (i = 0; i < s; i++){
		D[i] = 0;
	}

	//place all subheaps into D, combining
	while (sizeDLL(b->rootlist) != 0) {
		NODE *x = removeDLL(b->rootlist, 0);
		updateConsolidationArray(D, x, b);
	}

	b->extreme = 0;
	i = 0;
	for (i = 0; i < s; i++) {
		if (D[i] != 0) {
			insertDLL(b->rootlist, sizeDLL(b->rootlist), D[i]);

			NODE *d_i = D[i];
			NODE *ext = b->extreme;

			if(b->extreme == 0 || b->comparator(d_i->value, ext->value) < 0) {
				b->extreme = D[i];
			}
		}
	}
}

static void 
updateConsolidationArray(NODE **D, NODE *x, BINOMIAL *b) {
	if (x == 0){
		return;
	}
	int degree = sizeDLL(x->children);
	
	while (D[degree] != 0){
		x = combine(b, x, D[degree]);
		D[degree] = 0;
		degree++;
	}
	D[degree] = x;
}

static NODE *
combine(BINOMIAL *b, NODE *x, void *d){
	NODE *y = (NODE *)d; //D[degree]
	if (b->comparator(x->value, y->value) < 0) {
		insertDLL(x->children, sizeDLL(x->children), y);
		y->parent = x;
		return x;
	}
	else {
		insertDLL(y->children, sizeDLL(y->children), x);
		x->parent = y;
		return y;
	}
}

void *
insertBINOMIAL(BINOMIAL *b,void *value){
	NODE *n = newNODE(value, b->display, b->free);

	insertDLL(b->rootlist, 0, n);
	b->size += 1;

	consolidate(b);
	return n;
}


int 
sizeBINOMIAL(BINOMIAL *b){
	if (b != 0){
		return b->size;
	}
	else return 0;
}


void 
unionBINOMIAL(BINOMIAL *b,BINOMIAL *donor){
	unionDLL(b->rootlist, donor->rootlist);
	b->size += donor->size;
	donor->rootlist = newDLL(displayNODE, freeNODE);
	donor->size = 0;
	donor->extreme = NULL;
	consolidate(b);
}

static NODE *
bubbleUp(BINOMIAL *b, NODE *n){
	// psuedocode from website beastie.cs.ua.edu/cs201/assign-binomaial.html
	NODE *p = n->parent;

	if (n == p){
		return n;
	}
	//printf("before \n");
	if (b->comparator(n->value, p->value) >= 0) {
		//printf("in\n");
		return n;
	}
	//printf("after \n");

	if (b->update != 0) {
		//printf("hit");
		b->update(n->value, p);
	}

	if (b->update != 0) {
		//printf("tih");
		b->update(p->value, n);
	}
	void *temp = n->value;
	n->value = p->value;
	p->value = temp;
	

	return bubbleUp(b, p);
}
void 
deleteBINOMIAL(BINOMIAL *b,void *node){
	decreaseKeyBINOMIAL(b, node, 0);
	extractBINOMIAL(b);
}

void 
decreaseKeyBINOMIAL(BINOMIAL *b,void *node,void *value){
	NODE *n = (NODE *)node;

	n->value = value;

	NODE *extremeNode = b->extreme;
	n = bubbleUp(b, n);

	if (b->comparator(n->value, extremeNode->value) < 0) {
		b->extreme = n;
	}
}

void *
peekBINOMIAL(BINOMIAL *b){
	if (b != 0 && b->extreme != 0){
		NODE * ext;
		ext = b->extreme;

		return ext->value;
	}
	else return 0;	
}


void *
extractBINOMIAL(BINOMIAL *b){
	NODE *y = b->extreme;
	NODE *rtn_node = 0;

	lastDLL(b->rootlist);
	NODE *tail = currentDLL(b->rootlist);

	firstDLL(b->rootlist);
	NODE *current = currentDLL(b->rootlist);

	int i = 0;
	while (current != tail) {
		if (current == y) {
			rtn_node = removeDLL(b->rootlist, i);
			break;
		}
		i++;
		nextDLL(b->rootlist);
		current = currentDLL(b->rootlist);
	}
	if (current == tail) {
		if (current == y) {
			rtn_node = removeDLL(b->rootlist, i);
		}
	}

	lastDLL(y->children);
	if (moreDLL(y->children)){
		tail = currentDLL(y->children);
	}

	firstDLL(y->children);
	if (moreDLL(y->children)){
		current = currentDLL(y->children);
	}

	while (current != tail) {
		current->parent = current;
		//printf("extractbinomial: line 353: %d\n", sizeDLL(y->children));
		if (moreDLL(y->children)){
			nextDLL(y->children);
			current = currentDLL(y->children);
		}
		else {
			break;
		}
		
	}
	if (current == tail) {
		current->parent = current;
	}

	// put y->children in front of root list, emptying root list
	unionDLL(y->children, b->rootlist);
	// put y children all into root list, emptying y children
	unionDLL(b->rootlist, y->children);

	consolidate(b);
	b->size -= 1;
	
	void *rtn_val = rtn_node->value;

	freeDLL(rtn_node->children);
	free(rtn_node);

	return rtn_val;
}

void 
statisticsBINOMIAL(BINOMIAL *b,FILE *fp){
	int size = b->size;
	fprintf(fp, "size: %d\n", size);
	int root_list_size = sizeDLL(b->rootlist);
	fprintf(fp, "rootlist size: %d\n", root_list_size);

	if (sizeDLL(b->rootlist) != 0){
		NODE *ext = b->extreme;
		void *ext_val = ext->value;
		fprintf(fp, "extreme: ");
		ext->display(ext_val, fp);
		fprintf(fp, "\n");
	}
}

void 
displayBINOMIAL(BINOMIAL *b,FILE *fp){
	fprintf(fp, "rootlist: ");

	//get first node, save as tail, and save ext
	//int sizel = sizeDLL(b->rootlist);
	//printf("root list size in display: %d\n", sizel);
	if (sizeDLL(b->rootlist) != 0){
		lastDLL(b->rootlist);
		NODE *tail = currentDLL(b->rootlist);
		NODE *ext = b->extreme;
		
		firstDLL(b->rootlist);
		NODE *current = 0;

		int i = 0;

		for (i = 0; i <= sizeDLL(tail->children); i++) {

			current = currentDLL(b->rootlist);

			if ((sizeDLL(current->children) == i) && current != tail) {
				b->display(current->value, fp);
				if (current == ext) {
					fprintf(fp, "*");
				}
				nextDLL(b->rootlist);
				if (current != tail) {
					fprintf(fp, " ");
				}
			}

			else if (sizeDLL(current->children) != i) {
				fprintf(fp, "NULL ");
			}

			if (current == tail && sizeDLL(current->children) == i) {
				b->display(current->value, stdout);
				if (current == ext) {
					fprintf(fp, "*");
				}
			}
		}	
	}
	fprintf(fp, "\n");
}
// function that handles enqueueing the root list and children for
// both debugging and freeing
static void
queueHelper(DLL *items, int lvl, QUEUE *q, int flag) {
	// flag == 1, running displaydebug
	if (flag == 1) {
		if (sizeDLL(items) == 0) {
			return;
		}

		// first call, lvl == 0, enqueue root list
		// subsequent calls, enqueue the list of the child/children's child etc.
		if (lvl == 0) {
			enqueue(q, items);
		}
		// when lvl > 0, it loops through the whatever list is calling the function,
		// calls itself to possibly enqueue the child DLL, or loop through the list of child
		else {
			//get first node, save as tail, and start iterating from from
			lastDLL(items);
			NODE *tail = currentDLL(items);
			firstDLL(items);
			NODE *current = currentDLL(items);

			while (current != tail) {
				if (current != 0) {
					queueHelper(current->children, lvl-1, q, flag);
				}
				nextDLL(items);
				current = currentDLL(items);
			}
			if (current == tail) {
				if (current != 0){
					queueHelper(current->children, lvl-1, q, flag);
				}
			}
		}
	}
	// flag != 1, running free
	else {
		enqueue(q, items);

		if (sizeDLL(items) == 0) {
			return;
		}

		lastDLL(items);
		NODE *tail = currentDLL(items);
		firstDLL(items);
		NODE *current = currentDLL(items);

		while (current != tail) {
			if (current != 0) {
				queueHelper(current->children, 0, q, flag);
			}
			nextDLL(items);
			current = currentDLL(items);
		}
		if (current == tail) {
			if (current != 0){
				queueHelper(current->children, 0, q, flag);
			}
		}
	}
	
}

void 
displayBINOMIALdebug(BINOMIAL *b,FILE *fp){
	QUEUE *q = newQUEUE(0,0);

	//calculates the max_height of the binomial
	int max_height = 0;
	double binomial_height = binomialHeight(b);
	max_height = (int)(binomial_height);

	// for loop that calls a helper to enqueue all of the DLL's that need to print
	// then, deuqueues a DLL, and prints that DLL, creating a new line, and moving to the 
	// next root list value
	int i;
	for(i = 0; i <= max_height; i++){
		queueHelper(b->rootlist, i, q, 1);

		while (sizeQUEUE(q) > 0) {
			DLL* d = dequeue(q);
			if (d != 0) {
				displayDLL(d, fp);
			}
		}
		fprintf(fp, "\n");
	}

	freeQUEUE(q);
}

void 
freeBINOMIAL(BINOMIAL *b){
	if (b != 0) {
		QUEUE *q = newQUEUE(0,0);

		queueHelper(b->rootlist, 0, q, 0);

		while (sizeQUEUE(q) > 0){
			DLL *d = dequeue(q);
			if (d != 0){
				freeDLL(d);
			}
		}
		freeQUEUE(q);
		free(b);
	}
}
