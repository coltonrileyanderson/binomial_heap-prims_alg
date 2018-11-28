#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "sll.h"
#include "queue.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(9383);
    QUEUE *p = newQUEUE(displayINTEGER,freeINTEGER);
    enqueue(p,newINTEGER(3));
    enqueue(p,newINTEGER(4));
    enqueue(p,newINTEGER(2));
    displayQUEUE(p,stdout);
    printf("\n");
    void *value = dequeue(p);
    displayINTEGER(value,stdout);
    printf("\n");
    freeINTEGER(value);
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    value = dequeue(p);
    displayINTEGER(value,stdout);
    printf("\n");
    freeINTEGER(value);
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    freeINTEGER(dequeue(p));
    displayQUEUE(p,stdout);
    printf("\n");
    displayQUEUEdebug(p,stdout);
    printf("\n");
    freeQUEUE(p);
    return 0;
    }
