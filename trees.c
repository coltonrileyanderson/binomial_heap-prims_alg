/* 
 * trees.c 
 * by Colton Andreson
 * Feb 28, 2018
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "bst.h"
#include "gst.h"
#include "avl.h"
#include "string.h"

// holds the name of the corpus file
char *corpusname = "";

// holds the name of the commands file
char *commandsname = "";

// 0 = don't explain, 1 = explain;
int explain = 0;

// 0 = AVL, 1 = GST;
int tree_type = 0;

static void* corpus_processor(int, FILE *);
static void explainer(FILE *);
static void* commands_processor(int, void *, FILE *);

static void inserter(int, void *, void *);
static void *deleter(int, void *, void *);
static int findcount(int, void *, void *);
static void reporter(int, void *, FILE *);
static void displayer(int, void *, FILE *);
static void freer(int, void *);

static void Fatal(char *,...);
static int processOptions(int,char **);
static char *strdup (const char *s);
static char *cleanSTR(char *data);
static char *checkString(char *data);
//static char *cleanSTR(char *data, int space);


int
main(int argc,char **argv) {
	//int argIndex;

	if (argc == 1) Fatal("%d arguments!\n",argc-1);

    corpusname = argv[argc-2];
    commandsname = argv[argc-1];

    /*argIndex = */processOptions(argc,argv);
    void *tree = 0;
    //void *endtree;
    if (explain == 0){
        // use corpus
        FILE *corpusFile = fopen(corpusname, "r");
        
        if (NULL != corpusFile) {
            fseek (corpusFile, 0, SEEK_END);
            int size = ftell(corpusFile);

            if (size != 0) {
                fseek(corpusFile, 0, SEEK_SET);
                tree = corpus_processor(tree_type, corpusFile);
            }
        }
        

        fclose(corpusFile);
        
        //use commands
        FILE *commandsFile = fopen(commandsname, "r");

        if (NULL != commandsFile) {
            fseek (commandsFile, 0, SEEK_END);
            int size = ftell(commandsFile);

            if (size != 0) {
                fseek(commandsFile, 0, SEEK_SET);
                tree = commands_processor(tree_type, tree, commandsFile);
            } 
        }  
        fclose(commandsFile);

        // free whatever data structure
        freer(tree_type, tree);
    }

    else if (explain == 1) {
        explainer(stdout);
    }
	return 0;
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

static char *
checkString(char *data){
    char c;
    unsigned long i = 0;
    unsigned long x = 0;

    while ((c = data[i]) != '\0'){
        if (isalpha(c)) {
            data[x] = c;
            x++;
        }
        else if (c == '*'){
            data[x] = ' ';
            x++;
        }
        i++;

        
    }
    data[x] = '\0';
    //printf("%s\n", data);
    return data;
}

static char * 
cleanSTR(char *data) {
    unsigned long i = 0; // Scanning index 
    unsigned long x = 0; // Write back index 
    char c;
    int signal = 0;

    while (isspace(data[i])) {
        i++;
    }

    //if ((c = data[i]) == '\0') data = "";

    // change all characters to lower case, leave spaces
    while ((c = data[i]) != '\0') {
        // Check if character is either alphabetic
        if (isalpha(c)) {
            signal = 1;
            c = tolower(c);
            data[x] = c;
            x++;
        }
        else if(isspace(c) && signal == 1) {
            data[x] = '*';
            signal = 0;
            x++;
        }
        i++;
    }
    
    if (data[x-1] == '*'){
        data[x-1] = '\0';
    }

    else{
        data[x] = '\0';
    }
    //printf("%s\n", data);
    return data;
}

static int
processOptions(int argc, char **argv)
    {
    int argIndex;
    //int argUsed;
    //int separateArg;
    //char *test;
    //char *arg;

    argIndex = 1;

    //test = argv[argc - 1];

    while (argIndex < argc && *argv[argIndex] == '-')
        {
        /* check if stdin, represented by "-" is an argument */
        /* if so, the end of options has been reached */
        if (argv[argIndex][1] == '\0') return argIndex;
        /*
        separateArg = 0;
        argUsed = 0;

        if (argv[argIndex][2] == '\0')
            {
            arg = argv[argIndex+1];
            separateArg = 1;
            }
        else{
            arg = argv[argIndex]+2;
        }
        */
        switch (argv[argIndex][1])
            {
            /*
             * when option has an argument, do this
             *
             *     examples are -m4096 or -m 4096
             *
             *     case 'm':
             *         MemorySize = atol(arg);
             *         argUsed = 1;
             *         break;
             *
             *
             * when option does not have an argument, do this
             *
             *     example is -a
             *
             *     case 'a':
             *         PrintActions = 1;
             *         break;
             */
            case 'v':
                explain = 1;
                break;    
            case 'g':
                tree_type = 1;
                /*
                test = arg;
                if (test[0] != '-'){
                    filename = arg;
                    argUsed = 1;
                }
                */
                break;
            case 'r':
                tree_type = 0;
                /*
                test = arg;
                if (test[0] != '-'){
                    filename = arg;
                    argUsed = 1;
                }
                */
                break;

            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }
        /*
        if (separateArg && argUsed)
            ++argIndex;
        */
        ++argIndex;
        }

    return argIndex;
    }


static char *
strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                       // Copy the characters
    return d;                            // Return the new string
}

static void
explainer(FILE *fp){
    fprintf(fp, "EXPLANATION HERE\n");
}
static void *
corpus_processor(int type, FILE *fp){
    char *c;
    char *str = "";
    void *rtn = 0;

    if (type == 1) {
        GST *tree = newGST(displaySTRING, compareSTRING, freeSTRING);

        if(stringPending(fp)){
            c = readString(fp);
        }
        else {
            c = readToken(fp);
        }
        
        while (!feof(fp)){
            str = strdup(c);
            free(c);
            cleanSTR(str);
            checkString(str);
            
            if(strcmp(str, "") != 0){
                //printf("%s\n", str);
                insertGST(tree, newSTRING(str));
            }

            if(stringPending(fp)){
                c = readString(fp);
            }
            else if (!feof(fp)) {
                c = readToken(fp);
            }
        }
        rtn = tree;
    }
    else {
        AVL *tree = newAVL(displaySTRING, compareSTRING, freeSTRING); 

        if(stringPending(fp)){
            c = readString(fp);
        }
        else {
            c = readToken(fp);
        }
        
        while (!feof(fp)){
            str = strdup(c);
            free(c);
            cleanSTR(str);
            checkString(str);

            if(strcmp(str, "") != 0){
                //printf("%s\n", str);
                insertAVL(tree, newSTRING(str));
            }

            if(stringPending(fp)){
                c = readString(fp);
            }
            else if (!feof(fp)) {
                c = readToken(fp);
            }
        } 
        //displayAVL(tree, stdout);
        rtn = tree;
    }
    return rtn;
}

static void *
commands_processor(int type, void *tree, FILE *fp) {
    char c;
    char *a;
    char *str = "";
    void *rtn = 0;
    c = readChar(fp);

    while (!feof(fp)){
        switch(c){
            case 'i':
                if(stringPending(fp)){
                    a = readString(fp);
                }
                else if (!feof(fp)) {
                    a = readToken(fp);
                }

                str = strdup(a);
                free(a);
                cleanSTR(str);
                checkString(str);
                //printf("%s\n", str);

                //printf("ins|%s|\n", str);
                if(strcmp(str, "") != 0){
                    //printf("%s\n", str);
                    inserter(type, tree, newSTRING(str));
                }

                break;
            case 'd':
                if(stringPending(fp)){
                    a = readString(fp);
                }
                else if (!feof(fp)) {
                    a = readToken(fp);
                }

                str = strdup(a);
                free(a);
                cleanSTR(str);
                checkString(str);

                //printf("del|%s|\n", str);
                if(strcmp(str, "") != 0){
                    //printf("%s\n", str);
                    STRING *v = newSTRING(str);
                    void *p;
                    p = deleter(type, tree, v);

                    if (p == 0 && (findcount(type, tree, v) == 0)) {
                        fprintf(stdout, "Value ");
                        displaySTRING(v, stdout);
                        fprintf(stdout, " not found.\n");
                    }

                    freeSTRING(v);
                    freeSTRING(p);
                }
                break;
            case 'f':
                if(stringPending(fp)){
                    a = readString(fp);
                }
                else if (!feof(fp)) {
                    a = readToken(fp);
                }

                str = strdup(a);
                free(a);
                cleanSTR(str);
                checkString(str);
                

                int count = 0;

                if(strcmp(str, "") != 0){
                    //printf("%s\n", str);
                    STRING *v = newSTRING(str);

                    count = findcount(type, tree, v);
                    fprintf(stdout, "Frequency of %s: %d\n", str, count); 

                    freeSTRING(v);   
                }

                break;
            case 's':
                displayer(type, tree, stdout);
                break;
            case 'r':
                reporter(type, tree, stdout);
                break;
        }
        c = readChar(fp);
    }

    rtn = tree;
    return rtn;
}


static void inserter(int type, void *t, void *v){
    STRING *s = (STRING *)v;

    if (type == 1){
        GST *tree = (GST *)t;
        insertGST(tree, s);
    }
    else{
        AVL *tree = (AVL *)t;
        insertAVL(tree, s);
    }
}

static void *deleter(int type, void *t, void *v){
    STRING *s = (STRING *)v;
    void *rtn = 0;

    if (type == 1){
        GST *tree = (GST *)t;
        rtn = deleteGST(tree, s);
    }
    else{
        AVL *tree = (AVL *)t;
        rtn = deleteAVL(tree, s);
    }

    return rtn;
}

static int findcount(int type, void *t, void *v){
    STRING *s = (STRING *)v;
    int rtn = 0;

    if (type == 1){
        GST *tree = (GST *)t;
        rtn = findGSTcount(tree, s);
    }
    else{
        AVL *tree = (AVL *)t;
        rtn = findAVLcount(tree, s);
    }

    return rtn;
}


static void reporter(int type, void *t, FILE *fp){
    if (type == 1){
        GST *tree = (GST *)t;
        statisticsGST(tree, fp);
    }
    else{
        AVL *tree = (AVL *)t;
        statisticsAVL(tree, fp);
    }
}

static void displayer(int type, void *t, FILE *fp){
    if (type == 1){
        GST *tree = (GST *)t;
        displayGST(tree, fp);
    }
    else{
        AVL *tree = (AVL *)t;
        displayAVL(tree, fp);
    }
}

static void freer(int type, void *t) {
    if (type == 1){
        GST *tree = (GST *)t;
        freeGST(tree);
    }
    else{
        AVL *tree = (AVL *)t;
        freeAVL(tree);
    }
}