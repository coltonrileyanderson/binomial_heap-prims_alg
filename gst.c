/* 
 * gst.c 
 * by Colton Andreson
 * Feb 28, 2018
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "gst.h"

typedef struct gval {
	void *value;

	int count;

	void (*disp)(void *, FILE *);
	int (*comp)(void *, void *);
	void (*free)(void *);
} GVAL;

struct gst {
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
gcompare (void *v, void *w) {
	GVAL *gv = (GVAL *)v;
	GVAL *gw = (GVAL *)w;

	int rtn = gv->comp(gv->value, gw->value);
	return rtn;
}

void
gdisplay(void *v, FILE *fp){
	GVAL *g = (GVAL *)v;
	g->disp(g->value, fp);
	if (g->count > 1){
		fprintf(fp, "[%d]", g->count);
	}
}

void
gfree(void *v){
	GVAL *g = (GVAL *)v;
	g->free(g->value);
	free(g);
}

void
gswapper (BSTNODE *n1, BSTNODE *n2) {
	GVAL *ta = getBSTNODEvalue(n1);
	GVAL *tb = getBSTNODEvalue(n2);
	/* swap the values stored in the GST value objects */
    void *vtemp = ta->value;
    ta->value = tb->value;
    tb->value = vtemp;

    /* swap the counts stored in the GST value objects */
    int ctemp = ta->count;
    ta->count = tb->count;
    tb->count = ctemp;
}

GVAL *
newGVAL(GST *t, void *v) {
	GVAL *gstN = (GVAL *)malloc(sizeof(GVAL));

	assert(gstN != 0);

	gstN->value = v;

	gstN->count = 1;

	gstN->disp = t->display;
	gstN->comp = t->comparator;
	gstN->free = t->free;
	return gstN;
}

GST *       //d is dsiplay function; c is comparator function; f is freeing function;          
newGST(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*f)(void *)) {

	GST *t = (GST *)malloc(sizeof(GST));

	assert(t != 0);

	t->display = d;
	t->comparator = c;
	t->free = f;

	t->tree = newBST(gdisplay, gcompare, 0, gfree);

	t->size = 0;
	t->duplicates = 0;
    return t;
}

int 
sizeGST(GST *t){
	return t->size;
}

int 
duplicates(GST *t){
	return t->duplicates;
}
/******************************************************************************************************/
/*											find Functions											  */
/*
static int           // void pointer type is GVAL, returns count
findGVALcount(GST *t,void *v){
	GVAL *gv =  (GVAL *)v;
	int rtn = 0;

	BSTNODE *node = findBST(t->tree, gv);

	if (node == 0){
		rtn = 0;
	}
	else {
		GVAL *temp = getBSTNODEvalue(node);
		rtn = temp->count;
	}

	return rtn;

}
*/
int 				// void pointer type is a generic Value, returns count
findGSTcount(GST *t,void *v){
	GVAL *gv =  newGVAL(t, v);
	int rtn = 0;

	BSTNODE *node = findBST(t->tree, gv);

	if (node == 0){
		rtn = 0;
	}
	else {
		GVAL *temp = getBSTNODEvalue(node);
		rtn = temp->count;
	}
	// this might change
	free(gv);
	return rtn;

}

static void *	// void pointer type is GVAL, returns the GVAL
findGVAL(GST *t,void *v){
	GVAL *gv =  (GVAL *)v;
	void *rtn;

	BSTNODE *n = findBST(t->tree, gv);

	if (n != 0){
		GVAL *temp = getBSTNODEvalue(n);
		rtn = temp;
	}	
	else{
		rtn = 0;
	}

	return rtn;
}

// returns the value
void *			// void pointer type is generic value, returns that value
findGST(GST *t,void *v){
	GVAL *gv =  newGVAL(t, v);
	void *rtn;

	BSTNODE *n = findBST(t->tree, gv);
	//if (n == 0) printf("IS NULL");
	if (n != 0){
		GVAL *temp = getBSTNODEvalue(n);
		rtn = temp->value;
	}	
	else{
		rtn = 0;
	}
	// this might change
	free(gv);
	return rtn;
}

void
insertGST(GST *t,void *v){
	assert(t != 0);
	assert(v != 0);

	GVAL *new_GVAL = newGVAL(t, v);
	void *search = 0;

	if (sizeGST(t) == 0 || sizeBST(t->tree) == 0) {
		BSTNODE *added = insertBST(t->tree, new_GVAL);
		t->size += 1;

		// set the parent of the root to the root
		BSTNODE *r = getBSTroot(t->tree);
		setBSTNODEparent(added, r);
	}

	else{
		search = findGVAL(t, new_GVAL);

		if (search != 0) {
			GVAL *found = (GVAL *)search;
			found->count += 1;
			t->duplicates += 1;
		
			// free unused, duplicate GVAL
			gfree(new_GVAL);
		}
		else {
			insertBST(t->tree, new_GVAL);
			t->size += 1;
		}
	}
	

}

void *deleteGST(GST *t,void *v){
	GVAL *testGVAL = newGVAL(t, v);

	GVAL *foundGVAL = findGVAL(t, testGVAL);
	void *rtn = 0;

	//remove this later **
	/*
	if (foundGVAL == 0){
		fprintf(stdout, "%s", "Value ");
		t->display(v, stdout);
		fprintf(stdout, "%s", " not found.");
	}
	*/
	// **
	if (foundGVAL == 0) {
		rtn = 0;
	}

	else {
		if (foundGVAL->count > 1) {
			foundGVAL->count -= 1;
			t->duplicates -= 1;
		}
		else {
			BSTNODE *rtnNODE = deleteBST(t->tree, foundGVAL);
			GVAL *temp = getBSTNODEvalue(rtnNODE);
			rtn = temp->value;
			freeBSTNODE(rtnNODE, 0);
			free(temp);
			t->size -= 1;	
		}
	}
	free(testGVAL);

	return rtn;

}
/*
Duplicates: 2
Nodes: 8
Minimum depth: 2
Maximum depth: 4
*/
void 
statisticsGST(GST *t,FILE *fp){
	int dup_count;
	dup_count = duplicates(t);
	fprintf(fp, "Duplicates: %d\n", dup_count);
	statisticsBST(t->tree, fp);
}


void
displayGST(GST *t,FILE *fp){
	/*
	if (sizeGST(t) == 0){
		fprintf(fp, "%s\n", "EMPTY");
	}
	else{
		displayBSTdecorated(t->tree, fp);
	}
	*/
	displayBSTdecorated(t->tree, fp);
}

void
displayGSTdebug(GST *t,FILE *fp){
	displayBST(t->tree, fp);
}

void
freeGST(GST *t){
	BST *temp = t->tree;
	freeBST(temp);

	free(t);
}