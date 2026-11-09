#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void print_kv(const lstat_kv_t* kv, const size_t len, const char* label) {
  if (label != NULL) {
    printf("%s", label);
  }

  for (size_t i = 0; i < len; i++) {
    printf("kv[%zu]: { key: %f, value: %f }\n", i, *(double*)kv[i].key, *(double*)kv[i].value);
  }
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

lstat_kv_t lstat_max_frequency(const lstat_kv_t* kv, size_t nel) {
  if (kv == NULL) {
    return (lstat_kv_t){0};
  }

  // encontra maxima frequencia
  lstat_kv_t max = kv[0];
  for (size_t i = 1; i < nel; i++) {
    double vi = *(double*)kv[i].value;
    double maxv = *(double*)max.value;
    if (vi > maxv) {
      max = kv[i];
    }
  }

  return max;
}

bool lstat_frequency_upsert(lstat_kv_t* kv, size_t kv_nel, void* value) {
  // kv tem como key = numero e value = frequencia
  // se valor ja existe em kv incrementa frequencia

  // verificamos se o valor existe se existe somamos 1 na freqnecia
  // se nao existe adicionamos no kv com frequencia 1
  for (size_t i = 0; i < kv_nel; i++) {
    if (kv[i].key == value) {
      size_t count = *(size_t*)kv[i].value;
      count++;
      *(size_t*)kv[i].value = count;
      return true;
    }
  }

  // procurar primeiro valor NULL para alocar o novo valor no kv
  for (size_t i = 0; i < kv_nel; i++) {
    if (kv[i].key == NULL) {
      // Aloca memória para o contador inicial (1)
      size_t *new_count = malloc(sizeof(size_t));
      if (new_count == NULL) return false;
      *new_count = 1;

      // Insere na struct
      kv[i].key = value;
      kv[i].value = (void*)new_count;
      return true;
    }
  }

  return false;
}
