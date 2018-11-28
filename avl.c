/* 
 * avl.c 
 * by Colton Andreson
 * Feb 28, 2018
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "avl.h"

typedef struct aval {
	void *value;

	int count;
	int balance;
	int height;

	void (*disp)(void *, FILE *);
	int (*comp)(void *, void *);
	void (*free)(void *);
} AVAL;

struct avl {
	BST *tree;

	void (*display)(void *v, FILE *fp);
	int (*comparator)(void *val1,void *val2);
    void (*free)(void *v);

    int size;
    int duplicates;

};
/*
typedef void (*callback_display)(void *,FILE *);
typedef int (*callback_comparator)(void *,void *);
typedef void (*callback_swapper)(BSTNODE *,BSTNODE *);
typedef void (*callback_free)(void *);

callback_comparator callback_c;
*/
int
acompare (void *v, void *w) {
	AVAL *gv = (AVAL *)v;
	AVAL *gw = (AVAL *)w;

	//	gv->disp(gv->value,stdout);

	int rtn = gv->comp(gv->value, gw->value);
	return rtn;
}

void
adisplay(void *v, FILE *fp){
	AVAL *g = (AVAL *)v;
	g->disp(g->value, fp);
	//fprintf(fp, "{%d}", g->height);
	if (g->count > 1){
		fprintf(fp, "[%d]", g->count);
	}
	if (g->balance < 0) fprintf(fp, "%s", "-");
	else if (g->balance > 0) fprintf(fp, "%s", "+");

	
}

void
afree(void *v){
	AVAL *g = (AVAL *)v;
	g->free(g->value);
	free(g);
}

void
aswapper (BSTNODE *n1, BSTNODE *n2) {
	AVAL *ta = getBSTNODEvalue(n1);
	AVAL *tb = getBSTNODEvalue(n2);
	/* swap the values stored in the AVL value objects */
    void *vtemp = ta->value;
    ta->value = tb->value;
    tb->value = vtemp;

    /* swap the counts stored in the AVL value objects */
    int ctemp = ta->count;
    ta->count = tb->count;
    tb->count = ctemp;
}

AVAL *
newAVAL(AVL *t, void *v) {
	AVAL *AVLN = (AVAL *)malloc(sizeof(AVAL));

	assert(AVLN != 0);

	AVLN->value = v;

	AVLN->count = 1;
	AVLN->balance = 0;
	AVLN->height = 1;

	AVLN->disp = t->display;
	AVLN->comp = t->comparator;
	AVLN->free = t->free;
	return AVLN;
}

AVL *       //d is dsiplay function; c is comparator function; f is freeing function;          
newAVL(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*f)(void *)) {

	AVL *t = (AVL *)malloc(sizeof(AVL));

	assert(t != 0);

	t->display = d;
	t->comparator = c;
	t->free = f;

	t->tree = newBST(adisplay, acompare, aswapper, afree);

	t->size = 0;
	t->duplicates = 0;
    return t;
}

int 
sizeAVL(AVL *t){
	return t->size;
}

int 
duplicatesAVL(AVL *t){
	return t->duplicates;
}

/******************************************************************************************************/
/*											find Functions											  */
/*
static int           // void pointer type is AVAL, returns count
findAVALcount(AVL *t,void *v){
	AVAL *gv =  (AVAL *)v;
	int rtn = 0;

	BSTNODE *node = findBST(t->tree, gv);

	if (node == 0){
		rtn = 0;
	}
	else {
		AVAL *temp = getBSTNODEvalue(node);
		rtn = temp->count;
	}

	return rtn;

}
*/
int 				// void pointer type is a generic Value, returns count
findAVLcount(AVL *t,void *v){
	AVAL *gv =  newAVAL(t, v);
	int rtn = 0;

	BSTNODE *node = findBST(t->tree, gv);

	if (node == 0){
		rtn = 0;
	}
	else {
		AVAL *temp = getBSTNODEvalue(node);
		rtn = temp->count;
	}

	free(gv);
	return rtn;

}

static void *	// void pointer type is AVAL, returns the AVAL
findAVAL(AVL *t,void *v){
	AVAL *gv =  (AVAL *)v;
	void *rtn;

	BSTNODE *n = findBST(t->tree, gv);

	if (n != 0){
		AVAL *temp = getBSTNODEvalue(n);
		rtn = temp;
	}	
	else{
		rtn = 0;
	}

	return rtn;
}

// returns the value
void *			// void pointer type is generic value, returns that value
findAVL(AVL *t,void *v){
	AVAL *gv =  newAVAL(t, v);
	void *rtn;

	BSTNODE *n = findBST(t->tree, gv);

	if (n != 0){
		AVAL *temp = getBSTNODEvalue(n);
		rtn = temp->value;
	}	
	else{
		rtn = 0;
	}

	free(gv);
	return rtn;
}

static BSTNODE *
getSibling(BSTNODE *n){
	/*
    if n is its parent's left child, return the parent's right child
    if n is its parent's right child, return the parent's left child
    */
	BSTNODE *parent = getBSTNODEparent(n);
	BSTNODE *rtn;

	if (parent == 0) {
		rtn = 0;
	}
	if (getBSTNODEleft(parent) == n) {
		rtn = getBSTNODEright(parent);
	}
	if(getBSTNODEright(parent) == n) {
		rtn = getBSTNODEleft(parent);
	}

	return rtn;
}

static int 
linear(BSTNODE *n1, BSTNODE *n2, BSTNODE *n3) {
	/*
	return (gp.left == p && p.left == c)
            || (gp.right == p && p.right == c);
            */
	BSTNODE *child = n1;
	BSTNODE *parent = n2;
	BSTNODE *gparent = n3;

	if ((getBSTNODEleft(gparent) == parent && getBSTNODEleft(parent) == child) || 
			(getBSTNODEright(gparent) == parent && getBSTNODEright(parent) == child)){
		return 1;
	}
	else return 0;
}

static int
getHeight(BSTNODE *x) {
	if (x == 0) return 0;
	else {
		AVAL *val = getBSTNODEvalue(x);
		return val->height;
	}
}

static void 
setHeight(BSTNODE *x, int h){
	if (x == 0) return;
	else {
		AVAL *val = getBSTNODEvalue(x);
		val->height = h;
	}
}

static int 
maximum(int a, int b){
    return (a > b)? a : b;
}

static int
getBalance(void *v) {
	BSTNODE *n = (BSTNODE *)v;
	AVAL *val = getBSTNODEvalue(n);
	return val->balance;

}

static void 
setBalance(void *v) {
	int lheight = 0;
	int rheight = 0;
	int balance = 0;

	BSTNODE *n = v;
	AVAL *val = getBSTNODEvalue(n);

	if (getBSTNODEleft(n) != 0) {
		lheight = getHeight(getBSTNODEleft(n));
	}
	else {
		lheight = 0;
	}

	if (getBSTNODEright(n) != 0) {
		rheight = getHeight(getBSTNODEright(n));
	}
	else {
		rheight = 0;
	}

	balance = lheight - rheight;

	val->balance = balance;
	val->height = maximum(lheight, rheight) + 1;
	//printf("balance: %d\n", height);
	return;
}

static BSTNODE *
favors(BSTNODE *parent) {

	AVAL *p = getBSTNODEvalue(parent);
	BSTNODE * rtn;

	if (p->balance == 0){
		//printf("balanced\n");
		rtn = 0;
	}
	else if (p->balance > 0) {
		//printf("left heavy\n");
		rtn = getBSTNODEleft(parent);
	}
	else if (p->balance < 0) {
		//printf("right heavy\n");
		rtn = getBSTNODEright(parent);
	}

	return rtn;
}

static void 
rightrot(AVL *t, BSTNODE *x){
	BSTNODE *y = getBSTNODEleft(x); // set y
	setBSTNODEleft(x, getBSTNODEright(y)); // turn y's right into x's left

	if(getBSTNODEright(y) != 0) {
		BSTNODE *yright = getBSTNODEright(y);
		setBSTNODEparent(yright, x);
	}

	setBSTNODEparent(y, getBSTNODEparent(x)); // link x's parent to y

	if (getBSTroot(t->tree) == x) {
		setBSTroot(t->tree, y);
		setBSTNODEparent(y, y);
	}

	else if (x == getBSTNODEleft(getBSTNODEparent(x))) {
		setBSTNODEleft(getBSTNODEparent(x), y);
	}
	else
		setBSTNODEright(getBSTNODEparent(x), y);

	setBSTNODEright(y, x);
	setBSTNODEparent(x, y);

	//updateHeight(x);
    //updateHeight(y);

}

static void 
leftrot(AVL *t, BSTNODE *x){
	BSTNODE *y = getBSTNODEright(x); // set y
	setBSTNODEright(x, getBSTNODEleft(y)); // turn y's right into x's left

	if(getBSTNODEleft(y) != 0) {
		BSTNODE *yleft = getBSTNODEleft(y);
		setBSTNODEparent(yleft, x);
	}

	setBSTNODEparent(y, getBSTNODEparent(x)); // link x's parent to y

	if (getBSTroot(t->tree) == x) {
		setBSTroot(t->tree, y);
		setBSTNODEparent(y, y);
	}

	else if (x == getBSTNODEright(getBSTNODEparent(x))) {
		setBSTNODEright(getBSTNODEparent(x), y);
	}
	else
		setBSTNODEleft(getBSTNODEparent(x), y);

	setBSTNODEleft(y, x);
	setBSTNODEparent(x, y);

	//updateHeight(x);
	//updateHeight(y);
}

static void 
rotate(AVL *t, BSTNODE *y, BSTNODE *p) {
	int side = 0;

	if (getBSTNODEright(p) == y) side = 1;

	if (side == 0) {
		///printf("right\n");
		rightrot(t, p);
	}
	else {
		//printf("left\n");
		leftrot(t, p);
	}

}

static void
insertFIX(AVL *t, BSTNODE *x) {
	
	
	while (1) {
		BSTNODE *parent = getBSTNODEparent(x);
		if (getBSTroot(t->tree) == x){
			break;
		}

		//else if parent favors sibling
		else if (favors(parent) != 0 && (favors(parent) == getSibling(x))){
			setBalance(parent);
			//printf("parent favors siblig:\n");
			//displayAVL(t, stdout);
			break;
		}

		else if (getBalance(parent) == 0) {
			setBalance(parent);
			//printf("parent balanced:\n");		
			//displayAVL(t, stdout);
			x = parent;
			
		}

		else {
			BSTNODE *y = favors(x);
			parent = getBSTNODEparent(x);
			//printf("parent(p) of current x: ");
			//adisplay(getBSTNODEvalue(parent), stdout);
			//printf(", current x: ");
			//adisplay(getBSTNODEvalue(x), stdout);
			//printf(", favorite(y) of current x: ");
			//if (y != 0)
				//adisplay(getBSTNODEvalue(y), stdout);
			//printf("\n");
			if (y != 0 && (linear(y, x, parent) == 0)){ // case3
				//rotate y to x
				rotate(t, y, x);

				//printf("rotate y to x:\n");
				//displayAVL(t, stdout); 	

				//rotate y to parent
				rotate(t, y, parent);

				//printf("rotate y to p:\n");
				//displayAVL(t, stdout); 

				//set the balance of x
				//set the balnce of parent
				//set the balance of y
				setBalance(x);
				setBalance(parent);
				setBalance(y);

				//printf("**********CASE 3\n");
				//printf("parent(p) of current x: ");
				//adisplay(getBSTNODEvalue(parent), stdout);
				//printf(", current x: ");
				//adisplay(getBSTNODEvalue(x), stdout);
				//printf(", favorite(y) of current x: ");
				//adisplay(getBSTNODEvalue(y), stdout);
				//printf("\n");

				
			}
			else {	// case 4
				//rotate x to parent
				rotate(t, x, parent);

				//printf("rotate x to p:\n");
				//printf("parent(p) of current x: ");
				//adisplay(getBSTNODEvalue(parent), stdout);
				//printf(", current x: ");
				//adisplay(getBSTNODEvalue(x), stdout);
				//printf("\n"); 	
				//displayAVL(t, stdout);

				//set the balance of parent
				//set the balance of x
				setBalance(parent);
				setBalance(x);

				//printf("**********CASE 4\n");
				//printf("parent(p) of current x: ");
				//adisplay(getBSTNODEvalue(parent), stdout);
				//printf(", current x: ");
				//adisplay(getBSTNODEvalue(x), stdout);
				//printf("\n");

				
			}
			break;
		}
	}
}

void
insertAVL(AVL *t,void *v){
	assert(t != 0);
	assert(v != 0);
	
	AVAL *new_AVAL = newAVAL(t, v);
	void *search = 0;

	if (sizeAVL(t) == 0 || sizeBST(t->tree) == 0) {
		BSTNODE *added = insertBST(t->tree, new_AVAL);
		//setBSTNODEparent(inserted, inserted);
		t->size += 1;

		// set the parent of the root to the root
		if(getBSTroot(t->tree) == added){
			//BSTNODE *r = getBSTroot(t->tree);
			setBSTNODEparent(added, added);
		}
	}

	else{
		search = findAVAL(t, new_AVAL);

		//value already in the tree, increment count and t->duplicates
		if (search != 0) {
			AVAL *found = (AVAL *)search;
			found->count += 1;
			t->duplicates += 1;
		
			// free unused, duplicate AVAL
			free(new_AVAL);
		}
		// value not in the tree
		else {
			BSTNODE *inserted = insertBST(t->tree, new_AVAL);
			t->size += 1;

			//printf("--before insertfix--\n");
			//displayAVL(t, stdout);

			//insert fixup
			insertFIX(t, inserted);

			// make the root's parent itself
			//BSTNODE *root = getBSTroot(t->tree);
			//setBSTNODEparent(root, root);

			//fixHeights(t, getBSTNODEparent(inserted));

			//printf("--after insertfix--\n");
			//displayAVL(t, stdout);

		}
	}
}

static void
deleteFIX(AVL *t, BSTNODE *x) {
	//BSTNODE *toBeRemoved = x;

	AVAL *xval = getBSTNODEvalue(x);
	xval->balance = 0;
	while (1) {
		BSTNODE *parent = getBSTNODEparent(x);
		if (getBSTroot(t->tree) == x){
			break;
		}

		//else if parent favors x
		else if (favors(parent) != 0 && (favors(parent) == x)){
			setBalance(parent);

			//printf("parent favors x\n");
			//printf("parent(p) of current x: ");
			//adisplay(getBSTNODEvalue(parent), stdout);
			//printf("\n");
			//displayAVL(t, stdout);

			x = parent;
		}

		//parent is balanced == tree is balanced == stop looping
		else if (getBalance(parent) == 0) {	
			setBalance(parent);
			//printf("parent balanced:\n");	
			//displayAVL(t, stdout);
			break;
			
		}

		else {
			BSTNODE *p = getBSTNODEparent(x);
			BSTNODE *z = getSibling(x);
			BSTNODE *y = favors(z);
			//printf("current x: ");
			//adisplay(getBSTNODEvalue(x), stdout);
			//printf(" parent(p) of current x: ");
			//adisplay(getBSTNODEvalue(p), stdout);
			//printf(", sibling(z) of current x: ");
			//adisplay(getBSTNODEvalue(z), stdout);
			//printf(", favorite(y) of current z: ");
			//if (y != 0)
				//adisplay(getBSTNODEvalue(y), stdout);
			//printf("\n");

			// parent is not balanced, may favor the sibling of x, y exists
			if (y != 0 && (linear(y,z,p) == 0)){
				
				//rotate y to z
				rotate(t, y, z);
				//printf("rotate y to z:\n");
				//displayAVL(t, stdout); 	

				//rotate y to p
				rotate(t, y, p);
				//printf("rotate y to p:\n");
				//displayAVL(t, stdout);

				//set the balance of p
				//set the balnce of z
				//set the balance of y
				setBalance(p);
				setBalance(z);
				setBalance(y);

				//printf("after setting balance\n");
				//displayAVL(t, stdout);

				x = y;
			}

			// y doesn't exist or they are linear 
			else {	// case 4
				//rotate z to p
				rotate(t, z, p);
				//printf("rotate z to p:\n");
				//displayAVL(t, stdout);

				//set the balance of p
				//set the balance of z
				setBalance(p);
				setBalance(z);

				if(y == 0)
					break;
				x = z;				
			}
		}
	}
}

/*
static void 
fixBalances(BSTNODE *x) {
	//BSTNODE *parent = x;

	while(1){
		if (x == 0) {
			break;
		}
		if (getBalance(x) == 0) {
			setBalance(x);
			break;
		}
		else {
			setBalance(x);
			x = getBSTNODEparent(x);
		}
	}
}
*/

void *deleteAVL(AVL *t,void *v){
	void *rtn = 0;

	AVAL *new_AVAL = newAVAL(t, v);
	void *search_val = 0;
	void *search_aval = 0;

	if (sizeAVL(t) == 0 || sizeBST(t->tree) == 0) {
		rtn = 0;
	}
	else {
		search_val = findAVL(t, v);
				
		//printf("%d\n", c);
		if (search_val != 0) {
			int c = findAVLcount(t, v);
			if (c > 1) {
				search_aval = findAVAL(t, new_AVAL);
				AVAL *temp = (AVAL *)search_aval;

				temp->count -= 1;
				t->duplicates -= 1;
				rtn = 0;

			}
			else {
				BSTNODE *removed = findBST(t->tree, new_AVAL);

				//printf("before delete:\n");
				//displayAVL(t, stdout);

				// swap found node to successor(predecessor if not available)
				removed = swapToLeafBST(t->tree, removed);

				//printf("swapped to leaf:\n");
				//displayAVL(t, stdout);

				// setbalance of removed -- should be 0 because it is a leaf node
				//setBalance(removed);
				setHeight(removed, 0);

				//printf("deleteFixUp(start):\n");

				// call delete fix up routine on removed node
				deleteFIX(t, removed);

				//printf("deleteFixUp(end):\n");
				//displayAVL(t, stdout);
				
				//BSTNODE *removed_p = getBSTNODEparent(removed);
				// prune that removed node from tree
				pruneLeafBST(t->tree, removed);
				
				//printf("pruned:\n");
				//displayAVL(t, stdout);
				

				/* set balance of the tree -- REMOVE LATER SOMEHOW /
				BSTNODE *root = getBSTroot(t->tree);
				//balanceTree(t, root);

				// I THINK THIS METHOD ACTUALLY MIGHT WORK
				fixBalances(t, removed_p);

				//printf("balanced:\n");
				//displayAVL(t, stdout);
				/ setbalance end */

				// set the root's parent to itself
				//BSTNODE *root = getBSTroot(t->tree);
				//setBSTNODEparent(root, root);

				// incrememnt AVL size
				t->size -= 1;

				// increment BST size
				int s = sizeBST(t->tree);
				s -= 1;
				setBSTsize(t->tree, s);

				// save return value
				rtn = search_val;

				// free the node without freeing the value.
				freeBSTNODE(removed, free);
			}

		}
		// val not in tree
		else {
			rtn = 0;
		}
	}
	// free duplicate aval

	free(new_AVAL);

	return rtn;
}

/*
Duplicates: 2
Nodes: 8
Minimum depth: 2
Maximum depth: 4
*/
void 
statisticsAVL(AVL *t,FILE *fp){
	int dup_count;
	dup_count = duplicatesAVL(t);
	fprintf(fp, "Duplicates: %d\n", dup_count);
	statisticsBST(t->tree, fp);
}


void
displayAVL(AVL *t,FILE *fp){
	/*
	if (sizeAVL(t) == 0){
		fprintf(fp, "%s\n", "EMPTY");
	}
	else{
		displayBSTdecorated(t->tree, fp);
	}
	*/
	displayBSTdecorated(t->tree, fp);
}

void
displayAVLdebug(AVL *t,FILE *fp){
	displayBST(t->tree, fp);
}

void
freeAVL(AVL *t){
	BST *temp = t->tree;
	freeBST(temp);

	free(t);
}

