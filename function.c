#include "header.h"

void sicsim();
void selector(char input[]);
void help();
void dir();

void sicsim() {
	printf("%s>", "sicsim");
}
void selector(char input[]) {
	if (!strcmp(input, "help") || !strcmp(input, "h")) {
		help();
	} else if (!strcmp(input, "dir") || !strcmp(input, "d")) {
		dir();
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

void dir() {
	DIR *dir;
	struct dirent *direntp;

	dir = opendir(".");
	
	while ((direntp = readdir(dir)) != NULL) {
		char fileName[256];
		int returnStat;
		struct stat fileInfo;
		mode_t fileMode;
		
		strcpy(fileName, direntp->d_name);
		if ((returnStat = stat(fileName, &fileInfo)) ==-1) {
			perror("Error : ");
			exit(0);
		}
		fileMode = fileInfo.st_mode;
		printf("%s", fileName);
		if (S_ISDIR(fileMode)) {
			printf("/");
		} else if (fileMode & S_IXUSR || fileMode & S_IXGRP || fileMode & S_IXOTH) {
			printf("*");
		}
		puts("");
	}
	closedir(dir);
}
//reference
//https://linux.die.net/man/2/stat
//http://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
