/* 
 * dll.h 
 * by Colton Andreson
 * Jan 30, 2018
 * 
 * this is the header of dll.c. 
 * this header and it's accompanying implementation 
 * can be used to build a generic doubly linked list
 */

#ifndef __DLL_INCLUDED__
#define __DLL_INCLUDED__

#include <stdio.h>

typedef struct dll DLL;

extern DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)); 
extern void *insertDLL(DLL *items,int index,void *value);
extern void *removeDLL(DLL *items,int index);
extern void unionDLL(DLL *recipient,DLL *donor);
extern void *getDLL(DLL *items,int index);
extern void *setDLL(DLL *items,int index,void *value);
extern int sizeDLL(DLL *items);
extern void displayDLL(DLL *items,FILE *);
extern void displayDLLdebug(DLL *items,FILE *);
extern void freeDLL(DLL *items);

//new dll functions
extern void removeDLLall(DLL *);
extern void *removeDLLnode(DLL *,void *);
extern void firstDLL(DLL *);
extern void lastDLL(DLL *);
extern int moreDLL(DLL *);
extern void nextDLL(DLL *);
extern void prevDLL(DLL *);
extern void *currentDLL(DLL *);

//extern void *testPointers(DLL *items, FILE *fp);
#endif