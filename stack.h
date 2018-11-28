/* 
 * stack.h 
 * by Colton Andreson
 * Jan 30, 2018
 * 
 * this is the header of stack.c. 
 * this header and it's accompanying implementation 
 * can be used to build a generic doubly linked list stack
 * stack operations are as followed: insert at front(top) of list and remove from front(top) of list.
 */

#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

#include <stdio.h>

typedef struct stack STACK;

extern STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)); 
extern void push(STACK *items,void *value);
extern void *pop(STACK *items);
extern void *peekSTACK(STACK *items);
extern int sizeSTACK(STACK *items);
extern void displaySTACK(STACK *items,FILE *);
extern void displaySTACKdebug(STACK *items,FILE *);
extern void freeSTACK(STACK *items);

#endif