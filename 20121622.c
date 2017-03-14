#include "header.h"
#include "linkedlist.h"

int main() {
	linkedList *history = (linkedList *)malloc(sizeof(linkedList));
	history->head = NULL;
	history->tail = NULL;
	history->count = 0;
	while (1) {
		char input[100];
		sicsim();
		scanf("%s", input);
		if (!strcmp(input, "quit") || !strcmp(input, "q")) {
			quit();
		} else if (!strcmp(input, "history") || !strcmp(input, "hi")) {
			insertNode(history, input);
			printNodes(history);
		} else if (selector(input)) {
			insertNode(history, input);
		} else {
			printf("Wrong command!!\n");
		}
	}
}
