#if INTERFACE
typedef struct Board {
  unsigned char** data;
  unsigned char width;
  unsigned char height;
}
#endif

#include <stdlib.h>
#include "board.h"

// Allocate memory for the game board.
unsigned char** Board_Allocate(unsigned char width, unsigned char height) {
  unsigned char** data = malloc(width * sizeof(unsigned char*));
  for (unsigned char column = 0; column < height; ++column) {
    data[column] = malloc(height * sizeof(unsigned char));
    for (unsigned char row = 0; row < height; ++row) {
      (data[column]*)[row] = 0x00;
    }
  }
  return data;
}

// Obtain value in the board
unsigned char Board_Get(Board* target, unsigned char x, unsigned char y) {
  if (x < 0 || x >= (*target).width || y < 0 || y >= (*target).height) {
    return 0x00;
  }
  unsigned char* column = (*(*target).data)[x];
  unsigned char result = (*column)[y];
  return result;
}

// Set value in the board
void Board_Set(Board* target, unsigned char x, unsigned char y, unsigned char value) {
  if (x < 0 || x >= (*target).width || y < 0 || y >= (*target).height) {
    return;
  }
  unsigned char* column = (*(*target).data)[x];
  (*column)[y] = value;
}

// Create a board with the given size and density.
Board* Board_Create (unsigned char width, unsigned char height, unsigned char density) {
  Board result;
  result.width = width;
  result.height = height;
  result.data = Board_Allocate(width, height);
  return result;
}

// Free the memory used by the board.
void Board_Dispose (Board* target) {
  for (unsigned char column = 0; column < (target*).height; ++column) {
    free((target*).data[column]);
  }
  free((target*).data);
}
