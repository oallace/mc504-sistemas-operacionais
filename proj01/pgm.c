// A library that allows us to read and to write PGMB files.
// Inspired by: https://www.geeksforgeeks.org/how-to-read-a-pgmb-format-image-in-c/

// C Program to read a PGMB image
// and print its parameters
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

// Function to ignore any comments
// in file
void ignoreComments(FILE *fp) {
  int ch;
  char line[100];

  // Ignore any blank lines
  while ((ch = fgetc(fp)) != EOF && isspace(ch))
    ;

  // Recursively ignore comments
  // in a PGM image commented lines
  // start with a '#'
  if (ch == '#') {
    fgets(line, sizeof(line), fp);
    ignoreComments(fp);
  } else
    fseek(fp, -1, SEEK_CUR);
}

// Function to open the input a PGM
// file and process it
bool openPGM(PGMImage *pgm, const char *filename) {
  // Open the image file in the
  // 'read binary' mode
  FILE *pgmfile = fopen(filename, "rb");

  // If file does not exist,
  // then return
  if (pgmfile == NULL) {
    printf("File does not exist\n");
    return false;
  }

  ignoreComments(pgmfile);
  fscanf(pgmfile, "%s", pgm->pgmType);

  // Check for correct PGM Binary
  // file type
  if (strcmp(pgm->pgmType, "P5")) {
    fprintf(stderr, "Wrong file type!\n");
    exit(EXIT_FAILURE);
  }

  ignoreComments(pgmfile);

  // Read the image dimensions
  fscanf(pgmfile, "%d %d", &(pgm->width), &(pgm->height));

  ignoreComments(pgmfile);

  // Read maximum gray value
  fscanf(pgmfile, "%d", &(pgm->maxValue));
  ignoreComments(pgmfile);

  // Allocating memory to store
  // img info in defined struct
  pgm->data = malloc(pgm->height * sizeof(unsigned char *));

  // Storing the pixel info in
  // the struct
  if (pgm->pgmType[1] == '5') {

    fgetc(pgmfile);

    for (int i = 0; i < pgm->height; i++) {
      pgm->data[i] = malloc(pgm->width * sizeof(unsigned char));

      // If memory allocation
      // is failed
      if (pgm->data[i] == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
      }

      // Read the gray values and
      // write on allocated memory
      fread(pgm->data[i], sizeof(unsigned char), pgm->width, pgmfile);
    }
  }

  // Close the file
  fclose(pgmfile);

  return true;
}

// Function to write the output a PGM file
bool writePGM(PGMImage *pgm, const char *filename) {
  // Open the image file in the
  // 'write binary' mode
  FILE *pgmfile = fopen(filename, "w");

  // Check for correct PGM Binary
  // file type
  if (strcmp(pgm->pgmType, "P5")) {
    fprintf(stderr, "Wrong file type!\n");
    exit(EXIT_FAILURE);
  }

  fprintf(pgmfile, "%s\n", pgm->pgmType);

  // Write the image dimensions
  fprintf(pgmfile, "%d %d\n", pgm->width, pgm->height);

  // Write maximum gray value
  fprintf(pgmfile, "%d\n", pgm->maxValue);

  // Writing the pixels in file
  if (pgm->pgmType[1] == '5') {

    for (int i = 0; i < pgm->height; i++) {
      fwrite(pgm->data[i], sizeof(unsigned char), pgm->width, pgmfile);
    }
  }

  // Close the file
  fclose(pgmfile);

  return true;
}

// Function to print the file details
void printImageDetails(PGMImage *pgm, const char *filename) {
  FILE *pgmfile = fopen(filename, "rb");

  // Retrieving the file extension
  char *ext = strrchr(filename, '.');

  if (!ext)
    printf("No extension found"
           "in file %s",
           filename);
  else
    printf("File format"
           " : %s\n",
           ext + 1);

  printf("PGM File type : %s\n", pgm->pgmType);

  // Print type of PGM file, in ascii
  // and binary format
  if (!strcmp(pgm->pgmType, "P2"))
    printf("PGM File Format:"
           "ASCII\n");
  else if (!strcmp(pgm->pgmType, "P5"))
    printf("PGM File Format:"
           " Binary\n");

  printf("Width of img : %d px\n", pgm->width);
  printf("Height of img : %d px\n", pgm->height);
  printf("Max Gray value : %d\n", pgm->maxValue);

  // close file
  fclose(pgmfile);
}

// Alloc the memory to read a pgm file
PGMImage *alloc_pgm(void)
{
	return malloc(sizeof(PGMImage));
}

// Free up the memory allocated to the pgm structure
bool free_pgm(PGMImage *pgm)
{
	for (int i = 0; i < pgm->height; i++)
		free(pgm->data[i]);
	free(pgm->data);
	free(pgm);
	return true;
}