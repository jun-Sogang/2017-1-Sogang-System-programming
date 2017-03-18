#include "memory.h"



// void dump();  //dump
// void dumpRange();
// void printAddress();  //Memory address print
// void printData(); //Memory print
// void printASCII();  //ASCII print
// void printAll();  //Run Three of print function
// void printBlank();  //Print blank
// void printSemicolon();  //Print Semicolon

//
// int main() {
//   memory = (unsigned char*)calloc(maxSize, sizeof(unsigned char));
//   dumpAddress = 0;
//   while(1){
//     int input;
//     int from,to;
//
//     printf("input :");
//     scanf("%d",&input);
//     if(input == 1){
//       dump(&dumpAddress, maxSize);
//     }
//     else if(input ==2) {
//       scanf("%d", &from);
//       dump(&from, maxSize);
//     }else if(input == 3) {
//       scanf("%d %d",&from, &to);
//       dumpRange(&from, to);
//     } else{
//       break;
//     }
//   }
// }

void dump(int *start, int end, unsigned char memory[]) {
  for (int i = 0; i < 10; i += 1) {
    if (*start < end) {           //Over Memory?
      printAll(*start, end, memory);      //Print one line
      *start += 16 - *start % 16;     //Make start to first of next line address
    } else {
      printf("End of line\n");
      break;
    }
  }
}

void dumpRange(int *start, int end, unsigned char memory[]) {
  if (*start >= maxSize) {
    printf("Start : %d out of maxSize : %d\n", *start, maxSize);
  }
  else if (*start > end) {
    printf("Start is lager than end.\nStart : %d  End : %d\n", *start, end);
  } else if (end >= maxSize) {
    printf("End : %d out of maxSize : %d\n", end, maxSize);
  } else {
    int first = *start;
    while (1) {
      if (*start <= end && *start < maxSize) {           //Over Memory?
        printAll(*start, end, memory);      //Print one line
        *start += 16 - *start % 16;     //Make start to first of next line address
      } else {
        printf("from %d to %d print done\n", first, end);
        break;
      }
    }
  }
}


void printAll(int nowAddress, int end, unsigned char memory[]) {
  int addressStart = (nowAddress / 16) * 16;   //addressStart
  printAddress(addressStart);
  printData(nowAddress, addressStart, end, memory);
  printSemicolon();
  printASCII(addressStart, memory);
  puts("");
}

void printBlank() {
  printf(" ");
}
void printSemicolon() {
  printf(";");
}
void printAddress(int addressStart) {
  printf("%05X", addressStart);
  printBlank();
}

void printData(int nowAddress, int addressStart, int end, unsigned char memory[]) {
  for (int i = addressStart; i < nowAddress; i += 1) {
    printf("  ");
    printBlank();
  }
  for (int diff = nowAddress / 16 ; diff == nowAddress / 16; nowAddress += 1) {
    if (nowAddress <= end) {
      printf("%02X", memory[nowAddress]);
    } else {
      printf("  ");
    }
    printBlank();
  }
}

void printASCII(int addressStart, unsigned char memory[]) {
  for (int i = addressStart; i % 16 != 15; i += 1) {
    if (memory[i] >= 32 && memory[i] <= 126) {
      printf("%c", memory[i]);
    } else {
      printf(".");
    }
  }
}
