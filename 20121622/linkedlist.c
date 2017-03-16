#include "linkedlist.h"

void insertNode(linkedList *body, char command[]) {
	NODE *newNode = getNode();

	newNode->num = body->count;
	strcpy(newNode->command, command);	// newNode data insert
	body->count += 1;

	if (body->head == NULL && body->tail == NULL) {
		body->head = body->tail = newNode;
	} else {
		body->tail->next = newNode;
		body->tail = newNode;
	}	// connect newNode to body
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
		printf("\t%d\t", temp->num);
		printf("%s\n", temp->command);
		temp = temp->next;
	}
}

