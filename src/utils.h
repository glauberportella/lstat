#ifndef _UTILS_H_
#define _UTILS_H_

#include "types.h"
#include <stdbool.h>

void print_dataset(const lstat_dataset_t* dataset, const char* label);

/**
 * @brief Quick sort for dataset data
 * @param const lstat_dataset_t* dataset
 * @param double* sorted The output sorted buffer
 * @return void
 */
bool lstat_dataset_qsort(const lstat_dataset_t* dataset, double* sorted);

/**
 * @brief Compara dois valores (no caso da lstat dois double)
 * @param const void* a
 * @param const void* b
 * @return int -1 se a < b, 1 se a > b, 0 se a == b
 */
int lstat_compare(const void* a, const void* b);

lstat_freq_t* lstat_freq_create(const lstat_dataset_t* dataset, size_t* freq_size);

void lstat_freq_destroy(lstat_freq_t* freq);

#endif
