#include "header.h"
#include "datastructures.h"
#include "memory.h"

unsigned char *memory;  //Memory
int dumpAddress = 0;

NODE *hashTable[hashSize];

int main() {
	// make linkedList for history
	linkedList *history = (linkedList *)malloc(sizeof(linkedList));
	history->head = NULL;
	history->tail = NULL;
	history->count = 0;

	// memory allocation for dump
	memory = (unsigned char*)calloc(maxSize, sizeof(unsigned char));
	dumpAddress = 0;

	//makeHashTable
	makeHashTable(hashTable);

	while (1) {
		char input[100];	//command
		char copiedInput[100];
		int charLocation = 0;
		int lengthOfInput = 0;
		int lengthOfcopiedInput = 0;
		bool isChar = FALSE;
		sicsim();
		fgets(input, 100, stdin);			// Get one line
		lengthOfInput = strlen(input);
		input[lengthOfInput - 1] = '\0';	// Remove \n to \0

		for (int i = 0; i < lengthOfInput; i += 1) {
			if (input[i] != ' ' && isChar == FALSE) {
				isChar = TRUE;
				charLocation = i;
			}
			if (isChar == TRUE) {
				copiedInput[i - charLocation] = input[i];
			}
		}
		lengthOfcopiedInput = strlen(copiedInput);
		for (int i = lengthOfcopiedInput - 1; i >= 0; i -= 1) {
			if (copiedInput[i] == ' ') {
				copiedInput[i] = '\0';
			} else {
				break;
			}
		}
		isChar = FALSE;
		if (dumpAddress >= maxSize) dumpAddress = 0; // dumpAddress reset
		if (!strcmp(copiedInput, "quit") || !strcmp(copiedInput, "q")) {
			quit();
		} else if (!strcmp(copiedInput, "history") || !strcmp(copiedInput, "hi")) {
			insertNode(history, input);	// print history
			printNodes(history);
		} else if (!strcmp(copiedInput, "dump") || !strcmp(copiedInput, "du")) {
		//	dump(&dumpAddress, maxSize, memory);	// show 10 line about dump memory
			int temp = dumpAddress;
			dumpRange(&dumpAddress, dumpAddress + 160 - 1, memory);
			insertNode(history, input);
			dumpAddress = temp + 160;								// plus dumpAddress
		} else if (!strncmp(copiedInput, "dump ", 5) || !strncmp(copiedInput, "du ", 3)) {
			char inputCopy[100];			//copy input
			strcpy(inputCopy, copiedInput);
		  char *ptr = strtok(inputCopy, " ");			//command
		  char *start = strtok(NULL, ",");		//start
		  char *end = strtok(NULL, ",");		//value
		  ptr = strtok(NULL, " ");						//any input after value

		  if (ptr != NULL || start == NULL) {
		    printf("ERROR!!\n");						//if it's not right form. throw ERROR
		    printf("ex) (1) dump 4\n");
				printf("    (2) dump 4, 37\n");
		  } else {
				char trash[10];
				char comma = ',';
				int commaCount = 0;		//check number of comma
				int inputLength = strlen(copiedInput);
				int startInt;
				sscanf(start, "%X %s", &startInt, trash); //char -> hex
				int endInt = 0;
				if (end != NULL) {
					sscanf(end, "%X %s", &endInt, trash); //char -> hex
				}
				for (int i = 0; i < inputLength; i += 1) {	//check number of comma
					if (copiedInput[i] == comma) commaCount += 1;
				}
				if (strcmp(trash, "") || (end == NULL && commaCount != 0) || (end != NULL && commaCount != 1)) {	//number of comma == 2?
					printf("ERROR!!\n");						//if it's not right form. throw ERROR
			    printf("ex) (1) dump 4\n");
					printf("    (2) dump 4, 37\n");
					trash[0] = '\0';
				} else {	// Done
		      if (end == NULL) {
						if (startInt < 0 || startInt >= maxSize) {					// address range check
				      printf("ERROR | memory address : %X ~ %X\n", 0, maxSize - 1);
				    } else if (strlen(start) >= 6) {							// if over input
							printf("ERROR | please input 00000 ~ FFFFF\n");
						} else {
							dumpAddress = startInt;
							dumpRange(&dumpAddress, dumpAddress + 160 - 1, memory);
							insertNode(history, input);
							dumpAddress = startInt + 160;					// add dumpAddress
						}
					} else {
						if (startInt >= maxSize) {													// address range check
					    printf("ERROR | Start : %d out of maxSize : %d\n", startInt, maxSize);
					  } else if(strlen(start) >= 6 || strlen(end) > 6) {		//if over input
							printf("ERROR | please input 00000 ~ FFFFF\n");
						} else if (startInt > endInt) {
					    printf("ERROR | Start is lager than end.\nStart : %d  End : %d\n", startInt, endInt);
					  } else if (endInt >= maxSize) {
					    printf("ERROR |End : %d out of maxSize : %d\n", endInt, maxSize);
					  } else {
							dumpAddress = startInt;
							dumpRange(&dumpAddress, endInt, memory);
							insertNode(history, input);
							dumpAddress = endInt + 1;							// add dumpAddress
						}
					}
		    }
				commaCount = 0;		//reset commaCount
			}
		} else if (!strncmp(copiedInput, "edit ", 5) || !strncmp(copiedInput, "e ", 2)) {
			char inputCopy[100];			//copy input
			strcpy(inputCopy, copiedInput);
		  char *ptr = strtok(inputCopy, " ");			//command
		  char *start = strtok(NULL, ",");		//start
		  char *value = strtok(NULL, ",");		//value
		  ptr = strtok(NULL, " ");						//any input after value

		  if (ptr != NULL || start == NULL || value == NULL) {
		    printf("ERROR!!\n");						//if it's not right form. throw ERROR
		    printf("ex) edit 4, 6D\n");
		  } else {
				char trash[10];
				char comma = ',';
				int commaCount = 0;		//check number of comma
				int inputLength = strlen(copiedInput);
				int startInt;
				sscanf(start, "%X %s", &startInt, trash); //char -> hex
				int valueInt;
				sscanf(value, "%X %s", &valueInt, trash); //char -> hex

				for (int i = 0; i < inputLength; i += 1) {	//check number of comma
					if (copiedInput[i] == comma) commaCount += 1;
				}
				if (strcmp(trash, "") || commaCount != 1) {	//number of comma == 2?
					printf("ERROR!!\n");						//if it's not right form. throw ERROR
					printf("ex) edit 4, 6D\n");
					trash[0] = '\0';
				} else if (strlen(start) >= 6) {		//if over input
					printf("ERROR | please input start : 00000 ~ FFFFF\n");
				} else if (strlen(value) > 3) {		// if over input value
					printf("ERROR | please input value : 00 ~ FF\n");
				} else if (startInt < 0 || startInt >= maxSize) {	//Range check about startInt
		      printf("ERROR | memory address : 0 ~ %X\n", maxSize-1);
		    } else if (valueInt > 255 || valueInt < 0) {	// over value
		      printf("ERROR | value : %02X ~ %02X\n", 0, 255);
		    } else {	// Done
		      edit(startInt, (unsigned char)valueInt, memory);
		      insertNode(history, input);
		    }
				commaCount = 0;		//reset commaCount
			}
		} else if (!strncmp(copiedInput, "fill ", 5) || !strncmp(copiedInput, "f ", 2)) {
			char inputCopy[100];			//copy input
			strcpy(inputCopy, copiedInput);
			char *ptr = strtok(inputCopy, " ");			//command
			char *start = strtok(NULL, ",");		//start
			char *end = strtok(NULL, ",");			//end
			char *value = strtok(NULL, ",");		//value
			ptr = strtok(NULL, " ");						//any input after value

			if (ptr != NULL || start == NULL || end == NULL || value == NULL) {
				printf("ERROR!!\n");						//if it's not right form. throw ERROR
				printf("ex) fill 4, 20, 20\n");
			} else {
				char trash[10];
				char comma = ',';
				int commaCount = 0;		//check number of comma
				int inputLength = strlen(copiedInput);
				int startInt;
				sscanf(start, "%X %s", &startInt, trash); //char -> hex
				int endInt;
				sscanf(end, "%X %s", &endInt, trash); //char -> hex
				int valueInt;
				sscanf(value, "%X %s", &valueInt, trash); //char -> hex

				for (int i = 0; i < inputLength; i += 1) {	//check number of comma
					if (copiedInput[i] == comma) commaCount += 1;
				}
				if (strcmp(trash, "") || commaCount != 2) {
					printf("ERROR!!\n");						//if it's not right form. throw ERROR
					printf("ex) fill 4, 20, 20\n");
					trash[0] = '\0';
				} else if (strlen(start) >= 6 || strlen(end) > 6) { 	//if over input
					printf("ERROR | please input start, end : 00000 ~ FFFFF\n");
				} else if (strlen(value) > 3) {				//if over input value;
					printf("ERROR | please input value : 00 ~ FF\n");
				} else if (startInt > endInt) {	//start > end
					printf("ERROR | start : %X is lager than end : %X\n", startInt, endInt);
				} else if (endInt >= maxSize || startInt >= maxSize || startInt < 0 || endInt < 0) { // Over maxSize
					printf("ERROR | memory address : 0 ~ %X\n",maxSize-1);
				} else if (valueInt > 255 || valueInt < 0) {	// over value
					printf("ERROR | value : %02X ~ %02X\n", 0, 255);
				} else {	// Done
					fill(startInt, endInt, (unsigned char)valueInt, memory);
					insertNode(history, input);
					printf("Fill value : %X [ from start : %X to end : %X ]\n", valueInt, startInt, endInt);
				}
				commaCount = 0;		//reset commaCount
			}
		} else if(!strcmp(copiedInput, "reset")) {
			fill(0, maxSize - 1, 0, memory);	// fill : start = 0, end = maxSize, value = 0
			insertNode(history, input);
		} else if(!strcmp(copiedInput, "opcodelist")) {
			opcodelist(hashTable);		//print opcodelist
			insertNode(history, input);
		} else if(!strncmp(copiedInput, "opcode ", 7)) {
			char *ptr = strtok(copiedInput, " ");
			char *mnemonic = strtok(NULL, " ");				// get mnemonic string
			ptr = strtok(NULL, " ");									// if not right form
			if (ptr != NULL) {
				printf("ERROR!!\n");
				printf("ex) opcode ADD\n");
			} else if (mnemonicFunc(hashTable, mnemonic) == 1) { // isMnemonic : 1 ? 0
				insertNode(history, input);
			}	//print
		} else if (selector(copiedInput)) {
			insertNode(history, input);
		} else if (!strcmp(copiedInput, "")) {			//empty input
			puts("");
		} else {
			printf("Wrong command!!\n");
		}
	}
}
