/* 
 * test-bst.c 
 * by Colton Andreson
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "scanner.h"


void displayTree(BST *t, FILE *fp);
void removeTree(BST *t, int value);
int main(void) {

	BST *t = newBST(displayINTEGER, compareINTEGER, NULL, freeINTEGER);
	
	printf("\n%s\n", "BST Before Insert:");
    printf("%s\n", "----------------------------------");
	displayTree(t, stdout);
	
	insertBST(t, newINTEGER(10));
	insertBST(t, newINTEGER(5));
	insertBST(t, newINTEGER(15));
	insertBST(t, newINTEGER(1));
	insertBST(t, newINTEGER(3));
	insertBST(t, newINTEGER(12));
	insertBST(t, newINTEGER(19));

	printf("\n%s\n", "BST After Insert:");
    printf("%s\n", "----------------------------------");
	displayTree(t, stdout);

	removeTree(t, 5);
	printf("\n%s\n", "BST After Removal:");
	printf("%s\n", "----------------------------------");
	displayTree(t, stdout);

	removeTree(t, 10);
	printf("\n%s\n", "BST After Removal:");
	printf("%s\n", "----------------------------------");
	displayTree(t, stdout);

	removeTree(t, 12);
	printf("\n%s\n", "BST After Removal:");
	printf("%s\n", "----------------------------------");
	displayTree(t, stdout);

	removeTree(t, 3);
	printf("\n%s\n", "BST After Removal:");
	printf("%s\n", "----------------------------------");
	displayTree(t, stdout);

	removeTree(t, 15);
	printf("\n%s\n", "BST After Removal:");
	printf("%s\n", "----------------------------------");
	displayTree(t, stdout);

	removeTree(t, 1);
	printf("\n%s\n", "BST After Removal:");
	printf("%s\n", "----------------------------------");
	displayTree(t, stdout);

	removeTree(t, 19);
	printf("\n%s\n", "BST After Removal:");
	printf("%s\n", "----------------------------------");
	displayTree(t, stdout);

	printf("\n%s\n\n", "freeing and exiting. . .");
	freeBST(t);
	return 0;
}

void 
displayTree(BST *t, FILE *fp) {
	printf("\n%s\n", "preorder:");
	displayBST(t, fp);
	printf("\n");

	printf("\n%s\n", "level-order:");
	displayBSTdebug(t, fp);
	printf("\n");

	statisticsBST(t, stdout);
	printf("\n");
}
void
removeTree(BST *t, int value){
	BSTNODE *temp;
	INTEGER *val;

	val = newINTEGER(value);

	printf("Removing value ");
	displayINTEGER(val, stdout);
	printf(". . .\n\n");

	temp = deleteBST(t, val);
	
	if (temp != NULL) {
		INTEGER *i = getBSTNODEvalue(temp);
		printf("The value ");
		displayINTEGER(i, stdout);
		printf(" was effectively removed.\n");

		freeBSTNODE(temp, freeINTEGER);
		freeINTEGER(val);

	}
	else {
		printf("The value ");
		displayINTEGER(val, stdout);
		printf(" was not in the tree.\n");
	}
}

   
