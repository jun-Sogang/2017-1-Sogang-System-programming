#include "memory.h"

void dumpRange(int *start, int end, unsigned char memory[]) {
  int first = *start;
  while (1) {
    if (*start <= end && *start < maxSize) {           //Over Memory?
      printAll(*start, end, memory);      //Print one line
      *start += 16 - *start % 16;     //Make start to first of next line address
    } else {
      if (end >= maxSize) end = maxSize - 1;  // if over the memory, end = maxSize
      printf("From %X to %X print done\n", first, end);
      break;
    }
  }
}


void printAll(int nowAddress, int end, unsigned char memory[]) {
  int addressStart = (nowAddress / 16) * 16;         // start of address
  printAddress(addressStart);                        // print Address
  printData(nowAddress, addressStart, end, memory);  // print Data
  printSemicolon();                                  // print Semicolon
  printBlank();                                      // print blank
  printASCII(addressStart, memory);                  // print Data to ASCII
  puts("");
}

void printBlank() {
  printf(" ");
}
void printSemicolon() {
  printf(";");
}
void printAddress(int addressStart) {
  printf("%05X", addressStart);                     // print addressStart to hex
  printBlank();
}

void printData(int nowAddress, int addressStart, int end, unsigned char memory[]) {
  for (int i = addressStart; i < nowAddress; i += 1) {  // if not include in Range
    printf("  ");
    printBlank();
  }
  for (int diff = nowAddress / 16 ; diff == nowAddress / 16; nowAddress += 1) { // until last of line
    if (nowAddress <= end) {
      printf("%02X", memory[nowAddress]);               //print data
    } else {
      printf("  ");
    }
    printBlank();
  }
}

void printASCII(int addressStart, unsigned char memory[]) {
  for (int i = addressStart; i % 16 != 15; i += 1) {
    if (memory[i] >= 32 && memory[i] <= 126) {    // 20 ~ 7E boundary check
      printf("%c", memory[i]);
    } else {
      printf(".");
    }
  }
}

void edit(int address, unsigned char value, unsigned char memory[]) {
  memory[address] = value;                        // edit address of data to value
}
void fill(int start, int end, unsigned char value, unsigned char memory[]) {
  for (int i = start; i <= end; i += 1) {         // fill value ranged from start to end
    memory[i] = value;
  }
}
