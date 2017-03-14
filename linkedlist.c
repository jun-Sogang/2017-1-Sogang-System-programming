#define __USE_GNU
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


void insertNode(linkedList *body, int num, char command[]);  // insert new node to linkedlist
NODE *getNode();		// make new node
void printNodes(linkedList *body); // print all nodes

void insertNode(linkedList *body, int num, char command[]) {
	NODE *newNode = getNode();
	newNode->num = body->count;
	strcpy(newNode->command, command);	// newNode data insert
	if (body->head == NULL && body->tail == NULL) {
		body->head = body->tail = newNode;
	} else {
		body->tail->next = newNode;
		body->tail = newNode;
	}	// connect newNode to body
	body->count += 1;
}

NODE *getNode() {
	NODE *node = (NODE*)malloc(sizeof(NODE));

	node->num = 0;
	node->next = NULL;
	strcpy(node->command, "undefined");

	return node;	// return new node 
}

void printNodes(linkedList *body) {
	NODE *temp = body->head;
	while (temp != NULL) {
		printf("%d\n", temp->num);
		printf("%s\n", temp->command);
		temp = temp->next;
	}
}

int main(void) { 
	linkedList *L = (linkedList *)malloc(sizeof(linkedList)); 
	L->head = NULL; 
	L->tail = NULL; 
	L->count = 0;
	
	//linkedList pointer define end 
	char temp[16];
	
	strcpy(temp, "temp");
	insertNode(L, 1, temp); 
	insertNode(L, 2, temp); 
	insertNode(L, 3, temp); 
	insertNode(L, 4, temp); 
	insertNode(L, 5, temp); 
	insertNode(L, 6, temp); 
	insertNode(L, 7, temp); 
	printNodes(L); 
	return 0; 
}

