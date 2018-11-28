/* 
 * test-gst.c 
 * by Colton Andreson
 * Feb 28, 2018
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "gst.h"
#include "string.h"
#include "scanner.h"

int main(void) {

	GST *t = newGST(displaySTRING, compareSTRING, freeSTRING);
	printf("\n");
	displayGST(t, stdout);
	displayGSTdebug(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	insertGST(t, newSTRING("c"));
	insertGST(t, newSTRING("z"));
	insertGST(t, newSTRING("k"));
	insertGST(t, newSTRING("d"));
	insertGST(t, newSTRING("f"));
	insertGST(t, newSTRING("j"));
	insertGST(t, newSTRING("d"));

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	printf("\n DELETE d\n");
	STRING *s = newSTRING("d");
	void *p = deleteGST(t, s);

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	freeSTRING(s);
	freeSTRING(p);

	printf("\n INSERT l\n");
	insertGST(t, newSTRING("l"));

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	printf("\n DELETE f\n");
	s = newSTRING("f");
	p = deleteGST(t, s);

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	freeSTRING(s);
	freeSTRING(p);
	
	printf("\n DELETE c\n");
	s = newSTRING("c");
	p = deleteGST(t, s);

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	freeSTRING(s);
	freeSTRING(p);

	printf("\n INSERT n\n");
	insertGST(t, newSTRING("n"));

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");
	
	printf("\n INSERT h\n");
	insertGST(t, newSTRING("h"));

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	printf("\n INSERT g\n");
	insertGST(t, newSTRING("g"));

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	printf("\n DELETE j\n");
	s = newSTRING("j");
	p = deleteGST(t, s);

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");

	freeSTRING(s);
	freeSTRING(p);

	printf("\n INSERT k\n");
	insertGST(t, newSTRING("k"));

	printf("\n");
	displayGST(t, stdout);
	printf("\n");
	statisticsGST(t, stdout);
	printf("\n");
	
 ///////////////////
	freeGST(t);
	return 0;
}
