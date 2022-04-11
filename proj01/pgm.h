// A library that allows us to read and to write PGMB files.
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for storing the
// image data
typedef struct PGMImage {
  char pgmType[3];
  unsigned char **data;
  unsigned int width;
  unsigned int height;
  unsigned int maxValue;
} PGMImage;

// Function to open the input a PGM
// file and process it
bool openPGM(PGMImage *pgm, const char *filename);

// Function to write the output a PGM file
bool writePGM(PGMImage *pgm, const char *filename);

// Function to print the file details
void printImageDetails(PGMImage *pgm, const char *filename);

// Alloc the memory to read a pgm file
PGMImage *alloc_pgm(void);

// Free up the memory allocated to the pgm structure
bool free_pgm(PGMImage *pgm);