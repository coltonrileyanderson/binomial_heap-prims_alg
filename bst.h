#ifndef __BST_INCLUDED__
#define __BST_INCLUDED__

#include <stdio.h>

typedef struct bstnode BSTNODE;

extern BSTNODE *newBSTNODE(void *v);                                // D
extern void    *getBSTNODEvalue(BSTNODE *n);                        // D
extern void    setBSTNODEvalue(BSTNODE *n,void *value);             // D
extern BSTNODE *getBSTNODEleft(BSTNODE *n);                         // D
extern void    setBSTNODEleft(BSTNODE *n,BSTNODE *replacement);     // D
extern BSTNODE *getBSTNODEright(BSTNODE *n);                        // D
extern void    setBSTNODEright(BSTNODE *n,BSTNODE *replacement);    // D
extern BSTNODE *getBSTNODEparent(BSTNODE *n);                       // D
extern void    setBSTNODEparent(BSTNODE *n,BSTNODE *replacement);   // D
extern void    freeBSTNODE(BSTNODE *n,void (*free)(void *));        // D

typedef struct bst BST;

extern BST *newBST(
    void (*)(void *,FILE *),           //display
    int (*)(void *,void *),            //comparator
    void (*)(BSTNODE *,BSTNODE *),     //swapper
    void (*)(void *));                 //free
extern BSTNODE *getBSTroot(BST *t);                                 // D
extern void    setBSTroot(BST *t,BSTNODE *replacement);             // D
extern void    setBSTsize(BST *t,int s);                            // D
extern BSTNODE *insertBST(BST *t,void *value);                      // D
extern BSTNODE *findBST(BST *t,void *value);                        // D
extern BSTNODE *deleteBST(BST *t,void *value);                      // D
extern BSTNODE *swapToLeafBST(BST *t,BSTNODE *node);                // D
extern void    pruneLeafBST(BST *t,BSTNODE *leaf);                  // D
extern int     sizeBST(BST *t);                                     // D
extern void    statisticsBST(BST *t,FILE *fp);                      // 
extern void    displayBST(BST *t,FILE *fp);                         // D
extern void    displayBSTdebug(BST *t,FILE *fp);                    // D
extern void    displayBSTdecorated(BST *t,FILE *fp);                    // D
extern void    freeBST(BST *t);                                     // D
#endif