#include "header.h"
#include "linkedlist.h"
#include "dump.h"

unsigned char *memory;  //Memory
int * dumpAddress;

int main() {
	linkedList *history = (linkedList *)malloc(sizeof(linkedList));
	history->head = NULL;
	history->tail = NULL;
	history->count = 0;

	memory = (unsigned char*)calloc(maxSize, sizeof(unsigned char));
	*dumpAddress = 0;

	while (1) {
		char input[100];
		sicsim();
		scanf("%s", input);
		if (!strcmp(input, "quit") || !strcmp(input, "q")) {
			quit();
		} else if (!strcmp(input, "history") || !strcmp(input, "hi")) {
			insertNode(history, input);
			printNodes(history);
		} else if (!strcmp(input, "dump")) {
			dump(&dumpAddress, maxSize, memory);
		} else if (selector(input)) {
			insertNode(history, input);
		} else {
			printf("Wrong command!!\n");
		}
	}
}
