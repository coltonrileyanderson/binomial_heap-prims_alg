#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "integer.h"
#include "string.h"
#include "real.h"

int main(void)
{  
  QUEUE *list = newQUEUE(displayINTEGER, freeINTEGER);

  int x; //used in peeking
  INTEGER *i; //used in dequeueing
  int size; //used in sizing

  // enqueue into QUEUE ->
  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");
  enqueue(list, newINTEGER(0));
  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");
  enqueue(list, newINTEGER(1));
  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");
  enqueue(list, newINTEGER(2));
  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");
  enqueue(list, newINTEGER(3));
  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");
  enqueue(list, newINTEGER(4));
  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");
  enqueue(list, newINTEGER(5));
  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  size = sizeQUEUE(list);
  printf("the size of list is: %d\n", size);

  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  printf("\n");
  printf("The value ");
  i = dequeue(list);                   //remove from front
  displayINTEGER(i,stdout);
  printf(" was removed.\n");
  freeINTEGER(i);
  printf("\n");

  size = sizeQUEUE(list);
  printf("the size of list1 is: %d\n", size);

  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  
  printf("\n");
  x = getINTEGER((INTEGER *) peekQUEUE(list));
  printf("peek QUEUE (first value): %d\n", x);
  printf("\n");

  printf("The value ");
  i = dequeue(list);                   //remove from front
  displayINTEGER(i,stdout);
  printf(" was removed.\n");
  freeINTEGER(i);
  printf("\n");

  size = sizeQUEUE(list);
  printf("the size of list1 is: %d\n", size);

  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  printf("\n");
  x = getINTEGER((INTEGER *) peekQUEUE(list));
  printf("peek QUEUE (first value): %d\n", x);

  printf("The value ");
  i = dequeue(list);                   //remove from front
  displayINTEGER(i,stdout);
  printf(" was removed.\n");
  freeINTEGER(i);
  printf("\n");

  size = sizeQUEUE(list);
  printf("the size of list1 is: %d\n", size);

  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  printf("\n");
  x = getINTEGER((INTEGER *) peekQUEUE(list));
  printf("peek QUEUE (first value): %d\n", x);

  printf("The value ");
  i = dequeue(list);                   //remove from front
  displayINTEGER(i,stdout);
  printf(" was removed.\n");
  freeINTEGER(i);
  printf("\n");

  size = sizeQUEUE(list);
  printf("the size of list1 is: %d\n", size);

  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  printf("\n");
  x = getINTEGER((INTEGER *) peekQUEUE(list));
  printf("peek QUEUE (first value): %d\n", x);

  printf("The value ");
  i = dequeue(list);                   //remove from front
  displayINTEGER(i,stdout);
  printf(" was removed.\n");
  freeINTEGER(i);
  printf("\n");

  size = sizeQUEUE(list);
  printf("the size of list1 is: %d\n", size);

  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  printf("\n");
  x = getINTEGER((INTEGER *) peekQUEUE(list));
  printf("peek QUEUE (first value): %d\n", x);

  printf("The value ");
  i = dequeue(list);                   //remove from front
  displayINTEGER(i,stdout);
  printf(" was removed.\n");
  freeINTEGER(i);
  printf("\n");

  size = sizeQUEUE(list);
  printf("the size of list1 is: %d\n", size);

  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  enqueue(list, newINTEGER(5));
  enqueue(list, newINTEGER(4));
  enqueue(list, newINTEGER(3));
  
  printf("\n");
  size = sizeQUEUE(list);
  printf("the size of list is: %d\n", size);

  displayQUEUE(list, stdout);
  printf("\n");
  displayQUEUEdebug(list, stdout);
  printf("\n");

  printf("\n");
  freeQUEUE(list);
  return 0;
}