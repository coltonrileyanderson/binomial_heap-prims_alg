/* 
 * queue.c 
 * by Colton Andreson
 * Jan 30, 2018
 * 
 * this is the implementation of queue.h. 
 * this implementation uses a generic doubly linked list to implement a typical queue.
 * queue operations are as followed: insert at back(bottom) of list and remove from front(top) of list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "queue.h"
#include "sll.h"

typedef struct queue 
	{
	SLL *list;

    int size;
    void (*display)(void *v, FILE *fp);
    void (*free)(void *v);

	}QUEUE;

QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)){
	QUEUE *items = malloc(sizeof(QUEUE));

    assert(items != 0);

    //d is the display function
    items->display = d;
    //f is the freeing function
    items->free = f;

    SLL *list = newSLL(items->display, items->free);
    items->list = list;

    items->size = 0;
    
    return items;
}


/************************************************************************************************************************************/
/* GETTERS */

//first elem, elem to be removed first
void *peekQUEUE(QUEUE *items){
    SLL *list = items->list;
    void *v;

    v = getSLL(list, 0);

    return v;
}

// size
int sizeQUEUE(QUEUE *items){
    SLL *list = items->list;
    int s;

    s = sizeSLL(list);

    return s;
}


/************************************************************************************************************************************/
/* MUTATORS */

void enqueue(QUEUE *items,void *value){
    SLL *list = items->list;
    int s = sizeQUEUE(items);

	insertSLL(list, s, value);
}
void *dequeue(QUEUE *items){
    SLL *list = items->list;
    void *v; 

    v = removeSLL(list, 0);

    return v;
}


/************************************************************************************************************************************/
/* VISUALIZERS */

// display QUEUE without debugging
void displayQUEUE(QUEUE *items,FILE *fp){
    int index = 0;
    int s = sizeQUEUE(items);

    fprintf(fp, "<");
    if(s == 0) {
        fprintf(fp, "%s",""); 
    } else {
        items->display(getSLL(items->list, index), fp);

        index++;
        while (index < s){
            fprintf(fp, "%s", ",");

            items->display(getSLL(items->list, index), fp);

            index++; 
        }
    }
    fprintf(fp, ">");
}

// display QUEUE with debugging
void displayQUEUEdebug(QUEUE *items,FILE *fp){
    SLL *list = items->list;

    displaySLLdebug(list, fp);
}


/************************************************************************************************************************************/
/* FREERS */

void freeQUEUE(QUEUE *items){
	SLL *list = items->list;

	freeSLL(list);

	free(items);
}