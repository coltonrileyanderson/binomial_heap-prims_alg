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

int main(void)
{  
   //srandom(1);
    //simple INTEGER test of BINOMIAL
    BINOMIAL *p = newBINOMIAL(displayINTEGER,compareINTEGER,0,freeINTEGER);
    insertBINOMIAL(p,newINTEGER(0));
    insertBINOMIAL(p,newINTEGER(1));
    insertBINOMIAL(p,newINTEGER(2));
    insertBINOMIAL(p,newINTEGER(3));
    insertBINOMIAL(p,newINTEGER(4));
    insertBINOMIAL(p,newINTEGER(5));
    insertBINOMIAL(p,newINTEGER(6));
    insertBINOMIAL(p,newINTEGER(7));
    insertBINOMIAL(p,newINTEGER(8));
    insertBINOMIAL(p,newINTEGER(9));
    insertBINOMIAL(p,newINTEGER(10));
    insertBINOMIAL(p,newINTEGER(11));
    insertBINOMIAL(p,newINTEGER(12));
    printf("heap:\n");
    displayBINOMIAL(p,stdout);
    printf("debug:\n");
    displayBINOMIALdebug(p,stdout);
    printf("min should be %d\n",getINTEGER(peekBINOMIAL(p)));
    INTEGER *r = extractBINOMIAL(p);
    printf("min was %d\n",getINTEGER(r));
    printf("min now is %d\n",getINTEGER(peekBINOMIAL(p)));
    freeINTEGER(r);
    printf("heap:\n");
    displayBINOMIAL(p,stdout);
    printf("debug:\n");
    displayBINOMIALdebug(p,stdout);
    printf("min should be %d\n",getINTEGER(peekBINOMIAL(p)));
    r = extractBINOMIAL(p);
    printf("min is %d\n",getINTEGER(r));
    printf("min was %d\n",getINTEGER(r));
    printf("min now is %d\n",getINTEGER(peekBINOMIAL(p)));
    freeINTEGER(r);
    printf("heap:\n");
    displayBINOMIAL(p,stdout);
    printf("debug:\n");
    displayBINOMIALdebug(p,stdout);
    printf("min should be %d\n",getINTEGER(peekBINOMIAL(p)));
    r = extractBINOMIAL(p);
    printf("min was %d\n",getINTEGER(r));
    freeINTEGER(r);
    printf("size: %d\n",sizeBINOMIAL(p));
    while (sizeBINOMIAL(p) > 0) {
        printf("size b4: %d\n",sizeBINOMIAL(p));
        r = extractBINOMIAL(p);
        printf("size after: %d\n",sizeBINOMIAL(p));
        printf("min is %d\n",getINTEGER(r));
        displayBINOMIAL(p,stdout);
        
        freeINTEGER(r);

    }
    freeBINOMIAL(p);


    return 0;
 }