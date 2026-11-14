#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

void print_dataset(const lstat_dataset_t* dataset, const char* label) {
  if (label != NULL) {
    printf("[%s]: {\n", label);
  } else {
    printf("{\n");
  }

  // size field
  printf("\t.size = %zu,\n", dataset->size);

  // data field
  printf("\t.data = [");
  char* sep = ", ";
  for (size_t i = 0; i < dataset->size; i++) {
    if ((i + 1) == dataset->size) {
      sep = "";
    }
    printf("%f%s", dataset->data[i], sep);
  }

  printf("]\n}\n");
}

int lstat_compare(const void* a, const void* b) {
  double x = *(const double*)a;
  double y = *(const double*)b;

  if (x < y) return -1;
  if (x > y) return 1;

  return 0;
}

bool lstat_dataset_qsort(const lstat_dataset_t* dataset, double* sorted) {
  if (dataset == NULL || sorted == NULL) {
    return false;
  }
  memcpy(sorted, dataset->data, dataset->size * sizeof(double));
  qsort(sorted, dataset->size, sizeof(double), lstat_compare);
  return true;
}

lstat_freq_t* lstat_freq_create(const lstat_dataset_t* dataset, size_t* freq_size) {
  if (dataset == NULL) {
    return NULL;
  }
  
  lstat_freq_t* freqs = (lstat_freq_t*)calloc(dataset->size, sizeof(lstat_freq_t));

  if (freqs == NULL) {
    errno = EALLOCATION;
    return NULL;
  }

  *freq_size = 1;
  for (size_t i = 0; i < dataset->size; i++) {
    int count_value = 1;
    for (size_t j = i + 1; j < dataset->size; j++) {
      if (dataset->data[i] == dataset->data[j]) {
        count_value++;
      } else {
        (*freq_size)++;
      }
    }

    freqs[*freq_size - 1] = (lstat_freq_t){
      .value = dataset->data[i],
      .freq = count_value 
    };
  }

  return freqs;
}

void lstat_freq_destroy(lstat_freq_t* freq) {
  if (freq != NULL) {
    free(freq);
  }
}

