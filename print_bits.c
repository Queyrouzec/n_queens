#include <stdio.h>
#include <stdlib.h>

// used to make a list of when bits to use as a constant
int main(int argc, char *argsv[]) {
  if (argc != 2) {
    printf("Please give the number of bits");
    return 0;
  }

  int bits = atoi(argsv[1]);
  unsigned long prevBit = 1;
  printf("%li\n", prevBit);
  for (int i = 1; i < bits; i++) {
    prevBit <<= 1;
    printf("%li\n", prevBit);
  }
  return 0;
}
