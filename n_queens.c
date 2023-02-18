#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// bit manipulation of nqueens solution

// where only one bit is 1
// ex:
// 1 = 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 2 = 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 4 = 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// used to flip specific bits
const unsigned long BIT_FLIP[64] = {
    1,
    2,
    4,
    8,
    16,
    32,
    64,
    128,
    256,
    512,
    1024,
    2048,
    4096,
    8192,
    16384,
    32768,
    65536,
    131072,
    262144,
    524288,
    1048576,
    2097152,
    4194304,
    8388608,
    16777216,
    33554432,
    67108864,
    134217728,
    268435456,
    536870912,
    1073741824,
    2147483648,
    4294967296,
    8589934592,
    17179869184,
    34359738368,
    68719476736,
    137438953472,
    274877906944,
    549755813888,
    1099511627776,
    2199023255552,
    4398046511104,
    8796093022208,
    17592186044416,
    35184372088832,
    70368744177664,
    140737488355328,
    281474976710656,
    562949953421312,
    1125899906842624,
    2251799813685248,
    4503599627370496,
    9007199254740992,
    18014398509481984,
    36028797018963968,
    72057594037927936,
    144115188075855872,
    288230376151711744,
    576460752303423488,
    1152921504606846976,
    2305843009213693952,
    4611686018427387904,
};

// prints the binary
void printBits(unsigned long num, unsigned endLeng) {
  for (int i = endLeng - 1; i >= 0; i--) {
    unsigned long currBit = BIT_FLIP[i];
    int isOne = num >= currBit;
    if (isOne)
      num -= currBit;
    printf("%i ", isOne);
  }
}
// replaces the 0s and 1s
void printDynamic(unsigned long num, unsigned endLeng, char rep0[2],
                  char rep1[2]) {
  for (int i = endLeng - 1; i >= 0; i--) {
    unsigned long currBit = BIT_FLIP[i];
    int isOne = num >= currBit;
    if (isOne)
      num -= currBit;
    printf("%s ", isOne ? rep0 : rep1);
  }
}

int findQueensShort(int board_size, unsigned short *board, int curr_row,
                    unsigned short bit_flip_sum, unsigned short leftDiags,
                    unsigned short rightDiags, unsigned short vert) {
  // base case
  if (curr_row == board_size)
    return 1;
  // 0s in binary are valid positions
  unsigned short valid_pos = leftDiags | rightDiags | vert;

  // allows for future if statement to check bits and work properly by flipping
  // all unused bits
  valid_pos &= bit_flip_sum;

  // if there are no possibilities don't start the loop
  if (valid_pos == bit_flip_sum)
    return 0;

  for (int i = board_size - 1; i >= 0; i--) {
    unsigned short curr_bit_flip = BIT_FLIP[i];
    // checks if the current bit is taken. If it is then flips the bit so that
    // the next one can be checked. Otherwise it places the queen and checks the
    // next one.
    if (valid_pos >= curr_bit_flip) {
      valid_pos -= curr_bit_flip;
    } else {
      board[curr_row] = curr_bit_flip;
      // gets new ilocations taken
      unsigned short newLeftDiags = (curr_bit_flip | leftDiags) << 1,
                     newRightDiags = (curr_bit_flip | rightDiags) >> 1,
                     newVert = curr_bit_flip | vert;

      if (findQueensShort(board_size, board, curr_row + 1, bit_flip_sum,
                          newLeftDiags, newRightDiags, newVert) == 1)
        return 1;
    }
  }
  return 0;
}

int findQueens(int board_size, unsigned *board, int curr_row,
               unsigned bit_flip_sum, unsigned leftDiags, unsigned rightDiags,
               unsigned vert) {
  // base case
  if (curr_row == board_size)
    return 1;
  // 0s in binary are valid positions
  unsigned valid_pos = leftDiags | rightDiags | vert;

  // allows for future if statement to check bits and work properly by flipping
  // all unused bits
  valid_pos &= bit_flip_sum;

  // if there are no possibilities don't start the loop
  if (valid_pos == bit_flip_sum)
    return 0;

  for (int i = board_size - 1; i >= 0; i--) {
    unsigned curr_bit_flip = BIT_FLIP[i];
    // checks if the current bit is taken. If it is then flips the bit so that
    // the next one can be checked. Otherwise it places the queen and checks the
    // next one.
    if (valid_pos >= curr_bit_flip) {
      valid_pos -= curr_bit_flip;
    } else {
      board[curr_row] = curr_bit_flip;
      // gets locations taken
      unsigned newLeftDiags = (curr_bit_flip | leftDiags) << 1,
               newRightDiags = (curr_bit_flip | rightDiags) >> 1,
               newVert = curr_bit_flip | vert;

      if (findQueens(board_size, board, curr_row + 1, bit_flip_sum,
                     newLeftDiags, newRightDiags, newVert) == 1)
        return 1;
    }
  }
  return 0;
}

int findQueensLong(int board_size, unsigned long *board, int curr_row,
                   unsigned long bit_flip_sum, unsigned long leftDiags,
                   unsigned long rightDiags, unsigned long vert) {
  // base case
  if (curr_row == board_size)
    return 1;
  // 0s in binary are valid positions
  unsigned long valid_pos = leftDiags | rightDiags | vert;

  // allows for future if statement to check bits and work properly by flipping
  // all unused bits
  valid_pos &= bit_flip_sum;

  // if there are no possibilities don't start the loop
  if (valid_pos == bit_flip_sum)
    return 0;

  for (int i = board_size - 1; i >= 0; i--) {
    unsigned long curr_bit_flip = BIT_FLIP[i];
    // checks if the current bit is taken. If it is then flips the bit so that
    // the next one can be checked. Otherwise it places the queen and checks the
    // next one.
    if (valid_pos >= curr_bit_flip) {
      valid_pos -= curr_bit_flip;
    } else {
      board[curr_row] = curr_bit_flip;
      // gets locations taken
      unsigned long newLeftDiags = (curr_bit_flip | leftDiags) << 1,
                    newRightDiags = (curr_bit_flip | rightDiags) >> 1,
                    newVert = curr_bit_flip | vert;

      if (findQueensLong(board_size, board, curr_row + 1, bit_flip_sum,
                         newLeftDiags, newRightDiags, newVert) == 1)
        return 1;
    }
  }
  return 0;
}

void nQueensShort(unsigned short boardSize, int argc, char *argsv[]) {
  unsigned short bitFlipSum = 15;
  for (int i = 4; i < boardSize; i++) {
    bitFlipSum += BIT_FLIP[i];
  }

  unsigned short board[boardSize];
  for (int i = 0; i < boardSize; i++)
    board[i] = 0;

  findQueensShort(boardSize, board, 0, bitFlipSum, 0, 0, 0);

  if (argc == 4) {
    for (int i = 0; i < boardSize; i++) {
      printDynamic(board[i], boardSize, argsv[2], argsv[3]);
      printf("\n");
    }
  } else {
    // prints board
    for (int i = 0; i < boardSize; i++) {
      printBits(board[i], boardSize);
      printf("\n");
    }
  }
}

void nQueens(unsigned boardSize, int argc, char *argsv[]) {
  unsigned bitFlipSum = 15;
  for (int i = 4; i < boardSize; i++) {
    bitFlipSum += BIT_FLIP[i];
  }

  unsigned board[boardSize];
  for (int i = 0; i < boardSize; i++)
    board[i] = 0;

  findQueens(boardSize, board, 0, bitFlipSum, 0, 0, 0);

  if (argc == 4) {
    for (int i = 0; i < boardSize; i++) {
      printDynamic(board[i], boardSize, argsv[2], argsv[3]);
      printf("\n");
    }
  } else {
    // prints board
    for (int i = 0; i < boardSize; i++) {
      printBits(board[i], boardSize);
      printf("\n");
    }
  }
}
void nQueensLong(unsigned long boardSize, int argc, char *argsv[]) {
  unsigned long bitFlipSum = 15;
  for (int i = 4; i < boardSize; i++) {
    bitFlipSum += BIT_FLIP[i];
  }

  unsigned long board[boardSize];
  for (int i = 0; i < boardSize; i++)
    board[i] = 0;

  findQueensLong(boardSize, board, 0, bitFlipSum, 0, 0, 0);

  if (argc == 4) {
    for (int i = 0; i < boardSize; i++) {
      printDynamic(board[i], boardSize, argsv[2], argsv[3]);
      printf("\n");
    }
  } else {
    // prints board
    for (int i = 0; i < boardSize; i++) {
      printBits(board[i], boardSize);
      printf("\n");
    }
  }
}

int main(int argc, char *argsv[]) {
  if ((argc == 2 || argc == 4) == 0) {
    printf("Please give the proper args");
  }

  int boardSize = atoi(argsv[1]);

  if (boardSize < 4) {
    printf("Cannot place queens on a board that is less than 4 squares long.");
    return 0;
  } else if (boardSize > 64) {
    printf("This program is only built for boards that are 64 squares long.");
  }

  if (boardSize < 17) {
    nQueensShort(boardSize, argc, argsv);
  } else if (boardSize < 33) {
    nQueens(boardSize, argc, argsv);
  } else {
    nQueensLong(boardSize, argc, argsv);
  }
  return 0;
}
