/* 
 * gst.h
 * by Colton Andreson
 * Feb 28, 2018
 * 
 */
#ifndef __GST_INCLUDED__
#define __GST_INCLUDED__

#include <stdio.h>

typedef struct gst GST;

extern GST *newGST(
    void (*)(void *,FILE *),           //display
    int (*)(void *,void *),           //comparator
    void (*)(void *));                 //freeing function
extern void insertGST(GST *,void *);
extern int findGSTcount(GST *,void *);
extern void *findGST(GST *,void *);
extern void *deleteGST(GST *,void *);
extern int sizeGST(GST *);
extern int duplicates(GST *);
extern void statisticsGST(GST *,FILE *);
extern void displayGST(GST *,FILE *);
extern void displayGSTdebug(GST *,FILE *);
extern void freeGST(GST *);

#endif