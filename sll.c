/* 
 * sll.c 
 * by Colton Andreson
 * Jan 30, 2018
 * 
 * this is the implementation of sll.h. 
 * this implementation can be used to build a generic singly linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "sll.h"

/* PRIVATE INTERFACE STRUCT NODE */
typedef struct node
    {
    void *data;
    struct node *next;

    } NODE;

/* PUBLIC INTERFACE STRUCT SLL */

struct sll 
    {
    NODE *head;
    NODE *tail;

    int size;
    void (*display)(void *v, FILE *fp);
    void (*free)(void *v);
    };

/* CONSTRUCTOR */
static NODE *newNODE(void *d, NODE *n) {
    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    newNode->data = d;
    newNode->next = n;

    return newNode;
}

//insert a node that points to n(ext)
static NODE *insert(void *data, NODE *n) {
    NODE * newNode = newNODE(data, n);
    n = newNode;

    return n;
}


/*********************************/

/* CONSTRUCTOR */
SLL *newSLL(void (*d)(void *,FILE *),void (*f)(void *)) 
    {
    SLL *items = malloc(sizeof(SLL));
    assert(items != 0);
    items->head = NULL;
    items->tail = NULL;
    items->size = 0;
    //d is the display function
    items->display = d;
    //f is the freeing function
    items->free = f;
    return items;
    }

/* GETTERS */
int sizeSLL(SLL *items) {
    int size = 0;

    size = items->size;

    return size;
}

void *getSLL(SLL *items,int index) {
    NODE *temp, *tail;
    int i = 0;
    int s = sizeSLL(items);

    assert(index >= 0);
    assert(index < s);

    temp = items->head;
    tail = items->tail;

    // tail case
    if (index == (s - 1)){
        return tail->data;
    }

    // else case
    else {
        while(temp != NULL) {
            if (i == index) {
                return temp->data;
            }
            temp = temp->next;
            i += 1;
        }
    }

    return NULL;
}

/* SETTERS */
void *setSLLTail(SLL *items, NODE *node) {
    items->tail = node;

    return NULL;

}

void *setSLL(SLL *items,int index,void *value) {
    NODE *temp, *tail;
    int i = 0;
    void *item;

    int s = sizeSLL(items);

    assert(index >= 0);
    assert(index <= s);

    temp = items->head;

    // passed an empty items list, inserting at size (0)
    if (index == 0 && s == 0) {
        temp = newNODE(value, NULL);
        items->head = temp;
        items->tail = temp;

        items->size = 1;

        item = NULL;
    }

    // insert at tail
    else if (index == s) {
        // got to last element
        tail = items->tail;

        // create temp node with next set to null 
        temp = newNODE(value, NULL);
        tail->next = temp;

        items->size += 1;

        setSLLTail(items, temp);
        item = NULL;
    }

    // tail case
    else if (index == (s - 1)){
        tail = items->tail;

        item = tail->data;

        tail->data = value;
    }

    // mid case
    else {
        while(temp != NULL) {
            if (i == index) {
                item = temp->data;
                
                temp->data = value;
                break;
            }
            temp = temp->next;

            i += 1;
        } 
    }
    

    return item;
}

/* MUTATORS */
void insertSLL(SLL *items,int index,void *value) {
    /* find the prev node, starting from the first node*/
    NODE *current, *temp, *prev;
    int i = 0;
    int s = sizeSLL(items);

    assert(index >= 0);
    assert(index <= s);

    // INSERT at HEAD if list is NOT EMPTY
    if(items->size > 0 && index == 0) {
        current = items->head;

        // insert temp before current
        temp = insert(value, current);

        // set the list head
        items->head = temp;
    }

    // INSERT at HEAD if list EMPTY
    else if(items->head == NULL && index == 0) {
        temp = insert(value, NULL);
        items->head = temp;
        setSLLTail(items, temp);
    }

    // INSERT at MIDDLE
    else if (index > 0 && index != sizeSLL(items)){
        // insert by iterating from front
        current = items->head;

        while(current != NULL) {
            if (i == (index - 1)) {  
                prev = current;
                current = current->next;
                break;
            }
            // go visit each node and increment i until 
            // finding the index required
            current = current->next;
            i += 1;  
        } // end while not null

        // insert a node before current and set the 
        // node before temp to temp
        temp = insert(value, current);
        prev->next = temp;
    } // end if index > 0

    // INSERT at END
    else if(index == sizeSLL(items)){
        // got to last element
        current = items->tail;

        // create temp node with next set to null
        temp = newNODE(value, NULL);
        current->next = temp;

        setSLLTail(items, temp);
    }
    // incr size as last step
    items->size += 1;
}

void *removeSLL(SLL *items,int index) {
    NODE *current;
    current = items->head;
    NODE *prev;
    NODE *next;
    void *item;

    int i = 0;
    int s = sizeSLL(items);

    assert(s > 0);
    assert(index >= 0);
    assert(index < s);

    if(index == 0 && i == 0) {
        if(s == 1) {
            item = current->data;

            items->head = NULL;
            items->tail = NULL;
            items->size = 0;

            free(current);
        }

        else {
            items->head = current->next;
            
            //save current's data into item
            item = current->data;

            free(current);

            items->size -= 1;

            i = (index + 1);  
        }
        
    } 

    // removing from middle somewhere
    while (i < index) {

        if(i == (index - 1)){
            // set new tail if removing last element
            if((index + 1) == s) {
                items->tail = current;
            }

            // set prev to node before the one removing
            prev = current;
            current = current->next;

            //save current's data into item
            item = current->data;

            // remove current from list
            next = current->next;
            prev->next = next;

            //decrement and free
            items->size -= 1;
            free(current);

            break;
        } 

        current = current->next;
        i++;
    }
    
    // return data removed
    return item;
}

void unionSLL(SLL *recipient,SLL *donor){
    NODE *rt, *dh;

    if (recipient->head == NULL && donor->head != NULL) {
        assert(recipient->head != donor->head);
        recipient->head = donor->head;
        recipient->tail = donor->tail;
        recipient->size = donor->size;
        // set donor to empty
        donor->head = NULL;
        donor->tail = NULL;
        donor->size = 0;
        return;
    } else if (recipient->head != NULL && donor->head == NULL) {
        assert(recipient->head != donor->head);
        return;
    } else if (recipient->head == NULL && donor->head == NULL) {
        return;
    } else {
        // save r's tail, d's head
        rt = recipient->tail;
        dh = donor->head;

        // set r's tail to d's head
        rt->next = dh;

        // set r's tail to d's tail (end of the new list)
        recipient->tail = donor->tail; 
        
        //set new size
        int r_size = recipient->size;
        int d_size = donor->size;

        r_size = r_size + d_size;

        recipient->size = r_size;

        // set donor to empty
        donor->head = NULL;
        donor->tail = NULL;
        donor->size = 0;
    }
}

/* VISUALIZERS */

// display funct
void displaySLL(SLL *items,FILE *fp) {
    int index = 0;
    int s = sizeSLL(items);

    fprintf(fp, "{");
    if(s == 0) {
        fprintf(fp, "%s",""); 
    } else {
        items->display(getSLL(items, index), fp);

        index++;
        while (index < s){
            fprintf(fp, "%s", ",");

            items->display(getSLL(items, index), fp);

            index++; 
        }
    }
    fprintf(fp, "}");
}

// display debug funct
void displaySLLdebug(SLL *items,FILE *fp) {
    int index = 0;
    int s = sizeSLL(items);

    fprintf(fp, "head->{");
    if(s == 0) {
       //fprintf(fp, "%s","");
       fprintf(fp, "},tail->{"); 
    } else {
        items->display(getSLL(items, index), fp);

        index++;
        while (index < s){
            fprintf(fp, "%s", ",");

            items->display(getSLL(items, index), fp);

            index++;   
        }

        fprintf(fp, "},tail->{");
        
        items->display(getSLL(items, (sizeSLL(items) - 1)), fp);

    }
    fprintf(fp, "}");
}

/* FREERS */
void freeSLL(SLL *items) {

    NODE *current, *temp, *head;
    
    head = items->head;

    if(head != NULL)
    {
        current = head->next;

        if (items->free != NULL){
            items->free(head->data);
        }

        free(head);

        while(current != NULL)
        {
            temp = current->next;

            if (items->free != NULL){
                items->free(current->data);
            }
            
            free(current);

            current = temp;
        }
    
    }
    free(items);
}