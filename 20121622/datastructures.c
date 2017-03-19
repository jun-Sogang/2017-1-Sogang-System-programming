#include "datastructures.h"

void insertNode(linkedList *body, char command[]) {
	NODE *newNode = getNode();		//newNode

	// newNode data insert
	body->count += 1;
	newNode->num = body->count;
	strcpy(newNode->command, command);

	if (body->head == NULL && body->tail == NULL) {
		body->head = body->tail = newNode;		//if insert firstNode
	} else {
		body->tail->next = newNode;
		body->tail = newNode;
	}	// connect newNode to body
}

NODE *getNode() {
	NODE *node = (NODE*)malloc(sizeof(NODE));
	//node reset
	node->num = 0;
	node->next = NULL;
	strcpy(node->command, "undefined");

	return node;	// return new node
}

void printNodes(linkedList *body) {
	NODE *temp = body->head;
	while (temp != NULL) {		//check temp == null
		printf("\t%d\t", temp->num);
		printf("%s\n", temp->command);
		temp = temp->next;
	}		//print all nodes
}

void makeHashTable(NODE *hashTable[]) {
	FILE *fp;
	char opcodeNumString[4];
	char opcodeName[10];
	char formats[10];

	//File open check
	if ((fp = fopen("opcode.txt", "r")) == NULL) {
		printf("Can't open [opcode.txt] FILE.\n");
		return ;
	}

	//memory allocation to hashTable
	for (int i = 0; i < hashSize; i += 1) {
		hashTable[i] = getNode();
		hashTable[i]->num = -1;		//if no data, hashTable->num == -1
	}

	while(fscanf(fp, "%s %s %s", opcodeNumString, opcodeName, formats) != EOF) {
		int key = getIndexBelowMaxForKey(opcodeName, hashSize); // get hashKey
		int opcodeNum;

		sscanf(opcodeNumString, "%X", &opcodeNum);	//string to hex
		if (hashTable[key]->num == -1) {		//if no data
			hashTable[key]->num = opcodeNum;
			strcpy(hashTable[key]->command, opcodeName);		// insert data
		} else {
			NODE *last = hashTable[key];
			while (last->next != NULL) {		//find last data at hashTable
				last = last->next;
			}
			//insert data
			last->next = getNode();
			last->next->num = opcodeNum;
			strcpy(last->next->command, opcodeName);
		}
	}
	fclose(fp);	//close file
}

void opcodelist(NODE *hashTable[]) {	//print hashTable
	for (int i = 0; i < hashSize; i += 1) {
		NODE *data = hashTable[i];
		printf("%d : ",i);
		while (data != NULL && data->num != -1) { //if isData
			printf("[%s, %X]", data->command, data->num);	//print data
			if (data->next != NULL) {	//if hasNext data
				printf(" -> ");
			}
			data = data->next;
		}
		puts("");
	}
}

int mnemonicFunc(NODE *hashTable[], char opcode[]) {
	NODE *data = hashTable[getIndexBelowMaxForKey(opcode, hashSize)];
	while (data != NULL) {	//find data
		if (!strcmp(data->command, opcode)) break;
		data = data->next;
	}
	if (data == NULL) {	//if no data
		printf("Wrong mnemonic!!\n");
		return 0;
	} else {	//if isData
		printf("opcode is %X\n", data->num);
		return 1;
	}
}

int getIndexBelowMaxForKey(char str[], int max) {
	int hash = 0;
	int strLen = strlen(str);
	//make hash
	for (int i = 0; i < strLen; i += 1) {
		hash = (hash << 5) + hash + str[i];
		hash = hash & hash;
		hash = abs(hash);
	}
	return hash % max;
}
