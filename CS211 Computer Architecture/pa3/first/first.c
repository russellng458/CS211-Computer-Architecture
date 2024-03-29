#include <stdio.h>
#include <stdlib.h>

void printBinary(int w, unsigned long V) {
  unsigned long printer = 0;
  for(int i = w; i > 0; i--) {
    printer = V>>(i-1);
    if(printer & 1) {
      printf("1");
    }
    else {
      printf("0");
    }
  }
  printf("\n");
}

int bitFits(int w, unsigned long V) {
  unsigned long maxV = 0;
  for(int i = w; i > 0; i--) {
    if(maxV == 0) {
      maxV = 2;
    }
    else {
      maxV = maxV*2;
    }
  }

  if((maxV-1) < V) {
    unsigned long adjustedV = V%maxV;
    printBinary(w, adjustedV);
    return 0;
  }
  
  return 1;
}

int main(int argc, char* argv[argc+1]) {

  FILE* f1 = fopen(argv[1], "r");
  if(f1 == 0) {
    printf("error\n");
    return EXIT_SUCCESS;
  }

  unsigned long num = 0;
  int wbits = 0;

  while(fscanf(f1, "%lu %d\n", &num, &wbits) != EOF) {
    if(bitFits(wbits, num)) {
      printBinary(wbits, num);
    }
  }

  fclose(f1);
  return EXIT_SUCCESS;
}
