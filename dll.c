/* 
 * dll.c 
 * by Colton Andreson
 * Jan 30, 2018
 * 
 * this is the implementation of dll.h. 
 * this implementation can be used to build a generic doubly linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "dll.h"

/* PRIVATE INTERFACE STRUCT NODE */
typedef struct node
    {
    void *data;
    struct node *next;
    struct node *prev;

    } NODE;

/* PUBLIC INTERFACE STRUCT DLL */
struct dll 
    {
    NODE *head;
    NODE *tail;
    NODE *iterator;

    int size;
    void (*display)(void *v, FILE *fp);
    void (*free)(void *v);
    };

/* CONSTRUCTOR */

static NODE *newNODE(void *d, NODE *n, NODE *p) {
    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    newNode->data = d;
    newNode->next = n;
    newNode->prev = p;

    return newNode;
}

// insert a node that points to n(ext) and p(rev)
static NODE *insert(void *data, NODE *n, NODE *p) {
    NODE * newNode = newNODE(data, n, p);
    n = newNode;

    return n;
}


/*********************************/

/* CONSTRUCTOR */
DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)) 
    {
    DLL *items = malloc(sizeof(DLL));
    assert(items != 0);

    items->head = NULL;
    items->tail = NULL;
    items->iterator = NULL;

    items->size = 0;
    //d is the display function
    items->display = d;
    //f is the freeing function
    items->free = f;
    return items;
    }

/* GETTERS */
int sizeDLL(DLL *items) {
    int size = 0;

    size = items->size;

    return size;
}

void *getDLL(DLL *items,int index) {
    NODE *temp;
    int i = 0;
    int s = sizeDLL(items);
    int half = s / 2;

    assert(index >= 0);
    assert(index < s);

    if (index < half) {
        temp = items->head;

        while(temp != NULL && i != half) {
            if (i == index) {
                return temp->data;
            }
            
            temp = temp->next;

            i += 1;
        }
    }
    else if (index >= half) {
        temp = items->tail;
        i = s - 1;

        while(temp != NULL && i >= half) {
            if (i == index) {
                return temp->data;
            }
            
            temp = temp->prev;

            i -= 1;
        }
    }

    return NULL;
}

/* SETTERS */
void *setDLLTail(DLL *items, NODE *node) {
    items->tail = node;

    return NULL;

}

void *setDLL(DLL *items,int index,void *value) {
    NODE *temp, *tail;
    int i = 0;
    void * item;
    int s = sizeDLL(items);
    int half = s / 2;

    assert(index >= 0);
    assert(index <= s);

    // passed an empty items list, inserting at size (0)
    if (index == 0 && s == 0) {
        temp = newNODE(value, NULL, NULL);
        items->head = temp;
        items->tail = temp;

        items->size = 1;

        item = NULL;
    }

    // insert element at tail
    else if (index == s) {
        // got to last element
        tail = items->tail;

        // create temp node with next set to null and prev set to the list tail
        temp = newNODE(value, NULL, tail);
        tail->next = temp;

        items->size += 1;

        setDLLTail(items, temp);

        item = NULL;
    }

    // middle case less than half
    else if (index < half) {
        temp = items->head;
        while(temp != NULL && i != half) {
            if (i == index) {
                item = temp->data;
                temp->data = value;
                break;
            }

            temp = temp->next;
            i += 1;
        }
    }

    // middle case more than half
    else if (index >= half) {
        temp = items->tail;
        i = s - 1;
        while(temp != NULL && i >= half) {
            if (i == index) {
                item = temp->data;
                temp->data = value;
                break;
            }

            temp = temp->prev;
            i -= 1;
        }
    }

    return item;
}

/* MUTATORS */
void *insertDLL(DLL *items,int index,void *value) {

    /* find the prev node, starting from the first node*/
    NODE *current, *temp, *prev;
    int i = 0;

    int s = sizeDLL(items);
    int half = s / 2;

    assert(index >= 0);
    assert(index <= s);

    // INSERT at HEAD if list is NOT EMPTY
    if(items->size > 0 && index == 0) {
        current = items->head;

        // insert temp before current, set prev to NULL, current->prev to temp
        temp = insert(value, current, NULL);
        current->prev = temp;

        // set the list head
        items->head = temp;                                     
    }

    // INSERT at HEAD if list EMPTY
    else if(items->head == NULL && index == 0) {
        temp = insert(value, NULL, NULL);          
        items->head = temp;
        setDLLTail(items, temp);
    }

    // INSERT at MIDDLE
    else if (index > 0 && index != sizeDLL(items)){
        // insert by iterating from front
        if (index < half) {
            current = items->head;

            //loop through the list
            while(current != NULL && i != half) {
                // enter if when at prev node to the index inserting at
                if (i == (index - 1)) {  
                    prev = current;
                    current = current->next;
                    break;
                } 
                // go visit each node and increment i until finding the index required
                current = current->next;
                i += 1;  
            } // end while not null

            // create a temp node with current (node after the one inserting) 
            // and prev (node before the one inserting)
            temp = insert(value, current, prev);
            prev->next = temp;
            current->prev = temp;
        }

        // insert by iterating from back
        else if (index >= half) {
            current = items->tail;
            i = s - 1;

            //loop through the list
            while(current != NULL && i >= half) {
                // enter if when at prev node to the index inserting at
                if (i == index) {  
                    break;
                } 
                // go visit each node and increment i until finding the index required
                current = current->prev;
                i -= 1;  
            } // end while not null
            // set prev to the node before the one to be inserted
            prev = current->prev;

            // create a temp node with current (node after the one inserting) 
            // and prev (node before the one inserting)
            temp = insert(value, current, prev);
            prev->next = temp;
            current->prev = temp;
        }
    } // end if index > 0  

    // INSERT at END
    else if(index == sizeDLL(items)){
        // got to last element
        current = items->tail;

        // create temp node with next set to null and prev set to the list tail
        temp = newNODE(value, NULL, current);
        current->next = temp;

        setDLLTail(items, temp);
    }
    // incr size as last step
    items->size += 1;

    return temp;
}

void *removeDLL(DLL *items,int index) {
    NODE *current;
    current = items->head;
    NODE *prev;
    NODE *next;
    void *item;

    int i = 0;
    int s = sizeDLL(items);

    int half = s / 2; // used to determine whether or not to traverse from front or from back

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
            //save current's data into item
            item = current->data;

            next = current->next;
            items->head = next;

            next->prev = current->prev;

            free(current);

            items->size -= 1;
            if (items->size == 0){
                items->tail = NULL;
            }

            //i = (index + 1);
        }
    } 

    // removing tail element
    else if(index == (s - 1) && i == 0){
        current = items->tail;
        prev = current->prev;
        items->tail = prev;
        prev->next = NULL;

        //save current's data into item
        item = current->data;

        free(current);

        items->size -= 1;
        i = s;
    }

    // removing from bottom half middle somewhere
    else if (index < half) {
        while (current != NULL && i != half){
            if(i == (index - 1)){
                // set prev to node before the one removing
                prev = current;
                current = current->next;

                //save current's data into item
                item = current->data;

                // remove current from list
                next = current->next;
                prev->next = next;
                next->prev = prev;

                //decrement size
                items->size -= 1;
                free(current);

                break;
            } 

            current = current->next;
            i++;
        }
    }

    // removing from top half middle somewhere
    else if (index >= half) {
        i = s - 1;
        current = items->tail;

        while (current != NULL && i >= half){
            if(i == index){
                //save current's data into item
                item = current->data;

                // set next and prev, leaving current in the middle
                next = current->next;
                prev = current->prev;

                // set prev's next to next, and next's prev to prev
                // SKIP current, removing it from list
                prev->next = next;
                next->prev = prev;

                //decrement and free
                items->size -= 1;
                free(current);

                break;
            }

            current = current->prev;
            i--;
        }
    }

    // return data removed
    return item;
}

void unionDLL(DLL *recipient,DLL *donor){
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

        // set d's head's prev to r's tail
        dh->prev = rt;

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

void displayDLL(DLL *items,FILE *fp) {
    fprintf(fp, "{{");

    NODE *current = items->head;
    while (current != 0) {
        if (current->data != 0){
            items->display(current->data, fp);
            if (current != items->tail) {
                fprintf(fp, ",");
            }
        }
        current = current->next;
    }
    fprintf(fp, "}}");
}

void displayDLLdebug(DLL *items,FILE *fp) {
    int index = 0;
    int s = sizeDLL(items);

    fprintf(fp, "head->{{");
    if(s == 0) {
       //fprintf(fp, "%s","");
       fprintf(fp, "}},tail->{{"); 
    } else {
        items->display(getDLL(items, index), fp);

        index++;
        while (index < s){
            fprintf(fp, "%s", ",");

            items->display(getDLL(items, index), fp);

            index++;   
        }

        fprintf(fp, "}},tail->{{");
        
        items->display(getDLL(items, (sizeDLL(items) - 1)), fp);

    }
    fprintf(fp, "}}");
}


/* FREERS */
void freeDLL(DLL *items) {

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

void
removeDLLall(DLL *items){
    NODE *current, *head, *temp;
    if (items != 0) {
       head = items->head;

        if (head != 0) { 
            current = head->next;

            free(head);

            while (current != 0) {
                temp = current->next;

                free(current);

                current = temp;
            }
        }

        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->iterator = 0; 
    }
    
}

void *
removeDLLnode(DLL *items, void *n){
    NODE *removed = (NODE *)n; 
    if (items != 0) {
        if (removed != 0){
            NODE *removed_prev, *removed_next;
            removed_prev = removed->prev;
            removed_next = removed->next;


            if (removed_next != 0){
                removed_next->prev = removed->prev;
            }
            if (removed_prev != 0){
                removed_prev->next = removed->next;
            }

            if (removed == items->head) {
                items->head = removed->next;
            }

            if (removed == items->tail) {
                items->tail = removed->prev;
            }

            if (items->iterator == removed) {
                items->iterator = 0;
            }

            items->size -= 1;

            void *removed_data = removed->data;

            // might have to take this out -- will see when running tests
            free(removed);

            return removed_data; 
        }
    }
    return 0;
}

//sets the iterator to the head
void
firstDLL(DLL *items){
    //if (items != 0) {
        items->iterator = items->head;
    //}
}

//sets the iterator to the tail
void
lastDLL(DLL *items){
    //if (items != 0) {
        items->iterator = items->tail;
    //}
}

//returns 0 if iterator is null, 1 if it is not.
int moreDLL(DLL *items){
    if (items->iterator == 0) return 0;
    else return 1;
}

//returns the data of the iterator
void *currentDLL(DLL *items) {
    //if (items != 0 && items->iterator != 0) {
        NODE *i = items->iterator;
        return i->data;
    //}
    //else return 0;
}
//moves the iterator forward one node
void nextDLL(DLL *items) {
    //if (items != 0 && items->iterator != 0){
        NODE *i = items->iterator;
        NODE *next = i->next;
        items->iterator = next; 
    //}
    
}

//moves the iterator forward one node
void prevDLL(DLL *items) {
    //if (items != 0 && items->iterator != 0){
        NODE *i = items->iterator;
        NODE *prev = i->prev;
        items->iterator = prev; 
    //}
}