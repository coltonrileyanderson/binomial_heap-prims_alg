#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"
#include "string.h"
#include "real.h"

static void show(DLL *items)
{
   printf("The items are ");
   displayDLL(items,stdout);
   printf(".\n");
   printf("The items (debugged) are ");
   displayDLLdebug(items,stdout);
   printf(".\n");
}

int main(void)
{  
   
   DLL *list1 = newDLL(displayINTEGER,freeINTEGER);
   DLL *list2 = newDLL(displayINTEGER,freeINTEGER);
   int index;
   int x;
   int size1, size2;
   int val, idx;
   INTEGER *i;

   printf("\n");
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   printf("\n");
   size1 = sizeDLL(list1);
   printf("list1 is: %d items long.\n\n", size1);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   printf("\n");
   size2 = sizeDLL(list2);
   printf("list2 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "filling list1 ...");

   insertDLL(list1,0,newINTEGER(1));   
   for (index = 2; index <= 20; index+=1){
      insertDLL(list1,sizeDLL(list1),newINTEGER(index));
   }

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);

   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);

   printf("%s\n", "********************************");
   printf("%s\n\n", "filling list2 ...");

   insertDLL(list2,0,newINTEGER(20));   
   for (index = 19; index > 0; index-=1){
      insertDLL(list2,sizeDLL(list2),newINTEGER(index));
   }

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);

   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "testing the insert functions ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");

   val = 100;
   idx = 5;
   printf("the value %d was inserted to %s at index %d\n", val, "list1", idx);
   insertDLL(list1,idx,newINTEGER(val));

   val = 200;
   idx = sizeDLL(list1);
   printf("the value %d was inserted to %s at index %d\n", val, "list1", idx);
   insertDLL(list1,idx,newINTEGER(val));

   val = 201;
   idx = sizeDLL(list1);
   printf("the value %d was inserted to %s at index %d\n", val, "list1", idx);
   insertDLL(list1,idx,newINTEGER(val));

   val = 300;
   idx = 0;
   printf("the value %d was inserted to %s at index %d\n", val, "list1", idx);
   insertDLL(list1,idx,newINTEGER(val));

   val = 301;
   idx = 0;
   printf("the value %d was inserted to %s at index %d\n", val, "list1", idx);
   insertDLL(list1,idx,newINTEGER(val));

   val = 400;
   idx = 17;
   printf("the value %d was inserted to %s at index %d\n", val, "list1", idx);
   insertDLL(list1,idx,newINTEGER(val));

   val = 500;
   idx = sizeDLL(list1) / 2;
   printf("the value %d was inserted to %s at index %d\n", val, "list1", idx);
   insertDLL(list1,idx,newINTEGER(val));
   printf("\n");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");

   val = 600;
   idx = 6;
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));

   val = 701;
   idx = 0;
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));

   val = 700;
   idx = 0;
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));

   val = 801;
   idx = sizeDLL(list2);
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));

   val = 800;
   idx = sizeDLL(list2);
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));

   val = 900;
   idx = 16;
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));

   val = 1000;
   idx = sizeDLL(list2) / 2;
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));

   val = 111;
   idx = sizeDLL(list2) / 2;
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));

   val = 222;
   idx = sizeDLL(list2) / 2;
   printf("the value %d was inserted to %s at index %d\n", val, "list2", idx);
   insertDLL(list2,idx,newINTEGER(val));
   printf("\n");


   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "testing the remove functions ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);

   idx = sizeDLL(list1) - 1;
   printf("The value ");
   i = removeDLL(list1,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = 0;
   printf("The value ");
   i = removeDLL(list1,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = 3;
   printf("The value ");
   i = removeDLL(list1,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = 13;
   printf("The value ");
   i = removeDLL(list1,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   printf("\n");
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   idx = sizeDLL(list2) - 1;
   printf("The value ");
   i = removeDLL(list2,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = 0;
   printf("The value ");
   i = removeDLL(list2,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = 3;
   printf("The value ");
   i = removeDLL(list2,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = 14;
   printf("The value ");
   i = removeDLL(list2,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = sizeDLL(list2) / 2;
   printf("The value ");
   i = removeDLL(list2,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = 17;
   printf("The value ");
   i = removeDLL(list2,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);

   idx = 2;
   printf("The value ");
   i = removeDLL(list2,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);
   
   printf("\n");
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist1 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "testing the union functions (BEFORE) ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   unionDLL(list1, list2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "union functions results (AFTER) ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "union functions (empty recipient) ...");

   unionDLL(list2, list1);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "union functions (empty donor) ...");

   unionDLL(list1, list2);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "union functions (both empty) ...");

   DLL *test = newDLL(displayINTEGER,freeINTEGER);
   unionDLL(test, list2);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "test:");
   show(test);
   size1 = sizeDLL(test);
   printf("\ntest is: %d items long.\n\n", size1);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2:");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);


   printf("%s\n", "********************************");
   printf("%s\n\n", "testing getDLL functions on list1 ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);

   idx = 0;
   x = getINTEGER((INTEGER *) getDLL(list1,idx));
   printf("list1 index %d: %d\n", idx, x);

   idx = 1;
   x = getINTEGER((INTEGER *) getDLL(list1,idx));
   printf("list1 index %d: %d\n", idx, x);

   idx = sizeDLL(list1) - 1;
   x = getINTEGER((INTEGER *) getDLL(list1,idx));
   printf("list1 index %d: %d\n", idx, x);

   idx = sizeDLL(list1) - 2;
   x = getINTEGER((INTEGER *) getDLL(list1,idx));
   printf("list1 index %d: %d\n", idx, x);

   idx = sizeDLL(list1) / 2;
   x = getINTEGER((INTEGER *) getDLL(list1,5));
   printf("list1 index %d: %d\n", idx, x);

   idx = 10;
   x = getINTEGER((INTEGER *) getDLL(list1,17));
   printf("list1 index %d: %d\n", idx, x);

   idx = 30;
   x = getINTEGER((INTEGER *) getDLL(list1,25));
   printf("list1 index %d: %d\n", idx, x);

   printf("\n");
   printf("%s\n", "********************************");
   printf("%s\n\n", "testing setDLL functions on list1 ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list1:");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nlist1 is: %d items long.\n\n", size1);

   val = 111;
   idx = 0;
   i = setDLL(list1, idx, newINTEGER(val));
   printf("The value ");
   displayINTEGER(i,stdout);
   freeINTEGER(i);
   printf(" was changed at index %d\n", idx);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("the index %d on %s has been set to %d. PRINT %s: \n\n", idx, "list1", val, "list1");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nthe size of list1 is now: %d\n", size1);

   val = 222;
   idx = sizeDLL(list1)-1;
   i = setDLL(list1, idx, newINTEGER(val));
   printf("\nThe value ");
   displayINTEGER(i,stdout);
   freeINTEGER(i);
   printf(" was changed at index %d\n", idx);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("the index %d on %s has been set to %d. PRINT %s: \n\n", idx, "list1", val, "list1");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nthe size of list1 is now: %d\n", size1);

   val = 333;
   idx = sizeDLL(list1);
   i = setDLL(list1, idx, newINTEGER(val));
   printf("\nThe value NULL");
   //displayINTEGER(i,stdout);
   freeINTEGER(i);
   printf(" was changed at index %d\n", idx);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("the index %d on %s has been set to %d. The list has gotten longer. PRINT %s: \n\n", idx, "list1", val, "list1");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nthe size of list1 is now: %d\n", size1);

   val = 444;
   idx = 7;
   i = setDLL(list1, idx, newINTEGER(val));
   printf("\nThe value ");
   displayINTEGER(i,stdout);
   freeINTEGER(i);
   printf(" was changed at index %d\n", idx);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("the index %d on %s has been set to %d. PRINT %s: \n\n", idx, "list1", val, "list1");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nthe size of list1 is now: %d\n", size1);

   val = 555;
   idx = 26;
   i = setDLL(list1, idx, newINTEGER(val));
   printf("\nThe value ");
   displayINTEGER(i,stdout);
   freeINTEGER(i);
   printf(" was changed at index %d\n", idx);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("the index %d on %s has been set to %d. PRINT %s: \n\n", idx, "list1", val, "list1");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nthe size of list1 is now: %d\n", size1);

   val = 666;
   idx = (sizeDLL(list1) / 2) +1;
   i = setDLL(list1, idx, newINTEGER(val));
   printf("\nThe value ");
   displayINTEGER(i,stdout);
   freeINTEGER(i);
   printf(" was changed at index %d\n", idx);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("the index %d on %s has been set to %d. PRINT %s: \n\n", idx, "list1", val, "list1");
   show(list1);
   size1 = sizeDLL(list1);
   printf("\nthe size of list1 is now: %d\n", size1);

   printf("\n");
   printf("%s\n", "********************************");
   printf("%s\n\n", "testing setDLL functions on list2 (an empty list) ...");

   val = 1111;
   idx = sizeDLL(list2);
   i = setDLL(list2, idx, newINTEGER(val));
   printf("The value NULL");
   //displayINTEGER(i,stdout);
   freeINTEGER(i);
   printf(" was changed at index %d\n", idx);
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("the index %d on %s has been set to %d. The list has gotten longer. PRINT %s: \n\n", idx, "list2", val, "list2");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nthe size of list2 is now: %d\n", size2);

   printf("\n");
   printf("%s\n", "********************************");
   printf("%s\n\n", "emptying list2 ...");

   idx = sizeDLL(list2) - 1;
   printf("The value ");
   i = removeDLL(list2,idx);
   displayINTEGER(i,stdout);
   printf(" was removed from index %d\n", idx);
   freeINTEGER(i);
   printf("\n");
   printf("%s\n", "list2 (after remove):");
   show(list2);

   printf("\n");
   printf("%s\n", "********************************");
   printf("%s\n\n", "rebuilding list2 ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2 (empty):");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   INTEGER *nines = newINTEGER(999);
   INTEGER *eights = newINTEGER(888);
   INTEGER *sevens = newINTEGER(777);

   insertDLL(list2, 0, nines);
   insertDLL(list2, 0, eights);
   insertDLL(list2, 0, sevens);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2 (rebuilt):");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "testing remove till null (from BACK) ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2 (start):");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   while (sizeDLL(list2) > 0) {
      idx = sizeDLL(list2) - 1;
      printf("The value ");
      i = removeDLL(list2,idx);
      displayINTEGER(i,stdout);
      printf(" was removed from index %d\n", idx);
      freeINTEGER(i);
      printf("\n");
      printf("%s\n", "list2 (after remove):");
      show(list2);
      printf("\n");
   }
   
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2 (end):");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   printf("\n");
   printf("%s\n", "********************************");
   printf("%s\n\n", "rebuilding list2 ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2 (empty):");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   nines = newINTEGER(999);
   eights = newINTEGER(888);
   sevens = newINTEGER(777);

   insertDLL(list2, 0, nines);
   void *removeDLLnode_tester = insertDLL(list2, 0, eights);
   insertDLL(list2, 0, sevens);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2 (rebuilt):");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   printf("%s\n", "********************************");
   printf("%s\n\n", "testing remove till null (from FRONT) ...");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2 (start):");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);
   /*
   while (sizeDLL(list2) > 0) {
      idx = 0;
      printf("The value ");
      i = removeDLL(list2,idx);
      displayINTEGER(i,stdout);
      printf(" was removed from index %d\n", idx);
      freeINTEGER(i);
      printf("\n");
      printf("%s\n", "list2 (after remove):");
      show(list2);
      printf("\n");
   }
   
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "list2 (end):");
   show(list2);
   size2 = sizeDLL(list2);
   printf("\nlist2 is: %d items long.\n\n", size2);

   */
   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "test iterator:");

   int moreDLL_test;
   INTEGER *currentDLL_test;

   moreDLL_test = moreDLL(list2);
   printf("%d\n", moreDLL_test);

   firstDLL(list2);
   currentDLL_test = currentDLL(list2);
   displayINTEGER(currentDLL_test, stdout);
   printf("\n");
   moreDLL_test = moreDLL(list2);
   printf("%d\n", moreDLL_test);

   nextDLL(list2);
   currentDLL_test = currentDLL(list2);
   displayINTEGER(currentDLL_test, stdout);
   printf("\n");
   moreDLL_test = moreDLL(list2);
   printf("%d\n", moreDLL_test);

   lastDLL(list2);
   currentDLL_test = currentDLL(list2);
   displayINTEGER(currentDLL_test, stdout);
   printf("\n");
   moreDLL_test = moreDLL(list2);
   printf("%d\n", moreDLL_test);

   prevDLL(list2);
   currentDLL_test = currentDLL(list2);
   displayINTEGER(currentDLL_test, stdout);
   printf("\n");
   moreDLL_test = moreDLL(list2);
   printf("%d\n", moreDLL_test);

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "removeDLLnode:");

   INTEGER *returned_data = removeDLLnode(list2, removeDLLnode_tester);
   show(list2);
   printf("returned: \n");
   displayINTEGER(returned_data, stdout);
   printf("\n");

   printf("%s\n", "--------------------------------------------------------------------------------------------------------");
   printf("%s\n", "removeDLLall:");

   removeDLLall(list2);
   show(list2);
   freeINTEGER(nines);
   freeINTEGER(eights);
   freeINTEGER(sevens);
   printf("\n");

   printf("%s\n", "********************************");
   printf("%s\n\n", "free function, when the DLL isn't passed a freeing function (freeing function is null) ...");

   DLL* testFREE = newDLL(displayINTEGER, NULL);

   freeDLL(testFREE);

   printf("\n--------------------------------------------------------------------------------------------------------\nFreeing the list.\n");
   freeDLL(list1);
   freeDLL(list2);
   freeDLL(test);
   return 0;
 }