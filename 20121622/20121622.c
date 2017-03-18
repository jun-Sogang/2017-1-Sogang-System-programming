#include "header.h"
#include "linkedlist.h"
#include "memory.h"

unsigned char *memory;  //Memory
int dumpAddress = 0;



int main() {
	linkedList *history = (linkedList *)malloc(sizeof(linkedList));
	history->head = NULL;
	history->tail = NULL;
	history->count = 0;

	memory = (unsigned char*)calloc(maxSize, sizeof(unsigned char));
	dumpAddress = 0;

	while (1) {
		char input[100];
		sicsim();
		fgets(input, 100, stdin);			// Get one line
		input[strlen(input)-1] = '\0';	// Remove \n to \0
		if (!strcmp(input, "quit") || !strcmp(input, "q")) {
			quit();
		} else if (!strcmp(input, "history") || !strcmp(input, "hi")) {
			insertNode(history, input);
			printNodes(history);
		} else if (!strcmp(input, "dump")) {
			dump(&dumpAddress, maxSize, memory);
			insertNode(history, input);
		} else if (!strncmp(input, "dump ", 5) || !strncmp(input, "du ", 3)) {
			int inputLength = strlen(input);
			char firstNumber[100];
			char secondNumber[100];
			bool isEnd = FALSE;
			bool isFirstNum = FALSE;
			bool isBlankAfterFirstNum = FALSE;
			bool isDump = TRUE;
			bool isComma = FALSE;
			char blank = ' ';
			char comma = ',';
			int count = 0;
			int commandLength = !strncmp(input, "dump ", 5) ? 5 : 3;

			for (int i = commandLength; i < inputLength; i += 1) {
				if (isFirstNum == TRUE && input[i] == blank && input[i] != comma) {
					isBlankAfterFirstNum = TRUE;
				} else if (isFirstNum == TRUE && isBlankAfterFirstNum == TRUE && isComma == FALSE && input[i] != blank && input[i] != comma) {
					printf("There is no comma between two number\n");
					printf("ex) dump 4, 37\n");
					isDump = FALSE;
					firstNumber[0] = '\0';
					secondNumber[0] = '\0';
					break;
				}
				else if (input[i] != blank && input[i] != comma && isEnd == FALSE) {
					firstNumber[count++] = input[i];
					isFirstNum = TRUE;
				} else if(input[i] == comma) {
					isEnd = TRUE;
					isComma = TRUE;
					firstNumber[count] = '\0';
					count = 0;
				} else if(input[i] != blank) {
					secondNumber[count++] = input[i];
				}
			}
			if (isEnd == FALSE && isDump == TRUE) {
				firstNumber[count] = '\0';
				int start = atoi(firstNumber);
				dump(&start, maxSize, memory);
			} else if (isDump == TRUE && isEnd == TRUE){
				secondNumber[count] = '\0';
				int start = atoi(firstNumber);
				int end = atoi(secondNumber);
				dumpRange(&start, end, memory);
			}
			insertNode(history, input);
		} else if (selector(input)) {
			insertNode(history, input);
		} else {
			printf("Wrong command!!\n");
		}
	}
}
