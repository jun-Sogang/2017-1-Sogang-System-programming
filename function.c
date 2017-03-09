#include "header.h"

void sicsim();
void selector(char input[]);
void help();

void sicsim() {
	printf("%s>", "sicsim");
}
void selector(char input[]) {
	if (!strcmp(input, "help") || !strcmp(input, "h")) {
		help();
	}
}
void help() {
	printf("h[elp]\n");
	printf("d[ir]\n");
	printf("q[uit]\n");
	printf("hi[story]\n");
	printf("du[mp] [start, end]\n");
	printf("e[dit] address, value\n");
	printf("f[ill] start, end, value\n");
	printf("reset\n");
	printf("opcode mnemonic\n");
	printf("opcodelist\n");
}
