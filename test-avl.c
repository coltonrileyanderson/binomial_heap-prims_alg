/* 
 * test-avl.c 
 * by Colton Andreson
 * Feb 28, 2018
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "avl.h"
#include "string.h"
#include "scanner.h"

int main(void) {

	AVL *t = newAVL(displaySTRING, compareSTRING, freeSTRING);
	printf("\n");
	displayAVL(t, stdout);
	displayAVLdebug(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	insertAVL(t, newSTRING("c"));
	insertAVL(t, newSTRING("z"));
	insertAVL(t, newSTRING("k"));
	insertAVL(t, newSTRING("d"));
	insertAVL(t, newSTRING("f"));
	insertAVL(t, newSTRING("j"));
	insertAVL(t, newSTRING("d"));

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	printf("\n DELETE d\n");
	STRING *s = newSTRING("d");
	void *p = deleteAVL(t, s);

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	freeSTRING(s);
	freeSTRING(p);

	printf("\n INSERT l\n");
	insertAVL(t, newSTRING("l"));

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	printf("\n DELETE f\n");
	s = newSTRING("f");
	p = deleteAVL(t, s);

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	freeSTRING(s);
	freeSTRING(p);
	
	printf("\n DELETE c\n");
	s = newSTRING("c");
	p = deleteAVL(t, s);

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	freeSTRING(s);
	freeSTRING(p);

	printf("\n INSERT n\n");
	insertAVL(t, newSTRING("n"));

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");
	
	printf("\n INSERT h\n");
	insertAVL(t, newSTRING("h"));

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	printf("\n INSERT g\n");
	insertAVL(t, newSTRING("g"));

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	printf("\n DELETE j\n");
	s = newSTRING("j");
	p = deleteAVL(t, s);

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");

	freeSTRING(s);
	freeSTRING(p);

	printf("\n INSERT k\n");
	insertAVL(t, newSTRING("k"));

	printf("\n");
	displayAVL(t, stdout);
	printf("\n");
	statisticsAVL(t, stdout);
	printf("\n");
	
 ///////////////////
	freeAVL(t);
	return 0;
}