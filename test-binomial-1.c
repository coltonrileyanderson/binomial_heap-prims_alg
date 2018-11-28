#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "dll.h"
#include "queue.h"
#include "bst.h"
#include "avl.h"
#include "vertex.h"
#include "edge.h"
#include "binomial.h"
#include "integer.h"
#include "string.h"
#include "real.h"

void 
show(BINOMIAL *t){
   //printf("\n");
   displayBINOMIAL(t, stdout);
   displayBINOMIALdebug(t, stdout);
   statisticsBINOMIAL(t, stdout);
   printf("\n");
}

int main(void)
{  
   printf("\n");
   BINOMIAL *test = newBINOMIAL(displayINTEGER, compareINTEGER, 0, freeINTEGER);

   printf("INITIALIZE AND PRINT EMPTY BINOMIAL HEAP:\n");
   printf("*****************************************\n");
   show(test);

   printf("INSERT 0-12 IN BINOMIAL HEAP AND PRINT:\n");
   printf("***************************************\n");
   //insert 0-12
   insertBINOMIAL(test, newINTEGER(0));
   insertBINOMIAL(test, newINTEGER(1));
   insertBINOMIAL(test, newINTEGER(2));
   insertBINOMIAL(test, newINTEGER(3));
   insertBINOMIAL(test, newINTEGER(4));
   insertBINOMIAL(test, newINTEGER(5));
   insertBINOMIAL(test, newINTEGER(6));
   insertBINOMIAL(test, newINTEGER(7));
   insertBINOMIAL(test, newINTEGER(8));
   insertBINOMIAL(test, newINTEGER(9));
   insertBINOMIAL(test, newINTEGER(10));
   insertBINOMIAL(test, newINTEGER(11));
   insertBINOMIAL(test, newINTEGER(12));
   //show 0-12
   show(test);

   printf("TEST sizeBINOMIAL:\n");
   printf("******************\n");
   int test_size;
   test_size = sizeBINOMIAL(test);
   printf("%d\n\n", test_size);

   printf("TEST peekBINOMIAL:\n");
   printf("******************\n");
   INTEGER *test_peek;
   test_peek = peekBINOMIAL(test);
   displayINTEGER(test_peek, stdout);
   printf("\n\n");

   printf("TEST extractBINOMIAL AND DISPLAY BINOMIAL HEAP AFTER:\n");
   printf("*****************************************************\n");
   INTEGER *test_extract;
   test_extract = extractBINOMIAL(test);
   printf("EXTRACTED: ");
   displayINTEGER(test_extract, stdout);
   printf("\n");
   show(test);
   freeINTEGER(test_extract);

   printf("TEST extractBINOMIAL AND DISPLAY BINOMIAL HEAP AFTER:\n");
   printf("*****************************************************\n");
   //INTEGER *test_extract;
   test_extract = extractBINOMIAL(test);
   printf("EXTRACTED: ");
   displayINTEGER(test_extract, stdout);
   printf("\n");
   show(test);
   freeINTEGER(test_extract);

   



   //free test
   freeBINOMIAL(test);
   return 0;
 }