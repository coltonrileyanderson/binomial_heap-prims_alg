/* 
 * real.c 
 * by Colton Andreson
 * Jan 30, 2018
 * 
 * this is the implementation of real.h. 
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "real.h"

struct REAL
    {
    double value;
    };

REAL *
newREAL(double x)
    {
    REAL *p = malloc(sizeof(REAL));
    assert(p != 0);
    p->value = x;
    return p;
    }

double 
getREAL(REAL *v)
    {
    return v->value;
    }

double 
setREAL(REAL *v,double x)
    {
    double old = v->value;
    v->value = x;
    return old;
    }

void 
displayREAL(void *v,FILE *fp)
    {
    fprintf(fp,"%f",getREAL((REAL *) v));
    }

int 
compareREAL(void *v,void *w)
    {
    double d = getREAL(v) - getREAL(w);

    if(d > 0) {
        return 1;
    }

    if(d < 0) {
        return -1;
    }

    else {
        return 0;
    }
    }
   
int 
compareREALdecr(void *v,void *w)
    {
    double d = getREAL(w) - getREAL(v);
 
    if(d < 0) {
        return -1;
    }

    else if(d > 0) {
        return 1;
    }

    else {
        return 0;
    }
    }


void
freeREAL(void *v)
    {
    free((REAL *) v);
    }
