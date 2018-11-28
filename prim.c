/* 
 * prim.c 
 * by Colton Andreson
 * Feb 28, 2018
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "scanner.h"
#include "string.h"
#include "integer.h"
#include "edge.h"
#include "vertex.h"
#include "real.h"
#include "avl.h"
#include "binomial.h"
//remove
#include "queue.h"

// holds the name of the corpus file
char *graphFile = "";

// 0 = don't explain, 1 = explain;
int explain = 0;

int LARGESTLEVEL = 0;
int WEIGHT = 0;
//static void insertInto(BINOMIAL *bin1, BINOMIAL *bin2, )
static void stoogesort(VERTEX *a[], int i, int j);
static void primMST(BINOMIAL *pq, void *vert);
static void displayMST(VERTEX *src, FILE *fp);
static void *readGraph(FILE *f, AVL *edges, AVL *vertices, BINOMIAL *bin);
static void updateVERTEX(void *v1, void *v2);
static void explainer(FILE *);
static int checkForWeight(FILE *fp);
static void skipWhiteSpace(FILE *fp);
static void Fatal(char *,...);
//static int processOptions(int,char **);

//static char *cleanSTR(char *data, int space);


int
main(int argc,char **argv) {
	//int argIndex;

	if (argc == 1) Fatal("%d arguments!\n",argc-1);

    graphFile = argv[argc-1];
    
    if (strcmp(graphFile, "-v") == 0) 
        explain = 1;
    //processOptions(argc,argv);

    if (explain == 0){
        FILE *inFile = fopen(graphFile, "r");

        if (NULL != inFile) {
            fseek (inFile, 0, SEEK_END);
            int size = ftell(inFile);

            if (size != 0) {
                fseek(inFile, 0, SEEK_SET);
                AVL *edgeTree = newAVL(displayEDGE, compareEDGE, freeEDGE);
                AVL *vertexTree = newAVL(displayVERTEX, compareVERTEX, freeVERTEX);
                BINOMIAL *vertexHeap = newBINOMIAL(displayVERTEX, compareVERTEX, updateVERTEX, freeVERTEX);

                void *v = readGraph(inFile, edgeTree, vertexTree, vertexHeap);

                primMST(vertexHeap, v);
                displayMST(v, stdout);
            }
            else {
                printf("EMPTY\n");
            }
        }
        fclose(inFile);
    }

    else if (explain == 1) {
        explainer(stdout);
    }
	return 0;
}

//written by John C. Lusth in scanner.c
static void
skipWhiteSpace(FILE *fp)
    {
    int ch;

    /* read chars until a non-whitespace character is encountered */

    while ((ch = fgetc(fp)) != EOF && isspace(ch))
        continue;

    /* a non-space character got us out of the loop, so push it back */

    if (ch != EOF) ungetc(ch,fp);
    }


static void
skipNotDigit(FILE *fp)
    {
    int ch;

    /* read chars until a non-whitespace character is encountered */

    while ((ch = fgetc(fp)) != EOF && !isdigit(ch))
        continue;

    /* a non-space character got us out of the loop, so push it back */

    if (ch != EOF) ungetc(ch,fp);
    }

// adapted from John C. Lusth's "stringPending" function in scanner.c
static int
checkForWeight(FILE *fp)
    {
    int ch,result = 0;
    skipWhiteSpace(fp);
    ch = fgetc(fp);
    if (ch == EOF) {
        return 0;
    }
    if (ch == ';') {
        result = 1;
    }
    ungetc(ch,fp);
    return result;
    }

static void
updateVERTEX(void *v1, void *v2) {
    VERTEX *a = (VERTEX *)v1;

    setVERTEXowner(a, v2);
}

static void
explainer(FILE *fp){
    fprintf(fp, "Colton Anderson - 11625747 - CS201 - SPRING 2018 - LUSTH\n");
}

void
Fatal(char *fmt, ...) {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
}

static void setNeighborWeights(AVL *vertices, VERTEX *v1, VERTEX *v2, int w) {
    VERTEX *a = findAVL(vertices, v1);
    VERTEX *b = findAVL(vertices, v2);

    if (a == b) {
        return;
    }

    DLL *n1 = getVERTEXneighbors(a);
    DLL *n2 = getVERTEXneighbors(b);
    //DLL *w1 = getVERTEXweights(a);
    //DLL *w2 = getVERTEXweights(b);
    
    if (sizeDLL(n1) == 0 && sizeDLL(n2) == 0) {
        insertVERTEXneighbor(a, b);
        insertVERTEXweight(a, w);
        insertVERTEXneighbor(b, a);
        insertVERTEXweight(b, w);

    }
    else {
        lastDLL(n1);
        VERTEX *tail = 0;
        if (moreDLL(n1)){

            tail = currentDLL(n1);
        }
        firstDLL(n1);
        VERTEX *current = 0;
        int flag = 0;
        while (current != tail){
            current = currentDLL(n1);
            if (current == b){
                flag = 1;
                break;
            }
            nextDLL(n1);
        }

        if (flag == 0) {
            insertVERTEXneighbor(a, b);
            insertVERTEXweight(a, w);
            insertVERTEXneighbor(b, a);
            insertVERTEXweight(b, w);
        }
    }
}

static void *
readGraph(FILE *f, AVL *edges, AVL *vertices, BINOMIAL *bin){
    int int1 = 0, int2 = 0, w = 0;
    // get first 2 vertices
    skipWhiteSpace(f);
    int1 = readInt(f);
    //printf("success1\n");

    skipWhiteSpace(f);
    int2 = readInt(f);
    //printf("success2\n");

    // check to see if there is an edge weight, if not, set it to 1.
    if (checkForWeight(f) == 1) {
        w = 1;
    }
    else {
        w = readInt(f);
        //printf("success3\n");
    }
    
    if (int1 < int2) {
        insertAVL(edges, newEDGE(int1, int2, w));
    } else {
        insertAVL(edges, newEDGE(int2, int1, w));
    }

    VERTEX *v1 = newVERTEX(int1);
    VERTEX *v2 = newVERTEX(int2);

    insertAVL(vertices, v1);
    void *pv1 = insertBINOMIAL(bin, v1);
    setVERTEXowner(v1, pv1);

    setVERTEXpred(v1, 0);
    //setVERTEXkey(v1, 0);

    insertAVL(vertices, v2);
    
    setVERTEXowner(v2, insertBINOMIAL(bin, v2));
    setVERTEXpred(v2, 0);

    setNeighborWeights(vertices, v1, v2, w);

    skipNotDigit(f);

    while (!feof(f)) {
        //printf("!feof\n");
        // get next 2 vertices
        skipWhiteSpace(f);
        int1 = readInt(f);
        //printf("success4\n");
        skipWhiteSpace(f);
        int2 = readInt(f);

        // check to see if there is an edge weight, if not, set it to 1.
        if (checkForWeight(f) == 1) {
            w = 1;
        }
        else {
            w = readInt(f);
        }
        
        if (int1 < int2) {
            EDGE *e1 = newEDGE(int1, int2, w);
            if (!findAVL(edges, e1)) {
                insertAVL(edges, e1);
            }
            
        } else {
            EDGE *e2 = newEDGE(int2, int1, w);
            if (!findAVL(edges, e2)) {
                insertAVL(edges, e2);
            }
            
        }

        VERTEX *first = newVERTEX(int1);
        VERTEX *second = newVERTEX(int2);

        if (!findAVL(vertices, first)){
            insertAVL(vertices, first);
            setVERTEXpred(first, 0);
            setVERTEXowner(first, insertBINOMIAL(bin, first));
           //setVERTEXkey(first, INT_MAX);
        }
        if (!findAVL(vertices, second)){
            insertAVL(vertices, second);
            setVERTEXpred(second, 0);
            setVERTEXowner(second, insertBINOMIAL(bin, second));
            //setVERTEXkey(second, INT_MAX);
        }

        setNeighborWeights(vertices, first, second, w);

        skipNotDigit(f);
    }

    return v1;
}
    
static void primMST(BINOMIAL *pq, void *vert) { 
    VERTEX *origin = (VERTEX *)vert;
    setVERTEXkey(origin, 0);
    decreaseKeyBINOMIAL(pq, getVERTEXowner(origin), origin);;

    VERTEX *u = 0;
    VERTEX *v = 0;

    DLL *u_n;
    DLL *u_w;

    int u_n_size = 0;
    int u_w_size = 0;
    //int test = 0;
    int i;

    int uv_weight = 0;

    while (sizeBINOMIAL(pq) > 0){
        u = extractBINOMIAL(pq);

        if (getVERTEXpred(u) != 0) {
            insertVERTEXsuccessor(getVERTEXpred(u), u);
        }
        setVERTEXflag(u, 1);        
        // DLL lists of u's neighbors and u's weights
        u_n = getVERTEXneighbors(u);
        u_w = getVERTEXweights(u);

        u_n_size = sizeDLL(u_n);
        u_w_size = sizeDLL(u_w);
        // check to make sure the lists are the same size, if not break;

        i = 0;
        for (i = 0; i < u_n_size && i < u_w_size; i++){

            //vertex v in u_n at index i
            v = getDLL(u_n, i);
            //printf("Hello%d\n", compareVERTEX(u, v));
            uv_weight = getINTEGER(getDLL(u_w, i));
            
            if (getVERTEXkey(v) == -1) {
                setVERTEXkey(v, INT_MAX);
            }
            
            if (/*getVERTEXkey(v) || */uv_weight < getVERTEXkey(v)) {
                if (getVERTEXflag(v) != 1) {
                    setVERTEXkey(v, uv_weight);
                    decreaseKeyBINOMIAL(pq, getVERTEXowner(v), v);
                    setVERTEXpred(v, u);
                }
            }
        }
    }
}

// adapted from Geeks for Geeks
static void stoogesort(VERTEX *a[], int i, int j)
{
    VERTEX *temp;
    int k;

    VERTEX *ai = a[i];
    VERTEX *aj = a[j];

    if (getVERTEXnumber(ai) > getVERTEXnumber(aj)){
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    /*
    if (a[i] > a[j])
    {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;        
    }
    */
    if ((i + 1) >= j)
        return;
    k = (int)((j - i + 1) / 3);
    stoogesort(a, i, j - k);
    stoogesort(a, i + k, j);
    stoogesort(a, i, j - k);
}

static int levelCounter(VERTEX *v) {
    int level = 0;
    VERTEX *pred = getVERTEXpred(v);

    if(pred == 0) {
        return level;
    }
    else {
        while (pred != 0) {
            pred = getVERTEXpred(pred);
            level++;
        }
        if (level > LARGESTLEVEL) {
            LARGESTLEVEL = level;
        }
        return level;
    }
    //return rtn;
}

static void displayFormat(VERTEX *v, FILE *fp){
    displayVERTEX(v, fp);
    fprintf(fp, "(");
    displayVERTEX(getVERTEXpred(v), fp);
    int k = getVERTEXkey(v);
    WEIGHT += k;
    fprintf(fp, ")%d", k);

}
static void inserter(DLL *arr[], VERTEX *v, int level, FILE *fp){
    DLL *succ = getVERTEXsuccessors(v);
    if (sizeDLL(succ) == 0) return;

    DLL *temp = arr[level];

    int size = sizeDLL(succ);
    int i;

    for (i = 0; i < size; i++){
        VERTEX *x = getDLL(succ, i);
        insertDLL(temp, sizeDLL(temp), x);
        inserter(arr, x, level+1, fp);
    }


}

static void helper(DLL *d, VERTEX *v, int level, FILE *fp) {
    DLL *succ = getVERTEXsuccessors(v);
    if (sizeDLL(succ) == 0) return;

    int size = sizeDLL(succ);

    int i;
    for (i = 0; i < size; i++) {
        VERTEX *x = getDLL(succ, i);
        levelCounter(x);
        helper(d, x, level+1, fp);
    }
}

static void levelPrinter(DLL *l, int level, FILE *fp) {
    int size = sizeDLL(l);

    VERTEX *arr[size];
    int i;
    for (i = 0; i < size; i++) {
        VERTEX *x = getDLL(l, i);
        arr[i] = x;
    }
    stoogesort(arr, 0, size-1);

    fprintf(fp, "%d: ", level+1);

    for (i = 0; i < size; i++) {
        displayFormat(arr[i], fp);
        if (i == size-1) fprintf(fp, "\n");
        else fprintf(fp, " ");
    }
}
static void displayMST(VERTEX *src,  FILE *fp){
    fprintf(fp, "0: ");
    displayVERTEX(src, fp);
    fprintf(fp, "\n");
    DLL *d = newDLL(0, 0);

    // function that counts the number of levels needed
    helper(d, src, 1, fp);

    DLL *dllarr[LARGESTLEVEL];

    // inserts a newDLL in each level arr index
    int i;
    for (i = 0; i < LARGESTLEVEL; i++) {
        dllarr[i] = newDLL(0,0);
    }
    inserter(dllarr, src, 0, fp);

    //prints each level
    for (i = 0; i < LARGESTLEVEL; i++) {
        DLL *levelDLL = dllarr[i];
        levelPrinter(levelDLL, i, fp);
    }
    fprintf(fp, "weight: %d\n", WEIGHT);
}

