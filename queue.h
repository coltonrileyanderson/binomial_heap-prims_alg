/* 
 * queue.h 
 * by Colton Andreson
 * Jan 30, 2018
 * 
 * this is the header of queue.c. 
 * this header and it's accompanying implementation 
 * can be used to build a generic singly linked list queue
 * queue operations are as followed: insert at back(bottom) of list and remove from front(top) of list.
 */

#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

#include <stdio.h>

typedef struct queue QUEUE;

extern QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)); 
extern void enqueue(QUEUE *items,void *value);
extern void *dequeue(QUEUE *items);
extern void *peekQUEUE(QUEUE *items);
extern int sizeQUEUE(QUEUE *items);
extern void displayQUEUE(QUEUE *items,FILE *);
extern void displayQUEUEdebug(QUEUE *items,FILE *);
extern void freeQUEUE(QUEUE *items);

#endif