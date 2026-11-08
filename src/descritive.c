#include "types.h"
#include "descritive.h"
#include "utils.h"

#include <math.h>
#include <errno.h>

/**
 * @brief Somatório dos valores
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_sum(const lstat_dataset_t* dataset) {
  if (dataset == NULL) {
    errno = ENULLDATASET;
    return NAN;
  }

  double sum = 0.0;
  for (size_t i = 0; i < dataset->size; i++) {
    sum += dataset->data[i];
  }
  return sum;
}

/**
 * @brief Quantidade de observações
 * @param const lstat_dataset_t* dataset
 * @return size_t
 */
size_t stat_count(const lstat_dataset_t* dataset) {
  if (dataset == NULL) {
    errno = ENULLDATASET;
    return NAN;
  }

  return dataset->size;
}

/**
 * @brief Menor valor
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_min(const lstat_dataset_t* dataset) {
  if (dataset == NULL) {
    errno = ENULLDATASET;
    return NAN;
  }

  if (dataset->size == 0) {
    errno = EEMPTYDATASET;
    return NAN;
  }

  double min = dataset->data[0];
  for (size_t i = 1; i < dataset->size; i++) {
    min = fmin(min, dataset->data[i]);
  }
  return min;
} 

/**
 * @brief Maior valor
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_max(const lstat_dataset_t* dataset) {
  if (dataset == NULL) {
    errno = ENULLDATASET;
    return NAN;
  }

  if (dataset->size == 0) {
    errno = EEMPTYDATASET;
    return NAN;
  }

  double max = dataset->data[0];
  for (size_t i = 1; i < dataset->size; i++) {
    max = fmax(max, dataset->data[i]);
  }
  return max;
}

/**
 * @brief Amplitude (maximo - minimo)
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_range(const lstat_dataset_t* dataset) {
  double max = stat_max(dataset);
  double min = stat_min(dataset);

  if (isnan(max) || isnan(min)) {
    return NAN;
  }

  return max - min;
} 

/**
 * @brief Media aritimetica
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_mean(const lstat_dataset_t* dataset) {
  double sum = stat_sum(dataset);
  double count = stat_count(dataset);
  if (isnan(sum) || isnan(count)) {
    return NAN;
  }
  return sum / count;
} 

/**
 * @brief Mediana
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_median(const lstat_dataset_t* dataset) {
  if (dataset == NULL) {
    errno = ENULLDATASET;
    return NAN;
  }

  if (dataset->size == 0) {
    return NAN;
  }

  double* sorted = (double*)calloc(dataset->size, sizeof(double));
  if (sorted == NULL) {
    errno = EALLOCATION;
    return NAN;
  }

  if (!lstat_dataset_qsort(dataset, sorted)) {
    return NAN;
  }

  double median;

  if (dataset->size % 2 == 0) {
    // par (even)
    size_t n = dataset->size / 2 - 1;
    size_t m = n + 1;
    median = (dataset->data[n] + dataset->data[m]) / 2;
  } else {
    // impar (odd)
    size_t n = ceil((double)dataset->size / 2);
    median = dataset->data[n];
  }

  free(sorted);
  sorted = NULL;

  return median;
}

/**
 * @brief Moda
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_mode(const lstat_dataset_t* dataset) {
  if (dataset == NULL) {
    errno = ENULLDATASET;
    return NAN;
  }

  if (dataset->size == 0) {
    return NAN;
  }

  // [1, 3, 1, 1, 2, 4, 2]
  // montar array de lstat_kv_t com key = numero e value = frequencia
  lstat_kv_t* freqs = (lstat_kv_t*)calloc(dataset->size, sizeof(lstat_kv_t));
  if (freqs == NULL) {
    errno = EALLOCATION;
    return NAN;
  }

  // constroi dict de frequencias
  bool success = true;
  for (size_t i = 0; i < dataset->size; i++) {
    success = success && lstat_frequency_upsert(freqs, dataset->size, (void*)&dataset->data[i]);
  }

  if (!success) {
    for (size_t i = 0; i < dataset->size; i++) {
      if (freqs[i].value != NULL) {
        free(freqs[i].value);
      }
    }
    free(freqs);
    freqs = NULL;
    return NAN;
  }

  lstat_kv_t max = lstat_max_frequency(freqs, dataset->size);
  double mode = *(double*)max.key;

  for (size_t i = 0; i < dataset->size; i++) {
    if (freqs[i].value != NULL) {
      free(freqs[i].value);
    }
  }
  free(freqs);

  return mode;
}

/**
 * @brief Média geométrica
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_geometric_mean(const lstat_dataset_t* dataset) {
  if (dataset == NULL) {
    errno = ENULLDATASET;
    return NAN;
  }

  if (dataset->size == 0) {
    return NAN;
  } 
  
  double prod = 1;
  for (size_t i = 0; i < dataset->size; i++) {
    prod *= dataset->data[i];
  }

  double geomean = pow(prod, 1.0 / dataset->size);

  return geomean;
}

/**
 * @brief Média harmônica
 * @param const lstat_dataset_t* dataset
 * @return double
 */
double stat_harmonic_mean(const lstat_dataset_t* dataset) {
  if (dataset == NULL) {
    errno = ENULLDATASET;
    return NAN;
  }

  if (dataset->size == 0) {
    return NAN;
  }

  double suminv = 0;
  for (size_t i = 0; i < dataset->size; i++) {
    if (dataset->data[i] == 0) {
      return 0.0;
    }
    suminv += 1.0 / dataset->data[i];
  }

  double harmean = dataset->size / suminv;
  return harmean;
}
