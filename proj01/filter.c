// Autor: Wallace Lima, RA 195512
// Aplicador de filtros a uma imagem  utilizando pthreads
// Formato de imagem de Entrada: BMP
#include "pgm.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N_THREADS 3
#define FILTER_SIZE 3
// variáveis globais
// you can change the filter type by edit the comments below: 
// float filter[3][3] = {{0, -0.5, 0}, {-0.5, 3, -0.5}, {0, -0.5, 0}}; // sharpening filter
float filter[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}; // edge detection filter
// float filter[3][3] = {{0.111111, 0.111111, 0.111111}, {0.111111, 0.111111, 0.111111}, {0.111111, 0.111111, 0.111111}}; // blur filter

PGMImage *input_pgm, *output_pgm;

// Thread Function: Apply the filter in input image.
void *thread_fun(void *vargp) {
  int id = (long int)vargp;
  float aux;
  int displacement = FILTER_SIZE / 2; // used in output pixel calculation

  // Cada thread passa o filtro pelas linhas determinadas por seu id;
  for (int i = id; i < input_pgm->height; i += N_THREADS)
    for (int j = 0; j < input_pgm->width; j++) {
      // the border is set to black
      if (i == 0 || i == input_pgm->height - 1 || j == 0 ||
          j == input_pgm->width - 1) {
        output_pgm->data[i][j] = 0;
      } else {
        aux = 0;
        for (int i_f = 0; i_f < FILTER_SIZE; i_f++)
          for (int j_f = 0; j_f < FILTER_SIZE; j_f++) {
            aux +=
                filter[i_f][j_f] *
                input_pgm->data[i + i_f - displacement][j + i_f - displacement];
            if (aux < 0)
              output_pgm->data[i][j] = (unsigned char)0;
            else if (aux > 255)
              output_pgm->data[i][j] = (unsigned char)255;
            else
              output_pgm->data[i][j] = (unsigned char)aux / 1;
          }
      }
    }
  return NULL;
}

// Alloc the structure to store the output
PGMImage *alloc_output() {
  output_pgm = alloc_pgm();
  strcpy(output_pgm->pgmType, input_pgm->pgmType);
  output_pgm->height = input_pgm->height;
  output_pgm->width = input_pgm->width;
  output_pgm->maxValue = input_pgm->maxValue;
  // Allocating memory to store
  // img info in defined struct
  output_pgm->data = malloc(output_pgm->height * sizeof(unsigned char *));
  for (int i = 0; i < output_pgm->height; i++) {
    output_pgm->data[i] = malloc(output_pgm->width * sizeof(unsigned char));
    // If memory allocation
    // is failed
    if (output_pgm->data[i] == NULL) {
      fprintf(stderr, "malloc failed\n");
      exit(1);
    }
  };
  return output_pgm;
}

int main() {
  // Image reading:
  char ipfile[250];
  printf("Insert the PGMB Image path: ");
  scanf(" %s", ipfile);

  // Process the image and print its details
  input_pgm = alloc_pgm();
  if (openPGM(input_pgm, ipfile)) {
    printImageDetails(input_pgm, ipfile);
  } else {
    exit(EXIT_FAILURE);
  }

  // Creates the structure to output image
  output_pgm = alloc_output();

  // Apply the filter using pthreads:
  pthread_t pid[N_THREADS];
  for (long int i = 0; i < N_THREADS; i++) {
    pthread_create(&(pid[i]), NULL, thread_fun, (void *)i);
  }
  for (long int i = 0; i < N_THREADS; i++)
    pthread_join(pid[i], NULL);

  // Write the image filtered
  writePGM(output_pgm, "./output.pgm");

  // Free up the allocated structures
  free_pgm(input_pgm);
  free_pgm(output_pgm);

  return 0;
}
