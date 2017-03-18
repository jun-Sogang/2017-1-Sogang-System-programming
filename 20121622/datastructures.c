#include "datastructures.h"

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

void makeHashTable(NODE *hashTable[]) {
	FILE *fp;
	char opcodeNumString[4];
	char opcodeName[10];
	char formats[10];

	if ((fp = fopen("opcode.txt", "r")) == NULL) {
		printf("opcode.txt 파일을 열지 못했습니다.\n");
		return ;
	}

	for (int i = 0; i < hashSize; i += 1) {
		hashTable[i] = getNode();
		hashTable[i]->num = -1;
	}

	while(fscanf(fp, "%s %s %s", opcodeNumString, opcodeName, formats) != EOF) {
		int key = getIndexBelowMaxForKey(opcodeName, hashSize);
		int opcodeNum;

		sscanf(opcodeNumString, "%X", &opcodeNum);
		if (hashTable[key]->num == -1) {
			hashTable[key]->num = opcodeNum;
			strcpy(hashTable[key]->command, opcodeName);
		} else {
			NODE *last = hashTable[key];
			while (last->next != NULL) {
				last = last->next;
			}
			last->next = getNode();
			last->next->num = opcodeNum;
			strcpy(last->next->command, opcodeName);
		}
	}
	fclose(fp);
}

void opcodelist(NODE *hashTable[]) {
	for (int i = 0; i < hashSize; i += 1) {
		NODE *data = hashTable[i];
		printf("%d : ",i);
		while (data != NULL && data->num != -1) {
			printf("[%s, %X]", data->command, data->num);
			if (data->next != NULL) {
				printf(" -> ");
			}
			data = data->next;
		}
		puts("");
	}
}

void mnemonicFunc(NODE *hashTable[], char opcode[]) {
	NODE *data = hashTable[getIndexBelowMaxForKey(opcode, hashSize)];
	while (strcmp(data->command, opcode)) {
		data = data->next;
	}
	printf("opcode is %X\n", data->num);
}

int getIndexBelowMaxForKey(char str[], int max) {
	int hash = 0;
	int strLen = strlen(str);
	for (int i = 0; i < strLen; i += 1) {
		hash = (hash << 5) + hash + str[i];
		hash = hash & hash;
		hash = abs(hash);
	}
	return hash % max;
}
