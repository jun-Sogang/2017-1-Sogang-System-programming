#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
