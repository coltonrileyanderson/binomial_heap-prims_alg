/* 
 * bst.c 
 * by Colton Andreson
 * Feb 15, 2018
 * 
 * this is the implementation of bst.h. 
 * this implementation can be used to build a generic binary search tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "queue.h"

struct bstnode 
	{
	void *value;
	struct bstnode *left;
	struct bstnode *right;
	struct bstnode *parent;
	};

struct bst 
	{
	BSTNODE *root;
	int size;
	void (*display)(void *v, FILE *fp);
	int (*comparator)(void *val1,void *val2);
	void (*swapper)(BSTNODE *node1,BSTNODE *node2);
    void (*free)(void *v);
	};

/******************************************************************************************************/
/*									PRIVATE HELPER FUNCTIONS										  */

typedef void (*callback_display)(void *,FILE *);
typedef int (*callback_comparator)(void *,void *);
typedef void (*callback_swapper)(BSTNODE *,BSTNODE *);
typedef void (*callback_free)(void *);

static void
swapper (BSTNODE *n1, BSTNODE *n2) {
	void *temp;
	temp = getBSTNODEvalue(n1);
	setBSTNODEvalue(n1, getBSTNODEvalue(n2));
	setBSTNODEvalue(n2, temp);
}
/******************************************************************************************************/
/*										BSTNODE FUNCTIONS											  */
/******************************************************************************************************/

/******************************************************************************************************/
/*										BSTNODE CONSTRUCTOR											  */

BSTNODE *
newBSTNODE(void *v) {

	BSTNODE *bstN = (BSTNODE *)malloc(sizeof(BSTNODE));

    bstN->value = v;
    bstN->left = NULL;
    bstN->right = NULL;
    bstN->parent = NULL;

    return bstN;
}

/******************************************************************************************************/
/*									get/set value Functions											  */

void
setBSTNODEvalue(BSTNODE *n,void *value) {
	n->value = value;
}

void *
getBSTNODEvalue(BSTNODE *n) {

	void *temp_val;

	temp_val = n->value;

	if (temp_val != NULL) return temp_val;
	else return NULL;
}

/******************************************************************************************************/
/*									get/set left Functions											  */

void
setBSTNODEleft(BSTNODE *n,BSTNODE *replacement) {
	n->left = replacement;
}


BSTNODE *
getBSTNODEleft(BSTNODE *n) {
	BSTNODE * temp_left;

	temp_left = n->left;

	if (temp_left != NULL) return temp_left;
	else return NULL;
}

/******************************************************************************************************/
/*									get/set right Functions											  */

void
setBSTNODEright(BSTNODE *n,BSTNODE *replacement) {
	n->right = replacement;
}

BSTNODE *
getBSTNODEright(BSTNODE *n) {
	BSTNODE * temp_right;

	temp_right = n->right;

	if (temp_right != NULL) return temp_right;
	else return NULL;
}

/******************************************************************************************************/
/*									get/set parent Functions										  */

void
setBSTNODEparent(BSTNODE *n,BSTNODE *replacement) {
	n->parent = replacement;
}

BSTNODE *
getBSTNODEparent(BSTNODE *n) {
	BSTNODE * temp_parent;

	temp_parent = n->parent;

	if (temp_parent != NULL) return temp_parent;
	else return NULL;
}

/******************************************************************************************************/
/*											free Functions											  */

void
freeBSTNODE(BSTNODE *n,void (*f)(void *)) {
	if (n != NULL) {
		if (f != 0) {
			f(n->value);
		}
		free(n);
	}
}

/******************************************************************************************************/
/*											BST FUNCTIONS											  */
/******************************************************************************************************/

/******************************************************************************************************/
/*											BST Constructor											  */

BST *       //d is dsiplay function;   c is comparator function; s is swapper function;          
newBST(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*s)(BSTNODE *,BSTNODE *),
		void (*f)(void *)) { //f is freeing function

	BST *bst = (BST *)malloc(sizeof(BST));

	assert(bst != 0);

	bst->root = NULL;

	bst->display = d;
	bst->comparator = c;

	if (s != NULL){
		bst->swapper = s;
	}
	
	else {
		bst->swapper = swapper;
	}

	bst->free = f;

	bst->size = 0;
    return bst;
}

/******************************************************************************************************/
/*											get/set size Functions									  */

void
setBSTsize(BST *t, int s) {
	t->size = s;
}

int
sizeBST(BST *t) {
	return t->size;
}

/******************************************************************************************************/
/*											get/set root Functions									  */

void
setBSTroot(BST *t,BSTNODE *replacement) {
	t->root = replacement;
}

BSTNODE *
getBSTroot(BST *t) {
	assert(t->size > 0);
	return t->root;
}


/******************************************************************************************************/
/*											private Functions										  */

/* PRIVATE HELPER FUNCTION */
BSTNODE *
treeMin(BSTNODE *x){
	while (x->left != NULL){
		x = x->left;
	}
	return x;
}

/* PRIVATE HELPER FUNCTION */
BSTNODE *
treeMax(BSTNODE *x){
	while (x->right != NULL){
		x = x->right;
	}
	return x;
}

/* PRIVATE HELPER FUNCTION */
BSTNODE *
treeSuccessor(BSTNODE *x) {
	if (x->right != NULL) {
		return treeMin(x->right);
	}
	else return NULL;

	// uncomment this to implement up-the-tree functionality
	/*
	BSTNODE *y;
	y = x->parent;

	while (y != NULL && x == y->right){
		x = y;
		y = y->parent;
	}
	return y;
	*/
}

/* PRIVATE HELPER FUNCTION */
BSTNODE *
treePredecessor(BSTNODE *x) {
	if (x->left != NULL) {
		return treeMax(x->left);
		
	}
	else return NULL;

	// uncomment this to implement up-the-tree functionality
	/*
	BSTNODE *y;
	y = x->parent;

	while (y != NULL && x == y->left){
		x = y;
		y = y->parent;
	}
	return y;
	*/
}

/******************************************************************************************************/
/*											insert Functions										  */

BSTNODE *
insertBST(BST *t,void *value) {
	assert(t != 0);
	//assert(value != NULL);

	callback_comparator compare = t->comparator;

	BSTNODE *z = newBSTNODE(value);
	BSTNODE *y, *x;

	y = NULL;
	x = t->root;

	while (x != NULL) {
		y = x;
		if (compare(z->value, x->value) < 0)
			x = x->left;
		else x = x->right;
	}

	z->parent = y;

	// CASE: empty tree
	if (y == NULL) {
		t->root = z;
	}

	// CASE: non-empty tree, value inserted less than parent
	else if (compare(z->value, y->value) < 0)
		y->left = z;

	// CASE: non-empty tree, value inserted more than parent
	else y->right = z;

	t->size += 1;
	return z;
}

/******************************************************************************************************/
/*											find Functions											  */

// PRIVATE RECURSIVE FUNCTION FOR findBST
BSTNODE *
treeSearch (BSTNODE *x, void *value, callback_comparator compare) {
	if (x == NULL || (compare(value, x->value) == 0)) {
		return x;
	}

	if (compare(value, x->value) < 0) {
		return treeSearch(x->left, value, compare);
	}
	else {
		return treeSearch(x->right, value, compare);
	}
}

BSTNODE *
findBST(BST *t,void *value) {
	callback_comparator compare = t->comparator;

	BSTNODE *r, *rtn;
	r = t->root;

	rtn = treeSearch(r, value, compare);
	return rtn;
}

/******************************************************************************************************/
/*											delete Functions										  */

BSTNODE *
swapToLeafBST(BST *t,BSTNODE *node) {
	BSTNODE *succ, *pred;
	//callback_comparator compare = t->comparator;

	if (getBSTNODEleft(node) == NULL && getBSTNODEright(node) == NULL) {
		return node;
	}
	else {
		if (getBSTNODEright(node) != NULL) {
			succ = treeSuccessor(node);
			t->swapper(succ, node);
			succ = swapToLeafBST(t, succ);
			return succ;
		}
		else {
			pred = treePredecessor(node);
			t->swapper(pred, node);
			pred = swapToLeafBST(t, pred);
			return pred;
		}
	}
	// uncomment this to implement up-the-tree functionality
	
	/*
	if (node->left == NULL && node->right == NULL) {

		return node;
	}

	else {

		succ = treeSuccessor(node);

		if (succ != NULL) {

			if ((compare(succ->value, node->value) < 0)) {
				succ = NULL;
			}

		}

		if (succ != NULL) {
			t->swapper(node, succ);

			succ = swapToLeafBST(t, succ);
			return succ;
		}
		
		else {
			pred = treePredecessor(node);

			if (pred != NULL){
				t->swapper(node, pred);

				pred = swapToLeaf(t, pred);
				return pred;
			}
			
		}
		return NULL;
	}
	*/
}


void    
pruneLeafBST(BST *t,BSTNODE *leaf) {
	BSTNODE *leaf_parent;

	leaf_parent = leaf->parent;

	if (leaf_parent == NULL) {
		setBSTroot(t, NULL);
	}

	else {
		if (leaf == leaf_parent->left) {
			leaf_parent->left = NULL;
			leaf->parent = NULL;
		}
		else if(leaf == leaf_parent->right){
			leaf_parent->right = NULL;
			leaf->parent = NULL;
		}
	}

	// don't free because the leaf that is pruned needs to be returned by deleteBST
	//freeBSTNODE(leaf, t->free);
}

BSTNODE *
deleteBST(BST *t,void *value) {
	BSTNODE *temp;

	temp = findBST(t, value);

	if(temp != NULL) {
		temp = swapToLeafBST(t, temp);
		pruneLeafBST(t, temp);

	}

	t->size -= 1;

	return temp;
}

/******************************************************************************************************/
/*											stats Functions											  */

int
minimum(int a, int b){
	if (a < b){
		return a;
	}
	else {
		return b;
	}
}

int
maximum(int a, int b){
	if (a > b){
		return a;
	}
	else {
		return b;
	}
}

int
minDepth(BST* t, BSTNODE *node) {
	if (node == 0) return 0;

	if (node->left == 0 || node->right == 0) return 1;
	/*
	if (!node->left) return minDepth(t, node->right) + 1;

	if (!node->right) return minDepth(t, node->left) + 1;
	*/
	return minimum(minDepth(t, node->left), minDepth(t, node->right)) + 1;
}
/*
static int
maxDepth(BST *t, BSTNODE *node) {
	if (node == 0) return 0;

	int lheight = maxDepth(t, node->left);
	int rheight = maxDepth(t, node->right);

	if (lheight > rheight) return lheight + 1;
	return rheight + 1;

}
*/

static int 
maxDepth(BST *t, BSTNODE *node) {
	int depth, i;
    QUEUE *q = newQUEUE(t->display, t->free);

    if (node == NULL){
    	freeQUEUE(q);
    	return 0;
    }

	enqueue(q, node);

	depth = 0;

	while (sizeQUEUE(q) != 0){
		depth += 1;
		int size = sizeQUEUE(q);

		for (i = 0; i < size; i++) {
			BSTNODE *top = dequeue(q);
			
			if (top->left != NULL) {
				enqueue(q, top->left);
			}
			if (top->right != NULL) {
				enqueue(q, top->right);
			}
		}
	}
	
	freeQUEUE(q);
	return depth;
}

// function that prints to fp:
// Nodes: # of nodes
// Minimum depth: minimum depth (depth of first node with null children)
// Maximum depth: maximum depth	(dpeth of last node with null children)
void
statisticsBST(BST *t,FILE *fp) {
	int max_depth, min_depth, node_count;

	node_count = sizeBST(t);
	max_depth = maxDepth(t, t->root);
	min_depth = minDepth(t, t->root);

	min_depth -= 1;
	max_depth -= 1;

	fprintf(fp, "Nodes: %d\n", node_count);
	fprintf(fp, "Minimum depth: %d\n", min_depth);
	fprintf(fp, "Maximum depth: %d\n", max_depth);
}

/******************************************************************************************************/
/*											disp Functions											  */

void
preOrderDisplay(BSTNODE *r, BSTNODE *x, callback_display d, FILE *fp) {
	if (x != NULL){
		if (r != x) fprintf(fp, "%s", " [");
		d(x->value, fp);
		preOrderDisplay(r, x->left, d, fp);
		preOrderDisplay(r, x->right, d, fp);
		fprintf(fp, "%s", "]");
	}
}

void
displayBST(BST *t,FILE *fp) {
	BSTNODE *x = t->root;
	callback_display disp = t->display;

	if (x == NULL) {
		fprintf(fp, "%s", "[]");
	}
	else {
		fprintf(fp, "%s", "[");
		preOrderDisplay(x, x, disp, fp);
	}
}

void
displayBSTdebug(BST *t, FILE *fp) {
	callback_display d = t->display;
	callback_free	 f = t->free;
	if (t->root != NULL) {
		QUEUE *q = newQUEUE(d, f);
		BSTNODE *r = t->root;

		enqueue(q, r);

		while(1) {
			int count = sizeQUEUE(q);
			if (count == 0) break;

			while (count > 0) {
				BSTNODE *n = peekQUEUE(q);
				d(n->value, fp);
				dequeue(q);

				if (n->left != NULL) {
					enqueue(q, n->left);
				}
				if (n->right != NULL) {
					enqueue(q, n->right);
				}

				count -= 1;

				if (count != 0)
					fprintf(fp, "%s", " ");
			}
			fprintf(fp, "\n");
		}
		freeQUEUE(q);
	}
	else {
		return;
	}
}
static void
displayHelper(BSTNODE *n, FILE *fp, callback_display d){
	if (n->left == 0 && n->right == 0){
		fprintf(fp, "%s", "=");
	}
	d(n->value, fp);
	fprintf(fp, "%s", "(");

	BSTNODE *parent = n->parent;
	if(parent == 0 || n->parent == n){
		d(n->value, fp);
		fprintf(fp, "%s", ")X");
	}

	else {
		d(parent->value, fp);
		
		if(parent->left == n){
			fprintf(fp, "%s", ")L");
		}
		else {
			fprintf(fp, "%s", ")R");
		}
	}
}
void
displayBSTdecorated(BST *t,FILE *fp){
	callback_display d = t->display;
	callback_free	 f = t->free;
	int lvl = 0;
	if (t->root != 0) {
		QUEUE *q = newQUEUE(d, f);
		BSTNODE *r = t->root;

		enqueue(q, r);

		while(1) {
			int count = sizeQUEUE(q);
			if (count == 0) break;

			printf("%d: ", lvl);
			while (count > 0) {
				BSTNODE *n = peekQUEUE(q);
				
				displayHelper(n, fp, d);

				dequeue(q);

				if (n->left != NULL) {
					enqueue(q, n->left);
				}
				if (n->right != NULL) {
					enqueue(q, n->right);
				}

				count -= 1;

				if (count != 0)
					fprintf(fp, "%s", " ");
			}
			lvl += 1;
			fprintf(fp, "\n");
		}
		freeQUEUE(q);
	}
	else {
		
	}
}


/******************************************************************************************************/
/*											free Functions											  */

void
preOrderFree(BSTNODE *x, callback_free f) {
	if (x != NULL){
		preOrderFree(x->left, f);
		preOrderFree(x->right, f);
		if (f != NULL) f(x->value);
		free(x);
	}
}

void
freeBST(BST*t) {
	if (t->root != NULL){
		BSTNODE *x = t->root;
		//printf("%s\n", "hit");
		preOrderFree(x, t->free);
	}

	free(t);
}