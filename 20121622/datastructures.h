#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define hashSize 20

typedef struct node {
	int num;
	char command[64];
	struct node *next;
} NODE;

typedef struct _list {
	NODE *head;
	NODE *tail;
	int count;
} linkedList;

void insertNode(linkedList *body, char command[]);
NODE *getNode();
void printNodes(linkedList *body);
int getIndexBelowMaxForKey(char str[], int max);
void makeHashTable();
void opcodelist();
void mnemonicFunc();
