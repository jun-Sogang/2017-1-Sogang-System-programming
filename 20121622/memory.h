#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxSize 1048576




void dumpRange();
void printAddress();  //Memory address print
void printData(); //Memory print
void printASCII();  //ASCII print
void printAll();  //Run Three of print function
void printBlank();  //Print blank
void printSemicolon();  //Print Semicolon
void edit(int address, unsigned char value, unsigned char memory[]);
void fill(int start, int end, unsigned char value, unsigned char memory[]);
