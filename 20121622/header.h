#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } bool;

void sicsim();
bool selector();
bool help();
bool dir();
void quit();
void printNodes();
void insertNode();
