#include "header.h"

void sicsim();
bool selector(char input[]);
bool help();
bool dir();
void quit();

void sicsim() {
	printf("%s> ", "sicsim");
}
bool selector(char input[]) {
	if (!strcmp(input, "help") || !strcmp(input, "h")) {
		return help();
	} else if (!strcmp(input, "dir") || !strcmp(input, "d")) {
		return dir();
	} else {
		return FALSE;
	}
}
bool help() {
	printf("\th[elp]\n");
	printf("\td[ir]\n");
	printf("\tq[uit]\n");
	printf("\thi[story]\n");
	printf("\tdu[mp] [start, end]\n");
	printf("\te[dit] address, value\n");
	printf("\tf[ill] start, end, value\n");
	printf("\treset\n");
	printf("\topcode mnemonic\n");
	printf("\topcodelist\n");
	return TRUE;
}

bool dir() {
	DIR *dir;
	struct dirent *direntp;
	int count = 0;
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
		printf("\t");
		if ((++count)%5 == 0) {
			puts("");
		}
	}
	closedir(dir);
	puts("");
	return TRUE;
}
//reference
//https://linux.die.net/man/2/stat
//http://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html

void quit() {
	printf("   ^       ^        ( BYE ~)\n");
	printf("  (  x    x )	_____u\n");
	printf("   (    o    =/3		\n");
	printf("     ||  ||\n");
	exit(0);
}

