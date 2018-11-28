/* 
 * stack.c 
 * by Colton Andreson
 * Jan 30, 2018
 * 
 * this is the implementation of stack.h. 
 * this implementation uses a generic doubly linked list to implement a typical stack.
 * stack operations are as followed: insert at front(top) of list and remove from front(top) of list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "stack.h"
#include "dll.h"

typedef struct stack 
    {
    DLL *list;

    int size;
    void (*display)(void *v, FILE *fp);
    void (*free)(void *v);
    } STACK;


/************************************************************************************************************************************/
/* CONSTRUCTOR */

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)) 
    {
    STACK *items = malloc(sizeof(STACK));
    assert(items != 0);
    //d is the display function
    items->display = d;
    //f is the freeing function
    items->free = f;

    DLL *list = newDLL(items->display, items->free);
    items->list = list;

    items->size = 0;
    
    return items;
    }

/************************************************************************************************************************************/
/* GETTERS */

//size
int sizeSTACK(STACK *items){
    DLL *list = items->list;
    int s;

    s = sizeDLL(list);

    return s;
}


//first elem, elem to be removed first
void *peekSTACK(STACK *items){
    DLL *list = items->list;
    void *v;

    v = getDLL(list, 0);

    return v;
}


/************************************************************************************************************************************/
/* MUTATORS */

// push value to top of stack
void push(STACK *items,void *value){
    DLL *list = items->list;

    insertDLL(list, 0, value);

}

// pop value from top of stack
void *pop(STACK *items){
    DLL *list = items->list;
    void *v; 

    v = removeDLL(list, 0);

    return v;
}


/************************************************************************************************************************************/
/* VISUALIZERS */

// display stack without debugging
void displaySTACK(STACK *items,FILE *fp) {
    int index = 0;
    int s = sizeSTACK(items);

    fprintf(fp, "|");
    if(s == 0) {
        fprintf(fp, "%s",""); 
    } else {
        items->display(getDLL(items->list, index), fp);

        index++;
        while (index < s){
            fprintf(fp, "%s", ",");

            items->display(getDLL(items->list, index), fp);

            index++; 
        }
    }
    fprintf(fp, "|");
}

// display stack with debugging
void displaySTACKdebug(STACK *items,FILE *fp) {
    DLL *list = items->list;

    displayDLLdebug(list, fp);
}



/************************************************************************************************************************************/
/* FREERS */

void freeSTACK(STACK *items) {
    DLL *list = items->list;
    
    freeDLL(list);

    free(items);
}
